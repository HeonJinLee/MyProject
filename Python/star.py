for i in range(5):
	for j in range(5-i-1):
		print(" ",end='')
	for j in range(i*2+1):
		print("*",end='')
	print('')
for i in range(5):
	for j in range(i):
		print(" ",end='')
	for j in range(5*2-i*2-1):
		print("*",end='')
	print("")