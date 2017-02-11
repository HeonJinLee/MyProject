import hashlib
import os

fileNameList = []
fileSizeList = []
fileHashList = []

VirusDB = [
	'Eicar:68:44d88612fea8a8f36de82e1278abb02f',
	'Eicar:68:44d88612fea8a8f36de82e1278abb02f'
]

for hdb in VirusDB:
	fileNameList.append(hdb.split(':')[0])
	fileSizeList.append(int(hdb.split(':')[1]))
	fileHashList.append(hdb.split(':')[2])

def fileScan(fileName):
	print "[+] " + fileName + " : filescan start"
	if (checkFileSize(fileName)):
		matchHashValue(fileName)

def checkFileSize(fileName):
	fsize = os.path.getsize(fileName)
	for size in fileSizeList:
		if fsize == size:
			print "\t[+] File Size is Correct"
			return 1
		print "\t[-] File Size is not Correct"
		return 0

def matchHashValue(fileName):
	f = open(fileName,"rb")
	buf = f.read()
	f.close()

	md5 = hashlib.md5()
	md5.update(buf)
	fmd5 = md5.hexdigest()
	for hashValue in fileHashList:
		if fmd5 == hashValue:
			print "\t\t[+] " + fileName + " is eicar file"
			return 1
	print "\t\t[-] " + fileName + " is not eicar file"
	return 0

def dirScan(dir):
	for root, dirs, files in os.walk(dir):
		for file in files:
			fileScan(str(root) +"\\"+ file)

if __name__ == "__main__":
	dir ="C:\\python\\antivirus"
	dirScan(dir)
