 /** 
  * File:    listio.c
  * 
  * Author:  Mathieu Vu-Noreau (0884903)
  * Date:     10/10/2016
  * Course:   CIS*2750 - Software System Dvlmt & Intgrn
  * 
  * Summary of File: 
  * 
  *   Builds a system which stores strings in a linked structure.
  *   writes strings to structure and removes redundant whitespace
  *   characters and format them into HTML tags. The strings can be stored
  *   and retrieved from binary files. 
  * 
  */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "python2.7/Python.h"

#define SUCCESS 1
#define FAILURE 0


struct dataHeader {
    char *name;
    int length;
    struct dataString *next;
};

struct dataString {
    char *string;
    struct dataString *next;
};
struct returnStruct {
    int value;
    struct dataHeader *header;
};

/*-----------------------stringCombine-------------------------------
|  Function: void stringCombine(char *string1, char *string2, int position)
|
|  Purpose: inserts the second string parameter(string2) into the first 
|           string parameter(string1) at the given location (position).
|
|  Parameters:
|       char *string1 (IN/OUT) -- This parameter represents the first string to be manipulated
|                                 and added onto.
|       char *string2 (IN)     -- This parameter represents the string being 
|                                 added into the first string
|       int position (IN)      -- This parameter represents the location at which string2 will be 
|                                 added into string1
|
|  Returns: the combination of both string2 into string1 at the n-th position of the string 
|           (represented by position)
*-------------------------------------------------------------------*/
void stringCombine(char *string1, char *string2, int position)
{
    char *stringPart1, *stringPart2;
    int length;
    int c;
    length = strlen(string1);
    
    stringPart1 = malloc(position);
    stringPart2 = malloc(length-position+2);

    /*recreating the string before position(parameter :position)*/
    for (c=0; c < position - 1; c++){
        *(stringPart1+c) = *(string1+c);
    }
    *(stringPart1+c) = '\0';

    /*recreating the string after position(parameter :position)*/
    for (c=0; c <= length-position; c++){
        *(stringPart2+c) = *((string1+position-1)+c);
    }
    *(stringPart2+c) = '\0';

    /*string manipulation to add the string:
        -clear string
        -add first part of string
        -add string2(parameter 2)
        -add string part 2
    */
    strcpy(string1, "");
    strcat(string1, stringPart1);
    free(stringPart1);
    strcat(string1, string2);
    strcat(string1, stringPart2);
    free(stringPart2);
}

/*-----------------------getName-------------------------------------
|  Function: char * getName(struct dataHeader *header)
|
|  Purpose: Used to get the name of the structure
|
|  Parameters:
|       struct dataHeader *header (IN) -- this parameter represents the head of the struct,
|                                         it is used to point to its name element.
|
|  Returns: the name of the list.
*-------------------------------------------------------------------*/
char * getName(struct dataHeader *header){
    if ((header == NULL) || (header->name == '\0')){
        return '\0';
    }
    else{
        return header->name;
    }
}

/*-----------------------setName-------------------------------------
|  Function: int setName(struct dataHeader *header, char *name)
|
|  Purpose: used to set the name of the structure
|
|  Parameters:
|       struct dataHeader *header (IN) -- the header for where to allocate the name
|       char *name                (IN) -- the name being allocated as the structure name
|
|Returns: FAILURE (0) if function failed to malloc or string is empty, SUCCESS(1) if all is 
|         well and name is set
*-------------------------------------------------------------------*/
int setName(struct dataHeader *header, char *name){
    if ((header == NULL) || (name == '\0')){
        return FAILURE;
    }
    char *string = malloc(sizeof(char) * strlen(name) +1);
    if(string == NULL){
        return FAILURE;
    }
    strcpy(string,name);
    header->name = string;
    return SUCCESS;
}

/*-----------------------buildHeader-------------------------------------
|  Function: struct returnStruct buildHeader()
|
|  Purpose: Used to build the base of the structure
|
|  Parameters:
|       struct dataHeader *header (IN) -- the header for where to allocate the name
|       char *name                (IN) -- the name being allocated as the structure name
|
|  Returns: FAILURE (0) in returnStruct.value if function failed the malloc to build the header, SUCCESS(1) in returnStruct.value if all is 
|         well and the header is built and initalized
*-------------------------------------------------------------------*/
struct returnStruct buildHeader(){
    struct returnStruct returnVal;
    struct dataHeader *header = malloc(sizeof(struct dataHeader));
    if (header == NULL) { 
       returnVal.value = FAILURE;
       return returnVal;
   }
   returnVal.value = SUCCESS;
   header->name=NULL;
   header->length=0;
   header->next=NULL;
   returnVal.header = header;
   return returnVal;
}

/*-----------------------getLength-------------------------------------
|  Function: int getLength(struct dataHeader *header)
|
|  Purpose: get the length of the structure, found in the header of the structure
|
|  Parameters:
|       struct dataHeader *header (IN) -- given the header in which is stored the length
|
|  Returns: FAILURE (0) if the header passed into the function is non existant or corrupted, 
| 			returns the length of the header name if all is well 
*-------------------------------------------------------------------*/
int getLength(struct dataHeader *header){
    if (header == NULL)
    {
        return FAILURE;
    } 
    return header->length;
}

/*-----------------------addString-------------------------------------
|  Function: int addString(struct dataHeader *header, char *str)
|
|  Purpose: adds a new dataString to the linked structure every time the function is called. 
|           The new string is stored in the string pointer within the dataString struct.
|
|  Parameters:
|       struct dataHeader *header (IN) -- given the header in which the structure can be traversed
|       char *str                 (IN) -- The *str character string contains the string to store in the dataString struct.
|
|  Returns: FAILURE (0) if the header passed into the function is non existant or corrupted or if the string is null, 
| 			returns the length of the header name if all is well and string added
*-------------------------------------------------------------------*/
int addString(struct dataHeader *header, char *str){
    char *newString = malloc(sizeof(char) * strlen(str)+1);
    struct dataString *newNode = malloc(sizeof(struct dataString));
    if (header == NULL) { 
        return FAILURE;
    }
    strcpy(newString,str);
    newNode->string = malloc(sizeof(newString));
    if (newNode->string == NULL)
    {
        return FAILURE;
    }    
    newNode->string = newString;
    newNode->next = NULL;
    if (header->next == NULL){
        header->next = newNode;
    }
    else{
        struct dataString * current = header->next;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    return SUCCESS;
}

/*-----------------------printString-------------------------------------
|  Function: int printString(struct dataHeader *header)
|
|  Purpose: prints the strings found in the structure
|
|  Parameters:
|       struct dataHeader *header (IN) -- given the header in which the structure can be traversed for printing
|
|  Returns: Returns: FAILURE (0) if the header passed into the function is non existant or corrupted, 
| 			returns the length of the header name if all is well and all strings are printed
*-------------------------------------------------------------------*/
int printString(struct dataHeader *header){
    if (header == NULL)
    {
        return FAILURE;
    }
    struct dataString * current = header->next;
    while (current != NULL) {
        printf("%s",current->string);
        if(current->next == NULL)
        {
            break;
        }
        current = current->next;
    }
    return SUCCESS;
}

/*-----------------------processString-------------------------------------
|  Function: int processStrings(struct dataHeader *header)
|
|  Purpose: modifies the characters space, tab, newline, carriage return contained within the strings of the structure.
|           Multiple spaces are reduced to a single space and the string is shortened by the number of spaces removed.
|           Multiple tabs are replaced with a single tab and the string is shortened by the number of tabs removed.
|           A single newline character or a single carriage return is replaced with the string <BR>.
|           Two or more newline characters are replaced with the string <P>. Two or more carriage return characters are replaced with the string <P>.
|           Any combination of newlines and carriage returns is replaced by the string  <P>.
|           this string calculates the length of the total structure strings andupdates the head
|			if two <P> tags are found back to back with newlines and carraige returns, remove the preceding <P> tag
|  
|   Parameters:
|       struct dataHeader *header (IN) -- given the header in which the structure can be traversed to process its string
|
|  Returns: FAILURE (0) if the header passed into the function is non existant or corrupted, or a malloc does not have enough memory allocation 
| 			returns the length of the header name if all is well and string has been processed
*-------------------------------------------------------------------*/
int processStrings(struct dataHeader *header){
    if (header == NULL)
    {
        return FAILURE;
    }
    struct dataString * current = header->next;
    struct dataString * previous = header->next;
    header->length=0;
    /*traverses structure so that each string is processed*/
    while (current != NULL)
    {
        char *newstring= malloc(sizeof(char) * strlen(current->string)+1);
        if (newstring == NULL)
        {
            return FAILURE;
        }
        strcpy(newstring,current->string);
        int i=0;
        int j=0;

        int n= strlen(current->string);
        /*traverses string by chaacter and modifies the string for spaces, tabs, newlinecharacters or carriage returns*/
        while (i < n)
        {
            /******************************MULTIPLE SPACES*************************************/
            /*if two spaces are found in a row, remove a space and moves every character down one array spot*/
            if(newstring[i]==' ' && (newstring[i+1]==' ' || newstring[i-1]==' '))
            {
                for(j=i;j<n;j++)
                    newstring[j]=newstring[j+1];
                n--;
            }
            /******************************MULTIPLE TABS*************************************/
            /*if two tabs are found in a row, remove a tab and moves every character down one array spot*/
            else if(newstring[i]=='\t' && (newstring[i+1]=='\t' || newstring[i-1]=='\t'))
            {
                for(j=i;j<n;j++)
                    newstring[j]=newstring[j+1];
                n--;
            }
            /******************************SINGLE NEWLINE OR CR******************************/
            /*if a single newline or carriage return is found, remove the character and replace with <BR>*/
            else if((newstring[i]=='\n' || newstring[i]=='\r') && (newstring[i+1]!='\n' && newstring[i-1]!='\n' && newstring[i+1] !='\r' && newstring[i-1] !='\r'))
            {
                for (j=i; j<n-1; j++)
                    newstring[j]=newstring[j+1];
                n--;
                newstring[j]='\0';
                char *str2="<BR>";

                newstring=realloc(newstring,(strlen(str2)+1 + strlen(newstring)) * sizeof(char));
                if (newstring == NULL){
                    return FAILURE;
                }
                stringCombine(newstring, str2, i+1);   
                i=i+4;
                n=n+4;  
            }
            /******************************MULTIPLE NEWLINE OR CR******************************/
            /*if multiple carriage return or newline characters found, remove the characters until no more are found in a row
            then add the characters <P>*/
            else if((newstring[i]=='\n' || newstring[i]=='\r') && (newstring[i+1]=='\n' || newstring[i-1]=='\n' || newstring[i+1] =='\r' || newstring[i-1] =='\r'))
            {
                while(newstring[i] == '\n' || newstring[i] == '\r')
                {
                    for (j=i; j<n-1; j++)
                        newstring[j]=newstring[j+1];
                    n--;
                    if(i == n){
                        break;
                    }

                }
                newstring[j]='\0';
                char *str3="<P>";
                newstring=realloc(newstring,(strlen(str3)+1 + strlen(newstring)) * sizeof(char));
                if (newstring == NULL){
                    return FAILURE;
                }
                stringCombine(newstring, str3, i+1);
                i=i+3;
                n=n+3;
            }
            else
            {
                i++;
            }
        }
        free(current->string);
        current->string = newstring;
        header->length=header->length + i;
        current = current->next;
    }
    current = header->next; 
    //checking for previous <p> tag
    while(current != NULL){
        if (current->next == NULL){
            break;
        } 
        previous = current;
        current = current->next;       
        int n = strlen(previous->string)-1;
        //checks last characters for spaces or tabs, if tabs or space keep going until found non space or tab character
        while ((previous->string[n]) == ' ' || (previous->string[n] == '\t')){
            n--;
        }
        int x = 0;
        while ((current->string[x]) == ' ' || (current->string[x] == '\t')){
            x++;
        }
        //if characters before spaces or tabs are <P> then remove all characters after the <P> tag in the previous string
        if ((previous->string[(n-2)] == '<') && (previous->string[(n-1)] == 'P') && (previous->string[(n)] == '>')){
            if ((current->string[x] == '<') && (current->string[x+1] == 'P') && (current->string[x+2] == '>')){
                char *newstring= malloc(sizeof(char) * strlen(previous->string)+1);
                if (newstring == NULL)
                {
					return FAILURE;
				}
                strcpy(newstring,previous->string);
                newstring[n] = '\0';
                newstring[n-1] = '\0';
                newstring[n-2] = '\0';
                previous->string = newstring;
            }
        }
    }
    //create and open fifo
    char * filename = "myfifo";
    FILE * wfile; 
    wfile = fopen(filename, "w");
    mkfifo(filename,0777);
    current = header->next;
    //write the strings to the fifo
    fprintf(wfile,"%s\n",header->name);
    while(current != NULL){
        fprintf(wfile,"%s\n",current->string);
         if (current->next == NULL){
             break;
         } 
         current = current->next;   
    }
    fclose(wfile);
    //open python program and send filename as argment     
    FILE * pythonFile = fopen("a4.py", "r");
    Py_Initialize();
    //run python program
    PyRun_SimpleFile(pythonFile, "a4.py");
    Py_Finalize();
    //delete the fifo opened earlier
    unlink("myfifo") ;
    fclose(pythonFile);

    return SUCCESS;
}

/*-----------------------freeStructure-------------------------------------
|  Function: int freeStructure(struct dataHeader *header)
|
|  Purpose: frees the allocated structure by traversing the structure bottom up and releasing its data
|  
|   Parameters:
|       struct dataHeader *header (IN) -- given the header in which the structure can be traversed to free the data
|
|  Returns: FAILURE (0) if the header passed into the function is non existant or corrupted,
| 			returns SUCCESS if structure has been freed successfully
*-------------------------------------------------------------------*/
int freeStructure(struct dataHeader *header){
    if (header == NULL)
    {
        return FAILURE;
    }
    struct dataString *tmp;
    struct dataString *current;
    current = header->next;
    while (current != NULL)
    {
       tmp = current;
       current = current->next;
       free(tmp->string);
       free(tmp);
   }
   free(header->name);
   free(header);
   return SUCCESS;

}
/****************************FILE I/0*******************************/

/*-----------------------writeStrings-------------------------------------
|  Function: int writeStrings(char *filename, struct dataHeader * header)
|
|  Purpose: Writes all of the contents of the dataHeader and linked structure to a binary file.
|           Stores the character strings and the length integer from the dataHeader. Calculates
|           and stores the length of each character string.
|  
|   Parameters:
|       struct dataHeader *header (IN) -- given the header in which the structure can be traversed to write to file
|       char *filename            (IN) -- the name being allocated as the new file name
|
|  Returns: FAILURE (0) if the header passed into the function is non existant or corrupted, or a malloc does not have enough memory allocation 
| 			returns SUCCESS(1) if strings have successfully been printed to file
*-------------------------------------------------------------------*/

int writeStrings(char *filename, struct dataHeader * header){
    if (header == NULL){
        return FAILURE;
    }
    FILE *file;
    struct dataString *current;
    current = header->next;
    int n= strlen(header->name);
    file = fopen(filename,"wb");
    if (file == NULL)
    {
        return FAILURE;
    }
    fwrite(&n,sizeof(int),1,file);
    fwrite(header->name,sizeof(char),strlen(header->name),file);
    n = getLength(header);
    fwrite(&n,sizeof(int),1,file);
    while (current != NULL)
    {
        n= strlen(current->string);
        fwrite(&n,sizeof(int),1,file);
        fwrite(current->string,sizeof(char),strlen(current->string),file);
        current = current->next;
    }
    fclose(file);
    return SUCCESS;
}

/*-----------------------readStrings-------------------------------------
|  Function: struct dataHeader *readStrings(char *filename)
|
|  Purpose: reads the linked structure from a file created using the 
|           writeStrings() function and rebuilds the linked structure that is stored in the file. 
|  
|   Parameters: 
|       char *filename            (IN) -- the name of the file being read
|
|  Returns: FAILURE (0) in returnStruct.value if the header passed into the function is non existant or corrupted, or a malloc does not have enough memory allocation 
| 			returns  SUCCESS(1) in returnStruct.value if file has successfully been read
*-------------------------------------------------------------------*/

struct returnStruct readStrings(char *filename){
    struct returnStruct returnVal;
    int stringLength=0;
    FILE *ptr;
    ptr = fopen(filename,"rb"); 
    if (ptr == NULL) 
    {
        returnVal.value = FAILURE;
    }
    fread(&stringLength,sizeof(int),1,ptr);
    char *buffer= malloc(sizeof(char) * stringLength+1);
    if (buffer == NULL)
    {
        returnVal.value = FAILURE;
    }
    fread(buffer,sizeof(char),stringLength,ptr);
    struct dataHeader *structure = malloc(sizeof(struct dataHeader));
    if (structure == NULL){
        returnVal.value = FAILURE;
    }
    structure->name = buffer;
    fread(&stringLength,sizeof(int),1,ptr);
    structure->length = stringLength;
    while(1){
        if(feof(ptr))
            break;
        fread(&stringLength,sizeof(int),1,ptr);
        buffer = realloc(buffer,sizeof(char) * stringLength+1);
        if (buffer == NULL){
            returnVal.value = FAILURE;
        }
        fread(buffer,sizeof(char),stringLength,ptr);
        addString(structure,buffer);
    }
    fclose(ptr);
    returnVal.value = SUCCESS;
    return returnVal;

}
