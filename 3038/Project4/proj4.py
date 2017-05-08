#Ross Bearden
#CSCI 3038
#Project 4
import sys
import re
import multiprocessing as mp
#import time as t

#Pulled from p4starter.py file
#Searches two strings for the longest common substring
def lcs(S,T):
    m = len(S)
    n = len(T)
    counter = [[0]*(n+1) for x in range(m+1)]
    longest = 0
    lcs_set = set()
    for i in range(m):
        for j in range(n):
            if S[i] == T[j]:
                c = counter[i][j] + 1
                counter[i+1][j+1] = c
                if c > longest:
                    lcs_set = set()
                    longest = c
                    lcs_set.add(S[i-c+1:i+1])
                elif c == longest:
                    lcs_set.add(S[i-c+1:i+1])

    return lcs_set
    
   
#Need definition for the spawned processes
#Should take a subset of the total inputs and possible then range of those values
def doWork(start,stop,q,data):
	longest = 0
	#Holds list positions for two strings with longest common substring
	seq1 = 0
	seq2 = 0
	for i in range(start,stop):
		currStr= data[i]
		
		for j in range(len(data)):
			if i != j:
				subStr = lcs(currStr, data[j])
				length = subStr.pop()
				if (len(length)) > longest:
					longest = len(length)
					seq1 = i
					seq2 = j
	q.put([longest, seq1, seq2])

    
#Main code
#Opens file and reads the file into a list seperated at the new lines
with open(sys.argv[2]) as fileIn:
	input = fileIn.readlines()
#Splitting the input into a list of ids and sequences
seqList = []
idList = []
for i in range(len(input)):
	newLine = re.split(r'[\s|\t]\s*', input[i])
	idList.append(newLine[0])
	seqList.append(newLine[1])
	
#Creates a process id list and a queue to store process results
process = []
q = mp.Queue()
numProc = int(sys.argv[1])
#determine chunk size
chunkSize = int(len(input)/numProc)

for i in range(numProc):
	start = i*chunkSize
	stop = (i+1)*chunkSize
	#Create process with target doWork function
	p = mp.Process(target = doWork, args=(start,stop,q,seqList))
	process.append(p)
#Start processes
#startTime = t.time()
for p in process:
	p.start()
	
#Join processes back
for p in process:
	p.join()

#Determine longest substring in whole file
#print("%0.4f" % (t.time() - startTime))
check = []
longest = 0
seq1 = 0
seq2 = 0
for p in process:
	check = q.get()
	if check[0] > longest:
		longest = check[0]
		seq1 = check[1]
		seq2 = check[2]
		
print(longest, ' ', idList[seq1], ' ', idList[seq2])	





	