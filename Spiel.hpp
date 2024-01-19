#ifndef SPIEL_H
#define SPIEL_H
#include <memory>
#include "Spieler.hpp"

class Spiel
{
private:
public:
    bool spielerZug(std::shared_ptr<Spieler> spieler);
    bool hatKiGeschossen(std::shared_ptr<Spieler> gegener, int ireihe, int ispalte);
    void KIZug(std::shared_ptr<Spieler> gegener);
    void istSchiffVersenkt(std::shared_ptr<Spieler> spieler);
    bool sindAlleSchiffeVersenkt(std::shared_ptr<Spieler> spieler);
    bool istKoordinateGueltig(int reihe, int spalte);
    int KoordinatenInIndexUmwandeln(char buchstabe);
    bool spielen(std::shared_ptr<Spieler> spielerSpielfeld, std::shared_ptr<Spieler> KISpielfeld, bool amZug);
};

#endif
