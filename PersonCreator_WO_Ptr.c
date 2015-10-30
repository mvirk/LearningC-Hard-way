#include <stdio.h>


struct Person {
	char *name;
	int age;
	int height;
	int weight;
};

void Print_Person(struct Person person);


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
	printf("Height: %d \r\n", person.Height);
	printf("weight: %d \r\n", person.weight);
}


int main(int argc, char *argv[]){

	struct Person Arooj = Create_Person("Arooj", 29, 170, 80);
	struct Person Hasnain = Create_Person("Hasnain", 27, 185, 100);

	Print_Person(Arooj);
	Print_Person(Hasnain);

	struct Person Arooj = {0};
	struct Person Hasnain = {0};

}