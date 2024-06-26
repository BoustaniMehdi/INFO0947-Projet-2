#include <stdlib.h>
#include <assert.h>

#include "region.h"
#include "itineraireflamme.h"
#include "boolean.h"

struct cell_t{
    Region* region;
    struct cell_t* next; // Cellule suivante
    struct cell_t* previous; // Cellule précedente 
};

struct itineraireFlamme_t{
    struct cell_t* head; // Pointeur de début
    struct cell_t* tail; // Pointeur de fin
    unsigned int nb_regions;
    unsigned int nb_residents_total;
};

ItineraireFlamme* create_itineraire_list(Region* region1, Region* region2){
    assert(region1 != NULL && region2 != NULL && get_x(region1) != get_x(region2) && get_y(region1) != get_y(region2));

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

unsigned int nb_residents_list(ItineraireFlamme* itineraire, Region* region){
    assert(itineraire != NULL && region != NULL && is_present_list_assert(itineraire, region));

    return get_nb_residents(region);
}

Region* get_last_region_list(ItineraireFlamme* itineraire){
    assert(itineraire != NULL);

    return itineraire->tail->region;
}

Boolean is_present_list_assert(ItineraireFlamme* itineraire, Region* region){
    assert(itineraire != NULL && region != NULL);

    ItineraireFlamme* temp = copie_itineraire(itineraire);

    if(!nb_regions(temp)){
        free_itineraire_list(temp);
        return False;
    }
        
    if(temp->tail->region == region) // On check a chaque fois si la dernère région correspond à la région donnée
        return True;

    if(itineraire->tail->previous != NULL) // Condition vérifiant si la liste est vide.
        return is_present_list(remove_region_list(temp), region); // Cas récursif avec une liste plus petite pour atteindre le cas de base

    return False; // On prend quand même une valeur de retour par défaut au cas où
}

Boolean is_present_list(ItineraireFlamme* itineraire, Region* region){
    assert(itineraire != NULL && region != NULL);

    ItineraireFlamme* temp = itineraire;

    if(!nb_regions(temp)){// Cas de base (liste vide)
        free_itineraire_list(temp);
        return False;
    }
    if(temp->tail->region == region) // On check a chaque fois si la dernère région correspond à la région donnée
        return True;

    if(itineraire->tail->previous != NULL) // Condition vérifiant si la liste est vide.
        return is_present_list(remove_region_list(temp), region); // Cas récursif avec une liste plus petite pour atteindre le cas de base

    return False; // On prend quand même une valeur de retour par défaut au cas où
}

ItineraireFlamme* copie_itineraire(ItineraireFlamme* itineraire){
    assert(itineraire != NULL);

    ItineraireFlamme* copie = create_itineraire_list(itineraire->head->region, itineraire->head->next->region);

    if(copie == NULL)
        return NULL;

    Cellule* courante = itineraire->head->next->next;

    while(courante != NULL){
        Region* region = courante->region;
        add_region_list(copie, region);

        courante = courante->next;
    }

    return copie;
}

Boolean is_circuit_list(ItineraireFlamme* itineraire){
    assert(itineraire != NULL);

    ItineraireFlamme* temp = copie_itineraire(itineraire);

    if(nb_regions(temp) == 2){// Cas de base
        return False;
    } 
    
    if(is_present_list(remove_region_list(temp), itineraire->tail->region)) // On regarde si la région est présente ou non dans la sous-liste sans l'element à chercher.
        return True;                                                          // Cependant, il faudrait réflechir à une façon d'éviter le cas où plusieurs régions sont consécutives
    else{
        return is_circuit_list(temp); // Sinon, on rappelle is_circuit mais avec la sous-liste
    }

    return False; // On retourne False par défaut
}

ItineraireFlamme* add_region_list(ItineraireFlamme* itineraire, Region* region){
    assert(itineraire != NULL && region != NULL && (calcul_dist(get_last_region_list(itineraire), region)));

    Cellule* cell = malloc(sizeof(Cellule)); // On alloue une nouvelle place pour la région

    if(cell == NULL)
        return itineraire;
    
    cell->region = region;
    cell->next = NULL;
    cell->previous = itineraire->tail;

    itineraire->tail->next = cell;
    itineraire->tail = cell;

    itineraire->nb_regions++;
    
    itineraire->nb_residents_total += get_nb_residents(region);

    return itineraire;
}

ItineraireFlamme* remove_region_list(ItineraireFlamme* itineraire){
    assert(itineraire != NULL && nb_regions(itineraire) >= 2);

    itineraire->nb_residents_total -= get_nb_residents(itineraire->tail->region);

    itineraire->tail = itineraire->tail->previous;

    free(itineraire->tail->next); // On tue la région (RIP)

    itineraire->tail->next = NULL;

    itineraire->nb_regions--;

    return itineraire;
}

void free_itineraire_list(ItineraireFlamme* itineraire){
    assert(itineraire != NULL);

    Cellule* curr = itineraire->head;
    Cellule* next = NULL;

    while(curr != NULL){
        next = curr->next;
        
        free(curr->region);
        free(curr);

        curr = next;
    }

    free(itineraire);
}

