#Ross Bearden
#CSCI 3038
#Ralph Butler
#Project 2

import sys

#Open file
fileIn = open(sys.argv[1])

#Loop to read through file line by line
for line in fileIn:
    line.strip()
    newLine = line.split()
    newLine[1] = newLine[1].lower()
    sequence = newLine[1]
    for i in range(len(sequence)):
        if sequence[i:i+3] == "atg" or sequence[i:i+3] == "gtg":
            for j in range(i+3, i+99, 3):
                if sequence[j:j+3] == "tag": 
                    if(j+3)-i >= 33:
                        print(newLine[0], i, ((j+3)-i), sequence[i:i+3], sequence[j:j+3])
                break
                