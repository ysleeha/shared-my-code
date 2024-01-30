import numpy as np
def awgn(mean, var, N):


    y = np.sqrt(var)*np.random.randn(1,N) + mean
    return y

