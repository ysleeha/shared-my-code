# Image Recognition4


import cv2
import numpy as np
import os
import board
import neopixel
import time
import RPi.GPIO as GPIO
import serial

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)

port = '/dev/ttyACM0'
brate = 9600 #boudrate
cmd = 'temp'

port = serial.Serial(port, baudrate=brate, timeout=None)   # <2>
print(port.name)
port.write(cmd.encode())

buzzer=23
GPIO.setup(buzzer, GPIO.OUT)

pixels = neopixel.NeoPixel(board.D18, 24)

GPIO.setup(17, GPIO.IN, pull_up_down=GPIO.PUD_UP) 
GPIO.setup(26, GPIO.IN, pull_up_down=GPIO.PUD_UP) 

recognizer = cv2.face.LBPHFaceRecognizer_create()
recognizer.read('trainer/trainer.yml')
cascadePath = "haarcascades/haarcascade_frontalface_default.xml"
faceCascade = cv2.CascadeClassifier(cascadePath);
font = cv2.FONT_HERSHEY_SIMPLEX

#iniciate id counter
id = 1
a=0
# names related to ids: example ==> loze: id=1,  etc
# 이런식으로 사용자의 이름을 사용자 수만큼 추가해준다.
names = ['None', 'user' ]

# Initialize and start realtime video capture
cam = cv2.VideoCapture(0)
cam.set(3, 640) # set video widht
cam.set(4, 480) # set video height

# Define min window size to be recognized as a face
minW = 0.1*cam.get(3)
minH = 0.1*cam.get(4)

while True:
    
    if port.in_waiting != 0:
        content = port.readline()
        print(content[14:20].decode())
        
    ret, img =cam.read()
    #img = cv2.flip(img, -1) # Flip vertically
    gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
    input_state=GPIO.input(17)
    input_state1=GPIO.input(26)
    
    if(input_state1==False):
        print("safe")
        GPIO.output(buzzer, GPIO.LOW)
        a=0

    
    faces = faceCascade.detectMultiScale( 
        gray,
        scaleFactor = 1.2,
        minNeighbors = 5,
        minSize = (int(minW), int(minH)),
       )
    if(len(content) == 42 ):
        print("range off")
        pixels.fill((0,0,0))
        pixels.show()
    if(len(content) == 43 ):
        print("range on")
        pixels.fill((10,0,0))
        pixels.show()
    if(len(content) == 44 ):
        print("buzzer off")
        GPIO.output(buzzer, GPIO.LOW)
        
    for(x,y,w,h) in faces:
        cv2.rectangle(img, (x,y), (x+w,y+h), (0,255,0), 2)
        id, confidence = recognizer.predict(gray[y:y+h,x:x+w])
        # Check if confidence is less them 100 ==> "0" is perfect match
        if (confidence < 80):
            id = names[id]
            confidence = "  {0}%".format(round(100 - confidence))
            if (id == names[1]):
                if(input_state == False):
                    pixels.fill((10,0,0))
                    pixels.show()
                    a=1

        else:
            id = "unknown"
            confidence = "  {0}%".format(round(100 - confidence))
            pixels.fill((0,0,0))
            pixels.show()
            
        if(float(content[14:20]) > 50.00 and a==1):
            print("danger")
            GPIO.output(buzzer, GPIO.HIGH)
            
        cv2.putText(img, str(id), (x+5,y-5), font, 1, (255,255,255), 2)
        cv2.putText(img, str(confidence), (x+5,y+h-5), font, 1, (255,255,0), 1)  
    
    cv2.imshow('camera',img) 
    k = cv2.waitKey(10) & 0xff # Press 'ESC' for exiting video
    if k == 27:
        break
# Do a bit of cleanup
print("\n [INFO] Exiting Program and cleanup stuff")
cam.release()
cv2.destroyAllWindows()