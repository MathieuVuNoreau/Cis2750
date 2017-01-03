/* --------------------------------------------------------------------------------------------------------------
# 	File:    mydb.c
#	Author:  Mathieu Vu-Noreau (0884903)
# 	Date:     10/10/2016
#	Course:   CIS*2750 - Software System Dvlmt & Intgrn
#
#	Summary of File: 
* 			this file links to the mysql database and does a certain set of commands for my php page   	 
# --------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <time.h>
#include <stdint.h>

#define MAX_QUERY 1000024
#define HOSTNAME  "dursley.socs.uoguelph.ca"


#define USERNAME  "mvunorea"
#define PASSWORD  "0884903"
#define DATABASE  "mvunorea"

/*
	standard error clause.
*/
void error(char *msg, MYSQL *mysql){
	printf("%s\n%s\n",msg,mysql_error(mysql));
	exit(1);
}

/*
	clear the contents of an array of char's
*/
void clrstr(char *buf){
	buf[0] = '\0';
}

/*==========================================================================
	MAIN - mydb.c
==========================================================================*/
int main(int argc, char *argv[]) {
	MYSQL mysql;
	MYSQL_RES *res;
	MYSQL_ROW row;
	MYSQL_FIELD *field;
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	char query[MAX_QUERY];
	int x;
	int i = 0;
	int n;
	char dateTime[50];
	n=sprintf(dateTime,"%d-%d-%d %d:%d:%d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	
	/* 
		Connect to database server.
		Username and password must be filled in here.
		If no username or password is stored in DB then use NULL.
	*/
	if (argc != 2 && argc != 3){
		printf("%d argument please enter only 2 or 3 arguments\n",argc);
		printf("For more information run the program with '-help' as the second parameter\n");
		return 1;
	}
	//printf("connecting...\n");
	
	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "mydb");
	if (!mysql_real_connect(&mysql, HOSTNAME, USERNAME, PASSWORD,
		DATABASE, 0, NULL, 0)) {
	   error("Could not connect to host.",&mysql);
	}
	
	//printf("Selecting a specific database to work with.\n");
	
	/*
		Build query
	*/
	
	
	//printf("Creating students table.\n");
	
	/*
		Create students table
	*/
	clrstr(query);
	if (strcmp(argv[1],"-create")==0){
		strcat(query, "create table files (");
		strcat(query, "file_content LONGBLOB,");
		strcat(query, "file_length int,");
		strcat(query, "file_name char(255),");
		strcat(query,"DateCreated DATETIME DEFAULT NULL)");
		if(mysql_query(&mysql, query)){
			error("Could not create table!",&mysql);
		}
		clrstr(query);
	}
	if (strcmp(argv[1],"-lines")==0){
		// printf("printing database\n");
                strcpy(query, "select file_name from files");

                if(mysql_query(&mysql, query)){
                        error("fail select 2",&mysql);
                }

                if (!(res = mysql_store_result(&mysql))){
                        error("fail store 2",&mysql);
                }
                while ((row = mysql_fetch_row(res))) {
                        for (i=0; i < mysql_num_fields(res); i++){
                                printf("%s ", row[i]);
                        }
                        printf("\n");
                }
                clrstr(query);

	}
	else if (strcmp(argv[1],"-clear") == 0){
		/*
			clears all rows in table
		*/
		strcpy(query, "TRUNCATE files");
		if(mysql_query(&mysql,query))
			error("fail clear 1",&mysql);
		printf("all rows have been cleared\n");
		clrstr(query);
	}
	else if (strcmp(argv[1],"-show")== 0){\
		/*
			prints all values in database
		*/
		printf("printing database\n");
		strcpy(query, "select * from files");
	
		if(mysql_query(&mysql, query)){
			error("fail select 2",&mysql);
		}

		if (!(res = mysql_store_result(&mysql))){
			error("fail store 2",&mysql);
		}
		while ((row = mysql_fetch_row(res))) {
			for (i=0; i < mysql_num_fields(res); i++){
				printf("%s ", row[i]);
			}
			printf("\n");
		}
		clrstr(query);
	}
	else if (strcmp(argv[1],"-reset") == 0){
		/*
			Deletes the table
		*/
		strcpy(query, "drop table files");
		if(mysql_query(&mysql,query))
			error("fail drop 1",&mysql);
		printf("table has been deleted\n");
		clrstr(query);
	}
	else if (strcmp(argv[1],"-help") == 0){
		/*
			prints help table
		*/
		printf("======================================================================================================\n");
		printf("||                               Welcome to Matt's database help section                            ||\n");
		printf("||                                                                                                  ||\n");
		printf("|| My Program consists of 5 commands(all commands must be ran as a parameter to ./db):              ||\n");
		printf("|| ex: ./db -create | ./db -clear | ./db -reset                                                     ||\n");
		printf("||                                                                                                  ||\n");
		printf("|| -create         This command creates the table if it has not already been creates                ||\n");
		printf("||                                                                                                  ||\n");
		printf("|| -clear          This command remove all data from all the rows of the table                      ||\n");
		printf("||                                                                                                  ||\n");
		printf("|| -reset          This command deletes the table, after the use of this command, you will need     ||\n");
		printf("||                 to use the '-create command' to create the table after it has been deleted       ||\n");
		printf("||                                                                                                  ||\n");
		printf("|| -show           This displays all the values in the table (every row and every value in the row) ||\n");
		printf("||                                                                                                  ||\n");
		printf("|| ./db <file>   This command will enter the contents of the file, the file size, the file name     ||\n");
		printf("||             	   and the time and date the file was uploaded                                      ||\n");
		printf("||                                                                                                  ||\n");
		printf("|| ./db -lines   This command will print all the file names in the table                            ||\n");
		printf("||                                                                                                  ||\n");
		printf("|| ./db -showContent <file>   This command will print out the related html encoded text             ||\n");
		printf("||                              found for the file mentioned in the statement if it is found        ||\n");
		printf("||                              in the database                                                     ||\n");
        printf("||                                                                                                  ||\n");
		printf("======================================================================================================\n");
	}
	else if (strcmp(argv[1],"-showContent") == 0){
		char queryContent[1024];
		sprintf(queryContent, "select file_content from files where file_name='%s'", argv[2]); 
		strcpy(query, queryContent);

                if(mysql_query(&mysql, query)){
                        error("fail select 2",&mysql);
                }

                if (!(res = mysql_store_result(&mysql))){
                        error("fail store 2",&mysql);
                }
                while ((row = mysql_fetch_row(res))) {
                        for (i=0; i < mysql_num_fields(res); i++){
                                printf("%s ", row[i]);
                        }
                        printf("\n");
                }
                clrstr(query);
	}
	else{
		char filename[strlen(argv[1])];
		int sz;
		char fileSize[255];
		FILE * fp = fopen(argv[1], "r");
		fseek(fp, 0, SEEK_END); // seek to end of file
		sz = ftell(fp); // get current file pointer
		fseek(fp, 0, SEEK_SET);
		fclose(fp);
		printf("%d\n",sz);
		char *newfile=malloc(sizeof(char) * strlen(argv[1]));
		strcpy(filename,argv[1]);
		int num = 0;
		while (filename[num] != '.'){
			newfile[num] = filename[num];
			num++;
		}
		char *parsedName = newfile + 6;
		sprintf(fileSize, "%d", sz);
		clrstr(query);
		
		/*
		 * getting file contents
		*/
		
		
		char *source = NULL;
		fp = fopen(argv[1], "r");
if (fp != NULL) {
    /* Go to the end of the file. */
    if (fseek(fp, 0L, SEEK_END) == 0) {
        /* Get the size of the file. */
        long bufsize = ftell(fp);
        if (bufsize == -1) { /* Error */ }

        /* Allocate our buffer to that size. */
        source = malloc(sizeof(char) * (bufsize + 1));

        /* Go back to the start of the file. */
        if (fseek(fp, 0L, SEEK_SET) != 0) { /* Error */ }

        /* Read the entire file into memory. */
        size_t newLen = fread(source, sizeof(char), bufsize, fp);
        if ( ferror( fp ) != 0 ) {
            fputs("Error reading file", stderr);
        } else {
            source[newLen++] = '\0'; /* Just to be safe. */
        }
    }
    fclose(fp);
}
		printf("%s\n",source);
		/*
		 getting file contents
		*/
		/*
			Insert a records into the table
		*/
		printf("%s\n",parsedName);
		printf("Inserting students.\n");
		strcat(query,"insert into files values (");
		strcat(query, "'");
		strcat(query, source);
		strcat(query,"',");
		strcat(query, fileSize);
		strcat(query, ",'");
		strcat(query, parsedName);
		strcat(query, "','");
		strcat(query,dateTime);
		strcat(query, "')");
			if(mysql_query(&mysql, query)){
				error("Could not insert record",&mysql);
			}
	
		clrstr(query);
		printf("files have been inserted\n");
		free(newfile);
		free(source);
		free(parsedName);
		
	}
	/*
		Finally close connection to server
	*/
	mysql_close(&mysql);

	//printf("All done\n");

	return 0;
}
