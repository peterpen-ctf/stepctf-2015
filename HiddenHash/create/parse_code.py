#!/usr/bin/python
import sys
from re import *
from scipy.fftpack import *

def getNum(s_num):
	tk = findall(r'\S\S',s_num)
	ssum=0
	for i in range(len(tk)):
		cc = int(tk[len(tk)-i-1],16)
		ssum = (ssum << 8) + cc
	return ssum
def getProcCode(fn,fname):
	ff = open(fn,"r")
	seq=[]
	start=0
	for line in ff:
		if (fname in line) and ("ENDP" in line):
			start = 0
		if start == 1:
			if line[0] == ';':
				continue
			data = findall(r'\S{5}\s+(.+?)\t',line)
			print fname,"! ",data,hex(getNum(data[0]))
			seq.append(getNum(data[0]) * 1.0)

		if (fname in line) and ("PROC" in line):
			start = 1
	ff.close();
	return seq

start = 0
seq1 = getProcCode(sys.argv[1],"hash1")
seq2 = getProcCode(sys.argv[1],"hash2")
seq1=seq1[6:-5]
seq2=seq2[6:-5]
print seq1
print seq2

dseq1 = dct(seq1,1)
dseq2 = dct(seq2,1)
print seq1
print "double q1 [] = {"+",".join(map(str,dseq1))+"};"
print "unsigned int q1_len = %d;" % len(dseq1)
print map(lambda x:round(x/(2.0*(len(seq1)-1))),idct(dseq1,1))
print seq2
print "double q2 [] = {"+",".join(map(str,dseq2))+"};"
print "unsigned int q2_len = %d;" % len(dseq2)
print map(lambda x:round(x/(2.0*(len(seq2)-1))),idct(dseq2,1))


