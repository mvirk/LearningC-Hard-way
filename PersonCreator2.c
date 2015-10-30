#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define TR_DEBUG(y)		printf(ANSI_COLOR_YELLOW "%s \r\n" ANSI_COLOR_RESET, y);
#define TR_ERROR(y)		printf(ANSI_COLOR_RED "%s \r\n" ANSI_COLOR_RESET, y);

struct Person {
	char *name;
	int age;
	int height;
	int weight;
};

static const struct Person EmptyStruct;

void Print_Person(struct Person person);
int Str2int(char *string);


struct Person Create_Person(char *name, int age, int height, int weight){
	struct Person who;
	who.name = name;
	who.age = age;
	who.height = height;
	who.weight = weight;

	return who;
}

void Print_Person(struct Person person){
	printf("Name: %s \r\n", person.name);
	printf("Age: %d \r\n", person.age);
	printf("Height: %d \r\n", person.height);
	printf("weight: %d \r\n", person.weight);
}

int Str2int(char *string){
	int result = 0;
	int length = strlen(string);
	int i=0;

	for(i=0; i<length; i++){
		result = result*10+(string[i]-'0');
	}

	return result;
}


int main(int argc, char *argv[]){

	char *name, *age, *height, *weight;
	bool inputChecked = true;

	if(argc==5){
		if(!isalpha(*(argv[1]))){
			TR_ERROR("Argument 1 must be string.");
			inputChecked=false;
		}
		if(!isdigit(*(argv[2]))){
			TR_ERROR("Argument 2 must be an int.");
			inputChecked=false;
		}
		if(!isdigit(*(argv[3]))){
			TR_ERROR("Argument 3 must be an int.");
			inputChecked=false;
		}
		if(!isdigit(*(argv[4]))){
			TR_ERROR("Argument 4 must be an int.");
			inputChecked=false;
		}
	}

	if(argc==1){
		TR_DEBUG("[Optional] You can provide four arguments, if interested in initializing a person.");
		inputChecked=false;
	}
		

	struct Person Arooj = Create_Person("Arooj", 29, 170, 80);
	struct Person Hasnain = Create_Person("Hasnain", 27, 185, 100);

	Print_Person(Arooj);
	Print_Person(Hasnain);

	Arooj = EmptyStruct;
	Hasnain = EmptyStruct;

	if(Arooj.age==0){
		TR_DEBUG("Arooj reset.");
	}
	if(Hasnain.name==0){
		TR_DEBUG("Hasnain reset.");
	}

	if(inputChecked==true){
		name = argv[1];
		age = argv[2];
		height = argv[3];
		weight = argv[4];

		struct Person Random = Create_Person(name, Str2int(age), Str2int(height), Str2int(weight));
		Print_Person(Random);

		Random=EmptyStruct;

		if(Random.height==0){
			TR_DEBUG("Random reset.")
		}
	}

	return 0;

}