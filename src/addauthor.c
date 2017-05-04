#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stream.h"

void checkArg(int numArg)
{ 
    if (numArg < 3)
    {
    	printf("Error, operation was not performed.\n");
        exit(1);
    }
}

int main(int argc, char* argv[]) {

	checkArg(argc);

	int i;
	char* author;
	char* streams;
	author = malloc(sizeof(char)*256);
	streams = malloc(sizeof(char)*256);
	for(i = 0; i<256;i++) {
		author[i] = (char)0;
		streams[i] = (char)0;
	}

	int isAdd = 0;
	
	if(argc == 2) {
		printf ("A stream is missing.\n");
		free(author);
		free(streams);
		exit(1);
	}
	if(strcmp(argv[1], "-r") == 0 && argc == 3) {
		printf ("A stream is missing.\n");
		free(author);
		free(streams);
		exit(1);
	}
	else if(strcmp(argv[1], "-r") == 0 ) {
		strcpy(author, argv[3]);
		strcpy(streams,argv[2]);
		isAdd = 1;
	}
	else {
		strcpy(author, argv[2]);
		strcpy(streams,argv[1]);
	}
	
	/*loop for properly collecting stream names*/
	
	strcat(streams, "\n");
	if(strstr(streams, " ") != NULL) {
		free(streams);
		free(author);
		printf("Please do not enter any spaces in the stream list.");
		exit(1);
	}
	else if(streams[0] == '\n') {
		free(streams);
		free(author);
		printf("Please enter at least one stream.");
		exit(1);
	}
		

	if(isAdd == 0) {

		addUser(author, streams);
	}
	else
		removeUser(author, streams);
		
	free(streams);
	free(author);
	
	return 0;
}
