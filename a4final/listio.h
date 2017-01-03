#include <stdio.h>
#include <stdlib.h>
#include "listio.c"

/*-----------------------buildHeader-------------------------------------
|  Function: struct dataHeader *buildHeader()
|
|  Purpose: Used to build the base of the structure
|
|  Parameters:
|       struct dataHeader *header (IN) -- the header for where to allocate the name
|       char *name                (IN) -- the name being allocated as the structure name
|
|  Returns: an initialized dataHeader struct
*-------------------------------------------------------------------*/
struct returnStruct buildHeader();

/*-----------------------setName-------------------------------------
|  Function: void setName(struct dataHeader *header, char *name)
|
|  Purpose: used to set the name of the structure
|
|  Parameters:
|       struct dataHeader *header (IN) -- the header for where to allocate the name
|       char *name                (IN) -- the name being allocated as the structure name
|
*-------------------------------------------------------------------*/
int setName(struct dataHeader *header, char *name);

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
char * getName(struct dataHeader *header);

/*-----------------------getLength-------------------------------------
|  Function: int getLength(struct dataHeader *header)
|
|  Purpose: get the length of the structure, found in the header of the structure
|
|  Parameters:
|       struct dataHeader *header (IN) -- given the header in which is stored the length
|
|  Returns: the length of the header name
*-------------------------------------------------------------------*/
int getLength(struct dataHeader *header);

/*-----------------------addString-------------------------------------
|  Function: void addString(struct dataHeader *header, char *str)
|
|  Purpose: adds a new dataString to the linked structure every time the function is called. 
|           The new string is stored in the string pointer within the dataString struct.
|
|  Parameters:
|       struct dataHeader *header (IN) -- given the header in which the structure can be traversed
|       char *str                 (IN) -- The *str character string contains the string to store in the dataString struct.
|
|  Returns: void, but the result is a string added to the end of the structure
*-------------------------------------------------------------------*/
int addString(struct dataHeader *header, char *str);

/*-----------------------printString-------------------------------------
|  Function: void printString(struct dataHeader *header)
|
|  Purpose: prints the strings found in the structure
|
|  Parameters:
|       struct dataHeader *header (IN) -- given the header in which the structure can be traversed for printing
|
|  Returns: void, but the result is a printed string
*-------------------------------------------------------------------*/
int printString(struct dataHeader *header);

/*-----------------------processString-------------------------------------
|  Function: void processStrings(struct dataHeader *header)
|
|  Purpose: modifies the characters space, tab, newline, carriage return contained within the strings of the structure.
|           Multiple spaces are reduced to a single space and the string is shortened by the number of spaces removed.
|           Multiple tabs are replaced with a single tab and the string is shortened by the number of tabs removed.
|           A single newline character or a single carriage return is replaced with the string <BR>.
|           Two or more newline characters are replaced with the string <P>. Two or more carriage return characters are replaced with the string <P>.
|           Any combination of newlines and carriage returns is replaced by the string  <P>.
|           this string calculates the length of the total structure strings andupdates the head
|  
|   Parameters:
|       struct dataHeader *header (IN) -- given the header in which the structure can be traversed to process its string
|
|  Returns: void, but the result is structure with correctly processed strings
*-------------------------------------------------------------------*/
int processStrings(struct dataHeader *header);

/*-----------------------freeStructure-------------------------------------
|  Function: void freeStructure(struct dataHeader *header)
|
|  Purpose: frees the allocated structure by traversing the structure bottom up and releasing its data
|  
|   Parameters:
|       struct dataHeader *header (IN) -- given the header in which the structure can be traversed to free the data
|
*-------------------------------------------------------------------*/
int freeStructure(struct dataHeader *header);

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
void stringCombine(char *string1, char *string2, int position);

/****************************FILE I/0*******************************/

/*-----------------------writeStrings-------------------------------------
|  Function: void writeStrings(char *filename, struct dataHeader * header)
|
|  Purpose: Writes all of the contents of the dataHeader and linked structure to a binary file.
|           Stores the character strings and the length integer from the dataHeader. Calculates
|           and stores the length of each character string.
|  
|   Parameters:
|       struct dataHeader *header (IN) -- given the header in which the structure can be traversed to write to file
|       char *filename            (IN) -- the name being allocated as the new file name
|
|  Returns: none, but there will be a resulting binaryy file formatted in a particular eay
*-------------------------------------------------------------------*/
int writeStrings(char *filename, struct dataHeader * header);

/*-----------------------readStrings-------------------------------------
|  Function: struct dataHeader *readStrings(char *filename)
|
|  Purpose: reads the linked structure from a file created using the 
|           writeStrings() function and rebuilds the linked structure that is stored in the file. 
|  
|   Parameters: 
|       char *filename            (IN) -- the name of the file being read
|
|  Returns: the values from the filename in a structure.
*-------------------------------------------------------------------*/
struct returnStruct readStrings(char *filename);
