list_src=linkedlist.c
list_headers=list.h

tester_src=dev/tester/tester.c dev/tester/common.c
tester_headers=dev/tester/common.h

headers=$(list_headers) $(tester_headers)

all: tester

tester: $(list_src) $(tester_src) $(headers)
	@gcc -Wall -std=gnu11 $(list_src) $(tester_src) -o $@

clean:
	rm tester
