 /** 
  * File:    a3.c
  * 
  * Author:  Mathieu Vu-Noreau (0884903)
  * Date:     10/10/2016
  * Course:   CIS*2750 - Software System Dvlmt & Intgrn
  * 
  * Summary of File: 
  * 
  *   Runs listio library, takes input from command file ./a2 <filename> and translates it into HTML format
  *   if not HTML file is found, if it is found, prints it to stdout, if it isnt found, formats the file
  *   and prints to stdout but does not format the file
  */ 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "listio.h"

int main(int argc, char *argv[]){	
	int numberReturn;
	int c;
	char *filename = malloc((sizeof(char)) * (strlen(argv[1]) + strlen(".html")));
	if (filename == NULL){
		printf("not enough memory...\nexiting program\n");
		return 1;
	}
	//adds .html after filename to search for <filename>.html
	strcpy(filename,argv[1]);
	strcat(filename,".html");
	FILE *file = fopen(filename, "r");
	if (file != NULL) {
		printf("file found, attempting to print..\n");
		while ((c = getc(file)) != EOF)
			putchar(c);
		fclose(file);
	}
	else{
		printf("html file not found, searching for plaintext\n");
		file = fopen(argv[1], "r");
		if (file != NULL)
		{
			printf("FOUND plaintext\n");
			char buffer[4096];
			struct returnStruct *returnVal = malloc(sizeof(struct returnStruct));
			if (returnVal == NULL){
				printf("not enough memory\n program exiting..\n");
				return 1;
			}
			*returnVal = buildHeader();	
			if (returnVal->value == FAILURE){
				printf("buildheader failed...\nexiting program.\n");
				return 1;
			}
			numberReturn = setName(returnVal->header, argv[1]);
			if (numberReturn == FAILURE){
					printf("setName failed...\nexiting program.\n");
					return 1;
			}
			while (fgets(buffer, sizeof(buffer), file) != NULL)
			{
				//removing newline character created by fgets
				 if (buffer[strlen(buffer)] == '\n') {
				 	buffer[strlen(buffer)] = '\0';
				}
				numberReturn = addString(returnVal->header,buffer);
				if (numberReturn == FAILURE){
					printf("addString failed...\nexiting program.\n");
					return 1;
				}
			}
			if (feof(file))
			{
				printf("end of file\n");
			}
			else
			{
				printf("interrupted end of file\n");
			}
			fclose(file);
			//process strings and send to pyhton fifo
			numberReturn = processStrings(returnVal->header);
			if (numberReturn == FAILURE){
				printf("setName failed...\nexiting program.\n");
				return 1;
			}
			numberReturn = freeStructure(returnVal->header);
			if (numberReturn == FAILURE){
				printf("setName failed...\nexiting program.\n");
				return 1;
			}
			//printing new fifo file and deleting it
			FILE *file = fopen("myfifin", "r");
			while ((c = getc(file)) != EOF)
			 	putchar(c);
			fclose(file);
			int fileRename = rename("myfifin",filename);
			if (fileRename == 0){
				return 1;
				printf("file renamed failed\n");
			}
		}
		else{
			printf("file not found\n exiting program..\n");
		}
	}
	free(filename);
	return 0;
}
