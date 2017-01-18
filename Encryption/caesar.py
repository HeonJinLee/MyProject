import string

def shift(c, N):
	if c not in string.ascii_lowercase:
		return c
	if ord(c)+N > ord("z"):
		return chr( ord(c)+N -26)
	else:
		return chr(ord(c)+N)
	
def solve(chip):
	for i in range(1,26):
		mes = ''
		for c in chip:
			mes += shift(c,i)
		print "key("+str(i)+") : "+mes

if __name__ == '__main__':
	chip = raw_input('> ').lower()
	solve(chip)