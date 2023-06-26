from KMeans import KMeans
import pickle
import matplotlib.pyplot as plt
import numpy as np
from tqdm import tqdm #THIS IS FOR ONLY PROGRESS BAR, IT HAS NOTHING TO DO WITH THE CODE



dataset1 = pickle.load(open("../data/part2_dataset_1.data", "rb"))



dataset2 = pickle.load(open("../data/part2_dataset_2.data", "rb"))
data = [dataset1,dataset2]

d1, d2 = zip(*dataset1)
id=1
#FOR EACH DATA
for d in data:
    mighty_losses = [[] for x in range(9)]
    for k in range(10):
        

        for i in tqdm(range(2,11)):
            losses_each = []        
            
            for j in range(10):
                #CREATE
                model = KMeans(d, i,)
                #TRAIN
                centers, _, loss = model.run()
                #SAVE LOSS
                losses_each.append(loss)
                
            #TAKE THE MINIMUM OF THE 10 TRYING
            mighty_losses[i-2].append(np.min(losses_each))

        print(f"{k+1}th iteration...")
    
    #CALCULATE THE CONFIDENCE INTERVALS ON THE ALPHAS
    confidence_intervals = []
    for i in mighty_losses:
        nu = np.mean(i)
        sigma = np.std(i)
        interval = [round((nu - 1.96 * sigma / len(i)**0.5).item(),4) ,round((nu + 1.96 * sigma / len(i)**0.5).item(),4)]
        confidence_intervals.append(interval[0])
        confidence_intervals.append(interval[1])

    mighty_losses = [np.min(x) for x in mighty_losses]
    
    conf_plot = []

    #INDEX ARRENGMENT FOR PLOTING
    for i in range(2,11):
        conf_plot.append(i)
        conf_plot.append(i)

    #SAVE AND PLOT THE GRAPHS
    plt.xlabel("K")
    plt.ylabel("Loss")
    plt.plot(range(2,11),mighty_losses)
    plt.plot(conf_plot,confidence_intervals,"o",color = "red", alpha =0.5)
    plt.savefig(f"Kmeans_Dataset{id}.png")
    plt.show()
    id+=1





