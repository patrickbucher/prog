#!/usr/bin/python3

from bs4 import BeautifulSoup
import urllib3
import sys
import math

def fail():
    usage = sys.argv[0] + " [number of words] [nouns/verbs/adjectives]"
    sys.exit("usage: " + usage)

http = urllib3.PoolManager()

try:
    words = int(sys.argv[1])
    nargs = len(sys.argv)
    word_type = "all"
    if nargs >= 3 and sys.argv[2] in ["nouns", "verbs", "adjectives"]:
        word_type = sys.argv[2]
except:
    fail()

file_name = 'top-%d-%s.txt' % (words, word_type)
target = open(file_name, 'w')
target.truncate()

base_url = 'https://de.openrussian.org/list/%s?start=' % word_type
offset = 0
last_page = int(math.ceil(words / 50))
for i in range(1, last_page + 1):
    url = base_url + str(offset)
    offset += 50
    response = http.request('GET', url)
    soup = BeautifulSoup(response.data, "html.parser")
    tables = soup.findAll('table', { 'class' : 'wordlist' })
    for table in tables:
        rows = table.findAll('tr')
        for row in rows:
            numberCell = row.findAll('th')[0]
            cells = row.findAll('td')
            if len(cells) >= 2: 
                deCell = cells[0]
                deText = deCell.text
                ruCell = cells[1]
                ruLinks = ruCell.findAll('a')
                if len(ruLinks) > 0:
                    ruText = ruLinks[0].text
                else:
                    ruText = ruCell.text
                    
                target.write("%s;%s\n" % (deText, ruText))

target.close()
