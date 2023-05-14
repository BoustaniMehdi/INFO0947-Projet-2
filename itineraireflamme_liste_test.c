/**
 * @file itineraireflamme_liste_tests.c
 * 
 * @brief Ce fichier contient les fonctions de tests unitaires pour la librairie itineraireflamme mais sous forme de liste.
 * @author Boustani Mehdi S221594
 * @date 13 mai 2023
 */

#include <stdlib.h>
#include "itineraireflamme.h"
#include "region.h"
#include "seatest.h"


/**
 * all_tests
 *
 * @brief: Regroupe tous les tests unitaires
 *
 * @param /
 *
 * @pre: /
 * @post: Tous les tests sont regroupés
 *
 * @return
 *     /
 *
 */
static void all_tests();

static void test_itineraire();

static void test_itineraire(){

    Region* region1 = create_region(70, 100, "Tabodi");
    Region* region2 = create_region(20, -60, "Nde");


    ItineraireFlamme* itineraire = create_itineraire_list(region1, region2);

    set_nb_residents(region1, 1000);

    assert_int_equal(1000, get_nb_residents(region1));

    free_itineraire_list(itineraire);

}


static void test_fixture(){

    test_fixture_start();

    run_test(test_itineraire);

    test_fixture_end();
}

static void all_tests(){
    test_fixture();
}


int main(){

    return run_tests(all_tests);
}