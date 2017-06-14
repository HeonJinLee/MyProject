#센서 확인

import RPi.GPIO as GPIO 	#다목적 입력출력
import time
GPIO.setmode(GPIO.BCM)		#p05번 같은 번호로 사용할때 BCM모드로 사용
GPIO.setup(5,GPIO.OUT)		#p05번을 쓸거다. GPIO.OUT 출력을 위해
GPIO.output(5,True)		#불이 안들어오게 함
GPIO.output(5,False)		#불이 들어오게 함






#불이 5번 깜박 깜박 하게함.

import RPi.GPIO as GPIO
import time
GPIO.setmode(GPIO.BCM)
GPIO.setup(5,GPIO.OUT)
for i in range(1,6):
	try:
		GPIO.output(5,False)
		time.sleep(1)
		GPIO.output(5,True)
		time.sleep(4)
	except KeyboardInterrupt:
		GPIO.cleanup()






# 전구 두개가 번갈아 가면서 깜빡

import RPi.GPIO as GPIO
import time
GPIO.setmode(GPIO.BCM)
GPIO.setup(5,GPIO.OUT)
GPIO.setup(6,GPIO.OUT)
while(1):
	try:
		GPIO.output(6,False)
		time.sleep(1)
		GPIO.output(6,True)
		GPIO.output(5,False)
		time.sleep(1)
		GPIO.output(5,True)
	except KeyboardInterrupt:
		GPIO.cleanup()








#P26에 꽂은 버튼을 누르면 불이 들어옴

import RPi.GPIO as GPIO	#라즈베리파이 입출력 라이브러리를 파이썬에 가져 쓰겠다
import time

GPIO.setmode(GPIO.BCM)
GPIO.setup(26,GPIO.IN)
GPIO.setup(27,GPIO.IN)
GPIO.setup(5,GPIO.OUT)
off=1
on=0
try:
	while(1):
		if GPIO.input(26)==on:
			GPIO.output(5,on)
		else:
			GPIO.output(5,off)
			time.sleep(0.2)

except KeyboardInterrupt:
	GPIO.cleanup()







#27번과 26번 버튼을 누르면 5번 불과 6번 불이 번갈아 가며 나옴.

import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
GPIO.setup(26,GPIO.IN)
GPIO.setup(27,GPIO.IN)
GPIO.setup(5,GPIO.OUT)
GPIO.setup(6,GPIO.OUT)
off=1
on=0

def my_callback(channel):
	if GPIO.input(27)==on:
		print("switch 2 on")
		GPIO.output(5,on)
		GPIO.output(6,off)
	elif GPIO.input(26)==on:
		print("switch 1 on")
		GPIO.output(5,off)
		GPIO.output(6,on)

GPIO.add_event_detect(27,GPIO.FALLING,callback=my_callback)
GPIO.add_event_detect(26,GPIO.FALLING,callback=my_callback)

while(1):
	try:
		time.sleep(0.01)
	except KeyboardInterrupt:
		GPIO.remove_event_detect(27)
		GPIO.remove_event_detect(26)
		GPIO.cleanup()







#24번에 연결된 터치 센서를 누르면 5번 불이 들어옴

import RPi.GPIO as GPIO
import time
GPIO.setmode(GPIO.BCM)
GPIO.setup(5,GPIO.OUT)

on=0
off=1
pin_num=24

GPIO.setup(pin_num,GPIO.IN)
try:
	while True:
		pad_pressed = GPIO.input(pin_num)

		if pad_pressed:
			print("Touch")
			GPIO.output(5,on)
		else:
			GPIO.output(5,off)
	
		time.sleep(0.1)

except KeyboardInterrupt:
	GPIO.cleanup()






#24번에 연결된 터치센서 터치를 하면 23번 불이 들어옴

import time
import RPi.GPIO as GPIO
GPIO.setmode(GPIO.BCM)

pin_num=24
LED=23
GPIO.setup(pin_num, GPIO.IN)
GPIO.setup(LED,GPIO.OUT,initial=GPIO.LOW)

try:
	while True:
		pad_pressed = GPIO.input(pin_num)

		if pad_pressed:
			print("Touch")
			GPIO.output(LED,False)
		else:
			GPIO.output(LED,True)
except KeyboardInterrupt:
	GPIO.cleanup()







