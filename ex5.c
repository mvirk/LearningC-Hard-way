#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
	if (argc!=2){
		printf("ERROR: You suck. I need one argument. \n");

		return 1;
	}

	int i=0;
	int length = strlen(argv[1]);
	char letter;
	char all_letters[length];

	
	printf("Length of ARGV: %d\n", length);

	for (i=0; argv[1][i]!='\0'; i++){
		
		letter=argv[1][i];
		switch (letter){

			case 'a':
				all_letters[i] = letter-32;
				printf("%d: a - is a vowel.\n", i);
				break;
			case 'A':
				printf("%d: A - is a vowel.\n", i);
				all_letters[i] = letter+32;
				break;

			case 'i':
				all_letters[i] = letter-32;
				printf("%d: i - is a vowel.\n", i);
				break;
			case 'I':
				printf("%d: I - is a vowel.\n", i);
				all_letters[i] = letter+32;
				break;

			case 'o':
				all_letters[i] = letter-32;
				printf("%d: o - is a vowel.\n", i);
				break;
			case 'O':
				printf("%d: O - is a vowel.\n", i);
				all_letters[i] = letter+32;
				break;

			case 'u':
				all_letters[i] = letter-32;
				printf("%d: u - is a vowel.\n", i);
				break;
			case 'U':
				printf("%d: U - is a vowel.\n", i);
				all_letters[i] = letter+32;
				break;

			default:
				printf("%d: is not a vowel.\n",i );
				if(letter<91){
					all_letters[i] = letter+32;
				}
				else if(letter>96){
					all_letters[i] = letter-32;
				}

		}
	}
			printf("ALL LETTERS:");
			for (i=0; i<length; i++){
			printf("%c", all_letters[i]);
			}
			printf("\n");
			
	return 0;
}