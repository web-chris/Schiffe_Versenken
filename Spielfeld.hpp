#ifndef SPIELFELD_H
#define SPIELFELD_H
#include <vector>
#include <iostream>
enum ZellenStatus
{
    LEER,
    SCHIFF,
    TREFFER,
    VORBEI,
    VERSENKT
};

typedef std::vector<std::vector<ZellenStatus>> SpielFeld;
const int SPIELFELD_GROESSE = 10;

class Spielfeld
{

private:
    SpielFeld spielfeld;

public:
    void initSpielfeld();
    ZellenStatus gibZellenStatus(int ireihe, int ispalte);
    void setzeZellenStatus(int ireihe, int ispalte, ZellenStatus zellenStatus);
    bool vergleicheZelle(int ireihe, int ispalte, ZellenStatus zellenStatus);
    void spielfeldAusgeben(bool schiffAnzeigen);
    bool istPlatzierungGueltig(int reihe, int spalte, int groesse, bool vertikal);
    bool pruefeSchiffPlatzieren(int reihe, int spalte, int groesse, bool vertikal);
    void SchiffPlatzieren(int schifflaenge, int anzahl);
    SpielFeld gibFeld();
};

#endif
