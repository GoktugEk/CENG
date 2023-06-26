import numpy as np

class Distance:
    
    @staticmethod
    def calculateCosineDistance(x, y, _):
        res = np.dot(x,y)/ (np.linalg.norm(x) * np.linalg.norm(y))
        return  1 - res
    
    @staticmethod
    def calculateMinkowskiDistance(x, y, p=2):
        sum = 0

        for i in range(len(x)):
            sum += abs(x[i] - y[i])**p
            
        return sum**(1/p)
    
    @staticmethod
    def calculateMahalanobisDistance(x,y, S_minus_1):
        delta = x - y
        return np.sqrt(np.dot(np.dot(delta, S_minus_1), delta))
    
    @staticmethod
    def euclidian(x,y):
        return np.linalg.norm(x-y)


