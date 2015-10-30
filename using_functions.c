#include <stdio.h>
#include <ctype.h>
#include <string.h>

//int print_arguments(int argc, char* argv[]);
void print_letters(char args[], int length);
//int can_print_it(char ch);

int print_arguments(int argc, char* argv[]){

	int i = 0, length =0;

	for(i=1; i<argc; i++){
		length = strlen(argv[i]);
		print_letters(argv[i], length);
			}

	return 0;
}

void print_letters(char args[], int length){
	int i=0;
	//while(args[i]!='\0'){
	while(i<length){
		//if(can_print_it(args[i])){
		if(isalpha(args[i])||isblank(args[i])){
			printf("'%c' == %d", args[i], args[i]);
		}
		i++;
	}
	printf("\n");
}


/*int can_print_it(char ch){
	return isalpha(ch) || isblank(ch);
}*/

int main(int argc, char* argv[]){
	print_arguments(argc, argv);
	return 0;
}