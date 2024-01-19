#ifndef SPIEL_H
#define SPIEL_H
#include <memory>
#include "Spieler.hpp"

class Spiel
{
private:
public:
    bool spielerZug(std::shared_ptr<Spieler> spieler);
    bool Schuss(std::shared_ptr<Spieler> gegener, int ireihe, int ispalte);
    void KIZug(std::shared_ptr<Spieler> gegener);
    void schiffversenkt(std::shared_ptr<Spieler> spieler);
    bool alleSchiffeversenkt(std::shared_ptr<Spieler> spieler);
    bool istGueltigeKoordinate(int reihe, int spalte);
    int koordinateZuIndex(char buchstabe);
    bool spielen(std::shared_ptr<Spieler> spielerSpielfeld, std::shared_ptr<Spieler> KISpielfeld, bool amZug);
};

#endif