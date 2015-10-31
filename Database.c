#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>


/* --- Various Macros defined. Setting the colour of Traces and data lengths etc. --- */
#define 	ANSI_COLOR_YELLOW	"\x1b[33m"	
#define		ANSI_COLOR_RED		"\x1b[31m"
#define 	ANSI_COLOR_GREEN    "\x1b[32m"
#define 	ANSI_COLOR_RESET	"\x1b[0m"
#define 	ANSI_COLOR_CYAN     "\x1b[36m"
#define 	BPurple				"\033[1;35m" 
#define 	Color_Off			"\033[0m" 

#define		TR_ERROR(y)		printf(ANSI_COLOR_RED "\n[ERROR]:  %s \r\n" ANSI_COLOR_RESET, y);
#define 	TR_DEBUG(y)		printf(ANSI_COLOR_YELLOW "\n[DEBUG]:  %s \r\n" ANSI_COLOR_RESET, y);
#define 	TR_MESSAGE(y)	printf(ANSI_COLOR_CYAN "\n[MESSAGE:] %s \r\n" ANSI_COLOR_RESET, y);
#define 	TR_MAN(y)		printf(ANSI_COLOR_GREEN "\n %s \r\n" ANSI_COLOR_RESET, y);
#define 	TR_ENTRY(y)		printf(BPurple "\n %s \r\n" Color_Off, y);

#define 	MAX_DATA_LEN	512 /* 512 characters, it means 512 bytes*/
#define 	MAX_ROWS		100


/*---------------------------------------------------------------*/
/* ---  Data Structures and definitions (Global Definition)  --- */	
/*---------------------------------------------------------------*/

// Defines the structure for entry with id and stuff
typedef struct Entry{
	uint8_t id;
	uint8_t setFlag;
	char *name;
	char *email;
} Entry;

//Defines the actual Database structure whoch holds MAX_ROWS entries in it
typedef struct Database{
	Entry entry[MAX_ROWS];
} Database;

//Defines what is the state of Operation
typedef enum{
	INIT=0,
	INSERT,
	FETCH,
	DELETE,
	LIST,
}Operation;

// A structure providing information regarding DB, OperationMode, user arguments and internal messages
typedef struct Info{
	char *DB_NAME;
	Operation state;
	char *Message;
	uint8_t Num_Args;
}Info;

//This structure handles the connection of the user to the Database instance in the stack 
//and in the heap, i.e., in the file stored in the memory.
typedef struct Connection{
	FILE *stream;
	Database *dB;
	Info *info;
} Connection;



/*---------------------------------------------------------------*/
/* 	 					Function Protoypes  					 */	
/*---------------------------------------------------------------*/

Connection *Database_Open(Info *info);
void die_motherfucker(char *message);
int String2Int(char *string);
void Load_DB2Stack(Connection *connection);
void InitializeDatabase(Connection *connection, char *OptionalArguments[]);
uint8_t InsertEntry(Connection *connection, char *OptionalArguments[]);
uint8_t FetchEntry(Connection *connection, char *id);
void Database_Close(Connection *connection);


/*---------------------------------------------------------------*/
/* 	 					Function Definitions  					 */	
/*---------------------------------------------------------------*/

void die_motherfucker(char *message){
	if (errno){
		TR_ERROR(message);
		perror("");
	}
	else{
		TR_ERROR(message);
	}
exit(1);
}

int String2Int(char *string){
	int result=0;
	int length = strlen(string);
	int i=0;

	for (i=0; i<length; i++){
	result = result*10+(string[i]-'0');
	}
	return result;
}

Connection* Database_Open(Info *info){

	Connection *connection = (Connection*)malloc(sizeof(Connection));
	if(!connection) die_motherfucker("Memory allocation failed for Connection.");
	connection->dB = (Database*)malloc(sizeof(Database));
	if(!connection->dB) die_motherfucker("Memory allocation failed for Database.");
	connection->info = info;
	connection->info->Message = malloc(MAX_DATA_LEN*sizeof(char));

	switch(connection->info->state){
		case(INIT):
			/*Abort if the Database exists already.*/
			if((connection->stream=fopen(connection->info->DB_NAME, "r"))){
			die_motherfucker("Cannot Initialize. A DB already exists with the name provided.");
			}
			/*Else, create Database with read and write access. Initialize it with dummy values And load it over stack*/
			else {
			connection->stream = fopen(connection->info->DB_NAME, "w+");
			}
			break;
		case(INSERT):
			connection->stream = fopen(connection->info->DB_NAME, "r+");
			break;
		case(FETCH):
			connection->stream = fopen(connection->info->DB_NAME, "r");
		case(DELETE):
			break;
		case(LIST):
			break;
		default: 
			break;
	}

	/* Check if the file is opened, i.e., connection->stream is true*/
	if(connection->stream){
		//Load_DB2Stack(connection);
		sprintf(connection->info->Message, "Connection -> %s --- Established.", connection->info->DB_NAME);
		TR_MESSAGE(connection->info->Message);
	}
	else{
		die_motherfucker("Failed to Open requested Database.");
	}

	return connection;

}

void Load_DB2Stack(Connection *connection){
	int retcode = fread(connection->dB, sizeof(Database), 1, connection->stream);
	if(!retcode) die_motherfucker("Failure to load Database.");	
}

void InitializeDatabase(Connection *connection, char *OptionalArguments[]){

	int i=0;

		for (i=0; i<MAX_ROWS; i++){
			/* Prototype for struct initialization */
			Entry dummy_entry = {.id=i, .setFlag=0};
			connection->dB->entry[i] = dummy_entry;
		}	
	/*Check if there is any entry to add with initialization*/
	if(connection->info->Num_Args==6){
		InsertEntry(connection, OptionalArguments);
	}
}

uint8_t InsertEntry(Connection *connection, char *OptionalArguments[]){

	char *id = OptionalArguments[3];
	char *name = OptionalArguments[4];
	char *email = OptionalArguments[5];
	int retcode = 0;
	
	uint8_t ID = (uint8_t)String2Int(id);
	sprintf(connection->info->Message, "id = %d", ID);
	TR_DEBUG(connection->info->Message);

	rewind(connection->stream);
	if(connection->dB->entry[ID].setFlag){
		die_motherfucker("Cannot insert an entry. ID exists.");
	}
	else{
		connection->dB->entry[ID].setFlag = 1;
		connection->dB->entry[ID].name = name;
		connection->dB->entry[ID].email = email;
		retcode = fwrite(connection->dB, sizeof(Database), 1, connection->stream);
		if(!retcode){
			die_motherfucker("Could not insert an Entry. Failed to Write.");
		}
		else{
			sprintf(connection->info->Message,"Data inserted in Database=%s, with id=%d, and the state=%d", connection->info->DB_NAME, ID, connection->info->state);
			printf("\n %s \n", connection->dB->entry[ID].name);
			printf("\n %s \n", connection->dB->entry[ID].email);
			TR_MESSAGE(connection->info->Message);
		}
	}
	return 0;
}

uint8_t FetchEntry(Connection *connection, char *id){
	
/*	char *fetched_id= malloc(sizeof(char*));
	char *fetched_entry = malloc(MAX_DATA_LEN*sizeof(char));*/
	uint8_t ID = (uint8_t)String2Int(id);
	sprintf(connection->info->Message, "Fetching, entry id = %d", ID);
	TR_DEBUG(connection->info->Message);

	printf("\n%d\n", connection->dB->entry[ID].setFlag);
	printf("\n%s\n", connection->dB->entry[ID].name);
	printf("\n%s\n", connection->dB->entry[ID].email);

/*	sprintf(fetched_id, "--- Entry ID=%d",ID);
	TR_ENTRY(fetched_id);
	sprintf(fetched_entry, "--- Name = %s; --- Email = %s", connection->dB->entry[ID].name, connection->dB->entry[ID].email);
	TR_ENTRY(fetched_entry);

	free(fetched_id);
	free(fetched_entry);*/

	return 0;
}

void Database_Close(Connection *connection){
	free(connection->dB);
	fclose(connection->stream);
	free(connection->info->Message);
	free(connection->info);
	free(connection);

}

int main(int argc,char *argv[]){

	char *dBFileName;
	char *OperationMode;
	Connection *connection;
	Info *info = malloc(sizeof(Info));


	if(argc==2 && strcmp(argv[1], "MAN")==0) {

		TR_MAN("\r\n ---- MAN Page Database ---- \n");
		TR_MAN(" 1) Initializing a DB: ./Database <dB_File_Name> --init [id name email]");
		TR_MAN(" 2) Insert an Entry into DB: ./Database <dB_File_Name> --insert [id name email]");
		TR_MAN(" 3) Fetch an Entry from DB: ./Database <dB_File_Name> --fetch [id]");
		TR_MAN(" 4) Delete an Entry from DB: ./Database <dB_File_Name> --delete [id]");
		TR_MAN(" 5) Display list of entries in a DB: ./Database <dB_File_Name> --list [num_rows]");
		TR_MAN("\n ------------------------------END------------------------------------\n\n");
		exit(0);

	}

	if(argc<3){
		die_motherfucker("Insufficient Arguments.\n USAGE: ./Database <dB_File_Name> <operation_mode> [arguments] \n To see the manual, please write: ./Database MAN and press enter.");
		}
	else if(argc>=3){
		dBFileName = argv[1];
		OperationMode = argv[2];
		info->DB_NAME = dBFileName;
		info->Num_Args = argc;

		/* Initializing a Database*/
		if(strcmp(OperationMode, "--init")==0) {

			info->state = INIT;
			if (argc==4 || argc==5){
				die_motherfucker("Incomplete initial entry arguments. Use [id name email] OR do not provide any argument.");
			}
			else if (argc>6){
				die_motherfucker("Too many arguments.");
			}
			else{
				connection = Database_Open(info);
				InitializeDatabase(connection, argv);
				Database_Close(connection);
			}
		}
		/* Inserting an Entry into the Database*/
		else if(strcmp(OperationMode, "--insert")==0){

			info->state = INSERT;
			connection = Database_Open(info);
			Load_DB2Stack(connection);
			InsertEntry(connection, argv);
			Database_Close(connection);

		}
		/*Fetch an entry using id from the esisting Database*/
		else if(strcmp(OperationMode, "--fetch")==0){

			info->state = FETCH;
			connection = Database_Open(info);
			Load_DB2Stack(connection);
			FetchEntry(connection, argv[3]);
			Database_Close(connection);
			
		}
		/*Delete an Entry from the existing Database*/
		else if(strcmp(OperationMode, "--delete")==0){
			
		}
		/*Print out a list of Entries in an existing Database*/
		else if(strcmp(OperationMode, "--list")==0){
			
		}
		/*Throw an error message if the OperationMode is unrecognizable.*/
		else {
			die_motherfucker("Invalid Operation Mode.");
		}


	}
	return 0;
}