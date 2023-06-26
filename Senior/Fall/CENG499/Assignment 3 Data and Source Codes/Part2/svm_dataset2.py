import pickle
import numpy as np
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split, GridSearchCV, cross_val_score
from sklearn.svm import SVC
from sklearn.model_selection import GridSearchCV
import json


dataset, labels = pickle.load(open("../data/part2_dataset2.data", "rb"))

def confidance_interval_calculator(res : dict) -> list:
    scores = []
    for i in range(10):
        scores.append(res[f"split{i}_test_score"])
        
    scores = np.array(scores)
    
    
        
        

# Split the data into features and target
X = dataset
y = labels

# List to store the mean test scores of the configurations
means = []

# Configurations
configurations = None

for _ in range(5):
    print(f"Iteration {_+1}")
    
    # Split the data into training and test sets
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, shuffle=True, random_state=np.random.randint(0,1000))


    # Standardize the features
    scaler = StandardScaler()
    X_train = scaler.fit_transform(X_train)
    X_test = scaler.transform(X_test)

    # Define the parameters for the grid search
    param_grid = {'C': [0.1, 1, 10, 100], 'kernel': ['linear','sigmoid', 'rbf', 'poly']}

    # Create the SVM model
    model = SVC()

    # Create the grid search object with 5-fold cross-validation
    grid = GridSearchCV(model, param_grid, cv=10, return_train_score=True,verbose=1)

    # Fit the grid search object to the training data
    grid.fit(X_train, y_train)
    
    # Save the configurations
    configurations = grid.cv_results_["params"]

    # Get the best parameters from the grid search
    best_params = grid.best_params_

    # Use the best parameters to create a new SVM model
    best_model = SVC(C=best_params['C'], kernel=best_params['kernel'])

    # Fit the best model to the training data
    best_model.fit(X_train, y_train)

    # Print the best model
    print(f"Best Model's Configurations : {best_params}")
    
    # Calculate the accuracy of the best model on the test data
    accuracy = best_model.score(X_test, y_test)
    print(f'Test accuracy: {accuracy:.2f}\n')
    
    # Save the mean test scores of the models
    means.append(grid.cv_results_["mean_test_score"])


# Take the transpose of the matrix to achieve the means configuration by configuration.
means = np.array(means)
means = means.transpose()

for i,mean in enumerate(means): # Configuration times
    
    # Find the mean of means and the std of means
    mean_2, std = np.mean(mean), np.std(mean)
    
    # Calculate the confidence interval using the mean and standard deviation
    confidence_interval = (round(mean_2 - 1.96 * (std / 5**0.5),4), round(mean_2 + 1.96 * (std / 5**0.5),4))
    
    # Add the confidence interval to the configuration dictionary
    configurations[i]["Confidence Interval"] = confidence_interval
    

    

print("Here is the configurations and their confidence intervals...")
for i in configurations:
    pretty = json.dumps(i, indent=4)
    print(pretty)
    
    
    

