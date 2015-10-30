#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main ()
{

	
int number[4]={0};
char characters[4]={'a'};

printf ("Number:\n \t %d \t %d \t %d \t %d \n", number[0], number[1], number[2], number[3]);
printf ("Character:\n \t %c \t %c \t %c \t %c \n", characters[0], characters[1], characters[2], characters[3]);

number[0] =1;
number[1] =2;
number[2] =3;
number[3] =4;

characters[0] ='Z';
characters[1] ='E';
characters[2] ='D';
characters[3] ='\0';

printf ("Number Modified:\n \t %d \t %d \t %d \t %d \n", number[0], number[1], number[2], number[3]);
printf ("Character Modified:\n \t %c \t %c \t %c \t %c \n", characters[0], characters[1], characters[2], characters[3]);

printf("Printing Characters[] like a string, %s \n", characters);

char *another_way = "ZED";
printf("Another way via a Pointer, %s \n", another_way);
printf ("Another way, pointer, character wise:\n \t %c \t %c \t %c \t %c \n", characters[0], characters[1], characters[2], characters[3]);

return 0;
}