#!/usr/bin/env python

import requests

url = 'http://geo.groupkt.com/ip/161.45.162.200/json'
req = requests.get(url, headers={}, params={})

print("CONTENT:\n",req.content)
print()

jd = req.json()
print("JSON:\n",jd)
print(type(jd))
print()

from pprint import pprint

print("PRETTY JSON:")
pprint(jd)

print("POSTAL:\n", jd['RestResponse']['result']['postal'])
