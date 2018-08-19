import base64
import sys

option = sys.argv[1]
with open(sys.argv[2]) as f:
   if option == '-e':
      encoded = f.read()
      sys.stdout.write(base64.b64encode(encoded) + '\n')
   try:
      if option == '-d':
         decoded = f.read()
         sys.stdout.write(base64.b64decode(decoded) + '\n')
   except UnicodeDecodeError:
      print("Error")
