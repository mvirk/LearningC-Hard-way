#include <stdio.h>

int main (int argc,  char *argv[])
{
	int i=0;
	printf("ARGC %d: \n", argc);
		for (i=1; i<argc; i++){
			if(i==2){
				argv[i] = NULL;
			}
			else if(i==1){
				printf("You have only one argument. you SUCK !!");
			}
		printf("\t ARGV[%d]: %s \n",i, argv[i]);
		}

	char *states[] = {"Washington", NULL, "California", "Texas"}; 
	int num_states = 4;

		for (i=0; i<num_states; i++){
			printf("\t states[%d]: %s \n", i, states[i]);
		}

		return 0;

}