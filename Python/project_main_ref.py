import random_seq as rs
import linecode_gen as lg
import channel_filter as cf
import awgn as awgn
import rc_lpf as rl
import matched_filter as mf

import numpy as np
import matplotlib.pyplot as plt
from operator import eq

# Parameter setting
Rb = 1000 #1초당 1000비트 
fs = 10*Rb #샘플링은 10개 
# 아날로그 신호를 표현하기 위해 표에 10개 점 그리는거 Tb 만큼
# 10개의 표본으로 아날로그 신호 표현
Tb = 1/Rb #1비트는 1/1000초 
Ts = 1/fs # 1/10000초당 한개의 표본
B = fs/2 # system bandwidth
f_cutoff = 3000 # cut-off frequency for RC filter


nBits = 1*pow(10,6) # total number of bits
M = fs/Rb # number of samples per bit duration #비트당 몇개의 샘플

####################### Transmitter #################################
# signal generation
linecode = 'manchester'
b = rs.random_seq(nBits) #nBits 는 10에 6승 비트

[x, t, pulse_shape] = lg.linecode_gen(b,linecode,Rb,fs);

# determine signal amplitude assuming unit bit energy 
# bit energy Eb is assumed to be 1
Eb = 1
if eq(linecode,'polar_nrz'): 
    A = np.sqrt(Eb/Tb)
    threshold_A = 0
    threshold_B = 0
    str = 'Polar_NRZ Signaling'
    
elif eq(linecode, 'unipolar_nrz'): 
    A = np.sqrt(2*Eb/Tb)
    threshold_A = A/2
    threshold_B = A*Tb/2
    str = 'Unipolar NRZ Signaling'
    
elif eq(linecode, 'manchester'):
    A = np.sqrt(Eb/Tb)
    threshold_A = 0
    threshold_B = 0
    str = 'manchester Signaling'

    
x = A*x


EbN0_dB = np.arange(0,21,2)
Pe_simple = np.zeros(EbN0_dB.size)
Pe_lpf = np.zeros(EbN0_dB.size)
Pe_opt = np.zeros(EbN0_dB.size)
i = 0
for n in EbN0_dB :
    ####################### Channel #####################################
    EbN0 = pow(10,n/10)
    # AWGN channel
    noise_var = B/EbN0
    noise = awgn.awgn(0, noise_var, len(x))
    noise = noise.flatten()
    r = x + noise
    #print(r)
    ####################### Receier #####################################
    # 1. simple sampling receiver
    # Bit decision
    index = np.arange(1,nBits+1,1)
    b_hat = r[np.int64(M*index-M/4)-1] # generate decision variable by sampling received signal
    b_hat[b_hat < threshold_A] = 0
    b_hat[b_hat > threshold_A] = 1
    #print((M*index-M/4)-1)
    b = b.flatten()
    b_hat = b_hat.flatten()
    # check error
    num_error1 = 0
    err_bit1 = ((b-b_hat) != 0)
    num_error1 = num_error1 + sum(err_bit1)
    Pe_simple[i] = num_error1/nBits

    # 2. RC LPF fitler receiver
    y = rl.rc_lpf(r, f_cutoff, fs, Rb)
    # Bit decision
    index = np.arange(1,nBits+1,1)
    b_hat = y[np.int64(M*index-M/4)-1] # generate decision variable by sampling received signal
    b_hat[b_hat < threshold_A] = 0
    b_hat[b_hat > threshold_A] = 1
    #print(b_hat)
    b = b.flatten()
    b_hat = b_hat.flatten()
    # check error
    num_error2 = 0
    err_bit2 = ((b-b_hat) != 0)
    num_error2 = num_error2 + sum(err_bit2)
    Pe_lpf[i] = num_error2/nBits

    # 3. Matched filter receiver
    z = mf.matched_filter(pulse_shape, r, fs)
    # Bit decision
    index = np.arange(1,nBits+1,1)
    b_hat = z[np.int64(M*index)-1] # generate decision variable by sampling received signal
    b_hat[b_hat < threshold_B] = 0
    b_hat[b_hat > threshold_B] = 1
    #print(b_hat)
    b = b.flatten()
    b_hat = b_hat.flatten()
    # check error
    num_error3 = 0
    err_bit3 = ((b-b_hat) != 0)
    num_error3 = num_error3 + sum(err_bit3)
    Pe_opt[i] = num_error3/nBits
    #####################################################################
    print('Step of Eb/N0 = %d dB' %n)
    i = i + 1


plt.figure(1)
plt.plot(t[0:100],x[0:100],'bo-',label = 'transmitted signal')
plt.xlabel('Time')
plt.ylabel('Pulse')
plt.grid(True)
plt.legend(loc=0)
plt.title(str)

plt.figure(2)
plt.plot(t[0:100],r[0:100],'bo-',label = 'received signal')
plt.xlabel('Time')
plt.ylabel('Pulse')
plt.grid(True)
plt.legend(loc=0)
plt.title(str)

plt.figure(3)
plt.plot(t[0:100],y[0:100],'bo-',label = 'rc filtered signal')
plt.xlabel('Time')
plt.ylabel('Pulse')
plt.grid(True)
plt.legend(loc=0)
plt.title(str)

plt.figure(4)
plt.plot(t[0:100],z[0:100],'bo-',label = 'matched filtered signal')
plt.xlabel('Time')
plt.ylabel('Pulse')
plt.grid(True)
plt.legend(loc=0)
plt.title(str)


# Results
plt.figure(5)
plt.semilogy(EbN0_dB,Pe_simple,'bo-',label = 'Simple Sampling Receiver')
plt.semilogy(EbN0_dB,Pe_lpf,'kx-', label = 'RC LPF Receiver')
plt.semilogy(EbN0_dB,Pe_opt,'rd-', label = 'Matched Filter Receiver')
plt.xlabel('Eb/N0 [dB]')
plt.ylabel('probability of bit error')
plt.xlim(EbN0_dB[0],EbN0_dB[-1])
plt.ylim(pow(10,-5),1)
plt.grid(True)
plt.legend(loc=0)
plt.title(str)
plt.show()
