import numpy as np
import time 

# In the decision tree, non-leaf nodes are going to be represented via TreeNode
class TreeNode:
    def __init__(self, attribute):
        self.attribute = attribute
        # dictionary, k: subtree, key (k) an attribute value, value is either TreeNode or TreeLeafNode
        self.subtrees = {}

# In the decision tree, leaf nodes are going to be represented via TreeLeafNode
class TreeLeafNode:
    def __init__(self, data, label):
        self.data = data
        self.labels = label

class DecisionTree:
    def __init__(self, dataset: list, labels, features, criterion="information gain"):
        """
        :param dataset: array of data instances, each data instance is represented via an Python array
        :param labels: array of the labels of the data instances
        :param features: the array that stores the name of each feature dimension
        :param criterion: depending on which criterion ("information gain" or "gain ratio") the splits are to be performed
        """
        self.dataset = np.array(dataset)
        self.labels = np.array(labels)
        self.features = features
        self.criterion = criterion
        self.featuresidx : dict  = {k: v for v, k in enumerate(features)}
        self.withlabels = np.hstack((self.dataset,self.labels.reshape(-1,1)))
        # it keeps the root node of the decision tree
        self.root = None

        # further variables and functions can be added...


    def calculate_entropy__(self, dataset, labels) -> float:
        """
        :param dataset: array of the data instances
        :param labels: array of the labels of the data instances
        :return: calculated entropy value for the given dataset
        """
        entropy_value = 0.0

        unique, counts  = np.unique(labels,return_counts=True)
        
        

        for i in counts:
            p = i/sum(counts)
            entropy_value += -p * np.log2(p)


        return entropy_value

    def calculate_average_entropy__(self, dataset, labels, attribute) -> float:
        """
        :param dataset: array of the data instances on which an average entropy value is calculated
        :param labels: array of the labels of those data instances
        :param attribute: for which attribute an average entropy value is going to be calculated...
        :return: the calculated average entropy value for the given attribute
        """
        average_entropy = 0.0
        
        idx : int = self.featuresidx[attribute]
        
        col : np.ndarray = dataset[:,idx]
        
        uniques, counts = np.unique(col,return_counts=True) 

        for i in uniques:
            pruned = self.withlabels[self.withlabels[:,idx] == i]
            average_entropy += self.calculate_entropy__(dataset,pruned[:,-1]) / len(uniques)    
        
        return average_entropy

    def calculate_information_gain__(self, dataset, labels, attribute) -> float:
        """
        Calculates the information gain score for a given attribute in a dataset.
        The information gain score is a measure of how much the attribute reduces the 
        entropy of the labels in the dataset.
        
        :param dataset: array of the data instances on which an information gain score is going to be calculated
        :param labels: array of the labels of those data instances
        :param attribute: for which attribute the information gain score is going to be calculated
        :return: the calculated information gain score
        """
        # Initialize information_gain to 0.0
        information_gain = 0.0
        
        # Calculate the entropy of the labels in the dataset
        entropy_s : float = self.calculate_entropy__(dataset,labels)
        
        # Initialize entropy_values to 0.0
        entropy_values : float = 0.0
        
        # Get the index of the attribute in the dataset
        idx : int = self.featuresidx[attribute]
        
        # Get the values of the attribute in the dataset as a numpy array
        col : np.ndarray = np.array(dataset)[:,idx]
        
        # Get the unique values and counts for the attribute in the dataset
        uniques, counts = np.unique(col,return_counts=True) 

        # Stack the dataset and labels together as a single array
        dataset = np.hstack((dataset,labels.reshape(-1,1)))
        
        # Iterate through the unique values and counts of the attribute
        for i,c in zip(uniques,counts):
            # Prune the dataset to include only the rows where the attribute has the current unique value
            pruned = dataset[dataset[:,idx] == i]
            # Calculate the entropy of the pruned dataset
            e = self.calculate_entropy__(dataset,pruned[:,-1])
            # Add the contribution of this unique value to the entropy_values
            entropy_values += e * (c/sum(counts))
            
        # Calculate the information gain as the difference between the entropy of the labels and the entropy of the attribute
        information_gain = entropy_s - entropy_values
        
        # Return the calculated information gain score
        return information_gain

    

    def calculate_intrinsic_information__(self, dataset, labels, attribute):
        """
        Calculates the intrinsic information score for a given attribute in a dataset.
        The intrinsic information score is a measure of the amount of information 
        (in bits) that an attribute provides about the labels in the dataset.
        
        :param dataset: array of data instances on which an intrinsic information score is going to be calculated
        :param labels: array of the labels of those data instances
        :param attribute: for which attribute the intrinsic information score is going to be calculated
        :return: the calculated intrinsic information score
        """
        # Initialize intrinsic_info to 0
        intrinsic_info = 0
        
        # Get the index of the attribute in the dataset
        idx : int = self.featuresidx[attribute]
        
        # Get the unique values and counts for the attribute in the dataset
        uniques, counts = np.unique(np.array(dataset)[:,idx],return_counts=True)

        # Iterate through the counts of each unique value
        for count in counts:
            # Calculate the probability of each unique value occurring in the dataset
            p = count / len(dataset)
            # Add the contribution of this unique value to the intrinsic information score
            intrinsic_info -= p * np.log2(p)
            
        # Return the calculated intrinsic information score
        return intrinsic_info


    
    def calculate_gain_ratio__(self, dataset, labels, attribute):
        """
        :param dataset: array of data instances with which a gain ratio is going to be calculated
        :param labels: array of labels of those instances
        :param attribute: for which attribute the gain ratio score is going to be calculated...
        :return: the calculated gain ratio score
        """
        intrinsic_info = self.calculate_intrinsic_information__(dataset, labels, attribute)
        
        gain = self.calculate_information_gain__(dataset,labels,attribute)
        
        
        gain_ratio = gain / intrinsic_info
        
        return gain_ratio

    def ID3__(self, dataset, labels, used_attributes):
        """
        Recursive function for ID3 algorithm
        :param dataset: data instances falling under the current  tree node
        :param labels: labels of those instances
        :param used_attributes: while recursively constructing the tree, already used labels should be stored in used_attributes
        :return: it returns a created non-leaf node or a created leaf node
        """
        # Calculate the frequency of each label in the dataset
        print(used_attributes)
        uniques, counts = np.unique(labels,return_counts=True) 
        label_counts = dict(zip(uniques,counts))
        
        # If all instances in the dataset have the same label, return a leaf node with that label
        if len(label_counts) == 1:
            return TreeLeafNode("",uniques[0])
        
        # If there are no more attributes to use, return a leaf node with the most common label
        if len(used_attributes) == len(labels):
            return TreeLeafNode("",max(label_counts, key = label_counts.get))

        if self.criterion == "gain ratio":
            # Choose the attribute with the highest gain ratio
            best_attribute = [(self.calculate_gain_ratio__(dataset,labels,x),x) for x in self.features]
        elif self.criterion == "information gain":
            # Choose the attribute with the highest information gain
            best_attribute = [(self.calculate_information_gain__(dataset,labels,x),x) for x in self.features]
        else:
            print("Wrong criterion, exiting...")
            exit()
            
       
        best_attribute = max(best_attribute,key=lambda x : x[0])[1]

        # Create a new decision tree node with the best attribute
        tree = TreeNode(best_attribute)

        idx = self.featuresidx[best_attribute]
        
        # Add a new branch for each possible value of the best attribute
        values = dataset[:,idx]
        values = np.unique(values)
        
        
        for value in values:
            subdataset = []
            sublabels = []
            for i in range(len(dataset)):
                if dataset[i][idx] == value:
                    subdataset.append(dataset[i])
                    sublabels.append(labels[i])

            tree.subtrees[value] = self.ID3__(np.array(subdataset), np.array(sublabels), used_attributes + [best_attribute])
        
        return tree

    def predict(self, x):
        """
        :param x: a data instance, 1 dimensional Python array 
        :return: predicted label of x
        
        If a leaf node contains multiple labels in it, the majority label should be returned as the predicted label
        """
        predicted_label = None
        
        node = self.root
        
        while(type(node) == TreeNode):
            idx : int = self.featuresidx[node.attribute]
            
            node = node.subtrees[x[idx]]
        
        
        predicted_label = node.labels    

        return predicted_label

    def train(self):
        self.root = self.ID3__(self.dataset, self.labels, [])
        print("Training completed")