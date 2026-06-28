#include <vector>

using namespace std;

/**
 * @brief Struktura reprezentující jednu silnici (hranu) v grafu.
 */
struct Hrana {
    /** @brief Počáteční uzel (křižovatka) hrany. */
    int odkud;
    /** @brief Koncový uzel (křižovatka) hrany. */
    int kam;
};

/**
 * @brief Najde kořen (hlavního zástupce) komponenty pro zadaný vrchol.
 * * Funkce postupuje v hierarchii pole nadřízených (otců) tak dlouho, dokud
 * nenarazí na vrchol, který je otcem sám sobě. Slouží k detekci cyklů.
 * * @param parent Odkaz na vektor reprezentující nadřízené pro každý vrchol.
 * @param vrchol Identifikátor vrcholu, jehož kořen hledáme.
 * @return int Identifikátor kořene (hlavního zástupce) dané komponenty.
 */
int hledani_korene(vector<int>& parent, int vrchol);

/**
 * @brief Spojí dvě oddělené komponenty do jedné.
 * * Zjistí kořeny obou zadaných vrcholů. Pokud tyto vrcholy patří do různých
 * komponent (mají různé kořeny), funkce jeden kořen podřídí druhému, čímž
 * množiny sjednotí.
 * * @param parent Odkaz na vektor reprezentující nadřízené pro každý vrchol.
 * @param vrchol1 První vrchol patřící do propojované komponenty.
 * @param vrchol2 Druhý vrchol patřící do propojované komponenty.
 */
void spojeni(vector<int>& parent, int vrchol1, int vrchol2);