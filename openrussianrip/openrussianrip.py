#!/usr/bin/python3

from bs4 import BeautifulSoup
import urllib3

base_url = 'https://de.openrussian.org/list/all?start='
counter = 0

http = urllib3.PoolManager()

words = 30000
last_page = int(words / 50) + 1

for i in range(1, last_page):
    url = base_url + str(counter)
    counter += 50
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
                    
                print(numberCell.text, deText, ruText)
