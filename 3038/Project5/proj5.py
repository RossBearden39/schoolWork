#Ross Bearden
#CSCI 3038
#Project 5
#Web Scrapping

#for JSON format
import requests
#for XML fromat
from bs4 import BeautifulSoup
import sys
import re

#Function for scrapping xml site
def xSite(loc1, loc2):
	url = 'https://maps.googleapis.com/maps/api/distancematrix/xml'
	req = requests.get(url, params={'destinations': loc2, 'origins': loc1})
	soup = BeautifulSoup(req.content)
	print(soup.distance.find('text').string, ' between ', loc1, ' ', loc2)

#Function for scrapping JSON format site
def jSite(loc1, loc2):
	url = 'https://maps.googleapis.com/maps/api/distancematrix/json'
	req = requests.get(url, params={'destinations': loc2, 'origins': loc1})
	jsonData = req.json()
	print(jsonData['rows'][0]['elements'][0]['distance']['text'], ' between ', loc1, ' ', loc2)

#Function that visits a given url and prints all href values on the page
def printA(url):
	req = requests.get(url)
	soup = BeautifulSoup(req.content)
	for link in soup.find_all('a'):
		print(link.get('href'))

#Holds tag from command line to determine program execution
opt = sys.argv[1]
#Holds locations if -j or -x are used for program execution
loc1 = ''
loc2 = ''

if opt == '-j':
	loc1 = sys.argv[2]
	loc2 = sys.argv[3]
	jSite(loc1, loc2)
	
elif opt == '-x':
	loc1 = sys.argv[2]
	loc2 = sys.argv[3]
	xSite(loc1, loc2)
	
elif opt == '-a':
	url = sys.argv[2]
	printA(url)
	

	