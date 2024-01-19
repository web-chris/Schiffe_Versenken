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
//Umbenennen initSpielfeld
    void spielfeldInitialisieren();
    ZellenStatus gibZellenStatus(int ireihe, int ispalte);
//Umbenennen setzeZellenstatus
    void setzeZellenStatus(int ireihe, int ispalte, ZellenStatus zellenStatus);
//Umbenennen vergleicheZelle
    bool pruefeZellen(int ireihe, int ispalte, ZellenStatus zellenStatus);
//Umbenennen spielfeldAusgeben   bool schiffAnzeigen
    void spielfeldAusgebe(bool schiffAnzeige);
    bool istPlatzierungGueltig(int reihe, int spalte, int groesse, bool vertikal);
//Umbenennen pruefeSchiffPlatzieren
    bool schiffPlatzieren(int reihe, int spalte, int groesse, bool vertikal);

//Umbenennen SchiffPlatzieren
    void platziere_Schiffe(int schifflaenge, int anzahl);
    SpielFeld gibFeld();
};

#endif
