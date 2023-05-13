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
LDFLAGS=

# Files
ARRAY_EXEC=itineraireflamme_tableau_test
LIST_EXEC=itineraireflamme_liste_test
ARRAY_OBJECTS=region.o itineraireflamme_tableau.o itineraireflamme_tableau_test.o 
LIST_OBJECTS=region.o itineraireflamme_liste.o itineraireflamme_liste_test.o 

## Rules

all: test_array test_list

test_array: $(ARRAY_OBJECTS)
	$(LD) -o $(ARRAY_EXEC) $(ARRAY_OBJECTS) $(CFLAGS) $(LDFLAGS)

test_list: $(LIST_OBJECTS)
	$(LD) -o $(LIST_EXEC) $(LIST_OBJECTS) $(CFLAGS) $(LDFLAGS)

itineraireflamme_tableau.o : itineraireflamme_tableau.c region.c seatest.c
	$(CC) -c itineraireflamme_tableau.c -o $(ARRAY_OBJECTS) $(CFLAGS)

itineraireflamme_tableau_test.o : itineraireflamme_tableau_test.c region.c seatest.c
	$(CC) -c itineraireflamme_tableau.c -o $(ARRAY_OBJECTS) $(CFLAGS)

itineraireflamme_liste.o : itineraireflamme_liste.c region.c seatest.c
	$(CC) -c itineraireflamme_liste.c -o $(LIST_OBJECTS) $(CFLAGS)

itineraireflamme_liste_test.o : itineraireflamme_liste_test.c region.c seatest.c
	$(CC) -c itineraireflamme_liste.c -o $(LIST_OBJECTS) $(CFLAGS)

region.o: region.c
	$(CC) -c region.c -o region.o $(CFLAGS)

clean:
	rm -f *.o $(ARRAY_EXEC) $(LIST_EXEC) *~
