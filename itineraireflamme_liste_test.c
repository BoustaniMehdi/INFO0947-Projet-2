/**
 * @file itineraireflamme_liste_tests.c
 * 
 * @brief Ce fichier contient les fonctions de tests unitaires pour la librairie itineraireflamme mais sous forme de liste.
 * @author Boustani Mehdi S221594
 * @date 13 mai 2023
 */

#include <stdlib.h>
#include "seatest.h"
#include "itineraireflamme.h"
#include "region.h"


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


static void test_fixture(){

    test_fixture_start();

    //run_test(test);

    test_fixture_end();
}

static void all_tests(){
    test_fixture();
}


int main(){
    return run_tests(all_tests);
}