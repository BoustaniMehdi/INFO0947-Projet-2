/**
 * @file itineraireflamme.h
 * 
 * @brief Ce fichier contient les déclarations de types et les prototypes
 * des fonctions pour la manipulation de l'itinéraire.
 * 
 * @author Boustani Mehdi/ Touhami Ibrahim
 * @date 13 mai 2023
 * projet INFO0947 Projet 2
 */

#ifndef __ITINERAIRE_FLAMME__
#define __ITINERAIRE_FLAMME__

#include "region.h"
#include "boolean.h"

typedef struct cell_t Cellule;
typedef struct itineraireFlamme_t ItineraireFlamme;

ItineraireFlamme* create_itineraire_list(Region* region1, Region* region2);

unsigned int nb_regions(ItineraireFlamme* itineraire);

unsigned int nb_residents_total(ItineraireFlamme* itineraire);

unsigned int nb_residents(ItineraireFlamme* itineraire, Region* region);

Boolean is_present_list(ItineraireFlamme* itineraire, Region* region);

Boolean is_circuit_list(ItineraireFlamme* itineraire);

ItineraireFlamme* add_region_list(ItineraireFlamme* itineraire, Region* region);

ItineraireFlamme* remove_region_list(ItineraireFlamme* itineraire);


#endif //__ITINERAIRE_FLAMME__