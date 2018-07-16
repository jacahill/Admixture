/*
Rauf Salamzade
DATE - 07/03/13
PROGRAM NAME - D_stat_0.6.cpp
DESCRIPTION - C++ implementation of D_stat_0.6.py by James Cahill
""
This version is for fasta files, they should be aligned and ordered correctly 

If you want to calculate this D stat: D(Indiv1,Indiv2,Admix,OG)
Input is as follows:
python D_stat_0.5.py Indiv1.fa Indiv2.fa Admix.fa OG.fa block_size > D_I1_I2_Ad_OG.dstat
""
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

/* Example Run For Edser:

./D_stat_0.6 \
/mnt/tank/projects/bears_asymetric_hybridization/fastas_30/Den_all.fa \
/mnt/tank/projects/bears_asymetric_hybridization/fastas_30/Swe_all.fa \
/mnt/tank/projects/bears_asymetric_hybridization/fastas_30/WH1_all.fa \
/mnt/tank/projects/bears_asymetric_hybridization/fastas_30/Uam_all.fa \
1000 \
> ABBA_BABA_Den_Swe_WH1_Uam.out

*/

string scaffoldName(string val) {
	string result;
	for (int i=0; i < val.length(); i++) {
		if (i != 0) {
			result += val.at(i);
		}
		i++;
	}
	return result;
}

string doubleToString(double val) {
	string result;
	ostringstream convertd;
	convertd << val;
	result = convertd.str();
	return result;
}

string integerToString(int val) {
	string result;
	ostringstream convert;
	convert << val;
	result = convert.str();
	return result;
}

int main (int argc, char* argv[]) {
if ( argv[1]==NULL ) {
	cerr << "ERROR: Incorrect number of arguments provided" << endl;
	return 1;
}	
else if ( (argv[1][0]=='-' && argv[1][1]=='h') || (argv[1][0]=='-' && argv[1][1]=='-' && argv[1][2]=='h') ) { 
	cout << "Input format:" << endl;
	cout << "./a.out same_spp_1 same_spp_2 admix_spp outgroup_spp block_size" << endl;
	cout << "all input files should be aligned fastas generated with pu2fa by Ed Green" << endl;
	cout << "block_size should be an integer measured in bases" << endl;		
	return 0;
}
else if ( argv[1]==NULL || argv[2]==NULL || argv[3]==NULL || argv[4]==NULL || argv[5]==NULL ) {
	cerr << "ERROR: Incorrect number of arguments provided" << endl;
	return 1;
}
else {
  ifstream file1;
  ifstream file2;
  ifstream adfile;
  ifstream adfile2;
  ifstream ogfile;
  file1.open (argv[1]);
  file2.open (argv[2]);
  adfile.open (argv[3]);
  adfile2.open (argv[4]);
  ogfile.open (argv[5]);
  istringstream ss(argv[6]);
  int block;
  if (!(ss >> block)) {
  	cerr << "Invalid block argument: " << argv[5] << '\n';
  	return 1;
  }
  string scaffold = "";
  int ABBA1 = 0;
  int BABA1 = 0;
  int ABBA2 = 0;
  int BABA2 = 0;
  int total = 0;
  int count = 0;
  int counter = 0;
  
  string line1;
  string line2;
  string line3;
  string line4;
  string line5;
  string last1;
  string last2;
  string adlast;
  string adlast2;
  string oglast;
  
  cout << "scaffold\tend_block\tf_hat\tABBA1\tBABA1\tABBA2\tBABA2" << endl;
  //cout << "scaffold1\t0\t0\t0\t0\t0\t0\t0\t0\t0\t0\t0\t0\t0\t0\t0\t0\t0" << endl;
  
  if ( file1.is_open() && file2.is_open() && adfile.is_open() && adfile2.is_open() && ogfile.is_open() ) {
    while ( file1.good() && file2.good() && adfile.good() && adfile2.good() && ogfile.good() ) {
    	if (counter == 0) { 
		getline (file1,line1);
    		getline (file2,line2);
    		getline (adfile, line3);
    		getline (adfile2, line4);
    		getline (ogfile, line5);
    	}	
    	
	if ( line1.find(">") == 0 || line2.find(">") == 0 || line3.find(">") == 0 || line4.find(">") == 0 || line5.find(">") == 0) { 
		if (counter != 0) {
			if ( (ABBA2+BABA2) != 0) {
				string out = scaffold.substr(1) + "\t" + integerToString(total) + "\t" +  doubleToString( ( (double)ABBA1-(double)BABA1 ) / ( (double)ABBA2-(double)BABA2 ) ) + "\t" + integerToString(ABBA1) + "\t" +  integerToString(BABA1) + "\t" + integerToString(ABBA2) + "\t" +  integerToString(BABA2);
				cout << out << endl;
			} else {
				string out = scaffold.substr(1) + "\t" + integerToString(total) + "\t" + "0" + "\t" + integerToString(ABBA1) + "\t" +  integerToString(BABA1) + "\t" + integerToString(ABBA2) + "\t" +  integerToString(BABA2);
				cout << out << endl;
			}
		}
		total=0;
		
		while ( line1.find(">") != 0 ) {
			getline(file1,line1);
		}
		while ( line2.find(">") != 0 ) {
			getline(file2,line2);
		}
		while ( line3.find(">") != 0 ) {
			getline(adfile,line3);
		}
		while ( line4.find(">") != 0 ) {
			getline(adfile2,line4);
		}
		while ( line5.find(">") != 0 ) {
			getline(ogfile,line5);
		}
		if ( (line1.compare(line2)!=0) or (line1.compare(line3)!=0)  or (line1.compare(line4)!=0) or (line2.compare(line3)!=0) or (line2.compare(line4)!=0) or (line3.compare(line4)!=0) ) {
			cout << "ERROR: FASTA files do not have scaffolds in the same order" << endl;
			return(1);
		}
			
		scaffold = line1;
		ABBA1 = 0;
		BABA1 = 0;
		ABBA2 = 0;
		BABA2 = 0;
		last1 = "";
		last2 = "";
		adlast = "";
		adlast2 = "";
		oglast = "";
		for(int i = 0 ; i < line1.length() ; i++) {
			last1 += line1[i];
			last2 += line2[i];
			adlast += line3[i];
			adlast2 += line4[i];
			oglast += line5[i];
		}
    		getline (file1,line1);
    		getline (file2,line2);
    		getline (adfile, line3);
    		getline (adfile2, line4);
    		getline (ogfile, line5);
		count = 0;
    	}
	else {
		if ( (last1.length() == last2.length()) && (last1.length() == adlast2.length()) && (last1.length() == adlast.length()) && (last1.length() == oglast.length()) ) {
			while ( (count < line1.length()) && (count < line2.length()) && (count < line3.length()) && (count < line4.length()) ) {
				total++;
				if ( line1[count]!='N' && line2[count]!='N' && line3[count]!='N' && line4[count]!='N' && line5[count]!='N') {
					if ( line1[count]==line5[count] && line2[count]!=line5[count]) {
						if ( line2[count]==line4[count] ) {
							if (line1[count]=='A' and line2[count]=='C') {
								ABBA1++;
							} else if (line1[count]=='A' and line2[count]=='T') {
								ABBA1++;
							} else if (line1[count]=='C' and line2[count]=='A') {
                                               			ABBA1++;
                                                	} else if (line1[count]=='C' and line2[count]=='G') {
                                                        	ABBA1++;
                                                	} else if (line1[count]=='G' and line2[count]=='C') {
                                                        	ABBA1++;
                                                	} else if (line1[count]=='G' and line2[count]=='T') {
                                                        	ABBA1++;
                                                	} else if (line1[count]=='T' and line2[count]=='A') {
                                                        	ABBA1++;
                                                	} else if (line1[count]=='T' and line2[count]=='G') {
                                                        	ABBA1++;                                                       
							}
						}
					}
					if ( line1[count]!=line5[count] && line2[count]==line5[count]) {
						if ( line1[count]==line4[count] ) {
							if (line1[count]=='A' and line2[count]=='C') {
                                                                BABA1++;
                                                        } else if (line1[count]=='A' and line2[count]=='T') {
                                                                BABA1++;
                                                        } else if (line1[count]=='C' and line2[count]=='A') {
                                                                BABA1++;
                                                        } else if (line1[count]=='C' and line2[count]=='G') {
                                                                BABA1++;
                                                        } else if (line1[count]=='G' and line2[count]=='C') {
                                                                BABA1++;
                                                        } else if (line1[count]=='G' and line2[count]=='T') {
                                                                BABA1++;
                                                        } else if (line1[count]=='T' and line2[count]=='A') {
                                                                BABA1++;
                                                        } else if (line1[count]=='T' and line2[count]=='G') {
                                                                BABA1++;
                                                        }
						}
					}
					if ( line1[count]==line5[count] && line3[count]!=line5[count]) {
						if ( line3[count]==line4[count] ) {
							if (line1[count]=='A' and line3[count]=='C') {
                                                                ABBA2++;
                                                        } else if (line1[count]=='A' and line3[count]=='T') {
                                                                ABBA2++;
                                                        } else if (line1[count]=='C' and line3[count]=='A') {
                                                                ABBA2++;
                                                        } else if (line1[count]=='C' and line3[count]=='G') {
                                                                ABBA2++;
                                                        } else if (line1[count]=='G' and line3[count]=='C') {
                                                                ABBA2++;
                                                        } else if (line1[count]=='G' and line3[count]=='T') {
                                                                ABBA2++;
                                                        } else if (line1[count]=='T' and line3[count]=='A') {
                                                                ABBA2++;
                                                        } else if (line1[count]=='T' and line3[count]=='G') {
                                                                ABBA2++;
                                                        }
                                                
						}
					}
					if ( line1[count]==line4[count] && line4[count]!=line5[count]) {
						if ( line3[count]==line5[count] ) {
							if (line1[count]=='A' and line3[count]=='C') {
                                                                BABA2++;
                                                        } else if (line1[count]=='A' and line3[count]=='T') {
                                                                BABA2++;
                                                        } else if (line1[count]=='C' and line3[count]=='A') {
                                                                BABA2++;
                                                        } else if (line1[count]=='C' and line3[count]=='G') {
                                                                BABA2++;
                                                        } else if (line1[count]=='G' and line3[count]=='C') {
                                                                BABA2++;
                                                        } else if (line1[count]=='G' and line3[count]=='T') {
                                                                BABA2++;
                                                        } else if (line1[count]=='T' and line3[count]=='A') {
                                                                BABA2++;
                                                        } else if (line1[count]=='T' and line3[count]=='G') {
                                                                BABA2++;
                                                        }
                                                
						}
					}
				}
				if ( total%block==0 ) {
   					if ( (ABBA2+BABA2) != 0 ) {
  						string out = scaffold.substr(1) + "\t" + integerToString(total) + "\t" +  doubleToString( ( (double)ABBA1-(double)BABA1 ) / ( (double)ABBA2-(double)BABA2 ) ) + "\t" + integerToString(ABBA1) + "\t" +  integerToString(BABA1) + "\t" + integerToString(ABBA2) + "\t" +  integerToString(BABA2);
						cout << out << endl;
    					} else {
						string out = scaffold.substr(1) + "\t" + integerToString(total) + "\t" +  "0" + "\t" + integerToString(ABBA1) + "\t" +  integerToString(BABA1) + "\t" + integerToString(ABBA2) + "\t" +  integerToString(BABA2);
						cout << out << endl;
    					}
					ABBA1 = 0;
					BABA1 = 0;
					ABBA2 = 0;
					BABA2 = 0;
				}
				count++;
			}
		} else {
			cout << "ERROR: FASTA file lines should be of equal length" << endl;
			return(1);
		}	
		count = 0;
		last1 = "";
		last2 = "";
		adlast = "";
		adlast2 = "";
		oglast = "";
		for(int i = 0 ; i < line1.length() ; i++) {
			last1 += line1[i];
			last2 += line2[i];
			adlast += line3[i];
			adlast2 += line4[i];
			oglast += line5[i];
		}
    		getline (file1,line1);
    		getline (file2,line2);
    		getline (adfile, line3);
    		getline (adfile2, line4);
    		getline (ogfile, line5);
	}
        counter++;
    }
    if ( (ABBA2+BABA2) != 0  ) {
  	string out = scaffold.substr(1) + "\t" + integerToString(total) + "\t" +  doubleToString( ( (double)ABBA1-(double)BABA1 ) / ( (double)ABBA2-(double)BABA2 ) ) + "\t" + integerToString(ABBA1) + "\t" +  integerToString(BABA1) + "\t" + integerToString(ABBA2) + "\t" +  integerToString(BABA2);
	cout << out << endl;
    } else {
	string out = scaffold.substr(1) + "\t" + integerToString(total) + "\t" + "0" + "\t" + integerToString(ABBA1) + "\t" +  integerToString(BABA1) + "\t" + integerToString(ABBA2) + "\t" +  integerToString(BABA2);
	cout << out << endl;
    }
    file1.close();
    file2.close();
    adfile.close();
    adfile2.close();
    ogfile.close();
  }  
  else {
  	cout << "ERROR: Unable to open file(s)" << endl; 
  }
  return 0;
  }
}
