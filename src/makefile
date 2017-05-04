all: db translator addauthor post view produceList

view: view.py
	chmod +x view.py

produceList:
	chmod +x produceList.py

db: db.o
	gcc db.o -o db -lmysqlclient -L/usr/lib/x86_64-linux-gnu/

db.o: db.c
	gcc -Wall -ansi -c -g db.c -o db.o

translator: translator.c
	gcc -Wall -ansi -g translator.c -o translator

addauthor: addauthor.o libstream.a
	gcc addauthor.o -o addauthor -lstream -L.

post: post.o libstream.a
	gcc post.o -o post -lstream -L.

addauthor.o: addauthor.c stream.h
	gcc -Wall -ansi -g -c addauthor.c -o addauthor.o

post.o: post.c stream.h
	gcc -Wall -ansi -g -c post.c -o post.o

libstream.a: stream.c stream.h
	gcc -Wall -ansi -g -c stream.c -o stream.o;\
	ar cr libstream.a stream.o

post.c: a1 post.cc
	./a1 post.cc

a1: a1.c a1.h
	gcc -Wall -ansi -g a1.c a1.h -o a1

#cleans up executables, objects, the library and the generated c file
clean:
	rm *.o a1 addauthor post libstream.a post.c translator db

#removes all the contents of the message folder and the message folder itself
cleanM:
	rm messages/*;\
	rmdir messages

# server:
# 	scp a4.tar ccampb21@2750web.socs.uoguelph.ca:/srv/www/ccampb21/

server:
	scp makefile readme.txt addauthor.c post.cc stream.c stream.h a1.c a1.h translator.c db.c index.wpml index.php post.wpml post.php main_menu.wpml main_menu.php view_1.php view_1.wpml view_2.php view_2.wpml produceList.py view.py ccampb21@2750web.socs.uoguelph.ca:/srv/www/ccampb21/

serverSubmit:
	scp a4.tar ccampb21@2750web.socs.uoguelph.ca:/srv/www/ccampb21/

compress:
	tar cf a4.tar makefile readme.txt addauthor.c post.cc stream.c stream.h a1.c a1.h translator.c db.c index.wpml index.php post.wpml post.php main_menu.wpml main_menu.php view_1.php view_1.wpml view_2.php view_2.wpml produceList.py view.py