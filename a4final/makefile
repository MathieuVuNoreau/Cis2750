
all:
	gcc -Wall -g -pedantic -std=c99 -c listio.c listio.h
	ar rcs liblistio.a listio.o
	gcc -Wall -g -pedantic -std=c99 -I/user/include/python2.7 a4.c -lpython2.7 liblistio.a -o a4
	gcc mydb.c -o mydb.o -c
	gcc mydb.o -o db -lmysqlclient -L/usr/lib/x86_64-linux-gnu/
