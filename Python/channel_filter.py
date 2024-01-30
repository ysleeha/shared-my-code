import numpy as np
from scipy import signal

def channel_filter(x,gain,noise_power,f_cutoff,fs):

    Ts = 1/fs
    n_sample = len(x)
    time = (np.arange(n_sample)-1)*Ts

    ripple = 0.1
    filt_order = 8
    fpoints = 256


    Wc = f_cutoff
    Wn = Wc/(fs/2)

    [B,A] = signal.cheby1(filt_order, ripple, Wn)

   
    B = np.sqrt(gain) * B
    x = x.flatten() 

    y = signal.lfilter(B, A, x)
    noise  = np.random.randn(np.size(y))
    r = y + np.sqrt(noise_power)*noise
          
    return r, time
