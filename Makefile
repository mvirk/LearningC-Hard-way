CFLAGS=-Wall -g 
FILES=hello ex2 ex3 ex4 ex5 using_functions Dreaded_Pointers Dreaded_Pointers2 PersonCreator PersonCreator2 Database

# ANSI colours
NO_COLOR=\x1b[0m
OK_COLOR=\x1b[32;01m
ERROR_COLOR=\x1b[31;01m
WARN_COLOR=\x1b[33;01m

SUCESS_MSG=$(OK_COLOR)Build Successful$(NO_COLOR)
MAN_MSG=$(WARN_COLOR)Use [./Database MAN] command to see the manual$(NO_COLOR)


all: $(FILES)
.PHONY : all
ex3: 
	gcc $(CFLAGS) ex3.c -o ex3
	valgrind --track-origins=yes --leak-check=full --log-file=valgrind_log ./ex3 

ex4: 
	gcc $(CFLAGS) ex4.c -o ex4
	valgrind --track-origins=yes --leak-check=full --log-file=valgrind_log ./ex4 Punjab NULL Balouchistan KPK

ex5: clean
	gcc $(CFLAGS) ex5.c -o ex5
	valgrind --track-origins=yes --leak-check=full --log-file=valgrind_log ./ex5 $(ARGS)

using_functions: clean
	gcc $(CFLAGS) using_functions.c -o using_functions
	valgrind --track-origins=yes --leak-check=full --log-file=valgrind_log ./using_functions "$(ARGS)"

Dreaded_Pointers: clean
	gcc $(CFLAGS) Dreaded_Pointers.c -o Dreaded_Pointers
	valgrind --track-origins=yes --leak-check=full --log-file=valgrind_log ./Dreaded_Pointers

Dreaded_Pointers2: clean
	gcc $(CFLAGS) Dreaded_Pointers2.c -o Dreaded_Pointers2
	valgrind --track-origins=yes --leak-check=full --log-file=valgrind_log ./Dreaded_Pointers2 $(ARGS)
PersonCreator: clean
	gcc $(CFLAGS) PersonCreator.c -o PersonCreator
	valgrind --track-origins=yes --leak-check=full --log-file=valgrind_log ./PersonCreator $(ARG1) $(ARG2) $(ARG3) $(ARG4)

PersonCreator2: clean
	gcc $(CFLAGS) PersonCreator2.c -o PersonCreator2
	valgrind --track-origins=yes --leak-check=full --log-file=valgrind_log ./PersonCreator2 $(ARGS)

Database: clean
	gcc $(CFLAGS) Database.c -o Database
#valgrind --track-origins=yes --leak-check=full --log-file=valgrind_log ./Database $(ARGS)
	@/bin/echo -e "\n$(SUCESS_MSG)"	
	@/bin/echo -e "$(MAN_MSG)"

clean:
	rm -rf $(FILES)
