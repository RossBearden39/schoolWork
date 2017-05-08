#Ross Bearden
#CSCI 3038
#Dr. Butler
#p3mod.py
#Generator for reading and parsing a fasta file

def read_one_fasta_entry(f):
	#Intial Priming Read
	newLine = f.readline()
	firstLine = newLine.split(sep=' ')
	id = firstLine[0].strip('>') + '\n'
	dataStr = ''
	#reads through the whole file
	for line in f:
		#True when whole DNA value has been read
		if line[0] == '>':
			#this yields most of the results
			yield id, dataStr
			dataStr = ''
			id = '' 
			idLine = line.split(sep = ' ')
			id = idLine[0].strip('>') + '\n'
		else:
			#pieces together the DNA
			dataStr  = dataStr + line.rstrip('\n')
	#Yields the final DNA block in the file		
	yield id, dataStr