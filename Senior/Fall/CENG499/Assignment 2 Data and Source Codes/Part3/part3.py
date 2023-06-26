import pickle
from sklearn.cluster import AgglomerativeClustering
from sklearn.metrics import  silhouette_score,silhouette_samples
import matplotlib.pyplot as plt
import numpy as np
from scipy.cluster.hierarchy import dendrogram #ONLY FOR DENDROGRAM PLOTTING
import matplotlib.cm as cm

dataset = pickle.load(open("../data/part3_dataset.data", "rb"))

# PLOTS THE SILHOUETTES OF THE GIVEN MODEL CONFIGURATION
def silhouettePlot(n_clusters, model2, name):
    
    clabels = model2.fit_predict(dataset)
    score = silhouette_score(dataset,clabels)
    cluster_scores[n_clusters].append(score)
    
    sample_scores = silhouette_samples(dataset, clabels)
    low  = 10
    fig, ax = plt.subplots(1,1)
    
    
    
    ax.set_xlim([0,1])
    ax.set_ylim([0, len(dataset) + (n_clusters + 1) * 10])
    
    for x in range(n_clusters):
        ith = sample_scores[clabels == x]
        
        ith.sort()

        size = ith.shape[0]
        up = low + size 

        color = cm.nipy_spectral(float(x) / n_clusters)
        
        ax.fill_betweenx(
            np.arange(low, up),
            0,
            ith,
            facecolor=color,
            edgecolor=color,
            alpha=0.7,
        )
    
        ax.text(-0.05, low + 0.5 * size, str(x))
        low = up + 15
        
    ax.set_title("The silhouette plot for the various clusters.")
    ax.set_xlabel("The silhouette coefficient values")
    ax.set_ylabel("Cluster label")
    ax.axvline(x=score, color="red", linestyle="--")
    ax.set_yticks([])  
    ax.set_xticks([ 0, 0.2, 0.4, 0.6, 0.8, 1])
    plt.savefig(f"SilhouetteFor{name}K{n_clusters}.png")
    plt.clf()


#CREATING THE MODEL CONFIGURATIONS
def GenerateAggModels():
    return [
        AgglomerativeClustering(2,linkage="single",affinity="euclidean",compute_distances=True),
        AgglomerativeClustering(3,linkage="single",affinity="euclidean",compute_distances=True),
        AgglomerativeClustering(4,linkage="single",affinity="euclidean",compute_distances=True),
        AgglomerativeClustering(5,linkage="single",affinity="euclidean",compute_distances=True),
        AgglomerativeClustering(2,linkage="single",affinity="cosine",compute_distances=True),
        AgglomerativeClustering(3,linkage="single",affinity="cosine",compute_distances=True),
        AgglomerativeClustering(5,linkage="single",affinity="cosine",compute_distances=True),
        AgglomerativeClustering(4,linkage="single",affinity="cosine",compute_distances=True),
        AgglomerativeClustering(2,linkage="complete",affinity="euclidean",compute_distances=True),
        AgglomerativeClustering(3,linkage="complete",affinity="euclidean",compute_distances=True),
        AgglomerativeClustering(4,linkage="complete",affinity="euclidean",compute_distances=True),
        AgglomerativeClustering(5,linkage="complete",affinity="euclidean",compute_distances=True),
        AgglomerativeClustering(2,linkage="complete",affinity="cosine",compute_distances=True),
        AgglomerativeClustering(3,linkage="complete",affinity="cosine",compute_distances=True),
        AgglomerativeClustering(4,linkage="complete",affinity="cosine",compute_distances=True),
        AgglomerativeClustering(5,linkage="complete",affinity="cosine",compute_distances=True)
    ]


aggModels = GenerateAggModels()

scores = []


# AGGLOMERATIVE CLUSTERING
cluster_scores = {k : []  for k in range(2,6)}
for i,model in enumerate(aggModels):
    #TRAIN THE MODEL
    model.fit_predict(dataset)
    scores.append(silhouette_score(dataset, model.labels_))

    c = np.zeros(model.children_.shape[0])
    samples = len(model.labels_)
    
    for idx, m in enumerate(model.children_):
        cc = 0
        
        for cidx in m:

            if cidx < samples:
                cc += 1
            else:
                cc += c[cidx - samples]
        c[idx] = cc

        
    
    # PLOT THE DENDROGRAM
    if i %4 == 0:
        matrix = np.column_stack(
                [model.children_, model.distances_, c]
            ).astype(float)

        
        dendrogram(matrix)
    
    


        plt.title(f"Dendrogram for Model {model.linkage}, {model.affinity}")
        plt.xlabel("Data")
        plt.ylabel("Distances")
        plt.savefig(f'dendrogram_config{i+1}.png', bbox_inches='tight')
        plt.clf()
        
        
# PLOT THE SILHOUETTE GRAPHS 
for conf in GenerateAggModels()[:4]:
    silhouettePlot(conf.n_clusters, conf,"single, euclidian")
for conf in GenerateAggModels()[4:8]:
    silhouettePlot(conf.n_clusters, conf,"single, cosine")
for conf in GenerateAggModels()[8:12]:
    silhouettePlot(conf.n_clusters, conf,"complete, euclidian")
for conf in GenerateAggModels()[12:]:
    silhouettePlot(conf.n_clusters, conf,"complete, cosine")
    
        

    