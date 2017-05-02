list_src=linkedlist.c
main_src=dev/tester/tester.c dev/tester/common.c

header_src=list.h dev/tester/common.h

all: tester

tester: $(list_src) $(main_src) $(header_src)
	gcc -std=gnu11 $(list_src) $(main_src) -o tester

clean:
	rm tester
