import pickle
import numpy as np
from sklearn.svm import SVC
import matplotlib.pyplot as plt
from sklearn.preprocessing import StandardScaler


dataset, labels = pickle.load(open("../data/part2_dataset1.data", "rb"))
split = int(len(dataset) * 0.8)


svm = SVC(kernel="poly")
svm.fit(dataset,labels)

X = dataset
y = labels

h = .02

models = [SVC(C= 1.0,kernel="poly").fit(X,y),SVC(C = 0.000001,kernel="poly").fit(X,y),
          SVC(C = 1.0,kernel="rbf").fit(X,y),SVC(C = 0.000001,kernel="rbf").fit(X,y)]


# Plotting code is taken from the site : https://scikit-learn.org/0.18/auto_examples/svm/plot_iris.html


plt.figure(figsize=(10, 8))
# Plotting our two-features-space

plt.scatter(np.array(dataset)[:,0],np.array(dataset)[:,1],c = labels)

x_min, x_max = X[:, 0].min() - 1, X[:, 0].max() + 1
y_min, y_max = X[:, 1].min() - 1, X[:, 1].max() + 1
xx, yy = np.meshgrid(np.arange(x_min, x_max, h),
                     np.arange(y_min, y_max, h))

titles = ["C = 1, Kernel = poly",
          "C = 0.000001, Kernel = poly",
          "C = 1, Kernel = rbf",
          "C = 0.000001, Kernel = rbf"]

for i,svm in enumerate(models):
    plt.subplot(2, 2, i + 1)
    plt.subplots_adjust(wspace=0.4, hspace=0.4)


    Z = svm.predict(np.c_[xx.ravel(), yy.ravel()])

    # Put the result into a color plot
    Z = Z.reshape(xx.shape)
    plt.contourf(xx, yy, Z, cmap=plt.cm.coolwarm, alpha=0.8)

    # Plot also the training points
    plt.scatter(X[:, 0], X[:, 1], c=y, cmap=plt.cm.coolwarm)
    plt.xlabel('Sepal length')
    plt.ylabel('Sepal width')
    plt.xlim(xx.min(), xx.max())
    plt.ylim(yy.min(), yy.max())
    plt.xticks(())
    plt.yticks(())
    plt.title(titles[i])
    
plt.savefig("plots.png")
plt.show()