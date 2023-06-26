import numpy as np
import sys

class KNN:
    def __init__(self, dataset, data_label, similarity_function, similarity_function_parameters=None, K=1):
        """
        :param dataset: dataset on which KNN is executed, 2D numpy array
        :param data_label: class labels for each data sample, 1D numpy array
        :param similarity_function: similarity/distance function, Python function
        :param similarity_function_parameters: auxiliary parameter or parameter array for distance metrics
        :param K: how many neighbors to consider, integer
        """
        self.K = K
        self.dataset = dataset
        self.dataset_label = data_label
        self.similarity_function = similarity_function
        self.similarity_function_parameters = similarity_function_parameters
    
    def __str__(self) -> str:
        
        if type(self.similarity_function_parameters) == np.ndarray:
            param = "S^-1"
        elif self.similarity_function_parameters == None:
            param = "None"
        else:
            param = self.similarity_function_parameters
        return f"Function : {self.similarity_function.__name__ : ^30} | Parameter: {param : ^6} | K : {self.K : ^3}"
        

    def predict(self, instance):

        dists = []
        
        
        
        for i in range(len(self.dataset)):
            dists.append((self.similarity_function(instance, self.dataset[i], self.similarity_function_parameters),self.dataset_label[i]))

        dists.sort(key = lambda x : x[0])
        _,indices = zip(*dists)
        indices = indices[:self.K+1]
        return max(set(indices), key = indices.count)


