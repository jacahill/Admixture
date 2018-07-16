


import sys,os


file = open(sys.argv[1])
line = file.readline()
line = file.readline()
line = file.readline()

ABBA1 = 0
BABA1 = 0
ABBA2 = 0
BABA2 = 0

ABBA1_X = 0
BABA1_X = 0
ABBA2_X = 0
BABA2_X = 0

count = 0

X = ["scaffold20","scaffold100","scaffold105","scaffold113","scaffold115","scaffold122","scaffold134","scaffold141","scaffold167","scaffold170","scaffold179","scaffold184","scaffold_overflow_hack"]

while line:
	line = line.replace(" ", "")
	split = line.split("\t")
	#print split
	ABBA1 = ABBA1 + int(split[3])
	BABA1 = BABA1 + int(split[4])
	ABBA2 = ABBA2 + int(split[5])
	BABA2 = BABA2 + int(split[6][:-1])
	if split[0] == X[count + 1]:
		count = count + 1
		im = 1
	if split[0] == X[count]:
		#print im
		ABBA1_X = ABBA1_X + int(split[3])
		BABA1_X = BABA1_X + int(split[4])
		ABBA2_X = ABBA2_X + int(split[5])
		BABA2_X = BABA2_X + int(split[6][:-1])
	line = file.readline()
	im = 0
if len(sys.argv) == 2:	
	print sys.argv[1], float(ABBA1-BABA1)/float(ABBA2-BABA2)

if len(sys.argv) > 2:
	print ABBA1, BABA1, ABBA2, BABA2
	print ABBA1_X, BABA1_X, ABBA2_X, BABA2_X
	print ABBA1-ABBA1_X, BABA1-BABA1_X, ABBA2-ABBA2_X, BABA2-BABA2_X
