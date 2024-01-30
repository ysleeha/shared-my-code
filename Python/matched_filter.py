import numpy as np
from scipy import signal

def matched_filter(g, x, fs):

    dt =  1/fs

    # generate the filter impulse response
    l = np.arange(0,g.size)
    l = l[::-1]
    h = g[:,l]
    h = h.flatten()
    # generate output signal
    out = signal.convolve(h,x)*dt
    out = np.append(out.flatten(), 0)
   
    return out
