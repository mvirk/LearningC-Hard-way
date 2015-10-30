CFLAGS=-Wall -g 
FILES=hello ex2 ex3 ex4 ex5 using_functions Dreaded_Pointers Dreaded_Pointers2 PersonCreator PersonCreator2 Database

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
	@echo "Database.c compiled successfully."
	@echo "Use [./Database MAN] command to see the manual."
	
	#valgrind --track-origins=yes --leak-check=full --log-file=valgrind_log ./Database $(ARGS)

clean:
	rm -rf $(FILES)
