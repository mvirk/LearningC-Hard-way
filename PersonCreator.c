#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <ctype.h>

#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"
//#define TR_DEBUG(ANSI_COLOR_RED, f_, ... ,ANSI_COLOR_RESET) printf((f_), ##__VA_ARGS__)
#define TR_DEBUG(y)    printf(ANSI_COLOR_YELLOW "%s" ANSI_COLOR_RESET "\r\n",y);

struct Person {
	char *name;
	int age;
	int height;
	int weight;
};

void Print_Person(struct Person *person);
void Destroy_Person(struct Person *person);
int string_2_int(char *string);

struct Person *Create_Person(char *name, int age, int height, int weight){

	/* Define the structure */
	struct Person *who;
	/* Initialize the struct and allocate memory for that */
	who = malloc(sizeof(struct Person));
	/* Check if malloc was successful and valid memory is allocated */
	assert(who!=NULL);
	/* Fill the structure with values in the arguments */
	who->name = name;
	who->age = age;
	who->height = height;
	who->weight = weight;

	return who;

}

void Destroy_Person(struct Person *person){

	assert(person!=NULL);
	free(person);

}

void Print_Person (struct Person *person){

	printf("Memory Address of this Person: %p\r\n", person);
	printf("Name: %s\r\n", person->name);
	printf("Age: %i\r\n", person->age);
	printf("Height: %i\r\n", person->height);
	printf("weight: %i\r\n", person->weight);
	printf(" -----  -----  ----\r\n");

}

int string_2_int(char *string){
	int result=0;
	int i=0;
	int length = strlen(string);

	for(i=0; i<length; i++){
		result=result*10+(string[i]-'0');
	}
	return result;
}

int main (int argc, char *argv[]){

	char *name=0;
	char *age = 0;
	char *height = 0;
	char *weight = 0;
	bool inputCheck=true;

	if(argc!=5){
		TR_DEBUG("Error: Insufficient Arguments. Dropping user input. Must be 4.\r\n");
		inputCheck=false;
	}
	else if(argc==5){
		printf("argv1=%s", argv[1]);
		if(!isalpha(*(argv[1]))){
			TR_DEBUG("Error: 1st argument must be a string. NAME=string\r\n");
			inputCheck=false;
		}
		if(!isdigit(*(argv[2]))){
			TR_DEBUG("Error: 2nd argument must be a number. AGE=number\r\n");
			inputCheck=false;
		}
		if(!isdigit(*(argv[3]))){
			TR_DEBUG("Error: 3rd argument must be a number. HEIGHT=number\r\n");
			inputCheck=false;
		}
		if(!isdigit(*(argv[4]))){
			TR_DEBUG("Error: 4th argument must be a string. WEIGHT=number\r\n");
			inputCheck=false;
		}
	}

	name = argv[1];
	age = argv[2];
	height = argv[3];
	weight = argv[4];		

	/* Person Creator*/
	struct Person *Hasnain = Create_Person("Hasnain", 27, 180, 100);
	struct Person *Arooj = Create_Person("Arooj", 31, 160, 70);

	/* Print the Person Information*/
	Print_Person(Hasnain);
	Print_Person(Arooj);

	/* Destroy the Person*/
	Destroy_Person(Hasnain);
	Destroy_Person(Arooj);

	/* Creating, Printing, Destroying Random Person */
	if(inputCheck){
	struct Person *RandomPerson = Create_Person(name, string_2_int(age), string_2_int(height), string_2_int(weight));
	Print_Person(RandomPerson);
	Destroy_Person(RandomPerson);
	}

	return 0;


}