#include <stdio.h>

int main (int argv, char *argc[]){

	int i=0;

	/* --- Way 1 --- */

	for (i=1; i<argv; i++){
		printf("value at argc = %s \r\n", *(argc+i));
		printf("The address at argc = %p \r\n", argc+i);
	}

	/* --- Way 2 --- */

	char **argc_elements = argc;

	for (i=1; i<argv; i++){
		printf("value at argc = %s \r\n", argc_elements[i]);
		printf("The address at argc = %p \r\n", argc_elements[i]);
	}

	return 0;
}