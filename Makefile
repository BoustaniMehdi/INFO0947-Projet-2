### 
## Makefile
## INFO0947: Projet 2
## 
### 

## Variables

# Tools & flags
CC=gcc
CFLAGS=--std=c99 --pedantic -Wall -W -Wmissing-prototypes
LD=gcc
LDFLAGS=-L.

# Files
ARRAY_EXEC=itineraireflamme_tableau_test
LIST_EXEC=itineraireflamme_liste_test
ARRAY_OBJECTS=region.o itineraireflamme_tableau.o itineraireflamme_tableau_test.o seatest.o
LIST_OBJECTS=region.o itineraireflamme_liste.o itineraireflamme_liste_test.o seatest.o

## Rules

all: test_array test_list

test_array: $(ARRAY_OBJECTS)
	$(LD) -o $(ARRAY_EXEC) $(ARRAY_OBJECTS) $(CFLAGS) $(LDFLAGS) -lm

test_list: $(LIST_OBJECTS)
	$(LD) -o $(LIST_EXEC) $(LIST_OBJECTS) $(CFLAGS) $(LDFLAGS) -lm

itineraireflamme_tableau.o : itineraireflamme_tableau.c region.c boolean.c
	$(CC) -c itineraireflamme_tableau.c -o itineraireflamme_tableau.o $(CFLAGS)

itineraireflamme_tableau_test.o : itineraireflamme_tableau_test.c region.c seatest.c boolean.c
	$(CC) -c itineraireflamme_tableau_test.c -o itineraireflamme_tableau_test.o  $(CFLAGS)

itineraireflamme_liste.o : itineraireflamme_liste.c region.c boolean.c
	$(CC) -c itineraireflamme_liste.c -o itineraireflamme_liste.o $(CFLAGS)

itineraireflamme_liste_test.o : itineraireflamme_liste_test.c region.c seatest.c boolean.c
	$(CC) -c itineraireflamme_liste_test.c -o itineraireflamme_liste_test.o  $(CFLAGS)

region.o: region.c
	$(CC) -c region.c -o region.o $(CFLAGS)

boolean.o: boolean.c99
	$(CC) -c boolean.c -o boolean.o $(CFLAGS)

valgrind_array: test_array
	valgrind --leak-check=full --show-leak-kinds=all ./$(ARRAY_EXEC)
valgrind_list
valgrind_list: test_list
	valgrind --leak-check=full --show-leak-kinds=all ./$(LIST_EXEC)


clean:
	rm -f *.o $(ARRAY_EXEC) $(LIST_EXEC) *~
