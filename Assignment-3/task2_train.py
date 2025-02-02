# -*- coding: utf-8 -*-
"""task2_train.ipynb

Automatically generated by Colaboratory.

Original file is located at
    https://colab.research.google.com/drive/1nmA3WumHvvLAvgtMUf161H2R5g_sKOye
"""
import sys
import os
"""## Hyperparameters"""

isEdgeLength=False
early_stopping=False
toDecay=False
nIter=3
onColab=False

import torch
"""
  Uncomment if run on colab
"""
if onColab:
    from IPython.display import clear_output
    pt_version = torch.__version__
    print(pt_version)

    # # Run it for once before
    # !pip install torch-geometric-temporal
    # clear_output()

import pandas as pd
import numpy as np
from tqdm import tqdm
import matplotlib.pyplot as plt
import copy

import torch.nn.functional as F
from torch_geometric.data import Dataset, Data
from torch_geometric.utils import dense_to_sparse
from torch_geometric_temporal.nn.recurrent import A3TGCN
from torch_geometric_temporal.signal import StaticGraphTemporalSignal
from torch_geometric_temporal.signal import temporal_signal_split


"""### Hyperparameters"""
p=int(sys.argv[1])
f=int(sys.argv[2])
traffic_data_filename=sys.argv[3]
adjacency_matrix_filename=sys.argv[4]
graph_split_filename=sys.argv[5]
model_filename="mcs212138_task2.model"
adjacency_filename="./datasets/"+model_filename.split(".")[0]+"_adj.csv"


"""## Loading the dataset"""
print("Loading the dataset....")
traffic_data=pd.read_csv(traffic_data_filename,index_col=0)

traffic_data.head()

nodes=[str(i) for i in traffic_data]

print("No. of nodes: ",len(nodes))
print("No. of time steps: ",len(traffic_data[nodes[0]]))

X=[]
Y=[]
for i in range(traffic_data.shape[0]):
  if i+p+f>traffic_data.shape[0]:
    continue
  X.append(traffic_data.iloc[i:i+p,:])
  Y.append(traffic_data.iloc[i+p:i+p+f,:])
X=np.asarray(X)
Y=np.asarray(Y)

print(X.shape)
print(Y.shape)

"""### Loading the train, test and validation nodes."""
print("Loading the train,test and validation nodes....")
def get_train_test_validation_nodes(filename):
  data=np.load(filename)
  train_nodes=data["train_node_ids"].astype("str")
  test_nodes=data["test_node_ids"].astype("str")
  validation_nodes=data["val_node_ids"].astype("str")
  return train_nodes,test_nodes,validation_nodes

train_nodes,test_nodes,validation_nodes=get_train_test_validation_nodes(graph_split_filename)

train_nodes_mask=torch.zeros(len(nodes),dtype=torch.bool)
test_nodes_mask=torch.zeros(len(nodes),dtype=torch.bool)
validation_nodes_mask=torch.zeros(len(nodes),dtype=torch.bool)

node_mapping={}
inverse_node_mapping={}
for t in enumerate(nodes):
  node_mapping[str(t[1])]=t[0]
  inverse_node_mapping[t[0]]=str(t[1])

for node in train_nodes:
  if node in nodes:
    train_nodes_mask[node_mapping[node]]=True
  else:
    print(f"Node {node} not present as the column of nodes")

for node in test_nodes:
  if node in nodes:
    test_nodes_mask[node_mapping[node]]=True
  else:
    print(f"Node {node} not present as the column of nodes")

for node in validation_nodes:
  if node in nodes:
    validation_nodes_mask[node_mapping[node]]=True
  else:
    print(f"Node {node} not present as the column of nodes")

"""### Loading the graph dense adjacency matrix and making it sparse"""
print("Loading the adjacency matrix....")
data_adj=pd.read_csv(adjacency_matrix_filename,index_col=0)
data_adj.fillna(0,inplace=True)

print(data_adj.head())

edge_index,edge_weight=dense_to_sparse(torch.from_numpy(data_adj.values))
"""
  Uncomment according to the dataset
"""
if not isEdgeLength:
  edge_weight=1/edge_weight

"""### Model Class"""

from torch_geometric.nn import SAGEConv, GATv2Conv
class Model(torch.nn.Module):
  def __init__(self,node_features,periods,output_periods):
    super().__init__()
    self.layer1 = A3TGCN(in_channels=node_features, out_channels=32, periods=periods)
    self.linear=torch.nn.Linear(32,output_periods)
  
  def forward(self,d):
    X,edge_index,edge_weight=d.x,d.edge_index,d.edge_weight
    output1=F.relu(self.layer1(X,edge_index))
    output=self.linear(output1)
    return output

"""### Creating batches of data"""
print("Creating batch of data....")
final_data=[]
for i in range(X.shape[0]):
  x=X[i].reshape(p,1,-1)
  x=x.transpose((2,1,0))
  # print(X[i].shape,x.shape)
  y=Y[i].transpose((1,0))
  # y=y.transpose((2,1,0))
  # print(Y[i].shape,y.shape)
  x=torch.tensor(x,dtype=torch.double)
  y=torch.tensor(y,dtype=torch.double)
  # print(x.shape,y.shape)
  d=Data(x=x,y=y,edge_index=edge_index)
  d.train_nodes_mask=train_nodes_mask
  d.test_nodes_mask=test_nodes_mask
  d.validation_nodes_mask=validation_nodes_mask
  d.edge_weight=edge_weight
  final_data.append(d)

from torch_geometric.loader import DataLoader
dataloader=DataLoader(final_data,batch_size=32,shuffle=False)

def calculate_loss(Y_pred,Y,node_mask):
  error=0
  for i in range(Y_pred.shape[1]):
    error+=torch.mean(torch.abs(Y_pred[node_mask][i]-Y[node_mask][i])).item()
  return error/Y_pred.shape[1]

"""### Model Instance"""

model=Model(node_features=1,periods=p,output_periods=f).double()

print("Calculating initial MAE of the model....")
# model.eval()
# error=0
# n=len(dataloader.dataset)
# for data in tqdm(dataloader.dataset):
#   Y_pred=model(data)
#   error+=calculate_loss(Y_pred,data.y,validation_nodes_mask)
# print("Initial Validation Error is: ",error/n)

"""### Training the model"""
print("Training the model....")
last_error=1000000000000.0

decay=1.0
for iter in tqdm(range(nIter)):
  model.train()
  index=0
  for data in tqdm(dataloader):
    Y_pred=model(data)
    error=F.mse_loss(Y_pred[data.train_nodes_mask],data.y[data.train_nodes_mask])
    if i%100==0:
      print("The current MSE is: ", error.item())
    optimizer=torch.optim.Adam(model.parameters(), lr=0.001*decay)
    optimizer.zero_grad()
    error.backward()
    optimizer.step()
    index+=1
  model.eval()
  # if iter!=nIter-1:
  #   error=0
  #   n=len(dataloader.dataset)
  #   for data in tqdm(dataloader.dataset):
  #     Y_pred=model(data)
  #     error+=calculate_loss(Y_pred,data.y,validation_nodes_mask)
  #   print(f"The error after {iter+1} iterations is: ",error/n)
  """
    Early stopping the training
  """
  if early_stopping:
    if abs(last_error-error/n)>=0.05:
      last_error=error/n
    else:
      break
  if toDecay and iter%5==0:
    decay=decay/100.0

# error=0
# n=len(dataloader.dataset)
# model.eval()
# for data in dataloader.dataset:
#   Y_pred=model(data)
#   error+=calculate_loss(Y_pred,data.y,test_nodes_mask)
# print("The testing accuracy is: ",error/n)

"""### Saving the model"""
print("Saving the model....")
torch.save(model,model_filename)

cmd=f"cp {adjacency_matrix_filename} {adjacency_filename}"
os.system(cmd)



