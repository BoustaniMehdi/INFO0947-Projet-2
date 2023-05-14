#include <stdlib.h>
#include <assert.h>

#include "region.h"
#include "itineraireflamme.h"
#include "boolean.h"

struct itineraireFlamme_t {
    Region** regions;
    unsigned int nb_regions;
    unsigned int nb_residents_total;
};


ItineraireFlamme* create_itineraire_array(Region* region1, Region* region2){
    assert(region1 != NULL && region2 != NULL);

    ItineraireFlamme* itineraire = malloc(sizeof(ItineraireFlamme));

    if (itineraire == NULL)
        return NULL;

    itineraire->regions = malloc(2 * sizeof(Region*));

    if (itineraire->regions == NULL) {
        free(itineraire);
        return NULL;
    }

    itineraire->regions[0] = region1;
    itineraire->regions[1] = region2;
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
    assert(itineraire != NULL && region != NULL);

    return get_nb_residents(region);
}

Region* get_last_region_tableau(ItineraireFlamme* itineraire){
    assert(itineraire != NULL);

    return itineraire->regions[nb_regions(itineraire) - 1];

}

Boolean is_present_array(ItineraireFlamme* itineraire, unsigned int num_region){
    assert(itineraire != NULL);

    for(unsigned int i = 0; i < num_region; i++)
    {
        if(itineraire->regions[i] == itineraire->regions[num_region])
            return True;
    }

    return False;
}


Boolean is_circuit_array(ItineraireFlamme* itineraire){
    assert(itineraire != NULL);

    for(unsigned int i = 0; i < itineraire->nb_regions; i++)
    {
        if(is_present_array(itineraire, i))
            return True;
    }

    return False;
}


ItineraireFlamme* add_region_array(ItineraireFlamme* itineraire, Region* region){
    assert(itineraire != NULL && region != NULL);

    Region** new_regions = realloc(itineraire->regions, (itineraire->nb_regions + 1) * sizeof(Region*));

    if(new_regions == NULL)
        return itineraire;

    itineraire->regions = new_regions;
    itineraire->regions[itineraire->nb_regions] = region;
    itineraire->nb_regions++;
    itineraire->nb_residents_total += get_nb_residents(region);

    return itineraire;
}


ItineraireFlamme* remove_region_array(ItineraireFlamme* itineraire){
    assert(itineraire != NULL && itineraire->nb_regions > 2);

    Region* removed_region = itineraire->regions[itineraire->nb_regions - 1];
    itineraire->nb_residents_total -= get_nb_residents(removed_region);

    // Libérer la mémoire de la région supprimée
    free(removed_region);

    itineraire->nb_regions--;

    // Réallouer le tableau avec une taille réduite
    Region** new_regions = realloc(itineraire->regions, itineraire->nb_regions * sizeof(Region*));

    if(new_regions == NULL) 
        return itineraire;// En cas d'échec de réallocation, on conserve l'ancien tableau

    itineraire->regions = new_regions;

    return itineraire;
}

void free_itineraire_array(ItineraireFlamme* itineraire) {
    if (itineraire == NULL)
        return;

    // Libérer chaque région dans le tableau
    for (unsigned int i = 0; i < itineraire->nb_regions; i++) {
        free(itineraire->regions[i]);
    }

    // Libérer le tableau et la structure principale
    free(itineraire->regions);
    free(itineraire);
}