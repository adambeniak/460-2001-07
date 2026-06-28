#include "oprava_grafu.h"
#include <iostream>
#include <vector>

/**
 * @file oprava_grafu.cpp
 * @brief Implementace funkcí pro manipulaci s grafem a detekci komponent.
 * * Tento soubor obsahuje definice funkcí pro práci s datovou strukturou 
 * Disjoint-Set (Union-Find), které se používají k hledání kořenů a 
 * propojování izolovaných částí (komponent) silniční sítě.
 */

using namespace std;

int hledani_korene(vector<int>& parent, int vrchol) {
    while (parent[vrchol] != vrchol) {
        vrchol = parent[vrchol];
    }
    return vrchol;
}

void spojeni(vector<int>& parent, int vrchol1, int vrchol2) {
    int koren1 = hledani_korene(parent, vrchol1);
    int koren2 = hledani_korene(parent, vrchol2);
    
    if (koren1 != koren2) {
        parent[koren1] = koren2;
    }
}