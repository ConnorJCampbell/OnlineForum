#include "stream.h"

void updateStream(struct userPost *st) {
	/*int correct = 1;*/
	int i;
	char* databaseExe = malloc(sizeof(char)*12000);
	char* postInfo = malloc(sizeof(char)*12000);
	for(i = 0; i<12000;i++) {
		databaseExe[i] = (char)0;
		postInfo[i] = (char)0;
	}

	strcpy(postInfo, "Stream: ");
	strcat(postInfo, st->streamname);
	strcat(postInfo, "\nSender: ");
	strcat(postInfo, st->username);
	strcat(postInfo, "\nDate: ");
	strcat(postInfo, st->date);
	strcat(postInfo, "\n");
	strcat(postInfo, st->text);

	strcpy(databaseExe, "./db -post \"");
	strcat(databaseExe, st->username);
	strcat(databaseExe, "\" \"");
	strcat(databaseExe, st->streamname);
	strcat(databaseExe, "\" \"");
	strcat(databaseExe, postInfo);
	strcat(databaseExe, "\"");
	system(databaseExe);

	free(databaseExe);
	free(postInfo);
}

void addUser(char* username, char* list) {
	int i;
	char* currentStream = malloc(sizeof(char)*256);
	char* databaseExe = malloc(sizeof(char)*1000);
	for(i = 0; i<256;i++) {
		currentStream[i] = (char)0;
	}

	for(i = 0; i<1000;i++) {
		databaseExe[i] = (char)0;
	}
	
	i = 0;
	int j = 0;
	while(list[i] != '\0') {
		if (list[i] == ',' || list[i] == '\n') {

			/*Call on embedded SQL*/
			strcpy(databaseExe, "./db -adda \"");
			strcat(databaseExe, username);
			strcat(databaseExe, "\" \"");
			strcat(databaseExe, currentStream);
			strcat(databaseExe, "\"");
			system(databaseExe);			
				
			/*skip to the next value in list, reset the current Stream*/
			i++;

			for(j = 0; j<256;j++) {
				currentStream[j] = (char)0;
			}
			for(j = 0; j<1000;j++) {
				databaseExe[j] = (char)0;
			}
			j = 0;

		}
		/*Building the stream name*/
		else {
			currentStream[j] = list[i];
			j++;
			i++;
		}
	}

	free(databaseExe);
	free(currentStream);
}

void removeUser(char* username, char* list) {
	int i;
	char* currentStream = malloc(sizeof(char)*256);
	char* databaseExe = malloc(sizeof(char)*1000);
	for(i = 0; i<256;i++) {
		currentStream[i] = (char)0;
	}

	for(i = 0; i<1000;i++) {
		databaseExe[i] = (char)0;
	}

	i = 0;
	int j = 0;
	while(list[i] != '\0') {
		if (list[i] == ',' || list[i] == '\n') {

			/*Call on embedded SQL*/
			strcpy(databaseExe, "./db -rema \"");
			strcat(databaseExe, username);
			strcat(databaseExe, "\" \"");
			strcat(databaseExe, currentStream);
			strcat(databaseExe, "\"");
			system(databaseExe);			
				
			/*skip to the next value in list, reset the current Stream*/
			i++;

			for(j = 0; j<256;j++) {
				currentStream[j] = (char)0;
			}
			for(j = 0; j<1000;j++) {
				databaseExe[j] = (char)0;
			}
			j = 0;

		}
		/*Building the stream name*/
		else {
			currentStream[j] = list[i];
			j++;
			i++;
		}
	}
	free(currentStream);
	free(databaseExe);
}