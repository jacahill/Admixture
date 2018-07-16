### JAC July, 11 2012
###
### weighted_block_jackknife_0.1.py
###
### command line format
### python file.py d_stat_file block_size > output
###
### calculate the weighted block jackknife standard error of the D statistic.
### Input D statistic files generated by D_stat_0.6.py should be in the appropraite block size


### imports

import sys,os

### help!

if sys.argv[1] == "-h" or sys.argv[1] == "--help" or len(sys.argv) == 1:
	print "Insert help messege!"

### load files

file = open(sys.argv[1])
line = file.readline()
line = file.readline()
line = file.readline()


### vars

block_size = int(sys.argv[2])
auto_blocks = []
X_blocks = []


### defs

def f_calc(A,B,A2,B2):
	A=float(A)
	B=float(B)
	A2=float(A2)
	B2=float(B2)
	f=(A-B)/(A2-B2)
	return f

def knife(blocks):
	ABBA = 0
	BABA = 0
	ABBA2 = 0
	BABA2 = 0
	size = 0
	count = 0
	jack_ABBA = 0
	jack_BABA = 0
	jack_ABBA2 = 0
	jack_BABA2 = 0
	line_size = 0
	fhat = 0.0
	pre_i = []
	p_i = []
	weight = []
	p_dot = 0
	while count < len(blocks):
		ABBA += int(blocks[count][3])
		BABA += int(blocks[count][4])
		ABBA2 += int(blocks[count][5])
		BABA2 += int(blocks[count][6])
		size += ABBA + BABA + ABBA2 + BABA2
		count += 1
	count = 0
	fhat = f_calc(ABBA,BABA,ABBA2,BABA2)
	
	while count < len(blocks):
		jack_ABBA = ABBA - int(blocks[count][3])
		jack_BABA = BABA - int(blocks[count][4])
		jack_ABBA2 = ABBA2 - int(blocks[count][5])
		jack_BABA2 = BABA2 - int(blocks[count][6])
		jack_count = ABBA + BABA + ABBA2 + BABA2
		weight.append(float(jack_count)/float(size))
		fjack = f_calc(jack_ABBA,jack_BABA,jack_ABBA2,jack_BABA2)
		pre_i.append(fjack)
		count += 1
	count = 0
	while count < len(pre_i):
		tally = 0
		sum = 0.0
		while tally < len(pre_i):
			if tally != count:
				sum = sum + pre_i[tally]
			tally += 1
		p_i.append(sum)
		p_dot += sum
		count += 1
	p_dot = p_dot/count
	count = 0
	count = 0
	sigma = 0
	while count < len(p_i):
		sigma += weight[count]*((p_dot - p_i[count])**2)
		count += 1
	sigma = sigma*(count+1)
	sigma = (float((len(p_i) - 1))/float(len(p_i))) * sigma
	sigma = sigma**.5
	return sigma
		
### body



# filter down to useable blocks
while line:
	split = line.split("\t")
	if int(split[1])%block_size == 0:
		if split[0] == "scaffold20 " or split[0] == "scaffold100 " or split[0] == "scaffold105 " or split[0] == "scaffold113 " or split[0] == "scaffold115 " or split[0] == "scaffold122 " or split[0] == "scaffold134 " or split[0] == "scaffold141 " or split[0] == "scaffold167 " or split[0] == "scaffold170 " or split[0] == "scaffold179 " or split[0] == "scaffold184 ":
			X_blocks.append(split)
		else:
			auto_blocks.append(split)
	line = file.readline()
all_blocks = auto_blocks + X_blocks
out =  sys.argv[1] +"\t"+ str(knife(auto_blocks)) 
print out	

	

	
		
		
