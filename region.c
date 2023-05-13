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

#include "region.h"

struct region_t{
    float x;
    float y;
    char* name_region;
    char* name_capital;
    char* speciality;
    unsigned int nb_residents;
};