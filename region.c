/**
 * @file region.c
 *
 * @brief Ce fichier contient les définitions de types et
 * les fonctions pour la manipulation de régions.
 *
 * @author Boustani Mehdi/ Touhami Ibrahim
 * @date 13 mai 2023
 * projet INFO0947 Projet 2
 */
#include <math.h>
#include <stdlib.h>

#include "region.h"

struct region_t{
    float x;
    float y;
    char* name_region;
    char* name_capital;
    char* speciality;
    unsigned int nb_residents;
};

//j'avais pas le rapport la donc ya peut etre un soucis avec les types faut check
Region* create_region(float x, float y,char* name_region) {
    Region* region = malloc(sizeof(Region));

    region->x = x;
    region->y = y;
    region->name_region = name_region;
    return region;
}

// Obtenir la coordonnée X d'une région
float get_x_coordinate(Region* region) {
    return region->x;
}

// Obtenir la coordonnée Y d'une région
float get_y_coordinate(Region* region) {
    return region->y;
}

// Obtenir le nom de la région
const char* get_region_name(Region* region) {
    return region->name_region;
}

// Obtenir le nom du chef-lieu
const char* get_capital_name(Region* region) {
    return region->name_capital;
}

// Calculer la distance géographique entre deux régions (distance entre les chefs-lieux)
float calculate_distance(Region* region1, const Region* region2) {
    float distance = sqrt(pow(region1->x - region2->x, 2) + pow(region1->y - region2->y, 2));
    return distance;
}

// Enregistrer le nombre d'habitants de la région
void set_nb_residents(Region* region, unsigned int nb_residents) {
    region->nb_residents = nb_residents;
}

// Obtenir le nombre d'habitants de la région
unsigned int get_nb_residents(Region* region) {
    return region->nb_residents;
}

// Obtenir la spécialité de la région
const char* get_speciality(Region* region) {
    return region->speciality;
}

