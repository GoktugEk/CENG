import sys
sys.path.append('..')
import numpy as np
import random


class KMeansPlusPlus:
    def __init__(self, dataset, K=2, initial_centers = {}):
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
        self.initial_centers = {}
        
        #SET THE FIRST MEAN AS ONE OF  THE DATA POINT
        self.cluster_centers[0] = self.dataset[random.randint(0,len(self.dataset)-1)]
        
        for i in range(self.K-1):
            dists = []
            for sample in self.dataset:
                #FIND THE SAMPLE'S DISTANCE TO THE MEANS
                minDist = float("inf")
                for center in self.cluster_centers.values():
                    if center is None:
                        continue
                    minDist = min(minDist, np.linalg.norm(center-sample))
                    
                dists.append(minDist)
            # TAKE THE FURTHEST POINT
            idx = np.argmax(dists)
            self.cluster_centers[i+1] = self.dataset[idx]
            
    def calculateLoss(self):
        """Loss function implementation of Equation 1"""
        sum = 0
        
        for cluster, members in self.clusters.items():
            if members == []:
                continue
            
            center = self.cluster_centers[cluster]
            members = np.array(members)
            # CHECK THE MEMBER SAMPLES TO THE MEAN
            sum += np.sum(np.apply_along_axis(np.linalg.norm,1,members - center)**2) 
        
        return sum
    
    def move(self,cluster):
        # MOVE THE MEANS
        self.cluster_centers[cluster] = np.apply_along_axis(np.mean,0,self.clusters[cluster])
    
    
    def find_belonging(self,instance):
        # FIND THE CLUSTER OF GIVEN INSTANCE
        centers = np.array(list(self.cluster_centers.values()))

        dist = np.apply_along_axis(np.linalg.norm, 1, centers - instance)
        
        idx = np.argmin(dist)
        

        return (dist[idx],idx)

    def run(self):
        """Kmeans++ algorithm implementation"""
        for sample in self.dataset:
            
            #FIND CLUSTER THE INSTANCE SHOULD BE IN
            minDist = self.find_belonging(sample)
            #ADD IT AS A MEMBER
            self.clusters[minDist[1]].append(sample)
            #MOVE THE MEANS
            self.move(minDist[1])
            
        
        return self.cluster_centers, self.clusters, self.calculateLoss()
