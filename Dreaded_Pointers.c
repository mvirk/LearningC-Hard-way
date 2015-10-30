#include <stdio.h>

int main (){

	int ages [] = {21, 22, 23 ,24};
	char *names[] = {"zainab", "ayesha", "sunny", "arooj"};


	/* --- First way, looping through the arrays --- */

	int count_elements = sizeof(ages)/sizeof(int);
	printf("No. of elements in ages[] = %d\r\n", count_elements);
	int i=0;

	for (i=0; i<count_elements; i++){
		printf("Name = %s, Age=%d \r\n", names[i], ages[i]);
	}


	/* --- Second way, through pointers ---*/

	int *cur_ages = ages;
	char **cur_names = names;

	for (i=0; i<count_elements; i++){
		printf("Name via ptr = %s, Age via ptr=%d \r\n", *(cur_names+i), *(cur_ages+i));
	}

	/* --- Third way, pointers are just arrays --- */

	for (i=0; i<count_elements; i++){
		printf("Name via ptr_array = %s, Age via ptr_array=%d \r\n", cur_names[i], cur_ages[i]);
	}

	/* --- Fourth way, stupidity with pointers --- */

	printf ("\r\n ------ Now some madness, crazy looping ------\r\n");
	
	for (cur_ages=ages, cur_names=names; cur_ages-ages<count_elements; cur_ages++, cur_names++){
		printf("\ncur_ages=%p, ages=%p, distance=%i \n", cur_ages, ages, cur_ages-ages);
		printf("\nName via crazy_ptr =%s, Age via crazy_ptr =%d\n", *cur_names, *cur_ages);
	}

	return 0;







}