#적외선 감지 센서
import RPi.GPIO as GPIO
import time
GPIO.setmode(GPIO.BCM)
pir_pin=21
print ("PIR_SR501 motion sensor test")
GPIO.setup(pir_pin,GPIO.IN)
try:
	i=0
	while(True):
		i+=1
		pir_SR501_input=GPIO.input(pir_pin)
		print("light_input=%d i=%d"%(pir_SR501_input,i))
		if(pir_SR501_input==0):
			print("someone come in %s" % time.strftime("%H:%M:%S,%Y.%m.%d"))
			time.sleep(1)
except KeyboardInterrupt:
	GPIO.cleanup







#소음측정
#5V, GND, 21

import RPi.GPIO as GPIO
import time
GPIO.setmode(GPIO.BCM)

noise_pin=21
print("noise sencor test")
GPIO.setup(noise_pin, GPIO.IN)
try:
	i=0
	while(1):
		noise_input=GPIO.input(noise_pin)
		if(noise_input==1):
			print("noise_checkint every 500ms = %d normal" % noise_input)
		elif(noise_input==0):
			i+=1
			print("repeat %d noise happened = %d time = %s"%(i, noise_input, time.strftime("%H ;%M; %S")))
			time.sleep(0.5)

except KeyboardInterrupt:
	GPIO.cleanup()









#초음파 거리 센서 연결

import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
low = 0
high = 1
trig = 21
echo = 20
disatance1=[0,0,0,0]
GPIO.setup(trig, GPIO.OUT)
GPIO.setup(echo, GPIO.IN)
GPIO.output(trig, low)

def distance_check():
	GPIO.output(trig, high)
	time.sleep(0.00001)
	GPIO.output(trig, low)
	stop = 0
	start = 0
	while GPIO.input(echo)==0:			#echo가 high되는 시점을 기다림
		start = time.time()
	while GPIO.input(echo)==1:			#echo가 low되는 시점을 기다림
		stop = time.time()
	duration = stop - start
	distance = (duration * 340 * 100)/2		#소리의 속도 : 340m/s
						#340cm로 변환 후 편도거리 계산
	return distance

def average_disatance():
	distance=0
	for i in range(0,4):
		distance1[i]=distance_check()
		time.sleep(0.1)
	for i in range(0,4):
		distance += disatance1[i]
	distance = distance / 4
	return distance

try :
	i=0
	while 1:
		result_distance = average_distance()
		print("repeat = %d distance = %.1f cm" % (i, result_distance)
		time.sleep(1)
		i+=1
except KeyboardInterrupt:
	GPIO.cleanup()








#온/습도 측정
import time
import RPi.GPIO as GPIO
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
GPIO.cleanup()

class DHT11:
	pin = 0
	temp = -1
	humi = -1

	def __init__(self, pin, temp=-1, humi=-1):
		self.temp = temp
		self.humi = humi
		self.pin = pin

	def read(self):
		GPIO.setup(self.pin, GPIO.OUT)
		GPIO.output(self.pin, GPIO.HIGH)
		time.sleep(0.05)
		GPIO.output(self.pin, GPIO.LOW)
		time.sleep(0.018)
		GPIO.setup(self.pin, GPIO.IN, GPIO.PUD_UP)
		data = self.collect_input()
		pull_up_lengths = self.parse_data_pull_up_lengths(data)
		if len(pull_up_lengths) != 40:
			result = 0
			self.temp=0
			self.humi=0
			return result

		bits = self.calculate_bits(pull_up_lengths)
		the_bytes = self.bits_to_bytes(bits)
		checksum = self.calculate_checksum(the_bytes)
		if the_bytes[4] != checksum:
			result = 0
			self.temp = 0
			self.humi = 0
			return result
		result=1
		self.temp = the_bytes[2]
		self.humi = the_bytes[0]
		return result

		#온도 센서에 1비트씩 100번 읽음
	def collect_input(self):
		unchanged_count = 0
		max_unchanged_count = 100
		last = -1
		data = []
		while 1:
			current = GPIO.input(self.pin)
			data.append(current)
			if last != current:
				unchanged_count = 0
				last = current
			else:
				unchanged_count += 1
				if unchanged_count > max_unchanged_count:
					break
		return data

	def parse_data_pull_up_lengths(self. data):
		STATE_INIT_PULL_DOWN = 1
		STATE_INIT_PULL_UP = 2
		STATE_DATA_FIRST_PULL_DOWN = 3
		STATE_DATA_PULL_UP = 4
		STATE_DATA_PULL_DOWN = 5
		state = STATE_INIT_PULL_DOWN
		lengths = []
		current_length = 0
		for i in range(len(data)):
			current = data[i]
			current_length += 1
			if state == STATE_INIT_PULL_DOWN:
				if current ==GPIO.LOW:
					state = STATE_INIT_PULL_UP
					continue
				else:
					continue

			if state == STATE_INIT_PULL_UP:
				if current = GPIO.HIGH:
					state = STATE_DATA_FIRST_PULL_DOWN
					continue
				else:
					continue
				
			if state == STATE_DATA_FIRST_PULL_DOWN:
				if current == GPIO.LOW:
					state = STATE_DATA_PULL_UP
					continue
				else:
					continue

			if state == STATE_DATA_PULL_UP:
				if current == GPIO.HIGH:
					current_length = 0
					state = STATE_DATA_PULL_DOWN
					continue
				else:
					continue

			if state == STATE_DATA_PULL_DOWN:
				if current == GPIO.LOW:
					lengths.append(current_length)
					state = STATE_DATA_PULL_UP
					continue
				else:
					continue
		return lengths

	def calculate_bits(self, pull_up_lengths):
		bits = []
		halfway = 15
		for i in range(0, len(pull_up_lengths)):
			bit = False
			if pull_up_lengths[i]>halfway:
				bit = True
			bits.append(bit)
		return bits

	def bits_to_bytes(self,bits):
		the_bytes = []
		byte = 0
		for i in range(0, len(bits)):
			byte = byte << 1
			if(bits[i]):
				byte = byte | 1
			else : 
				byte = byte | 0
			if((i+1) % 8 == 0):
				the_bytes.append(byte)
				byte = 0
		return the_bytes

	def calculate_checksum(self, the_bytes):
		return the_bytes[0] + the_bytes[1] + the_bytes[2] + the_bytes[3] & 255

data = DHT11(pin=4)

while 1:
	result = data.read()				#데이터 읽기
	if result:
		print("Temperature : %d C" % data.temp)	#온도 출력
		print("Humidity : %d %%" % data.humi)	#습도 출력
	time.sleep(1)
























