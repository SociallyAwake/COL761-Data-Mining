import sys
import os
import numpy as np
import pandas as pd
import torch
from torch_geometric.utils import dense_to_sparse
from torch_geometric.data import Dataset, Data
import torch.nn.functional as F
from torch_geometric_temporal.nn.recurrent import A3TGCN


"""### Hyperparameters """
p=int(sys.argv[1])
f=int(sys.argv[2])
traffic_data_filename=sys.argv[3]
output_filename=sys.argv[4]
model_filename=sys.argv[5]
adjacency_matrix_filename="./datasets/"+model_filename.split(".")[0]+"_adj.csv"

class Model(torch.nn.Module):
  def __init__(self,node_features,periods):
    super().__init__()
    self.layer1 = A3TGCN(in_channels=node_features, out_channels=32, periods=periods)
    self.linear=torch.nn.Linear(32,periods)
  
  def forward(self,d):
    X,edge_index,edge_weight=d.x,d.edge_index,d.edge_weight
    output1=F.relu(self.layer1(X,edge_index))
    output=self.linear(output1)
    return output
print("-------------------------")
print("Loading the model....")
model=torch.load(model_filename).double()


# testing purposes
# data=pd.read_csv("./datasets/d1_X.csv",index_col=0)
# print(data.shape)
# print(data.head())
# Y=[]
# for i in range(17):
#     Y.append(data.iloc[i+12:i+12+f,:].values)
# Y=np.asarray(Y)
# print("This is the groundtruth shape")
# print(Y.shape)
# np.savez("./datasets/d1_X.npz",x=X)
print("Loading the test data....")
data=np.load(traffic_data_filename)['x']

X=np.empty((data.shape[0],data.shape[1],data.shape[2]))
for i in range(data.shape[0]):
    X[i,:,:]=data[i,:,:]

print("Loading the adjacency matrix....")
data_adj=pd.read_csv(adjacency_matrix_filename,index_col=0)
data_adj.fillna(0,inplace=True)
edge_index,edge_weight=dense_to_sparse(torch.from_numpy(data_adj.values))

final_data=[]
for i in range(X.shape[0]):
    x=X[i].reshape(12,1,-1)
    x=x.transpose((2,1,0))
    x=torch.tensor(x,dtype=torch.double)
    d=Data(x=x,edge_index=edge_index)
    d.edge_weight=edge_weight
    final_data.append(d)

print("Shhhh!!! Prediction going on....")
Y_pred=np.zeros((data.shape[0],f,data.shape[2]))
print(Y_pred.shape)
with torch.no_grad():
    model.eval()
    for i,d in enumerate(final_data):
        y=model(d)
        Y_pred[i:i+1,:,:]=y.reshape(y.shape[1],y.shape[0])[:f,:]


print("Writing the prediction to the file....")
np.savez("output_file.npz",y=Y_pred)
