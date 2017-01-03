#!/usr/bin/python3

# --------------------------------------------------------------------------------------------------------------
# 	File:    a4.py
#	Author:  Mathieu Vu-Noreau (0884903)
# 	Date:     10/10/2016
#	Course:   CIS*2750 - Software System Dvlmt & Intgrn
#
#	Summary of File: 
# 
#   	Receives fifo from c program, and adds html tags to the file, <html>,<title>,<body>
#		also reads the file related to html file, <filename>.info, if found adds the styles to the strings
#		once styles added, opens fifo and sends file back to c for printing 
# --------------------------------------------------------------------------------------------------------------

import os, sys, re
import os.path


filename = "myfifo"
#opening pipe created in c
pipe = open(filename, "r")
#reading strings from fifo
with pipe as f:
	lines = [line.rstrip('\n') for line in pipe]
pipe.close()
#removing file after reading strings into array
os.remove(filename)
infoFile = lines[0] + ".info"
#only used first line to hold filename, I therefore deleted the string after it was used for its prupose
#inserting html tags <html>,<title>,<body>
lines.insert(1,'<BODY>')
lines.insert(0,'<TITLE>')
lines.insert(2,'</TITLE>')
lines.insert(0,'<HEAD>')
lines.insert(0,'<HTML>')
lines.insert(5,'</HEAD>') 
lines.append('</BODY>')
lines.append('</HTML>')


if os.path.isfile(infoFile):
	stylingFile = open(infoFile,"r")
	#reads styling file and checks if there are similar strings in array
	with stylingFile as f:
		content = [line.rstrip('\n') for line in stylingFile]
		for string in content:
			for line in lines:
				loc = lines.index(line)
				if string:
					if (string[2:] in line):
						style = string[0]
						#if found in string, sub only whole words, and add style reference from <filename.info>
						lines[loc] = re.sub(r"\b%s\b" % string[2:], '<' + style + '>' + string[2:] + "</" + style + '>', line)
#makes new fifo for new strings with html tags
os.mkfifo(filename)
filename = "myfifin"
fileout = open(filename,"w")
#writes string to file
for content in lines:
 	fileout.write(content)
fileout.close()


