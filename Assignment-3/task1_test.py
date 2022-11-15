import torch
import pandas as pd
import numpy as np
import os
import sys
from torch_geometric.data import Dataset, Data
from torch_geometric.utils import dense_to_sparse

# 
from torch_geometric.nn import SAGEConv, GATv2Conv
import torch.nn.functional as F
class Model(torch.nn.Module):
  def __init__(self):
    super().__init__()
    # Test:0
    self.layer1=SAGEConv(1,32,'mean')
    self.layer2=SAGEConv(32,16,'mean')
    
    ## Test:1
    # self.layer1=GATv2Conv(1, 32, edge_dim=1)
    # self.layer2=GATv2Conv(32, 16, edge_dim=1)
    
    ## Test:2
    # self.layer1=GATConv(1,32,edge_dim=1)
     # self.layer2=GATConv(32,16,edge_dim=1)

    self.linear=torch.nn.Linear(16,1)
  
  def forward(self,d):
    X,edge_index,edge_weight=d.x,d.edge_index,d.edge_weight

    output1=F.relu(self.layer1(X,edge_index))
    output2=F.relu(self.layer2(output1,edge_index))

    output=self.linear(output2)

    return output
# 
mode=Model().double()

"""### Hyperparameters"""

traffic_data_filename=sys.argv[1]
output_filename=sys.argv[2]
model_filename=sys.argv[3]
model=torch.load(model_filename)
adjacency_matrix_filename="./datasets/"+model_filename.split(".")[0]+"_adj.csv"
debug_flag=True
num_nodes=207 

"""### Loading the test file"""
print("Loading the test data....")
data=pd.read_csv(traffic_data_filename,index_col=0)
X=np.empty((data.shape[0],data.shape[1]))
for i in range(data.shape[0]):
    X[i:i+1,:]=data.iloc[i,:]


"""### Loading the adjacency matrix"""
print("Loading adjacency matrix....")
data_adj=pd.read_csv(adjacency_matrix_filename,index_col=0)
data_adj.fillna(0,inplace=True)

edge_index,edge_weight=dense_to_sparse(torch.from_numpy(data_adj.values))

"""### Creating data object for testing"""
print("Creating data for testing....")
final_data=[]
for i in range(X.shape[0]):
    d=Data(x=torch.tensor(X[i],dtype=torch.double).reshape(-1,1),edge_index=edge_index)
    d.edge_weight=edge_weight
    final_data.append(d)

"""### Prediction the output"""
print("Shhhhh!!! Predicting going on....")
Y_pred=np.zeros((X.shape[0],X.shape[1]))
with torch.no_grad():
    model.eval()
    for i,d in enumerate(final_data):
        Y_pred[i:i+1,:]=model(d).reshape(1,-1)

print("Test data dimensions are: ",X.shape)
print("Prediction dimensions are:",Y_pred.shape)
if debug_flag:
  error=0
  n=X.shape[0]
  for i in range(1,X.shape[0]):
    error+=np.mean(np.abs(Y_pred[i-1]-X[i]))
  print("MAE is: ", error/(n-1))


"""### Saving the prediction to a csv file"""
print("Writing the predictions to file....")
df=pd.DataFrame(Y_pred)
df.to_csv(output_filename,header=False,index=False)


print("Done and dusted")