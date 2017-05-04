#ifndef __STREAM_H__
#define __STREAM_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

/*Struct for holding information that is used to create a post*/
struct userPost {
	char* username;
	char* streamname;
	char* date;
	char* text;
};

/*Creates a new post using the information from the struct in the parameter*/
void updateStream(struct userPost *st);

/*Adds a new user to a stream, creates the stream if it doesn't exist*/
void addUser(char* username, char* list);

/*Removes a user from a given stream*/
void removeUser(char* username, char* list);

#endif