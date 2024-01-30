import numpy as np

def linecode_gen(bit_sequence, code_name, data_rate, samp_freq):
#bit_sequecne=10에 6승 data=1000, samp=10*data
#bit_sequence는0또는 1로 생각
    
    fs = samp_freq; #10*Rb
    Rb = data_rate; # 1000
    
    Ts = 1/fs;
    Tb = 1/Rb;

    no_binary = len(bit_sequence)
    no_sample = no_binary * Tb/Ts;
    
    time = np.arange(no_sample) * Ts;

    if code_name == 'polar_nrz':
        basic_pulse = np.ones((1,np.int64(fs/Rb))) # 1을 가로로 10개 만드는 놈 [1, … ,1]
        # 10개의 샘플을 가진다.
        b_seq = 2*bit_sequence - np.ones((np.size(bit_sequence),1))
        # b_seq가 1 또는 -1 이니까 basic_pulse에 1 곱하면 위로 -1곱하면 아래로
        # 그럼 polar_nrz 같은 모양이 나온다.
    
    elif code_name == 'unipolar_nrz':
        basic_pulse = np.ones((1,np.int64(fs/Rb)))
        b_seq = bit_sequence
        
    elif code_name == 'manchester':
        a1=-np.ones((1,np.int64(fs/(2*Rb))))
        a2=np.ones((1,np.int64(fs/(2*Rb))))
        basic_pulse = np.c_[a1,a2]
                
        b_seq = 2*bit_sequence - np.ones((np.size(bit_sequence),1))
       

    x = np.matmul(b_seq, basic_pulse) # 10 x 10 나온다
    out_waveform = x.flatten() # 10 x 10을 일렬로 평평하게 펴준다 [숫자, ...... ,숫자]
    t = time
    pulse = basic_pulse
    
    return out_waveform, t, pulse

