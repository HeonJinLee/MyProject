import datetime
import requests
import os
import json
from bs4 import BeautifulSoup

today = datetime.date.today()

f = open("C:\lhj\boannews\%s.txt" % today,'w')

## HTTP GET Request
req = requests.get("https://www.boannews.com/media/t_list.asp")

## HTML 소스 가져오기
html = req.text

## 첫 인자는 html 소스 코드, 두 번째 인자는 어떤 parser 명시.
soup = BeautifulSoup(html, 'html.parser')

## Copy Selector
my_titles = soup.select(
   'div > a:nth-child(1)'
   )

for title in my_titles:
   f.write(title.text)
   f.write("https://www.boannews.com")
   f.write(title.get('href')) 
