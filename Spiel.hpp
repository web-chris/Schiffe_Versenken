#ifndef SPIEL_H
#define SPIEL_H
#include <memory>
#include "Spieler.hpp"

class Spiel
{
private:
public:
    bool spielerZug(std::shared_ptr<Spieler> spieler);
// Umbenennen istSpielFeldVomGegenerGeschossen oder hatKiGeschossen
    bool Schuss(std::shared_ptr<Spieler> gegener, int ireihe, int ispalte);
    void KIZug(std::shared_ptr<Spieler> gegener);
// Umbenennen istSchiffVersenkt
    void schiffversenkt(std::shared_ptr<Spieler> spieler);
// Umbenennen sindAlleSchiffeVersenkt
    bool alleSchiffeversenkt(std::shared_ptr<Spieler> spieler);
// Umbenennen istKoordinateGueltig
    bool istGueltigeKoordinate(int reihe, int spalte);
// Umbenennen KoordinatenInIndexUmwandeln
    int koordinateZuIndex(char buchstabe);
    bool spielen(std::shared_ptr<Spieler> spielerSpielfeld, std::shared_ptr<Spieler> KISpielfeld, bool amZug);
};

#endif
