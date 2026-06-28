/**
 * @file main.cpp
 * @brief Hlavní řídící program pro opravu nesouvislé silniční sítě.
 */

#include "oprava_grafu.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

/**
 * @brief Hlavní funkce programu.
 * * Zpracovává argumenty příkazové řádky. Načítá hrany ze souboru, detekuje zbytečné
 * hrany tvořící cykly a následně tyto hrany využívá k propojení odříznutých
 * komponent grafu tak, aby vznikla souvislá síť.
 * * @param argc Počet argumentů příkazové řádky.
 * @param argv Pole textových řetězců z příkazové řádky.
 * @return int Návratový kód programu (0 při úspěchu, 1 při chybě).
 */
int main(int argc, char* argv[]) {

    vector<Hrana> nactene;
    vector<Hrana> zbytecne;

    string nazev_souboru = "RoadSystem1.txt";
    if (argc > 1) {
        nazev_souboru = argv[1];
    }

    ifstream vstup(nazev_souboru);

    if (!vstup) {
        cerr << "Chyba při otevírání souboru: " << nazev_souboru << endl;
        return 1;
    }

    int odkud, kam;
    while (vstup >> odkud >> kam) {
        nactene.push_back({odkud, kam});
    }
    vstup.close();

    int nejvetsi_vrchol = 0;
    for (const auto& hrana : nactene) {
        nejvetsi_vrchol = max(nejvetsi_vrchol, max(hrana.odkud, hrana.kam));
    }

    vector<int> parent(nejvetsi_vrchol + 1);
    vector<bool> visited(nejvetsi_vrchol + 1, false);

    for (int i = 0; i <= nejvetsi_vrchol; ++i) {
        parent[i] = i; 
    }
    
    for (const auto& hrana : nactene) {
        visited[hrana.odkud] = true;
        visited[hrana.kam] = true;

        int koren_odkud = hledani_korene(parent, hrana.odkud);
        int koren_kam = hledani_korene(parent, hrana.kam);

        if (koren_odkud == koren_kam) {
            zbytecne.push_back(hrana);
        } else {
            spojeni(parent, hrana.odkud, hrana.kam);
        }
    }

    vector<int> hlavni_koreny;
    for (int i = 0; i <= nejvetsi_vrchol; ++i) {
        if (visited[i] && parent[i] == i) {
            hlavni_koreny.push_back(i);
        }
    }

    cout << "Pocet souvislych komponent zadanneho grafu: " << hlavni_koreny.size() << endl;

    if (hlavni_koreny.size() > 1) {
        int pocet_komponent = hlavni_koreny.size();
        int potreba_hran = pocet_komponent - 1;

        if ((int)zbytecne.size() < potreba_hran) {
            cout << "Uloha nema reseni. Nedostatek hran na opravu." << endl;
        } else {
            for (int i = 0; i < potreba_hran; ++i) {
                cout << "Odebrana hrana: " << zbytecne[i].odkud << " " << zbytecne[i].kam << endl;
                cout << "Vlozena hrana: " << hlavni_koreny[i] << " " << hlavni_koreny[i+1] << endl;
            }

            cout << "Pocet souvislych komponent po oprave: 1" << endl;
        }
    } else {
        cout << "Graf je jiz spojeny." << endl;
    }

    return 0;
}