#include "region.h"

struct cell_t{
    Region* region;
    struct cell_t* next;
};

struct itineraireFlamme_t{
    struct cell_t* head;
    struct cell_t* tail;
    unsigned int nb_regions;
    unsigned int nb_residents_total;
};