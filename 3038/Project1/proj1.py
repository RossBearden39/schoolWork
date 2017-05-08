#Ross Bearden
#CSCI 3038
#Ralph Butler
#Project 1

import math
import sys
import random

ndarts = int(sys.argv[1])
inCircle = 0

for i in range(ndarts):
	x = random.random()
	y = random.random()
	if (math.sqrt((x*x +y*y))) <= 1:
		inCircle += 1

print("pi estimate = ", 4*(inCircle/ndarts))	

	
	