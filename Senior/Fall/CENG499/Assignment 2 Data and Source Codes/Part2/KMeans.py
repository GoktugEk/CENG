import sys
sys.path.append('..')
from Distance import Distance 
import pandas as pd #ONLY FOR VISUALIZATION AND THE SAKE OF SIMPLICITY
import random
import numpy as np


class KMeans:
    def __init__(self, dataset, K=2):
        """
        :param dataset: 2D numpy array, the whole dataset to be clustered
        :param K: integer, the number of clusters to form
        """
        self.K = K
        self.dataset = dataset
        # each cluster is represented with an integer index
        # self.clusters stores the data points of each cluster in a dictionary
        self.clusters = {i: [] for i in range(K)}
        # self.cluster_centers stores the cluster mean vectors for each cluster in a dictionary
        self.cluster_centers = {i: None for i in range(K)}
        # you are free to add further variables and functions to the class
        
        df = pd.DataFrame(self.dataset)
        
        #INITIALIZATION
        maxes = df.max()
        mins  = df.min()
        # I AM CREATING CENTERS RANDOMLY BETWEEN THE MINIMUM AND MAXIMUM DIMENSION POINTS ON THE DATASET
        for c in range(self.K):
            center = []
            for i in range(len(maxes)):
                center.append(random.uniform(mins[i],maxes[i]))
            center = np.array(center)
            self.cluster_centers[c] = center

    def calculateLoss(self):
        """Loss function implementation of Equation 1"""
        sum = 0
        
        for cluster, members in self.clusters.items():
            if members == []:
                continue
            center = self.cluster_centers[cluster]
            members = np.array(members)
            #CHECK THE CLUSTERS LOSS WITH ITS MEMBERS
            sum += np.sum(np.apply_along_axis(np.linalg.norm,1,members - center)**2) 
        
        return sum
    
    def move(self,cluster):
        #MOVE THE CLUSTERS
        self.cluster_centers[cluster] = np.apply_along_axis(np.mean,0,self.clusters[cluster])
    
    
    def find_belonging(self,instance):
        #FIND THE CLUSTER OF THE GIVEN INSTANCE
        centers = np.array(list(self.cluster_centers.values()))

        dist = np.apply_along_axis(np.linalg.norm, 1, centers - instance)
        
        idx = np.argmin(dist)
        

        return (dist[idx],idx)
                

    def run(self):
        """Kmeans algorithm implementation"""
        
    
        
        for sample in self.dataset:
            
            #FIND WHICH CLUSTER IS CLOSEST
            minDist = self.find_belonging(sample)
            #ADD AS A MEMBER
            self.clusters[minDist[1]].append(sample)
            #MOVE THE MEANS
            self.move(minDist[1])
            
        
        return self.cluster_centers, self.clusters, self.calculateLoss()
