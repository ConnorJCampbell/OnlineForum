#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "stream.h"

class PostEntry {
    char* stream;
    char* text;
    char* date;
    struct userPost* myPost;

    int readInput(char* username, char* streamVar, char* textVar) {
    	
    	/*store input*/
    	strcpy(stream, streamVar);
		strcpy(text, textVar);
	    return 0;
    }

    void formatEntry(char* username) {
    	myPost = malloc(sizeof(struct userPost));
    	myPost->username   = malloc(sizeof(char)*strlen(username) + 1);
    	myPost->streamname = malloc(sizeof(char)*strlen(stream) + 1);
    	myPost->text       = malloc(sizeof(char)*strlen(text) + 1);
    	strcpy(myPost->username, username);
    	strcpy(myPost->streamname, stream);
    	strcpy(myPost->text, text);
    }

    void getTimeDate() {
    	time_t t = time(NULL);
    	struct tm *tm = localtime(&t);
    	myPost->date = malloc(sizeof(char)*strlen(asctime(tm)) + 1);
    	strcpy(date,asctime(tm));
    	date[strlen(date) - 1] = '\0';
    	strcpy(myPost->date, date);
    }

    void submitPost() {
    	updateStream(myPost);
    	free(myPost->username);
    	free(myPost->streamname);
    	free(myPost->text);
    	free(myPost->date);
    	free(myPost);
    }
};

void checkArg(int numArg)
{ 
    if (numArg < 2)
    {
    	printf("Please run with a username. Exiting progr\n");
        exit(1);
    }
}

int main(int argc, char* argv[]) {

	/*checkArg(argc);*/
	char* author;
	int i;
	class PostEntry tempValues;
	author = malloc(sizeof(char)*256);
	tempValues.stream = malloc(sizeof(char)*256);
	tempValues.date   = malloc(sizeof(char)*256);
	tempValues.text   = malloc(sizeof(char)*10000);

	for(i = 0; i<256;i++) {
		tempValues.stream[i] = (char)0;
		tempValues.date[i]   = (char)0;
		author[i] = (char)0;
    }
	for(i = 0; i<10000;i++)
		tempValues.text[i] = (char)0;

	strcpy(author, argv[1]);

	if (tempValues.readInput(author, argv[2], argv[3]) == 1) {
		free(tempValues.stream);
		free(tempValues.date);
		free(tempValues.text);
		free(author);
		exit(1);
	}
	tempValues.formatEntry(author);
	tempValues.getTimeDate();
	tempValues.submitPost();

	free(author);
	free(tempValues.stream);
	free(tempValues.date);
	free(tempValues.text);

	return 0;
}