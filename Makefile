hash: hash_table.c
	gcc -pedantic -Wall -c -g hash_table.c

tests: unit_tests.c
	gcc -Wall unit_tests.c -g hash_table.c -lcunit -o unit_tests 

memtest: unit_tests
	valgrind --leak-check=full ./unit_tests
	