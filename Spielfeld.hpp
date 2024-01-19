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
    void spielfeldInitialisieren();
    ZellenStatus gibZellenStatus(int ireihe, int ispalte);
    void setzeZellenStatus(int ireihe, int ispalte, ZellenStatus zellenStatus);
    bool pruefeZellen(int ireihe, int ispalte, ZellenStatus zellenStatus);
    void spielfeldAusgebe(bool schiffAnzeige);
    bool istPlatzierungGueltig(int reihe, int spalte, int groesse, bool vertikal);
    bool schiffPlatzieren(int reihe, int spalte, int groesse, bool vertikal);
    void platziere_Schiffe(int schifflaenge, int anzahl);
    SpielFeld gibFeld();
};

#endif