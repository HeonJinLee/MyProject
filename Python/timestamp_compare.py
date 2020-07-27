#timestamp를 입력받아, 해당 두 시간 차이 구하는 툴

import time
import pprint
from datetime import datetime

col = ['2010-03-04 08:28:35', '2011-03-04 08:28:35', '2011-12-04 18:18:35', '2010-03-07 08:28:35', '2015-03-04 08:28:35', '2010-03-06 08:28:35', '2013-04-04 08:28:35', '2013-03-04 08:28:35', '2017-05-04 08:28:35', '2016-03-04 08:28:35']
row = ['2010-03-04 08:28:35', '2015-03-04 08:28:35', '2011-12-04 18:18:35', '2010-03-07 08:28:35', '2012-03-04 08:28:35', '2010-03-06 08:28:35', '2013-04-04 08:28:35', '2013-03-04 08:28:35', '2017-05-04 08:28:35', '2010-03-04 08:28:35']

row_arr = list()
col_arr = list()
test = [[0] * (len(col)+1) for i in range(len(row)+1)]
num_row = 0
count = 1

for i in col:
   col_timestamp = time.mktime(datetime.strptime(i, '%Y-%m-%d %H:%M:%S').timetuple())
   col_arr.append(col_timestamp)
   
for i in row:
   row_timestamp = time.mktime(datetime.strptime(i, '%Y-%m-%d %H:%M:%S').timetuple())
   test[0][count] = row_timestamp

   if test[num_row][0] is not None:
      test[count][0] = col_arr[num_row]
	  
   count = count + 1
   num_row = num_row + 1

count = 1

for i in range(len(col)+1):
   if count == len(col)+1:
      break
   for j in range(len(row)+1):
      if test[0][count] >= test[count][0]:
         test[count][count]=test[0][count] - test[count][0]
      else:
         test[count][count]=test[count][0] - test[0][count]

   count = count + 1

pprint.pprint(test)
