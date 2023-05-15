/**
 * @file itineraireflamme_array_tests.c
 * 
 * @brief Ce fichier contient les fonctions de tests unitaires pour la librairie itineraireflamme mais sous forme de arraye.
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

static void test_is_circuit();

static void test_nb_regions();

static void test_nb_residents_total();

static void test_nb_residents_array();

static void test_get_last_region();

static void test_is_circuit(){

    Region* region1 = create_region(70, 100, "Tabodi");
    Region* region2 = create_region(20, -60, "Nde");

    ItineraireFlamme* itineraire = create_itineraire_array(region1, region2);
    
    assert_false(is_circuit_array(itineraire));
    assert_true(is_circuit_array(add_region_array(itineraire, region1)));
    assert_false(is_circuit_array(remove_region_array(itineraire)));
    

    free_itineraire_array(itineraire);
}

static void test_nb_regions(){
    Region* region1 = create_region(70, 100, "Tabodi");
    Region* region2 = create_region(20, -60, "Nde");

    ItineraireFlamme* itineraire = create_itineraire_array(region1, region2);

    int initialNumber = nb_regions(itineraire);

    assert_int_equal(2, nb_regions(itineraire));
    assert_int_equal(initialNumber += 1, nb_regions(add_region_array(itineraire, region1)));
    assert_int_equal(initialNumber -= 1, nb_regions(remove_region_array(itineraire)));

    free_itineraire_array(itineraire);
}

static void test_nb_residents_total(){

    Region* region1 = create_region(70, 100, "Tabodi");
    Region* region2 = create_region(20, -60, "Nde");
    Region* region3 = create_region(60, -10, "Regular");


    ItineraireFlamme* itineraire = create_itineraire_array(region1, region2);

    int initialNumber = nb_residents_total(itineraire);

    assert_int_equal(get_nb_residents(region1) + get_nb_residents(region2), nb_residents_total(itineraire));
    assert_int_equal(initialNumber += get_nb_residents(region3), nb_residents_total(add_region_array(itineraire, region3)));
    assert_int_equal(initialNumber -= get_nb_residents(get_last_region_array(itineraire)), nb_residents_total(remove_region_array(itineraire)));

    free_itineraire_array(itineraire);

}

static void test_nb_residents_array(){

    Region* region1 = create_region(70, 100, "Tabodi");
    Region* region2 = create_region(20, -60, "Nde");


    ItineraireFlamme* itineraire = create_itineraire_array(region1, region2);

    assert_int_equal(get_nb_residents(region1), nb_residents_array(itineraire, region1));
    assert_int_equal(nb_residents_array(itineraire, region2), nb_residents_array(add_region_array(itineraire, region1), region2));
    assert_int_equal(nb_residents_array(itineraire, region2), nb_residents_array(remove_region_array(itineraire), region2));

    free_itineraire_array(itineraire);
}

static void test_get_last_region(){

    Region* region1 = create_region(70, 100, "Tabodi");
    Region* region2 = create_region(20, -60, "Nde");
    Region* region3 = create_region(60, -10, "Regular");


    ItineraireFlamme* itineraire = create_itineraire_array(region1, region2);

    assert_string_equal(get_region_name(region2), get_region_name(get_last_region_array(itineraire)));
    assert_string_equal(get_region_name(region3), get_region_name(get_last_region_array(add_region_array(itineraire, region3))));
    assert_string_equal(get_region_name(get_last_region_array(itineraire)), get_region_name(get_last_region_array(remove_region_array(itineraire))));

    free_itineraire_array(itineraire);

}


static void test_fixture(){

    test_fixture_start();

    run_test(test_is_circuit);
    run_test(test_nb_regions);
    run_test(test_nb_residents_total);
    run_test(test_nb_residents_array);
    run_test(test_get_last_region);

    test_fixture_end();
}

static void all_tests(){
    test_fixture();
}


int main(){
    
    return run_tests(all_tests);
}