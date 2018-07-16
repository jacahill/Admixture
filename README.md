# Admixture
Here we provide an example workflow for our admixutre scripts.
Code is provided as is and without warenty. 
These scripts have minimal dependencies and are written in either C++ (file suffix .cpp) or python (file suffix .py).

Basic Workflow:
0)
Compile the C++ code.

1) 
Generate Input data from bam files. 

For this pipeline you should have one fully filtered bam file per sample.
haploidize each bam file to a fasta. I use R. Ed Green's pu2fa program available here- https://github.com/Paleogenomics/Chrom-Compare
Usage: For each chromosome run:

samtools mpileup -s -f REF\_GENOME -q30 -Q60 -r CHROMOSOME BAMFILE.bam | \
pu2fa -c CHROMOSOME -C MAX\_COVERAGE > haploidized_fasta.fa

The very high basequality threshold "-Q60" is useful for minimizing the impact of sequencing error, but is generally only atainable via merging overlapping paired end reads.  For Single end data or Paired End data with few overlaps -Q30 or -Q40 will be more appropriate.

MAX\_COVERAGE is the 95th percentile of coverage across the genome. This is a useful filter because it will help to exclude regions of duplication and poor assembly that could bias your results.

Then concatenate all of the single chromosome fastas into a single fasta.

cat haploidized_fasta_scaffold*.fa > haploidized_fasta_all.fa


2) 
D-statistics.  
First decide whether to use the all sites version (suitable for most data) or the transversion only version (suitable for ancient DNA).

Then for each combination you want to test run:
Dstat P1_all.fa P2_all.fa P3_all.fa OG_all.fa 5000000 > P1_P2_P3_OG.dstat
   P1 and P2 are the two most closely related populations (eg African and Non-African human see Green et al. 2010)
   P3 is more distantly related and is hypothesized to have admixed with either P1 or P2 (eg. Neanderthal, see Green et al. 2010)
   OG is the outgroup, this should be distant enough to not have incomplete lineage sorting or admixture with P1,P2 or P3.  (eg. Chimp, see Green et al. 2010)
   5000000 is the output block size, this is used to calculate weighted block jackknife significance later. 5Mb is the recommended block size for most species however, if the reference genome N50 is < 5Mb and admixture is ancient smaller values can be used without negative impacts. If you are testing for very recent admixture you may wish to increase the block size above 5Mb to ensure it is larger than the longest non-recombined block.
   
To quantify the D-statistic values use the parser program:
python D-stat_parser.py P1_P2_P3_OG.dstat 1
  This emits:
  P1_P2_P3_OG.dstat Dstat ABBA BABA
  If Dstat > 0. P2 and P3 share an excess of derived alleles
  If Dstat < 0. P1 and P3 share an excess of derived alleles
  
  The second argument "1" is optional. It emits the results in 1 line format.  You can also print the results them with a header by not including the second argument but in general I find the method shown to be more useful.

Testing for statistical significance:
Use the weighted_block_jackknife_D.py program to measure the standard error.
python weighted_block_jackknfie_D.py P1_P2_P3_OG.dstat 5000000
  Give the program the dstat file and the block size.  It will then calculated the standard error.
  It will the  output filename and standard error.
  
  To determine whether your result is significant divide the result from the D-stat_parser by the weighted_block_jackknife_D result to get the Z-score.  Z-scores > 3 are generally considered significant.
  


