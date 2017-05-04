
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOSTNAME  "dursley.socs.uoguelph.ca"
#define USERNAME  "ccampb21"
#define PASSWORD  "0918831"
#define DATABASE  "ccampb21"

/*
	standard error clause.
*/
void error(char *msg, MYSQL *mysql){
	printf("%s\n<BR>%s\n<BR>",msg,mysql_error(mysql));
	exit(0);
}

void error2(char *msg, MYSQL *mysql){
	printf("%s\n%s\n",msg,mysql_error(mysql));
	exit(0);
}
/*
	clear the contents of an array of char's
*/
void clrstr(char *buf){
	buf[0] = '\0';
}

int main(int argc, char *argv[]) {

	char* author = NULL;
	char* stream = NULL;
	char* text2 = NULL;
	char* flag = NULL;
	int i;

	flag = argv[1];
	if(strcmp(flag, "-access") == 0) {
		author = argv[2];
	}
	if(strcmp(flag, "-adda") == 0 || strcmp(flag, "-rema") == 0 || strcmp(flag, "-view") == 0 || 
		strcmp(flag, "-post") == 0 || strcmp(flag, "-mark") == 0 || strcmp(flag, "-increase") == 0 ||
		 strcmp(flag, "-decrease") == 0 || strcmp(flag, "-viewAll") == 0) {
		author = argv[2];
		stream = argv[3];
	}
	char text[12000];
	if(strcmp(flag, "-post") == 0) {
		text2 = argv[4];
		text[0] = '\0';
		int tCount = 0;
		for(i = 0; i < strlen(text2); i++) {
			if(text2[i] == '\'') {
				text[tCount] = '\'';
				tCount++;
				text[tCount] = '\'';
				tCount++;
			}
			else {
				text[tCount] = text2[i];
				tCount++;
			}
		}
	}


	MYSQL mysql;
	char query[12000];
	char message[512];
	MYSQL_RES *res;
	MYSQL_ROW row;

	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "db");
	if (!mysql_real_connect(&mysql, HOSTNAME, USERNAME, PASSWORD,
		DATABASE, 0, NULL, 0)) {
	   error("Could not connect to host.",&mysql);
	}
	
	clrstr(query);
	
	strcat(query, "create table if not exists authors (name char(255) not null,");
	strcat(query, "stream char(255) not null,");
	strcat(query, "last_read int,");
	strcat(query, "primary key(name,stream) )");

	/*
		Create authors table
	*/
	if(mysql_query(&mysql, query)){
	  error("Could not create author table",&mysql);
	}
	
	clrstr(query);

	strcat(query, "create table if not exists posts (name char(255) not null,");
	strcat(query, "stream char(255),");
	strcat(query, "post varchar(10000), ");
	strcat(query, "timeVar datetime)");

	/*
		Create posts table
	*/
	if(mysql_query(&mysql, query)){
	  error("Could not create post table",&mysql);
	}
	
	clrstr(query);

	strcat(query, "create table if not exists streamList (stream char(255) not null)");

	/*
		Create streamList table
	*/
	if(mysql_query(&mysql, query)){
	  error("Could not create streamList table",&mysql);
	}

	clrstr(query);
	/*Adding an author*/
	if(strcmp(flag, "-adda") == 0) {
		
		clrstr(query);

		strcpy(query, "insert into authors (name, stream, last_read) values ('");
		strcat(query, author);
		strcat(query, "','");
		strcat(query, stream);
		strcat(query, "',0)");

		if(mysql_query(&mysql, query)){
			clrstr(message);
			strcat(message, "Error adding ");
			strcat(message, author);
			strcat(message, " to the ");
			strcat(message, stream);
			strcat(message, " stream");
			error(message,&mysql);
		}
		else {
			printf("%s was added to the %s stream.<BR>", author, stream);
		}

		clrstr(query);

		strcpy(query, "insert into streamList values ('");
		strcat(query, stream);
		strcat(query, "')");

		if(mysql_query(&mysql, query)){
			error("Error adding the stream to the streamList table",&mysql);
		}

		clrstr(query);
	}

	/*Removing an author*/
	else if(strcmp(flag, "-rema") == 0) {

		clrstr(query);

		strcat(query, "select * from authors where authors.name = '");
		strcat(query, author);
		strcat(query, "' and authors.stream = '");
		strcat(query, stream);
		strcat(query, "'");

		if(mysql_query(&mysql, query))
			error("Cannot check author table",&mysql);

		if (!(res = mysql_store_result(&mysql))){
			error("failed store",&mysql);
		}
		if(mysql_num_rows(res) == 0) {
			printf("%s already does not have access to the %s stream.<BR>", author, stream);
			exit(0);
		}

		clrstr(query);

		/*
			remove author
		*/

		strcat(query, "delete from authors where authors.name = '");
		strcat(query, author);
		strcat(query, "' and authors.stream = '");
		strcat(query, stream);
		strcat(query, "'");

		if(mysql_query(&mysql, query)){
			clrstr(message);
			strcat(message, "Error removing ");
			strcat(message, author);
			strcat(message, " from the ");
			strcat(message, stream);
			strcat(message, " stream");
			error(message,&mysql);
		}
		else {
			printf("%s was successfully removed from the %s stream.<BR>", author, stream);
		}

		clrstr(query);
	}

	/*making a post*/
	else if(strcmp(flag, "-post") == 0) {
		
		clrstr(query);

		strcat(query, "select * from authors where authors.name = '");
		strcat(query, author);
		strcat(query, "' and authors.stream = '");
		strcat(query, stream);
		strcat(query, "'");

		if(mysql_query(&mysql, query))
			error("Cannot check author table",&mysql);

		if (!(res = mysql_store_result(&mysql))){
			error("failed store",&mysql);
		}
		if(mysql_num_rows(res) == 0) {
			printf("%s does not have access to the %s stream.<BR> To gain access, use the addauthor option<BR>", author, stream);
			exit(0);
		}

		clrstr(query);
		strcpy(query, "insert into posts values ('");
		strcat(query, author);
		strcat(query, "','");
		strcat(query, stream);
		strcat(query, "','");
		strcat(query, text);
		strcat(query, "', NOW())");

		if(mysql_query(&mysql, query)){
			clrstr(message);
			strcat(message, "Error adding your post to the ");
			strcat(message, stream);
			strcat(message, " stream");
			error(message,&mysql);
		}
		else {
			printf("Your message was posted<BR>");
		}

		clrstr(query);
	}

	/*Printing out the list the user has access to*/
	else if(strcmp(flag, "-access") == 0){

		sprintf(query, "select * from authors where authors.name = '%s'",author);

		if(mysql_query(&mysql, query)){
			error("ERROR Could not check the streams that you have access to.",&mysql);
		}

		if (!(res = mysql_store_result(&mysql))){
			error("failed store",&mysql);
		}
		if(mysql_num_rows(res) == 0) {
			printf("(none)<BR>");
			exit(0);
		}
		else {
			while ((row = mysql_fetch_row(res))) {
				printf("%s ", row[1]);
			}
			printf("all <BR>");
		}

		clrstr(query);

	}

	/*For when a view page is first loaded in*/
	else if(strcmp(flag, "-view") == 0){
		int num = 0;
		int count = 0;

		strcat(query, "select * from authors where authors.name = '");
		strcat(query, author);
		strcat(query, "' and authors.stream = '");
		strcat(query, stream);
		strcat(query, "'");

		if(mysql_query(&mysql, query)){
			error("ERROR Could not check the streams that you have access to.",&mysql);
		}

		if (!(res = mysql_store_result(&mysql))){
			error("failed store",&mysql);
		}
		if(mysql_num_rows(res) == 0) {
			printf("You do not have access to the %s stream<BR>", stream);
			exit(0);
		}
		row = mysql_fetch_row(res);
		num = atoi(row[2]);

		clrstr(query);

		strcat(query, "select * from posts where posts.stream = '");
		strcat(query, stream);
		strcat(query, "'");

		if(mysql_query(&mysql, query)){
			error("ERROR Failed to select posts.",&mysql);
		}
		if (!(res = mysql_store_result(&mysql))){
			error("failed store",&mysql);
		}

		count = 0;
		int totalPost = mysql_num_rows(res);


		int compare = num;
		if(compare == totalPost) {
			compare = compare - 1;
			printf("-----You have reached the Final Post-----<BR>");
		}
		while ((row = mysql_fetch_row(res))) {
			if(count == compare) {
				char copy[12000];
				strcpy(copy, row[2]);
				int j = 0;
				for(j = 0; j<strlen(copy); j++) {
					if(copy[j] == '\n')
						printf("<BR>");
					else
						printf("%c", copy[j]);
				}
				break;
			}
			count++;
		}

		
		clrstr(query);
		num++;
		if(num <= totalPost) {
			strcat(query, "update authors set last_read = 1+authors.last_read where authors.name = '");
			strcat(query, author);
			strcat(query, "' and authors.stream = '");
			strcat(query, stream);
			strcat(query, "'");

			if(mysql_query(&mysql, query))
				error("ERROR Failed to update last read post.",&mysql);

			clrstr(query);
		}

	}

	/*For when an all view page is first loaded in*/
	else if(strcmp(flag, "-viewAll") == 0){
		int num = 0;
		int count = 0;

		strcat(query, "select * from authors where authors.name = '");
		strcat(query, author);
		strcat(query, "'");

		if(mysql_query(&mysql, query)){
			error("ERROR Could not check the streams that you have access to.",&mysql);
		}

		if (!(res = mysql_store_result(&mysql))){
			error("failed store",&mysql);
		}
		if(mysql_num_rows(res) == 0) {
			printf("You do not have access to any streams.<BR>");
			exit(0);
		}
		row = mysql_fetch_row(res);
		num = 0;

		clrstr(query);

		sprintf(query, "select * from posts where stream in (select stream from authors where name = '%s')", author);

		if(mysql_query(&mysql, query)){
			error("ERROR Failed to select posts.",&mysql);
		}
		if (!(res = mysql_store_result(&mysql))){
			error("failed store",&mysql);
		}

		count = 0;
		int totalPost = mysql_num_rows(res);


		int compare = num;
		if(compare == totalPost) {
			compare = compare - 1;
			printf("-----You have reached the Final Post-----<BR>");
		}
		while ((row = mysql_fetch_row(res))) {
			if(count == compare) {
				char copy[12000];
				strcpy(copy, row[2]);
				int j = 0;
				for(j = 0; j<strlen(copy); j++) {
					if(copy[j] == '\n')
						printf("<BR>");
					else
						printf("%c", copy[j]);
				}
				break;
			}
			count++;
		}
		clrstr(query);

	}

	/*Mark all as read*/
	else if(strcmp(flag, "-mark") == 0){
		int count = 0;

		strcat(query, "select * from authors where authors.name = '");
		strcat(query, author);
		strcat(query, "' and authors.stream = '");
		strcat(query, stream);
		strcat(query, "'");

		if(mysql_query(&mysql, query)){
			error("ERROR Could not check the streams that you have access to.",&mysql);
		}

		if (!(res = mysql_store_result(&mysql))){
			error("failed store",&mysql);
		}
		if(mysql_num_rows(res) == 0) {
			printf("You do not have access to the %s stream<BR>", stream);
			exit(0);
		}

		clrstr(query);

		strcat(query, "select * from posts where posts.stream = '");
		strcat(query, stream);
		strcat(query, "'");

		if(mysql_query(&mysql, query)){
			error("ERROR Failed to select posts.",&mysql);
		}
		if (!(res = mysql_store_result(&mysql))){
			error("failed store",&mysql);
		}

		int totalPost = mysql_num_rows(res);

		clrstr(query);

		sprintf(query, "update authors set last_read = %d where authors.name = '%s' and authors.stream = '%s'",totalPost, author, stream);

		if(mysql_query(&mysql, query))
			error("ERROR Failed to update last read post.",&mysql);

		clrstr(query);

		int compare = totalPost;
		if(compare == totalPost) {
			compare = compare - 1;
			printf("-----You have reached the Final Post-----<BR>");
		}
		count = 0;
		while ((row = mysql_fetch_row(res))) {
			if(count == compare) {
				char copy[12000];
				strcpy(copy, row[2]);
				int j = 0;
				for(j = 0; j<strlen(copy); j++) {
					if(copy[j] == '\n')
						printf("<BR>");
					else
						printf("%c", copy[j]);
				}
				break;
			}
			count++;
		}

		
		clrstr(query);
	}

	/*Next post*/
	else if(strcmp(flag, "-increase") == 0){
		int offset = atoi(argv[4]);
		int num = 0;
		int count = 0;

		if(strcmp(stream, "all") != 0) {
			strcat(query, "select * from authors where authors.name = '");
			strcat(query, author);
			strcat(query, "' and authors.stream = '");
			strcat(query, stream);
			strcat(query, "'");

			if(mysql_query(&mysql, query)){
				error("ERROR Could not check the streams that you have access to.",&mysql);
			}

			if (!(res = mysql_store_result(&mysql))){
				error("failed store",&mysql);
			}
			if(mysql_num_rows(res) == 0) {
				printf("You do not have access to the %s stream<BR>", stream);
				exit(0);
			}
			row = mysql_fetch_row(res);
			num = atoi(row[2]);
		}
		else {
			strcat(query, "select * from authors where authors.name = '");
			strcat(query, author);
			strcat(query, "'");

			if(mysql_query(&mysql, query)){
				error("ERROR Could not check the streams that you have access to.",&mysql);
			}

			if (!(res = mysql_store_result(&mysql))){
				error("failed store",&mysql);
			}
			if(mysql_num_rows(res) == 0) {
				printf("You do not have access to any streams.<BR>");
				exit(0);
			}
			row = mysql_fetch_row(res);
			num = 0;
		}

		clrstr(query);

		if(strcmp(stream, "all") != 0) {
			strcat(query, "select * from posts where posts.stream = '");
			strcat(query, stream);
			strcat(query, "'");
		}
		else{
			sprintf(query, "select * from posts where stream in (select stream from authors where name = '%s')", author);
		}

		if(mysql_query(&mysql, query)){
			error("ERROR Failed to select posts.",&mysql);
		}
		if (!(res = mysql_store_result(&mysql))){
			error("failed store",&mysql);
		}

		int totalPost = mysql_num_rows(res);
		int compare = num;

		if(strcmp(stream, "all") != 0) {
			if(offset < 0) {
				compare += offset;
				compare--;
			}
		}
		else{
			compare+=offset;
		}

		if(compare == totalPost) {
			compare = compare - 1;
			printf("-----You have reached the Final Post-----<BR>");
		}

		count = 0;
		while ((row = mysql_fetch_row(res))) {
			if(count == compare) {
				char copy[12000];
				strcpy(copy, row[2]);
				int j = 0;
				for(j = 0; j<strlen(copy); j++) {
					if(copy[j] == '\n')
						printf("<BR>");
					else
						printf("%c", copy[j]);
				}
				break;
			}
			count++;
		}

		
		clrstr(query);
		num++;
		if(offset >= 0 && strcmp(stream, "all") != 0) {
			if(num <= totalPost) {
				strcat(query, "update authors set last_read = 1+authors.last_read where authors.name = '");
				strcat(query, author);
				strcat(query, "' and authors.stream = '");
				strcat(query, stream);
				strcat(query, "'");

				if(mysql_query(&mysql, query))
					error("ERROR Failed to update last read post.",&mysql);

				clrstr(query);
			}
		}
	}

	else if(strcmp(flag, "-decrease") == 0){
		int offset = atoi(argv[4]);
		int num = 0;
		int count = 0;

		if(strcmp(stream, "all") != 0) {
			strcat(query, "select * from authors where authors.name = '");
			strcat(query, author);
			strcat(query, "' and authors.stream = '");
			strcat(query, stream);
			strcat(query, "'");

			if(mysql_query(&mysql, query)){
				error("ERROR Could not check the streams that you have access to.",&mysql);
			}

			if (!(res = mysql_store_result(&mysql))){
				error("failed store",&mysql);
			}
			if(mysql_num_rows(res) == 0) {
				printf("You do not have access to the %s stream<BR>", stream);
				exit(0);
			}
			row = mysql_fetch_row(res);
			num = atoi(row[2]);
		}
		else {
			strcat(query, "select * from authors where authors.name = '");
			strcat(query, author);
			strcat(query, "'");

			if(mysql_query(&mysql, query)){
				error("ERROR Could not check the streams that you have access to.",&mysql);
			}

			if (!(res = mysql_store_result(&mysql))){
				error("failed store",&mysql);
			}
			if(mysql_num_rows(res) == 0) {
				printf("You do not have access to any streams.<BR>");
				exit(0);
			}
			row = mysql_fetch_row(res);
			num = 0;
		}

		clrstr(query);

		if(strcmp(stream, "all") != 0) {
			strcat(query, "select * from posts where posts.stream = '");
			strcat(query, stream);
			strcat(query, "'");
		}
		else{
			sprintf(query, "select * from posts where stream in (select stream from authors where name = '%s')", author);
		}

		if(mysql_query(&mysql, query)){
			error("ERROR Failed to select posts.",&mysql);
		}
		if (!(res = mysql_store_result(&mysql))){
			error("failed store",&mysql);
		}
	
		int totalPost = mysql_num_rows(res);
		int compare = num + offset;
		if(num == totalPost) {
			compare--;
		}
		else
			compare--;

		if(compare <= -1) {
			compare = 0;
			printf("---You have reached the first post---<BR>");
		}

		count = 0;
		while ((row = mysql_fetch_row(res))) {
			if(count == compare) {
				char copy[12000];
				strcpy(copy, row[2]);
				int j = 0;
				for(j = 0; j<strlen(copy); j++) {
					if(copy[j] == '\n')
						printf("<BR>");
					else
						printf("%c", copy[j]);
				}
				break;
			}
			count++;
		}

		
		clrstr(query);
	}

	else if(strcmp(flag, "-reset") == 0) {

		clrstr(query);

		/*Rmove author table*/
		strcat(query, "drop table if exists authors");

		if(mysql_query(&mysql,query))
	  		error("failed to remove tables",&mysql);
	  	else
	  		printf("The author table was successfully dropped\n");

		clrstr(query);

		/*Remove post table*/
		strcat(query, "drop table if exists posts");

		if(mysql_query(&mysql,query))
	  		error("failed to remove tables",&mysql);
	  	else
	  		printf("The posts table was successfully dropped\n");

		clrstr(query);

		/*Remove streamList table*/
		strcat(query, "drop table if exists streamList");

		if(mysql_query(&mysql,query))
	  		error("failed to remove tables",&mysql);
	  	else
	  		printf("The streamList table was successfully dropped\n");

		clrstr(query);
	}

	else if(strcmp(flag, "-clear") == 0) {
		clrstr(query);

		/*Clear the author table*/
		strcpy(query, "select * from authors");
	
		if(mysql_query(&mysql, query))
			error2("Cannot check author table",&mysql);

		if (!(res = mysql_store_result(&mysql))){
			error2("failed store 1",&mysql);
		}
		if(mysql_num_rows(res) == 0) {
			printf("There are no authors already\n");
		}
		else {

			clrstr(query);

			strcat(query, "truncate table authors");


			if(mysql_query(&mysql,query))
		  		error2("failed to clear author table",&mysql);
		  	else {
		  		printf("The author table was successfully cleared.\n");
		  	}
	  	}
		

		clrstr(query);

		/*Clear the posts table*/
		strcpy(query, "select * from posts");
	
		if(mysql_query(&mysql, query))
			error2("Cannot check posts table",&mysql);

		if (!(res = mysql_store_result(&mysql))){
			error2("failed store",&mysql);
		}
		if(mysql_num_rows(res) == 0) {
			printf("There are no posts already\n");
		}
		else {

			clrstr(query);

			strcat(query, "truncate table posts");

			if(mysql_query(&mysql,query))
		  		error2("failed to clear the posts table",&mysql);
		  	else
		  		printf("The posts table was successfully cleared.\n");

			clrstr(query);
		}

		/*Clear the streamList table*/
		strcpy(query, "select * from streamList");
	
		if(mysql_query(&mysql, query))
			error2("Cannot check streamList table",&mysql);

		if (!(res = mysql_store_result(&mysql))){
			error2("failed store",&mysql);
		}
		if(mysql_num_rows(res) == 0) {
			printf("There are no streams already\n");
		}
		else {

			clrstr(query);

			strcat(query, "truncate table streamList");

			if(mysql_query(&mysql,query))
		  		error2("failed to clear the streamList table",&mysql);
		  	else
		  		printf("The streamList table was successfully cleared.\n");
		}

		clrstr(query);
	}
	
	/*
		print author and stream
	*/
	else if(strcmp(flag, "-users") == 0) {

		clrstr(query);

		strcpy(query, "select * from authors");
	
		if(mysql_query(&mysql, query))
		  error2("Cannot print authors",&mysql);
		
		/*
			Store results from query into res structure.
		*/
		if (!(res = mysql_store_result(&mysql))){
			error2("failed store 1",&mysql);
		}
		if(mysql_num_rows(res) == 0) {
			printf("There are no authors\n");
		}

		while ((row = mysql_fetch_row(res))) {
			printf("%s, %s\n", row[0],row[1]);
		}

		clrstr(query);
	}

	else if(strcmp(flag, "-streams") == 0) {
		
		clrstr(query);

		strcpy(query, "select distinct stream from streamList");
	
		if(mysql_query(&mysql, query))
		  error2("Cannot print streams",&mysql);
		
		/*
			Store results from query into res structure.
		*/
		if (!(res = mysql_store_result(&mysql))){
			error2("failed store 1",&mysql);
		}
		if(mysql_num_rows(res) == 0) {
			printf("There are no streams\n");
		}

		while ((row = mysql_fetch_row(res))) {
			printf("%s\n", row[0]);
		}

		clrstr(query);
	}

	else if(strcmp(flag, "-posts") == 0) {
		
		clrstr(query);

		strcpy(query, "select post from posts");
	
		if(mysql_query(&mysql, query))
		  error2("Cannot search post table",&mysql);
		
		/*
			Store results from query into res structure.
		*/
		if (!(res = mysql_store_result(&mysql))){
			error2("failed store 1",&mysql);
		}
		if(mysql_num_rows(res) == 0) {
			printf("There are no posts\n");
		}

		while ((row = mysql_fetch_row(res))) {
			printf("%s\n", row[0]);
		}

		clrstr(query);
	}

	else if(strcmp(flag, "-help") == 0) {
		
		printf("********************\n"
			   "     db Usage\n"
			   "********************\n"
			   "\n"
			   "To clear all the tables, run \"./db -clear\"\n\n"
			   "To drop all the tables, run \"./db -reset\"\n\n"
			   "To print out all the posts, run \"./db -posts\"\n\n"
			   "To print out all the users, run \"./db -users\"\n\n"
			   "To print out all the streams, run \"./db -clear\"\n\n");
	}
	
	
	mysql_close(&mysql);

	return 0;
}