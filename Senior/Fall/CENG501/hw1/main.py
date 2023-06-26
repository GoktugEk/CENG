import numpy as np
import pickle, gzip
import hw1_sol as hw1
import sys
from matplotlib import pyplot as plt
import plot_boundary_on_data  

# Read in training data
with gzip.open(sys.argv[1]) as f:
    data, labels = pickle.load(f, encoding='latin1')
    labels = np.array(labels, dtype=np.int8)
    labels[labels==0] = -1

# (Random) Initial values for w and b
w0 = 0.1*np.random.randn(data.shape[1]) 
b0 = 0.1*np.random.randn(1)

# Optimization
w,b,losses = hw1.minimize_l2loss(data, labels, w0,b0, int(sys.argv[3]),
        float(sys.argv[4]))
plt.plot(losses)
plt.xlabel('iterations')
plt.ylabel('loss')
plt.savefig('losses.png')

# Show the result of training
#print w,b
plt.figure()
if w.size==2:
    plot_boundary_on_data.plot(data, labels, lambda x: hw1.f(x,w,b)[0]>0)

if w.size==784: # special to MNIST
    plt.imshow(w.reshape(28,28));
    plt.savefig("weights.png")


# Test on test data
with gzip.open(sys.argv[2]) as f:
    test_data, test_labels = pickle.load(f, encoding='latin1')
    test_labels = np.array(test_labels, dtype=np.int8)
    test_labels[test_labels==0] = -1
    

plt.show()
yhat = np.sign(hw1.f(test_data, w, b)[0])
print(np.mean(yhat==test_labels)*100, "% of test examples classified correctly.")
