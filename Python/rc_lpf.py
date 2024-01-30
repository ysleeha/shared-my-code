import numpy as np
from scipy import signal

def rc_lpf(x , fc, fs, Rb):

    samples_per_bit = np.int64(fs/Rb)
    fc_n = [fc/(fs/2)] # nomralized cut-off frequency
    B, A = signal.butter(1, fc_n)
    y = signal.filtfilt(B, A, x)
    #y = out1

    #out3 = signal.filtfilt(B, A, zeros(1,samples_per_bit), out2)
    #y = [out1.flatten() out3.flatten()]


    return y
