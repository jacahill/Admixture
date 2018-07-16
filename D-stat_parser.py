### This is for looking at the output of D_stat_0.6.py output files in order to determine 
### D statistic for the whole genome, the autosomes only and the X only


import sys, os



file = open(sys.argv[1])
line = file.readline()
line = file.readline()

split = line.split("\t")

ABBA = 0
BABA = 0
X_ABBA = 0
X_BABA = 0

while line:
#	if split[0] == "scaffold20 " or split[0] == "scaffold100 " or split[0] == "scaffold105 " or split[0] == "scaffold113 " or split[0] == "scaffold115 " or split[0] == "scaffold122 " or split[0] == "scaffold134 " or split[0] == "scaffold141 " or split[0] == "scaffold167 " or split[0] == "scaffold170 " or split[0] == "scaffold179 " or split[0] == "scaffold184 ":
#		X_ABBA = X_ABBA + int(split[3])
#		X_BABA = X_BABA + int(split[4])
	ABBA = ABBA + int(split[3])
	BABA = BABA + int(split[4])
	line = file.readline()
	split = line.split("\t")
	if len(split) < 3:
		break
	
#auto_ABBA = ABBA-X_ABBA
#auto_BABA = BABA-X_BABA
if len(sys.argv) == 2:
	print str(sys.argv[1])
	print "type\tDstat\tABBA\tBABA"
	print "whole genome", float(ABBA-BABA)/float(ABBA+BABA),  ABBA, BABA
#	print "X chromosome", float(X_ABBA-X_BABA)/float(X_ABBA+X_BABA), X_ABBA, X_BABA
#	print "autosome", float(auto_ABBA-auto_BABA)/float(auto_ABBA+auto_BABA), auto_ABBA, auto_BABA
else:
	out = str(sys.argv[1]) + "\t" +  str(float(ABBA-BABA)/float(ABBA+BABA)) + "\t" + str(ABBA) + "\t"+ str(BABA)
#	out = str(sys.argv[1]) + "\t" +  str(float(ABBA-BABA)/float(ABBA+BABA)) + "\t" +  str(float(X_ABBA-X_BABA)/float(X_ABBA+X_BABA)) + "\t" +  str(float(auto_ABBA-auto_BABA)/float(auto_ABBA+auto_BABA)) + "\t" + str(auto_ABBA) + "\t" + str(auto_BABA) + "\t" + str(X_ABBA) + "\t" + str(X_BABA)
	print out
