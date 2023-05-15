/**
 * @file region.h
 * 
 * @brief Ce fichier contient les déclarations de types et les prototypes
 * des fonctions pour la manipulation de régions.
 * 
 * @author Boustani Mehdi/ Touhami Ibrahim
 * @date 13 mai 2023
 * projet INFO0947 Projet 2
 */

#ifndef __REGION__
#define __REGION__

typedef struct region_t Region;

Region* create_region(float x, float y, char* name_region);

float get_y(Region* region);

float get_x(Region* region);

char* get_region_name(Region* region);

char* get_capital_name(Region* region);

float calcul_dist(Region* region1, Region* region2);

void set_nb_residents(Region* region, unsigned int nb_residents);

unsigned int get_nb_residents(Region* region);

char* get_speciality(Region* region);

#endif //__REGION__
