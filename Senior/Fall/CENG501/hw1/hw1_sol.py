import numpy as np
from tqdm import tqdm

def sigma(x):
    """Sigma function for the function f.
    """
    return (2 / (1+np.exp(-x))) -1 


def grads_for_f(w,x,b)-> tuple:
    """Calculates the gradients for w and b

    Args:
        w (np.array): D dimensional
        x (np.array): D dimensional
        b (int): Scalar

    Returns:
        _type_: _description_
    """
    mult = np.matmul(x,w)
    a  = 2*(1 + np.exp(-(mult + b)))**(-2) * np.exp(-mult - b)
    return a[0]*x,a



def f(x,w,b) -> tuple: # do not change this line!
    # implement the function f() here
    # x is a N-by-D numpy array
    # w is a D dimensional numpy array
    # b is a scalar
    # Should return three things:
    # 1) the output of the f function, as a N dimensional numpy array,
    # 2) gradient of f with respect to w,
    # 3) gradient of f with respect to b

    #print(f"shapes,  x: {x.shape}, w : {w.shape}")
    grads = grads_for_f(w,x,b)
    return sigma(np.matmul(x,w) + b),grads[0],grads[1]

    


def grads_for_l2(x,y,w,b):
    N: int = len(y)
    summb: float = 0.0
    summw: float = 0.0
        
    for i in range(N):
        
        
        tup = f(x[i],w,b)
        
        summw += -2 * (y[i] - tup[0]) * tup[1]
        summb += -2 * (y[i] - tup[0]) * tup[2]

    summw /= N
    summb /= N
    
    return summw,summb
    

def l2loss(x,y,w,b): # do not change this line!
    # implement the l2loss here
    # x is a N-by-D numpy array
    # y is a N dimensional numpy array
    # w is a D dimensional numpy array
    # b is a scalar
    # Should return three items:
    # 1) the L2 loss which is a scalar,
    # 2) the gradient of the loss with respect to w,
    # 3) the gradient of the loss with respect to b
    
    N: int = len(y)
    summ: float = 0.0
    summw: float = 0.0
    summb: float = 0.0
    
    for i in range(N):
        tup: tuple = f(x[i],w,b)
        diff = y[i] - tup[0]
        
        summ += diff**2
        summw += -2 * diff * tup[1]
        summb += -2 * diff * tup[2]

        
    summ /= N 
    summw /= N
    summb /= N
           
    return summ,summw,summb
    



def minimize_l2loss(x,y,w,b, num_iters=100, eta=1): # do not change this line!
    # implement the gradient descent here
    # x is a N-by-D numpy array
    # y is a N dimensional numpy array
    # w is a D dimensional numpy array
    # b is a scalar
    # num_iters (optional) is number of iterations
    # eta (optional) is the stepsize for the gradient descent
    # Should return three items: 
    # 1) final w
    # 2) final b
    # 3) list of loss values over iterations 
    
    
    losses : list = []

    

    for i in tqdm(range(num_iters)):

        loss,w_grad,b_grad = l2loss(x,y,w,b)

        w = w - eta * w_grad
        b = b - eta * b_grad

        losses.append(loss)
        
        
        
    return w,b,losses
