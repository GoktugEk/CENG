import sys
sys.path.append('..')
from Distance import Distance 
import pickle
from Knn import KNN
from sklearn.model_selection import StratifiedKFold
import numpy as np


# Make predictions 
def ModelPredict(model : KNN, x_test : np.array) -> np.array:
    pred = []
    for sample in x_test:
        res = model.predict(sample)
        # CALCULATE THE ACCURACY
        pred.append(res)
    
    pred = np.array(pred)
    
    return pred



# Create model configurations
def CreateModels(x : np.array,y : np.array) -> list[KNN]:
    # FIRST CALCULATE THIS PARAMETER 
    S_minus_1 = np.linalg.inv(np.cov(x.T))
    
    return [
        KNN(x,y,Distance.calculateCosineDistance,None,5),
        KNN(x,y,Distance.calculateCosineDistance,None,10),
        KNN(x,y,Distance.calculateCosineDistance,None,30),
        KNN(x,y,Distance.calculateMinkowskiDistance,2,5),
        KNN(x,y,Distance.calculateMinkowskiDistance,2,10),
        KNN(x,y,Distance.calculateMinkowskiDistance,2,30),
        KNN(x,y,Distance.calculateMinkowskiDistance,4,5),
        KNN(x,y,Distance.calculateMinkowskiDistance,4,10),
        KNN(x,y,Distance.calculateMinkowskiDistance,4,30),
        KNN(x,y,Distance.calculateMinkowskiDistance,6,5),
        KNN(x,y,Distance.calculateMinkowskiDistance,6,10),
        KNN(x,y,Distance.calculateMinkowskiDistance,6,30),
        KNN(x,y,Distance.calculateMahalanobisDistance,S_minus_1,5),
        KNN(x,y,Distance.calculateMahalanobisDistance,S_minus_1,10),
        KNN(x,y,Distance.calculateMahalanobisDistance,S_minus_1,30)
    ]


print("There are 15 different configurations")
print("Calculating...")

    


dataset, labels = pickle.load(open("../data/part1_dataset.data", "rb"))

fold = 10



# STORE THE MEANS OF THE CROSS VALIDATIONS
means = [[] for x in range(15)]

for i in range(5):
    folder = StratifiedKFold(fold, shuffle=True)
    
    # STORE THE FOLDS' ACCURACIES
    cross_val_results = [[] for x in range(15)]
    for i, j in folder.split(dataset, labels):
        # GETTING THE DATASETS
        x_train, x_test = dataset[i], dataset[j]
        y_train, y_test = labels[i], labels[j]
        
        
        # CREATE CONFIGURATIONS
        models = CreateModels(x_train, y_train)

        
        for idx, model in enumerate(models):
            pred = ModelPredict(model, x_test)
            res = np.mean(np.array(pred == y_test,dtype=float))*100
            
            cross_val_results[idx].append(res)


    for idx,i in enumerate(cross_val_results):
        means[idx].append(np.mean(i))

# CONFIDANCE INTERVAL CALCULATION FOR EACH MEAN
intervals = []
for conf in means:
    nu = np.mean(conf)
    sigma = np.std(conf)
    confidance_interval = [round((nu - 1.96 * sigma / 5**0.5).item(),4) ,round((nu + 1.96 * sigma / 5**0.5).item(),4)]
    intervals.append(confidance_interval)


# TURN THEM TO PRINTABLE FORMAT
printable = ["Confidence interval is [{} - {}]".format(x[0],x[1]) for x in intervals]

# PRINT THE RESULTS
for i,m in zip(printable,models):
    print(m,"  -->  " ,i)
    
    


        
        
        
    


