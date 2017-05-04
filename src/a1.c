#include "a1.h"

int main(int argc, char* argv[]) {

	checkArg(argc);

	FILE* inFile;
    inFile = fopen(argv[1], "r");
    nullFile(inFile);

    char** keyArray;
    int kCount = 0;
    int kCharCount = 0;
    int size = 10;
    int columns = 1000;

    int i;
    int j;
    int k;
    int l;
    keyArray = malloc(sizeof(char*)*size);
    for(i=0; i<size; i++) {
    	keyArray[i] = malloc(sizeof(char)*columns);
    	for(j=0; j<columns; j++){
    		keyArray[i][j] = (char)0;
    	}
    }

    int c;
    int prev;
    int prev2;
    prev   = 'p';
    prev2  = '"';

    while((c = fgetc(inFile)) != EOF) {
    	if(c == ' ' || c == '\t' || c == '\n' || c == '\r') {
    		kCount++;
			kCharCount = 0;

			/*printf("%c", c);*/
			if(kCount == size) {
				keyArray = extendArray(keyArray, size);
				size *= 2;
			}

			keyArray[kCount][kCharCount] = c;
			kCharCount++;
    		/*printf("\n");*/
    	}

    	else if(c == '"') {
    		kCount++;
			kCharCount = 0;

			if(kCount >= size) {
				keyArray = extendArray(keyArray, size);
				size *= 2;
			}

			keyArray[kCount][kCharCount] = c;
			kCharCount++;
    		while((c = fgetc(inFile)) != EOF) {
    			keyArray[kCount][kCharCount] = c;
				kCharCount++;
    			if((c == '"' && prev != '\\') || (c == '"' && prev == '\\' && prev2 == '\\'))
    				break;
    			prev2 = prev;
    			prev  = c;
    		}
    		prev = '"';
    	}

    	else if(c == '/') {
    		kCount++;
			kCharCount = 0;

			if(kCount >= size) {
				keyArray = extendArray(keyArray, size);
				size *= 2;
			}

			keyArray[kCount][kCharCount] = c;
			kCharCount++;
    		c = fgetc(inFile);
    		if(c == '*') {
    			keyArray[kCount][kCharCount] = c;
				kCharCount++;
    			while((c = fgetc(inFile)) != EOF) {
	    			keyArray[kCount][kCharCount] = c;
					kCharCount++;
	    			if(c == '/' && prev == '*')
	    				break;
	    			prev  = c;
    			}
    			prev = '/';
    		}
    		else if(c == '/'){
    			keyArray[kCount][kCharCount] = c;
				kCharCount++;
    			while((c = fgetc(inFile)) != EOF) {
	    			if(c == '\n')
	    				break;
	    			keyArray[kCount][kCharCount] = c;
					kCharCount++;
    			}
    			kCount++;
				kCharCount = 0;

				if(kCount >= size) {
					keyArray = extendArray(keyArray, size);
					size *= 2;
				}

				keyArray[kCount][kCharCount] = '\n';
				kCharCount++;
    			prev = '\n';
    		}
    		else {
    			keyArray[kCount][kCharCount] = c;
				kCharCount = 0;
                kCount++;
				if(kCount >= size) {
					keyArray = extendArray(keyArray, size);
					size *= 2;
				}

				
	    	}
    	}

    	else if(c == '{' || c == '}' || c == ',' || c == ';' || c == ')' || c == '(' || c == '*' || c == '.' || c == '=' || c == '[' || c == ']' || c == '-') {
    			kCount++;
    			kCharCount = 0;

    			if(kCount >= size) {
					keyArray = extendArray(keyArray, size);
					size *= 2;
				}

    			keyArray[kCount][kCharCount] = c;
    			kCharCount++;

    	}

    	else {
    		if(prev == '{' || prev == '}' || prev == ',' || prev == ';' || prev == ')' || prev == '(' || prev == '*' || prev == '.' || prev == '=' || prev == '-' || prev == '[' || prev == ']' || prev == '\t' || prev == '\n' || prev == '\r'  || prev == ' ') {
    			kCount++;
    			kCharCount = 0;

    			if(kCount >= size) {
					keyArray = extendArray(keyArray, size);
					size *= 2;
				}

    			keyArray[kCount][kCharCount] = c;
    			kCharCount++;
    			/*printf("\n%c", c);*/
    		}
    		else {
    			keyArray[kCount][kCharCount] = c;
    			kCharCount++;
    			/*printf("%c", c);*/
    		}
    	}
    	prev = c;

    }
    fclose(inFile);


    int fSSize = 50;
    char** functionStrings;
    char** functionNames;
    int fSCounter = 0;
    int fNCount = 0;
    int bCounter = 0;
    char* currClass = malloc(sizeof(char)*100);
    char* tempName;
    char* newFunc = malloc(sizeof(char)*columns);
    char* tempString = malloc(sizeof(char) * columns);
    char* tempString2 = malloc(sizeof(char) * columns);

    int vNum = 100;
    char** classVariables;
    char** oldFuncs;
    char** newFuncs;
    char** tempVariables;
    char** tempList;
    char** createdClass;
    char** waitingList;
    char** constructorStrings;

    classVariables = malloc(sizeof(char*)*vNum);
    oldFuncs = malloc(sizeof(char*)*vNum);
    newFuncs = malloc(sizeof(char*)*vNum);
    createdClass = malloc(sizeof(char*)*vNum);
    waitingList = malloc(sizeof(char*)*vNum);
    for(i=0; i<vNum; i++) {
    	classVariables[i] = malloc(sizeof(char)*vNum);
        oldFuncs[i] = malloc(sizeof(char)*vNum);
        newFuncs[i] = malloc(sizeof(char)*vNum);
        createdClass[i] = malloc(sizeof(char)*vNum);
        waitingList[i] = malloc(sizeof(char)*vNum);
    	for(j=0; j<vNum; j++){
    		classVariables[i][j] = (char)0;
            oldFuncs[i][j] = (char)0;
            newFuncs[i][j] = (char)0;
            createdClass[i][j] = (char)0;
            waitingList[i][j] = (char)0;
    	}
    }

    int cVarCount = 0;
    int replaceCount = 0;
    int tempVarCount = 0;
    int createdCount = 0;
    int waitingCount = 0;
    int conCount = 0;
    int fBCount = 0;

    int inMain = 0;
    int inFunction = 0;
    int classExists = 0;
    int firstEntry = 1;

    char* tempVar;
    char* tempFunc;
    char* tempClass;
    char* currentClass;
    char* currVar;
    char* currFunc;

    FILE* outFile;
    char* fName = argv[1];
    fName[strlen(fName) - 1] = '\0';
    outFile = fopen(fName, "w");

    for(i=0; i<size; i++) {
        if(strcmp(keyArray[i], "class") == 0) {
            fprintf(outFile,"struct");
            strcpy(currClass, nextNonWhite(keyArray, &i, outFile));
            strcpy(newFunc, currClass);
            /*Inside class declaration*/
            if(strcmp(nextNonWhite(keyArray, &i, outFile), "{") == 0){
                functionStrings = malloc(sizeof(char*)*fSSize);
                functionNames = malloc(sizeof(char*)*fSSize);
                tempVariables = malloc(sizeof(char*)*vNum);
                tempVarCount = 0;
                fSCounter = 0;
                fNCount = 0;
                bCounter = 1;
                i++;
                while(bCounter != 0) {
                    if(strcmp(keyArray[i], "{") == 0) {
                        bCounter++;
                        fprintf(outFile,"%s", keyArray[i]);
                    }
                    else if(strcmp(keyArray[i], "}") == 0) {
                        fprintf(outFile,"%s", keyArray[i]);
                        bCounter--;
                    }
                    else {
                        if(strcmp(nextNonWhiteSafe(keyArray, i), "(") == 0) {
                            inFunction = 1;
                            if(isFunctionDef(keyArray, i) == 1) {
                                /*Testing if the star is appended onto the front
                                if(keyArray[i][0] == '*') {
                                    for
                                }*/
                                strcpy(oldFuncs[replaceCount], keyArray[i]);
                                strcat(oldFuncs[replaceCount], " ");
                                strcat(oldFuncs[replaceCount], currClass);
                                strcat(newFunc, keyArray[i]);
                                while(strcmp(keyArray[i], "(") != 0) {
                                    i++;
                                }
                                concatenateFunc(newFunc, keyArray, i);

                                /*Saving the function*/
                                j = lastNonWhiteIndex(keyArray, i);
                                strcpy(keyArray[j], newFunc);

                                /*copying entire function into a list so it can be
                                printed back out with other functions*/
                                while(strcmp(keyArray[j], "\n") != 0) {
                                    j--;
                                }
                                strcpy(tempString, keyArray[j]);
                                j++;

                                tempList = malloc(sizeof(char*)*100);
                                for(k=0; k<tempVarCount; k++) {
							    	tempList[k] = malloc(sizeof(char)*100);
							    	for(l=0; l<100; l++){
							    		tempList[k][l] = tempVariables[k][l];
							    	}
							    }
                                fBCount = 0;
                                while(strcmp(keyArray[j], "}") != 0 || fBCount != 0) {
                                    if(strlen(tempString) > 900) {
                                        functionStrings[fSCounter] = malloc(sizeof(char)*columns);
                                        strcpy(functionStrings[fSCounter], tempString);
                                        fSCounter++;
                                        strcpy(tempString, keyArray[j]);
                                        j++;
                                    }
                                    else {
                                    	/*extra check for class variables*/
                                    	for(k = 0; k<tempVarCount; k++) {
                                    		if(strcmp(keyArray[j], tempList[k]) == 0) {
                                    			l = j;
                                    			while(strcmp(lastNonWhite(keyArray, l), ",") == 0) {
                                    				l = lastNonWhiteIndex(keyArray, l);
													l = lastNonWhiteIndex(keyArray, l);
                                    			} 
                                    			if(isVarType(keyArray, lastNonWhiteIndex(keyArray, l)) == 1) {
                                    				strcpy(tempList[k], "\0");
                                    			}
                                    			else {
                                    				strcpy(keyArray[j],"tempStruct->");
                                    				strcat(keyArray[j], tempList[k]);
                                    			}
                                    		}
                                    	}
                                    	if(strcmp(keyArray[j], "(") == 0 && strcmp(newFunc, lastNonWhite(keyArray, j)) == 0) {
                                    		strcat(tempString, "(struct ");
                                    		strcat(tempString, currClass);
                                    		strcat(tempString, " * tempStruct");
                                    		if(strcmp(nextNonWhiteSafe(keyArray, j), ")") != 0)
                								strcat(tempString, ", ");
                							j++;
                                    	}


                                    	/*check for functions being called within functions*/
                                    	else if (strcmp(nextNonWhiteSafe(keyArray, j), "(") == 0) {
                                    		currFunc = keyArray[j];

                                    		tempFunc = "\0";
							                tempClass = "\0";
							                for(k = 0; k<=replaceCount; k++) {
							                	if (strcmp(currClass, tempClass) == 0 && strcmp(tempFunc, currFunc) == 0){
							                		/*Check for a function being used within another function of the same class*/
							                		if(strcmp(lastNonWhite(keyArray, j), ".") !=0) {
							                			strcpy(keyArray[j], "struct ");
							                			strcat(keyArray[j], currClass);
							                			strcat(keyArray[j], " * temp");
							                			strcat(keyArray[j], currClass);
							                			strcat(keyArray[j], ";\n\t\t");
							                			strcat(keyArray[j], newFuncs[k-1]);
							                			strcat(tempString, keyArray[j]);
							                			j++;
							                			while(strcmp(keyArray[j], "(") !=0) {
							                				 strcat(tempString, keyArray[j]);
							                				 j++;
							                			}
							                			strcat(keyArray[j], "temp");
							                			strcat(keyArray[j], currClass);
							                			if(strcmp(nextNonWhiteSafe(keyArray, j), ")") !=0)
							                				strcat(keyArray[j], ",");
							                		}
							                		else
							                			strcpy(keyArray[j], newFuncs[k-1]);
							                		break;
							                	}
							                    strcpy(tempString2, oldFuncs[k]);
							                    tempFunc = strtok(tempString2, " ");
							                    tempClass = strtok(NULL, " ");
							                }
							                strcat(tempString, keyArray[j]);
							                j++;
							            }
							            else if(strcmp(keyArray[j], "class") == 0) {
							            	strcat(tempString, "struct");
							            	tempClass = nextNonWhiteCat(keyArray, &j, tempString);
							            	tempName = nextNonWhiteCat(keyArray, &j, tempString);
							            	j++;
							            	while(strcmp(keyArray[j], ";") !=0) {
				                				 strcat(tempString, keyArray[j]);
				                				 j++;
				                			}
				                			strcat(tempString, ";\n\tmyconstructor");
				                			strcat(tempString, tempClass);
				                			strcat(tempString, "(&");
				                			strcat(tempString, tempName);
				                			strcat(tempString, ");");	
				                			j++;
							            }
                                    	else{
	                                        strcat(tempString, keyArray[j]);
	                                        j++;
                                            if(strcmp(keyArray[j], "{") == 0)
                                                fBCount++;

                                            else if(strcmp(keyArray[j], "}") == 0)
                                                fBCount--;

	                                    }
                                    }
                                }
                                freeDuplicate(tempList, tempVarCount);
                                strcat(tempString, "}");
                                functionStrings[fSCounter] = malloc(sizeof(char)*columns);
                                strcpy(functionStrings[fSCounter], tempString);
                                fSCounter++;
                                fprintf(outFile,"(*%s)", newFunc);

                                /*adding to list for constructors*/
                                functionNames[fNCount] = malloc(sizeof(char)*columns);

                                /*adding to list for replacing functions*/
                                strcpy(functionNames[fNCount], newFunc);
                                strcpy(newFuncs[replaceCount], newFunc);
                                fNCount++;
                                replaceCount++;

                                /*print out parameters for function pointer in class*/
                                fprintf(outFile,"(struct %s *", currClass);
                                i++;                    
                                if(strcmp(keyArray[i], ")") !=0 && strcmp(nextNonWhiteSafe(keyArray, i), ")") != 0)
                					fprintf(outFile, ",");
                                while(strcmp(keyArray[i], ")") != 0) {
                                    if(strcmp(nextNonWhiteSafe(keyArray, i), ",") != 0 && strcmp(nextNonWhiteSafe(keyArray, i), ")") !=0 )
                                        fprintf(outFile,"%s", keyArray[i]);
                                    i++;
                                }
                                fprintf(outFile,")");
                                fBCount = 0;
                                while(strcmp(keyArray[i], "}") != 0 || fBCount != 0) {
                                    i++;
                                    if(strcmp(keyArray[i], "{") == 0)
                                        fBCount++;

                                    else if(strcmp(keyArray[i], "}") == 0)
                                        fBCount--;
                            }
                                if(strcmp(nextNonWhiteSafe(keyArray, i), ";" )!= 0) {
                                	fprintf(outFile,";");
                                }
                                strcpy(newFunc, currClass);
                            }
                            else
                                fprintf(outFile,"%s", keyArray[i]);
                        }

                        /*Adding class variables to a list*/
                        else if(inFunction == 0 && strcmp(keyArray[i], ";") == 0 ) {

                        	fprintf(outFile,"%s", keyArray[i]);
                        
                        	tempName = lastNonWhite(keyArray, i);
							j = i;
							
							do {
								j = lastNonWhiteIndex(keyArray, j);
								j = lastNonWhiteIndex(keyArray, j);
								while(strcmp(keyArray[j], "=") == 0 || strcmp(keyArray[j], ".") == 0) {
									j = lastNonWhiteIndex(keyArray, j);
									j = lastNonWhiteIndex(keyArray, j);
									tempName =nextNonWhiteSafe(keyArray, j);
								}
								
								
								tempVariables[tempVarCount] = malloc(sizeof(char)*vNum);
								strcpy(tempVariables[tempVarCount], tempName);
								tempVarCount++;
								tempName = lastNonWhite(keyArray, j);
							} while(strcmp(keyArray[j], ",") == 0);
						}
							
                        else {

                            fprintf(outFile,"%s", keyArray[i]);
                        }
                    }

                    i++;
                }
                /*exiting class*/
                inFunction = 0;
                fprintf(outFile,";");
                for(j = 0; j<fSCounter; j++) {
                    fprintf(outFile,"%s", functionStrings[j]);
                    free(functionStrings[j]);
                }
                free(functionStrings);

                fprintf(outFile, "\n\tvoid myconstructor%s(struct %s * tempStruct){\n", currClass, currClass);
                for(j = 0; j<fNCount;j++) {
                    fprintf(outFile, "\t\ttempStruct->%s = %s;\n", functionNames[j], functionNames[j]);
                    free(functionNames[j]);
                }
                free(functionNames);

                for(j = 0; j<tempVarCount; j++) {
                    
                    free(tempVariables[j]);
                }
                free(tempVariables);

                fprintf(outFile,"\t}\n");
                strcpy(createdClass[createdCount], currClass);
                createdCount++;
                if(strcmp(nextNonWhiteSafe(keyArray, i), ";") == 0) {
                    i = nextNonWhiteIndex(keyArray, i) + 1;
                }
            }

            else {
                /*save class variable along with its class*/
                constructorStrings = malloc(sizeof(char*)*20);
                conCount = 0;
                do {
	                classExists = 0;
	                if(strcmp(keyArray[i], ",") == 0) {
	                	i = nextNonWhiteIndex(keyArray, i);
	                }
	                for(j=0; j<createdCount; j++) {
	                	if(strcmp(currClass, createdClass[j]) == 0) {
	                		constructorStrings[conCount] = malloc(sizeof(char)*50);
	                		strcpy(constructorStrings[conCount], "\nmyconstructor");
	                		strcat(constructorStrings[conCount], currClass);
	                		strcat(constructorStrings[conCount], "(&");
	                		strcat(constructorStrings[conCount], keyArray[i]);
	                		strcat(constructorStrings[conCount], ");");
	                		/*fprintf(outFile, "\nmyconstructor%s(&%s);", currClass, keyArray[i]);*/
	                		conCount++;
	                		classExists = 1;
	                	}
	                }
	                if(classExists == 0) {
	                	strcpy(waitingList[waitingCount], keyArray[i]);
	                	strcat(waitingList[waitingCount], " ");
	                	strcat(waitingList[waitingCount], currClass);
	                	waitingCount++;
	                }
	                strcpy(classVariables[cVarCount], keyArray[i]);
	                strcat(classVariables[cVarCount], " ");
	                strcat(classVariables[cVarCount], currClass);
	                cVarCount++;
	                
	                if(conCount != 1 && conCount != 0) 
	                	fprintf(outFile,"%s", keyArray[i]);
	                while(strcmp(keyArray[i], ",") != 0 && strcmp(keyArray[i], ";") != 0) {
	                	i++;
	                	fprintf(outFile,"%s", keyArray[i]);
	                }
	              
	            } while(strcmp(keyArray[i], ";") != 0);
                for(j = 0; j < conCount; j++) {
                	fprintf(outFile, constructorStrings[j]);
                	free(constructorStrings[j]);
                }
                free(constructorStrings);
            }
        }
        else if(strcmp(keyArray[i], "main") == 0){
            inMain = 1;
            fprintf(outFile,"%s", keyArray[i]);
            firstEntry = 0;

        }
        else if(inMain == 1) {
        	if(strcmp(keyArray[i], "\n") == 0 && firstEntry == 0) {
				tempVar = "\0";
                tempClass = "\0";
                for(j = 0; j<waitingCount; j++) {
                	strcpy(tempString2, waitingList[j]);
                    tempVar = strtok(tempString2, " ");
                    tempClass = strtok(NULL, " ");

                	for (k = 0; k < createdCount; k++) {
	                    if (strcmp(createdClass[k], tempClass) == 0){
	                    	fprintf(outFile, "\n\tmyconstructor%s(&%s);", tempClass, tempVar);
	                    	strcpy(waitingList[j], "1 1");    		
	                	}
	                }
                }
        		firstEntry = 1;
        	}
            if(strcmp(keyArray[i], ".") == 0) {
                j = 0;

                currVar = lastNonWhite(keyArray, i);
                currFunc = nextNonWhiteSafe(keyArray, i);
                tempVar = "\0";

                

                while(strcmp(currVar, tempVar) != 0 && j<cVarCount) {
                    strcpy(tempString, classVariables[j]);
                    tempVar = strtok(tempString, " ");
                    currentClass = strtok(NULL, " ");
                    j++;
                }

                if(strcmp(currVar, tempVar) !=0) {
                	fprintf(outFile, ".");
                	continue;
                }
    
                tempFunc = "\0";
                tempClass = "\0";
                j = 0;

                /*strcpy(tempString2, oldFuncs[j]);
                tempFunc = strtok(tempString2, " ");
                tempClass = strtok(NULL, " ");
                j++;*/
 
                for(j = 0; j<=replaceCount; j++) {
                	if (strcmp(currentClass, tempClass) == 0 && strcmp(tempFunc, currFunc) == 0){
                		break;
                	}
                    strcpy(tempString2, oldFuncs[j]);
                    tempFunc = strtok(tempString2, " ");
                    tempClass = strtok(NULL, " ");
                }

                
                if(!tempFunc) {
                	fprintf(outFile, ".");
                	continue;
                }

                fprintf(outFile, ".%s", newFuncs[j-1]);
                i+=2;
                strcat(keyArray[i], "&");
                strcat(keyArray[i], currVar);
                if(strcmp(nextNonWhiteSafe(keyArray, i), ")") != 0)
                	strcat(keyArray[i], ", ");
                
            }
            fprintf(outFile,"%s", keyArray[i]);
        }
        else
            fprintf(outFile,"%s", keyArray[i]);
    }

    fclose(outFile);
    free(currClass);
    free(tempString);
    free(tempString2);
    free(newFunc);
    freeArray(keyArray, size);
    freeArray(classVariables, vNum);
    freeArray(oldFuncs, vNum);
    freeArray(newFuncs, vNum);
    freeArray(createdClass, vNum);
    freeArray(waitingList, vNum);
    /*freeArray(classArray, caSize);*/

	return 0;
}

/**
 * checkArg checks to make sure that only 1 command line arguement was entered in addition to the
 * executable. Exits the program if any more or less are entered.
 */
void checkArg(int numArg)
{
    if (numArg != 2)
    {
    	printf("Incorrect number of command line arguements. Exiting program.\n");
        exit(1);
    }
}

/**
 * nullFile takes a file pointer as input and checks if it exists. If it does not, the program
 * will exit.
 */
void nullFile(FILE* fptr) {
    if (fptr == NULL)
    {
        printf("The specified file is missing. The program cannot continue.\n");
        exit(1);
    }
}

void freeArray(char ** array, int size) {
	int i;
	for(i=0; i<size; i++) {
    	free(array[i]);
    }
    free(array);
}

char** extendArray(char ** array, int size) {
	int i;
	int j;
	char** tempArray;
	tempArray = malloc(sizeof(char*)*(size*2));
    for(i=0; i<size*2; i++) {
    	tempArray[i] = malloc(sizeof(char)*1000);
        for(j=0; j<1000; j++){
    		tempArray[i][j] = (char)0;
    	}
    }

    for(i=0; i<size; i++) {
    	for(j=0; j<1000; j++){
    		tempArray[i][j] = array[i][j];
    	}
    }

    freeArray(array, size);
    return tempArray;
}

char* nextNonWhite(char** array, int* i, FILE* outFile) {
    (*i)++;
    while(strcmp(array[*i], " ") == 0 || strcmp(array[*i], "\t") == 0 ||
        strcmp(array[*i], "\n") == 0  || strcmp(array[*i], "\r") == 0) {
        fprintf(outFile,"%s", array[*i]);
        (*i)++;
    }
    fprintf(outFile,"%s", array[*i]);
    return array[*i];
}

char* nextNonWhiteCat(char** array, int* i, char* string) {
    (*i)++;
    while(strcmp(array[*i], " ") == 0 || strcmp(array[*i], "\t") == 0 ||
        strcmp(array[*i], "\n") == 0  || strcmp(array[*i], "\r") == 0) {
        strcat(string, array[*i]);
        (*i)++;
    }
    strcat(string, array[*i]);
    return array[*i];
}

char* nextNonWhiteSafe(char** array, int i) {
    i++;
    while(strcmp(array[i], " ") == 0 || strcmp(array[i], "\t") == 0 ||
        strcmp(array[i], "\n") == 0  || strcmp(array[i], "\r") == 0) {
        i++;
    }
    return array[i];
}

int nextNonWhiteIndex(char** array, int i) {
    (i)++;
    while(strcmp(array[i], " ") == 0 || strcmp(array[i], "\t") == 0 ||
        strcmp(array[i], "\n") == 0  || strcmp(array[i], "\r") == 0) {
        (i)++;
    }
    return i;
}

char* lastNonWhite(char** array, int i) {
    i--;
    while(strcmp(array[i], " ") == 0 || strcmp(array[i], "\t") == 0 ||
        strcmp(array[i], "\n") == 0  || strcmp(array[i], "\r") == 0) {
        i--;
    }
    return array[i];
}

int lastNonWhiteIndex(char** array, int i) {
    (i)--;
    while(strcmp(array[i], " ") == 0 || strcmp(array[i], "\t") == 0 ||
        strcmp(array[i], "\n") == 0  || strcmp(array[i], "\r") == 0) {
        (i)--;
    }
    return i;
}

int isFunctionDef(char** array, int i) {
    i++;
    while(strcmp(array[i], ")") != 0) {
        i++;
    }
    i++;
    while(strcmp(array[i], " ") == 0 || strcmp(array[i], "\t") == 0 ||
        strcmp(array[i], "\n") == 0  || strcmp(array[i], "\r") == 0) {
        i++;
    }
    if(strcmp(array[i], "{") == 0)
        return 1;
    else
        return 0;
}

/*
 * Takes in a function name and adds extra characters to the end, which are
 * determined by the function's parameters.
 * function = the function to be changed
 * array = 2D character array containing parameter information
 * i = current index in the array when the concatenateFunc is called
 */
void concatenateFunc(char* function, char** array, int i) {
    char* temp;
    int cIn;
    cIn = i;
    if(strcmp(nextNonWhiteSafe(array, i), ")") != 0) {
        do{
            temp = nextNonWhiteSafe(array, cIn);
            cIn = nextNonWhiteIndex(array, cIn);

            /*Int checks*/
            if(strcmp(temp,"int") == 0) {
                if(strcmp(nextNonWhiteSafe(array, cIn), "*") == 0)
                    strcat(function,"I");
                else
                    strcat(function, "i");
            }

            /*Char checks*/
            if(strcmp(temp,"char") == 0) {
                if(strcmp(nextNonWhiteSafe(array, cIn), "*") == 0)
                    strcat(function,"C");
                else
                    strcat(function, "c");
            }

            /*double checks*/
            if(strcmp(temp,"double") == 0) {
                if(strcmp(nextNonWhiteSafe(array, cIn), "*") == 0)
                    strcat(function,"D");
                else
                    strcat(function, "d");
            }

            /*double checks*/
            if(strcmp(temp,"short") == 0) {
                if(strcmp(nextNonWhiteSafe(array, cIn), "*") == 0)
                    strcat(function,"S");
                else
                    strcat(function, "s");
            }

            /*double checks*/
            if(strcmp(temp,"long") == 0) {
                if(strcmp(nextNonWhiteSafe(array, cIn), "*") == 0)
                    strcat(function,"L");
                else
                    strcat(function, "l");
            }

            /*double checks*/
            if(strcmp(temp,"float") == 0) {
                if(strcmp(nextNonWhiteSafe(array, cIn), "*") == 0)
                    strcat(function,"F");
                else
                    strcat(function, "f");
            }


            cIn = commaIndex(array, cIn);
        } while(cIn != -1);
    }
}

int commaIndex(char** array, int i) {
    while (strcmp(array[i], ",") != 0) {
        if(strcmp(array[i], ")") == 0)
            return -1;
        i++;
    }
    return i;
}

int isVarType(char** array, int i) {
    if (strcmp(array[i], "int") == 0 || strcmp(array[i], "char") == 0 ||
        strcmp(array[i], "double") == 0 || strcmp(array[i], "float") == 0 || strcmp(array[i], "long") == 0 ||
        strcmp(array[i], "short") == 0)
        return 1;
    else if(strcmp(array[i], "*") == 0) {
        while(strcmp(array[i], "*") == 0) {
    	   i = lastNonWhiteIndex(array, i);
        }
    }
    if (strcmp(array[i], "int") == 0 || strcmp(array[i], "char") == 0 ||
        strcmp(array[i], "double") == 0 || strcmp(array[i], "float") == 0 || strcmp(array[i], "long") == 0 ||
        strcmp(array[i], "short") == 0 || strcmp(array[i], "FILE") == 0 || strcmp(array[i], "DIR") == 0)
        return 1;	 
    else
        return 0;
}

void freeDuplicate(char** array, int size) {
	int i;
	for(i=0; i<size; i++) {
    	free(array[i]);
    }
    free(array);
}
