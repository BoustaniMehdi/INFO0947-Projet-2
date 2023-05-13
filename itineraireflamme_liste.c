#include <stdlib.h>
#include <assert.h>

#include "region.h"
#include "itineraireflamme.h"

struct cell_t{
    Region* region;
    struct cell_t* next; // Cellule suivante
    struct cell_t* previous; // Cellule précedente 
};

struct itineraireFlamme_t{
    struct cell_t* head; // Pointeur de début
    struct cell_t* tail; // Pointeur de fin
    unsigned int nb_regions; // Pas longueur de la liste étant donné qu'une même région peut être présente plusieurs fois.
    unsigned int nb_residents_total;
    unsigned int length; // Longueur de la liste
};

ItineraireFlamme* create_itineraire_list(Region* region1, Region* region2){
    assert(region1 != NULL && region2 != NULL);

    ItineraireFlamme* itineraire = malloc(sizeof(ItineraireFlamme));

    if(itineraire == NULL)
        return NULL;

    itineraire->head = malloc(sizeof(Cellule));

    if(itineraire->head == NULL){
        free(itineraire);
        return NULL;
    }

    itineraire->tail = malloc(sizeof(Cellule));

    if(itineraire->tail == NULL)
    {
        free(itineraire->head);
        free(itineraire);

        return NULL;
    }

    // Initialisation de la liste doublement chaînée

    itineraire->head->region = region1;
    itineraire->head->next = itineraire->tail;
    itineraire->head->previous = NULL;

    itineraire->tail->region = region2;
    itineraire->tail->next = NULL;
    itineraire->tail->previous = itineraire->head;

    itineraire->nb_regions = 2;
    itineraire->nb_residents_total = get_nb_residents(region1) + get_nb_residents(region2);

    return itineraire;
}

unsigned int nb_regions(ItineraireFlamme* itineraire){
    assert(itineraire != NULL);

    return itineraire->nb_regions;
}

unsigned int nb_residents_total(ItineraireFlamme* itineraire){
    assert(itineraire != NULL);

    return itineraire->nb_residents_total;
}

unsigned int nb_residents(ItineraireFlamme* itineraire, Region* region){
    assert(itineraire != NULL && region != NULL && is_present_list(itineraire, region));

    return get_nb_residents(region);
}

unsigned int is_present_list(ItineraireFlamme* itineraire, Region* region){
    assert(itineraire != NULL && region != NULL);

    ItineraireFlamme* temp = itineraire;

    if(!nb_regions(itineraire)) // Cas de base (liste vide)
        return 0;
    
    if(temp->tail->region == region) // On check a chaque fois si la dernère région correspond à la région donnée
        return 1;

    if(itineraire->tail->previous != NULL) // Condition vérifiant si la liste est vide.
        return is_present_list(remove_region_list(temp), region); // Cas récursif avec une liste plus petite pour atteindre le cas de base

    return 0; // On prend quand même une valeur de retour par défaut au cas où
}

unsigned int is_circuit_list(ItineraireFlamme* itineraire){
    assert(itineraire != NULL);

    ItineraireFlamme* temp = itineraire;

    if(nb_regions(itineraire) == 2) // Cas de base
        return 0;
    
    if(is_present_list(remove_region_list(temp), itineraire->tail->region)) // On regarde si la région est présente ou non dans la sous-liste sans l'element à chercher.
        return 1;                                                          // Cependant, il faudrait réflechir à une façon d'éviter le cas où plusieurs régions sont consécutives
    else{
        return is_circuit_list(temp); // Sinon, on rappelle is_circuit mais avec la sous-liste
    }
    

    return 0; // On retourne 0 par défaut
}

ItineraireFlamme* add_region_list(ItineraireFlamme* itineraire, Region* region){
    assert(itineraire != NULL && region != NULL);

    Cellule* cell = malloc(sizeof(Cellule)); // On alloue une nouvelle place pour la région

    if(cell == NULL)
        return itineraire;
    
    cell->region = region;
    cell->next = NULL;
    cell->previous = itineraire->tail;

    itineraire->tail->next = cell;
    itineraire->tail = cell;

    if(!is_present_list(itineraire, region))
        itineraire->nb_regions++;
    
    itineraire->nb_residents_total += get_nb_residents(region);
    itineraire->length++; // length augmente même s'il y a des régions identiques dans l'itinéraire.

    return itineraire;
}

ItineraireFlamme* remove_region_list(ItineraireFlamme* itineraire){
    assert(itineraire != NULL && nb_regions(itineraire) > 2);

    itineraire->nb_residents_total -= get_nb_residents(itineraire->tail->region);

    itineraire->tail = itineraire->tail->previous;

    free(itineraire->tail->next); // On tue la région (RIP)

    itineraire->tail->next = NULL;

    itineraire->nb_regions--;
    itineraire->length--;

    return itineraire;
}

