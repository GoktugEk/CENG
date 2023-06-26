import torch
import torch.nn as nn
import numpy as np
import pickle
import matplotlib.pyplot as plt


# FIRST MODEL WITH RELUS
class Model(nn.Module):
    def __init__(self, input_size, h1, h2, class_num, activation):
    
        super(Model,self).__init__()
        
        if(h2 == None and activation == "ReLU"):   #ONE HIDDEN LAYER WITH RELU
            
            self.layer = nn.Sequential(
            nn.Linear(input_size, h1),
            nn.ReLU(),
            nn.Linear(h1,class_num)
                
            )
        elif(h2 == None and activation == "Tanh"): #ONE HIDDEN LAYER WITH TANH
            self.layer = nn.Sequential(
            nn.Linear(input_size, h1),
            nn.Tanh(),
            nn.Linear(h1,class_num)
                
            )
        elif(h2 != None and activation == "ReLU"): #TWO HIDDEN LAYERS WITH RELUS
            self.layer = nn.Sequential(
            nn.Linear(input_size, h1),
            nn.ReLU(),
            nn.Linear(h1,h2),
            nn.ReLU(),
            nn.Linear(h2,class_num)
            )
        elif(h2 != None and activation == "Tanh"): #TWO HIDDEN LAYERS WITH TANHS
            self.layer = nn.Sequential(
            nn.Linear(input_size, h1),
            nn.Tanh(),
            nn.Linear(h1,h2),
            nn.Tanh(),
            nn.Linear(h2,class_num)
            )
        
    # THIS IS THE THE FORWARD FUNCTION THAT MODEL MAKES A PREDICTION WITHOUT SOFTMAX
    def forward(self,input):    

        x = self.layer(input)

        return x



 
 

# we load all the datasets of Part 3
x_train, y_train = pickle.load(open("data/mnist_train.data", "rb"))
x_validation, y_validation = pickle.load(open("data/mnist_validation.data", "rb"))
x_test, y_test = pickle.load(open("data/mnist_test.data", "rb"))


x_train = x_train/255.0
x_train = x_train.astype(np.float32)

x_test = x_test / 255.0
x_test = x_test.astype(np.float32)

x_validation = x_validation/255.0
x_validation = x_validation.astype(np.float32)

# and converting them into Pytorch tensors in order to be able to work with Pytorch
x_train = torch.from_numpy(x_train)
y_train = torch.from_numpy(y_train).to(torch.long)

x_validation = torch.from_numpy(x_validation)
y_validation = torch.from_numpy(y_validation).to(torch.long)

x_test = torch.from_numpy(x_test)
y_test = torch.from_numpy(y_test).to(torch.long)

    
#IF THERE IS GPU, WE WANT TO USE IT
device = None
if torch.cuda.is_available():
    device = 'cuda:0'
else:
    device = 'cpu'
    

input_size = 28*28 # INPUT SIZE IS 784



losses = [] # WE STORE TRAINING LOSSES
val_losses = [] # WE STORE VALIDATION LOSSES
intervals = [] # WE STORE ALL THE CONFIDANCE INTERVALS SO THAT WE CAN PICK THE BEST CONFIGURATION


# THESE ARE THE CONFIGURATIONS THAT WE WANT TO TRY. Hidden Layer 1, Hidden Layer 2, Learning Rate, Epochs respectively. 
models = [
    [100, None, 0.5,   "ReLU"],
    [100, None, 0.25,  "ReLU"],
    [200, None, 0.5,   "ReLU"],
    [200, None, 0.25,  "ReLU"],
    [100, None, 0.5,   "Tanh"],
    [100, None, 0.25,  "Tanh"],
    [200, None, 0.5,   "Tanh"],
    [200, None, 0.25,  "Tanh"],
    [50, 50, 0.5,   "ReLU"],
    [50, 50, 0.25,  "ReLU"],
    [100, 100, 0.5,   "ReLU"],
    [100, 100, 0.25,  "ReLU"],
    [50, 50, 0.5,   "Tanh"],
    [50, 50, 0.25,  "Tanh"],
    [100, 100, 0.5,   "Tanh"],
    [100, 100, 0.25,  "Tanh"]
    ]


# PRINTING THE CONFIGURATIONS 
print(f"The Grid : Hidden Layer 1, Hidden Layer 2, Learning Rate, Activation Functions")
for idx,i in enumerate(models):
    print(f"{idx+1}:              {i[0]},              {i[1]},          {i[2]},        {i[3]},")

    

    
softmax = nn.Softmax(dim=1)
    

# FOR EACH CONFIGURATION WITH MODEL 1
for idx,(h1,h2,rate,func) in enumerate(models):
    accuracies  = []
    losses = []
    val_losses = []
    

    # TEN TIMES
    for _ in range(10):
        loss = nn.CrossEntropyLoss() # DEFINING THE LOSS FUNCTION
        model = Model(input_size, h1, h2, 10, func)
        optimizer = torch.optim.SGD(model.parameters(),lr=rate,momentum=0.85)

        
        
        #TRAINING ITERATION
        for e in range(200):
            
            optimizer.zero_grad()
            
            # MAKE THE PREDICTIONS
            pred = model(x_train)
            
            # RECEIVE THE LOSS
            loss_val = loss(pred,y_train)
            losses.append(float(loss_val))
            
            # BACK PROPOGATION
            loss_val.backward()
            
            # STEP
            optimizer.step()
            
            # DO THE SAME FOR THE VALIDATION DATASET
            val_pred = model(x_validation)
            val_loss = loss(val_pred,y_validation)
            val_losses.append(val_loss)
            
            res = torch.mean((y_train == torch.argmax(pred,1)).float())*100
            val_res = torch.mean((y_validation == torch.argmax(val_pred,1)).float())*100
            

            #print("Iteration : %d - Train Loss %.4f - Train Accuracy : %.2f - Validation Loss : %.4f Validation Accuracy : %.2f" % (e+1, float(loss_val), res.item(), float(val_loss), val_res.item()), end= "\r")
            
        
        #print()    

        
        test_pred = softmax(model(x_test))
        test_acc = torch.mean((y_test == torch.argmax(test_pred,1)).float())*100
        res = (test_pred.argmax(dim=1)).reshape(-1) == y_test
        #test_acc = sum(res) / len(res) * 100
        
        
        print(f"Grid row number : {idx+1}, Iteration : {_+1}, Test Accuracy: {test_acc:.4}",end="\r")
        accuracies.append(test_acc.item())
        
    
    #CONFIDANCE INTERVAL CALCULATION
    accuracies = torch.tensor(accuracies)
    nu = torch.mean(accuracies)
    sigma = torch.std(accuracies)
    confidance_interval = [(nu - 1.96 * sigma / 10**0.5).item() ,(nu + 1.96 * sigma / 10**0.5).item()]
    intervals.append(confidance_interval)
     
    losses = torch.mean(torch.tensor(losses)).item()
    val_losses = torch.mean(torch.tensor(val_losses)).item()
    print(f"Grid row number : {idx+1}, Confidance Interval : {confidance_interval[0]:.4} - {confidance_interval[1]:.4}, Validation Loss : {val_losses:.4}, Training Loss : {losses:.4}")
    



# MERGING VALIDATION AND TRAINING DATA
new_data_x = torch.concat((x_train,x_validation))
new_data_y = torch.concat((y_train,y_validation))

means = [torch.mean(torch.tensor(x)) for x in intervals]

# FINDING THE BEST MODEL
idx = torch.argmax(torch.tensor(means))
config = models[idx]


h1, h2, rate, activation = config


accuracies = []
# TRAIN THE BEST MODEL
for _ in range(10):
    
    # EITHER THE MODEL WILL BE MODEL 1 OR 2

    model = Model(input_size, h1, h2  ,10, activation)
    loss = nn.CrossEntropyLoss()

    optimizer = torch.optim.SGD(model.parameters(),lr=rate,momentum=0.85)
    
    for e in range(200):
        
        optimizer.zero_grad()
        
        pred = model(new_data_x)
        loss_val = loss(pred,new_data_y)
        
        loss_val.backward()
        optimizer.step()

        
    # ACCURACY CALCULATION AND PREDICTIONS WITH SOFTMAX    
    test_pred = softmax(model(x_test))
    test_acc = torch.mean((y_test == torch.argmax(test_pred,1)).float())*100


    
    accuracies.append(test_acc.item())
        
accuracies = torch.tensor(accuracies)
nu = torch.mean(accuracies)
sigma = torch.std(accuracies)
confidance_interval = [(nu - 1.96 * sigma / 10**0.5).item() ,(nu + 1.96 * sigma / 10**0.5).item()]
print(f"Confidance Interval : {confidance_interval[0]:.4} - {confidance_interval[1]:.4}") 
       

