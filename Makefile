all: tester

tester: linkedlist.c dev/tester/tester.c list.h
	gcc -std=gnu11 linkedlist.c dev/tester/tester.c -o tester
