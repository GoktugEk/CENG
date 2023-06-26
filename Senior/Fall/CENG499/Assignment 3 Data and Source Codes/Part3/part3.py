import numpy as np
from DataLoader import DataLoader
from sklearn.svm import SVC
from sklearn.neighbors import KNeighborsClassifier
from sklearn.tree import DecisionTreeClassifier
from sklearn.ensemble import RandomForestClassifier
from sklearn.model_selection import cross_val_score, GridSearchCV,RepeatedStratifiedKFold, cross_validate
from sklearn.preprocessing import MinMaxScaler
import numpy as np
from sklearn.pipeline import make_pipeline
from joblib import parallel_backend # For concurrent processing
import json # for pretty printing

data_path = "../data/credit.data"

dataset, labels = DataLoader.load_credit_with_onehot(data_path)

# Load the dataset
X = dataset
y = labels



# Define the models to be compared
models = [SVC(), KNeighborsClassifier(), DecisionTreeClassifier(), RandomForestClassifier()]
model_names = ["SVM", "KNN", "Decision Tree", "Random Forest"]


# Define the grid search configurations for each model
svm_grid_1 = {'svc__C': [0.1, 1, 10], 'svc__kernel': ['rbf','linear', 'poly']}
knn_grid_1 = {'kneighborsclassifier__n_neighbors': [2,3,4,5,6], 'kneighborsclassifier__metric': ['euclidean', "manhattan","cosine"]}
dt_grid_1 = {'decisiontreeclassifier__max_depth': [3,6,9], 'decisiontreeclassifier__criterion': ['gini', 'entropy']}
rf_grid_1 = {'randomforestclassifier__n_estimators': [10, 20, 30], 'randomforestclassifier__max_depth': [3, 6, 9]}

grid_configs = [svm_grid_1, knn_grid_1, dt_grid_1, rf_grid_1]


outer_cv = RepeatedStratifiedKFold(n_splits=3,n_repeats=5, random_state=np.random.randint(1, 1000))
inner_cv = RepeatedStratifiedKFold(n_splits=5,n_repeats=5, random_state=np.random.randint(1, 1000))

scores =  {"SVM" : {}, "KNN" : {}, "Decision Tree" : {}, "Random Forest" : {}}
with parallel_backend('threading', n_jobs=3):
    for i,model in enumerate(models):
        # for random forest more repeat
        if i == 3:
            outer_cv = RepeatedStratifiedKFold(n_splits=3,n_repeats=25, random_state=np.random.randint(1, 1000)) # for training random forest 5 times more
        pipeline = make_pipeline(MinMaxScaler(),model)
        
        grid = GridSearchCV(pipeline, grid_configs[i], scoring="accuracy", cv= inner_cv, verbose=True,n_jobs=8)
        
        val = cross_validate(grid, dataset, labels, scoring=["accuracy","f1"], cv=outer_cv, verbose=True,return_estimator=True)
        params = val["estimator"][0].best_params_
        val = list(zip(val["test_accuracy"],val["test_f1"]))
        m = np.mean(val,axis=0)
        s = np.std(val,axis=0)
        l = len(val)
        
        def confidence(mean, std, l):
            return (mean - 1.96 * std / np.sqrt(l), mean + 1.96 * std / np.sqrt(l))
        
        acc = confidence(m[0],s[0],l)
        f1 = confidence(m[1],s[1],l)

        scores[model_names[i]]["Params"] = params
        scores[model_names[i]]["Accuracy"] = acc
        scores[model_names[i]]["F1"] = f1

        
    pretty = json.dumps(scores,indent=4)
    print(pretty)

    
    

