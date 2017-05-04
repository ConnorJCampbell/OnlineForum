#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void grabText(char* storage, char* tempTag, char* subString, int max, int toAdd);

int main(int argc, char* argv[]) {

	if (argc < 2) {
    	printf("Missing filename. Exiting program.\n");
        exit(1);
    }

	char configLine[1000];
	char fileLine[256];
	FILE* inFile;
    inFile = fopen(argv[1], "r");

    int textSize = 256;
    int numSize = 6;

    int i, charCount;
    char* tempTag;
    char* subString;
    char tagType, tempChar;
    int position = 0;

    char* textField = malloc(sizeof(char)*textSize);
    char* tempField = malloc(sizeof(char)*textSize);
    char* hiddenField = malloc(sizeof(char)*textSize);
    char* filepath = malloc(sizeof(char)*textSize);
    char* sizeField = malloc(sizeof(char)*numSize);

    int isForm = 0;
    int isFirst = 0;

    printf("<html>\n<body>\n\n");

    while(fgets(configLine, 1000, inFile) != NULL) {
   		if(strstr(configLine, ".b(") != NULL || strstr(configLine, ".r(") != NULL || strstr(configLine, ".i(") != NULL) {
   			isForm = 1;
   			isFirst = 1;
   		}
    	tempTag = strtok(configLine, ")");
    	while(tempTag != NULL) {
		    /*while(strcmp(tempTag, "\n") != 0) {*/
		    	tagType = tempTag[1];

		    	/*Header Tag*/
		    	if(tagType == 'h') {

		    		/*Check for size field*/
		    		subString = strstr(tempTag, "size=");
		    		for (i = 0; i< numSize; i++)
    					sizeField[i] = (char)0;
		    		if(subString != NULL) {

						position = subString - tempTag;
						position += 5;
						charCount = 0;
						tempChar = tempTag[position];

						while(tempChar != '\0') {
							sizeField[charCount] = tempChar;
							charCount++;
							position++;
							tempChar = tempTag[position];
						}
		    		}
		    		else
		    			strcpy(sizeField, "3");

		    		/*Check for text field*/
		    		subString = strstr(tempTag, "text=\"");
		    		if(subString != NULL) {

		    			grabText(textField, tempTag, subString, textSize, 6);
						printf("<H%s>%s</H%s>\n", sizeField, textField, sizeField);
		    		}
		    		else
		    			printf("<H%s>HEADING</H%s>\n", sizeField, sizeField);
		    	}

		    	/*text tag*/
		    	else if(tagType == 't') {

		    		/*Check for file field*/
		    		subString = strstr(tempTag, "file=\"");
		    		if(subString != NULL) {

		    			grabText(textField, tempTag, subString, textSize, 6);
		    			FILE* textFile = fopen(textField, "r");
		    			if(fgets(fileLine, 256, textFile) != NULL) {
		    				printf("%s <br>", fileLine);
		    			}
		    			while(fgets(fileLine, 256, textFile) != NULL) {
		    				printf("%s <br>", fileLine);
		    			}
		    			fclose(textFile);
		    		}

		    		else{
			    		/*Check for text field*/
			    		subString = strstr(tempTag, "text=\"");
			    		if(subString != NULL) {

			    			grabText(textField, tempTag, subString, textSize, 6);
							printf("%s\n", textField);
			    		}
			    		else
			    			printf("Default text\n");
		    		}
		    	}

		    	/*Button Tag*/
		    	else if(tagType == 'b') {

		    		/*Check for link field*/
	    			if(isForm == 1 && isFirst == 1) {
	    				subString = strstr(tempTag, "link=\"");
	    				if(subString != NULL) { 
		    				grabText(textField, tempTag, subString, textSize, 6);
							printf("<form method=\"POST\" action=\"%s\">\n", textField);
						}
						else
							printf("<form method=\"POST\">\n");
						isFirst = 0;
	    			}

		    		/*Check for name field*/
		    		subString = strstr(tempTag, "name=\"");
		    		grabText(textField, tempTag, subString, textSize, 6);
		    		if(isForm == 1)
		    			printf("\t");
		    		printf("<input type=\"submit\" name=\"%s\" value=\"%s\">\n",textField, textField);
		    		if(isForm == 1)
		    			printf("</form>\n");

		    	}

		    	/*Line tag*/
		    	else if(tagType == 'd') {
		    		printf("<HR>\n");
		    	}

		    	/*Executable tag*/
		    	else if(tagType == 'e') {
		    		subString = strstr(tempTag, "exe=\"");
		    		grabText(textField, tempTag, subString, textSize, 5);
		    		FILE* tempFile;

		    		/*Check current directory*/
		    		for (i = 0; i< textSize; i++)
							filepath[i] = (char)0;
			    	strcpy(filepath, "./");
			    	strcat(filepath, textField);
		    		if((tempFile = fopen(textField, "r")) != NULL) {
		    			fclose(tempFile);
		    			system(filepath);
		    		}
		    		else {
			    		/*Check bin*/
			    		for (i = 0; i< textSize; i++)
							filepath[i] = (char)0;
			    		strcpy(filepath, "/usr/local/bin/");
			    		strcat(filepath, textField);
			    		if((tempFile = fopen(filepath, "r")) != NULL) {
							fclose(tempFile);
			    			system(filepath);
						}
						else {
							/*Check system bin*/
							for (i = 0; i< textSize; i++)
								filepath[i] = (char)0;
							strcpy(filepath, "/bin/");
				    		strcat(filepath, textField);
				    		if((tempFile = fopen(filepath, "r")) != NULL) {
								fclose(tempFile);
				    			system(filepath);
							}
							else {
								printf("Could not find executable");
							}
						}
					}

		    	}

		    	/*Link tag*/
		    	else if(tagType == 'l') {

		    		/*Check for the link field*/
		    		subString = strstr(tempTag, "link=\"");
		    		if(subString != NULL) {
		    			grabText(textField, tempTag, subString, textSize, 6);
						printf("<a href=\"%s\">", textField);
		    		}

		    		/*Check for the text field*/
		    		subString = strstr(tempTag, "text=\"");
		    		if(subString != NULL) {
		    			grabText(textField, tempTag, subString, textSize, 6);
						printf("%s</a>\n", textField);
		    		}
		    		else
		    			printf("link</a>\n");	
		    	}

		    	/*Picture Tag*/
		    	else if(tagType == 'p') {

		    		/*Check for the text field*/
		    		subString = strstr(tempTag, "image=\"");
		    		if(subString != NULL) {
		    			grabText(textField, tempTag, subString, textSize, 7);
						printf("<img src=\"%s\" alt=\"Missing Icon\" style=\"", textField);
		    		}

		    		/*Check for the size field*/
		    		subString = strstr(tempTag, "size=");
		    		if(subString != NULL) {
		    			for (i = 0; i< numSize; i++)
    						sizeField[i] = (char)0;

						position = subString - tempTag;
						position += 5;
						charCount = 0;
						tempChar = tempTag[position];

						/*Grab Width*/
						while(tempChar != 'x') {
							sizeField[charCount] = tempChar;
							charCount++;
							position++;
							tempChar = tempTag[position];
						}
						printf("width:%spx;", sizeField);

						/*Grab Height*/
						for (i = 0; i< numSize; i++)
    						sizeField[i] = (char)0;

    					charCount = 0;
    					position++;
    					tempChar = tempTag[position];
    					while(tempChar != '\0') {
							sizeField[charCount] = tempChar;
							charCount++;
							position++;
							tempChar = tempTag[position];
						}

						printf("height:%spx;\">\n", sizeField);
		    		}
		    		else
		    			printf("width:100px;height:100px;\">\n");
		    	}

		    	/*Input tag*/
		    	else if(tagType == 'i') {

		    		/*Check for the action field*/
					if(isForm == 1 && isFirst == 1) {
						if((subString = strstr(tempTag, "action=\"")) != NULL) {
    						grabText(textField, tempTag, subString, textSize, 8);
							printf("<form method=\"POST\" action=\"%s\">\n", textField);
						}
						else
							printf("<form method=\"POST\">\n");
						isFirst = 0;
	    			}

					/*Check for the text field*/
					while((strstr(tempTag, "text=\"")) != NULL) {
						if(isForm == 1)
							printf("\t");
			    		subString = strstr(tempTag, "text=\"");
		    			grabText(textField, tempTag, subString, textSize, 6);
						tempTag[subString - tempTag] = '@';
						printf("%s <br>\n", textField);

						/*Check for the name field*/
						if(isForm == 1)
							printf("\t");
			    		subString = strstr(tempTag, "name=\"");
		    			grabText(textField, tempTag, subString, textSize, 6);
		    			tempTag[subString - tempTag] = '@';
						printf("<input type=\"text\" name=\"%s\" ", textField);

						/*Check for the value field*/
			    		subString = strstr(tempTag, "value=\"");
		    			grabText(textField, tempTag, subString, textSize, 7);
		    			tempTag[subString - tempTag] = '@';
						printf("value=\"%s\"> <br>\n", textField);
						
					}

					if(isForm == 1)
		    			printf("\t");
		    		printf("<input type=\"submit\" name=\"submit\" value=\"Submit\"> <br>\n");
		    		if(isForm == 1)
		    			printf("</form>\n");

		    	}

		    	/*Radio Tag*/
		    	else if(tagType == 'r') {

		    		/*Check for the action field*/
	    			if(isForm == 1 && isFirst == 1) {
	    				subString = strstr(tempTag, "action=\"");
	    				if(subString != NULL) { 
		    				grabText(textField, tempTag, subString, textSize, 8);
							printf("<form method=\"POST\" action=\"%s\">\n", textField);
						}
						else
							printf("<form method=\"POST\">\n");
						isFirst = 0;
	    			}

					/*Check for the text field*/
		    		subString = strstr(tempTag, "name=\"");
	    			grabText(textField, tempTag, subString, textSize, 6);

	    			int firstValue = 1;
					/*Check for the value field*/
		    		subString = strstr(tempTag, "value=\"");
		    		while(subString != NULL) {
		    			for (i = 0; i< textSize; i++)
    						tempField[i] = (char)0;

						position = subString - tempTag;
						position += 7;
						charCount = 0;
						tempChar = tempTag[position];

						while(tempChar != '\"') {
							tempField[charCount] = tempChar;
							charCount++;
							position++;
							tempChar = tempTag[position];
						}
						if(isForm == 1)
							printf("\t");
						printf("<label for=\"%s\">%s</label>\n\t<input type=\"radio\" name=\"%s\" value=\"%s\"",tempField,tempField, textField, tempField);
						if(firstValue == 1) {
							printf("checked><BR>\n");
							firstValue = 0;
						}
						else
							printf("><BR>\n");

						tempTag[subString - tempTag] = '@';
						subString = strstr(tempTag, "value=\"");
		    		}
		    		printf("\n");

		    	}

		    	/*Extra tag for text area*/
		    	else if (tagType == 'q') {

		    		/*Check for the action field*/
					if(isForm == 1 && isFirst == 1) {
						if((subString = strstr(tempTag, "action=\"")) != NULL) {
    						grabText(textField, tempTag, subString, textSize, 8);
							printf("<form method=\"POST\" action=\"%s\">\n", textField);
						}
						else
							printf("<form method=\"POST\">\n");
						isFirst = 0;
	    			}

	    			if(isForm == 1)
		    			printf("\t");
		    		/*Check for the name field*/
		    		subString = strstr(tempTag, "name=\"");
		    		if(subString != NULL) {
		    			grabText(textField, tempTag, subString, textSize, 6);
						printf("<textarea name=\"%s\" ", textField);
		    		}

		    		/*Check for the value field*/
		    		subString = strstr(tempTag, "value=\"");
		    		if(subString != NULL) {
		    			grabText(textField, tempTag, subString, textSize, 7);
						printf("placeholder=\"%s\" rows=\"10\" cols=\"80\"></textarea> <br>\n", textField);
		    		}
		    	}

		    	/*Extra tag for hidden input*/
		    	else if (tagType == 'x') {

		    		/*Check for the action field*/
					if(isForm == 1 && isFirst == 1) {
						if((subString = strstr(tempTag, "action=\"")) != NULL) {
    						grabText(textField, tempTag, subString, textSize, 8);
							printf("<form method=\"POST\" action=\"%s\">\n", textField);
						}
						else
							printf("<form method=\"POST\">\n");
						isFirst = 0;
	    			}

	    			if(isForm == 1)
		    			printf("\t");
		    		/*Check for the name field*/
		    		subString = strstr(tempTag, "name=\"");
		    		if(subString != NULL) {
		    			grabText(textField, tempTag, subString, textSize, 6);
						printf("<input type=\"hidden\" name=\"%s\" ", textField);
		    		}

		    		/*Check for the value field*/
		    		subString = strstr(tempTag, "value=\"");
		    		if(subString != NULL) {
		    			grabText(textField, tempTag, subString, textSize, 7);
						printf("value=\"%s\">\n", textField);
		    		}
		    	}

		    	tempTag = strtok(NULL, ")");
		    	
		    /*}*/
		}
		isForm = 0;
	}

	printf("\n</html>\n</body>\n");

	free(textField);
	free(tempField);
	free(sizeField);
	free(hiddenField);
	free(filepath);
    fclose(inFile);
	return 0;
}


void grabText(char* storage, char* tempTag, char* subString, int max, int toAdd) {
	int i, position, charCount;
	char tempChar;

	for (i = 0; i< max; i++)
		storage[i] = (char)0;

	position  = subString - tempTag;
	position += toAdd;
	charCount = 0;
	tempChar  = tempTag[position];

	while(tempChar != '\"') {
		storage[charCount] = tempChar;
		charCount++;
		position++;
		tempChar = tempTag[position];
	}
}