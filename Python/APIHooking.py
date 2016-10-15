import utils, sys
from pydbg import *
from pydbg.defines import *
'''
BOOL WINAPI WriteFile(
	_In_		HANDLE hFile,
	_In_		LPCVOID lpBuffer,
	_In_		DWORD nNumberOfBytesToWrite,
	_Out_opt_	LPDWORD lpNumberOfBytesWritten,
	_Inout_opt_	LPOVERLAPPED lpOverlapped
	);
	'''
dbg = pydbg()
isProcess = False

orgPattern = 'Python'
repPattern = 'Difficult'
processName = 'notepad.exe'		#32비트 메모장 

def replaceString(dbg, args):		#콜백 함수 선언
	buffer = dbg.read_process_memory(args[1],args[2])	#메모리 값 읽기
	#지정된 주소에서 지정된 길이 만큼 메모리주소를 읽어서 반환(Kernel32.ReadProcessMemory)

	if orgPattern in buffer:
		print "[APIHooking] Before : %s" % buffer
		buffer = buffer.replace(orgPattern, repPattern)	#값 바꾸기
		replace = dbg.write_process_memory(args[1],buffer)
		print '[APIHooking] After : %s' % dbg.read_process_memory(args[1],args[2])
	return DBG_CONTINUE

for(pid, name) in dbg.enumerate_processes():	#프로세스 ID 리스트 얻기
	if name.lower() == processName:
		isProcess = True
		hooks = utils.hook_container()

		dbg.attach(pid)		#프로세스 핸들(자원을 다룰수 있는) 구하기
		print "Saves a process handle in self.h_process of pid[%d]" % pid

		hookAddress = dbg.func_resolve_debuggee("kernel32.dll","WriteFile")
		#원하는 Win32 API 함수를 찾아서 해당 주소 반환

		if hookAddress:
			hooks.add(dbg, hookAddress, 5, replaceString, None)		#중단점 설정
			print "sets a breakpoint at the designated address : 0x%08x" % hookAddress
			break
		else:
			print "[Error] : couldn't resolve hook address"
			sys.exit(-1)

if isProcess:
	print "waiting for occuring debugger event"
	dbg.run()
else:
	print "[Error] : There in no process [%s]"%processName
	sys.exit(-1)
