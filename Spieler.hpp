#ifndef SPIELER_H
#define SPIELER_H

#include <iostream>
#include "Spielfeld.hpp"
#include <memory>

enum class SpielerTyp
{
    KI,
    Spieler
};

class Spieler
{

private:
    SpielerTyp spielerTyp;
    std::shared_ptr<Spielfeld> spielfeld;
    bool init;

public:
    Spieler(SpielerTyp pSpielerTyp);

    ZellenStatus gibZellenStatus(int ireihe, int ispalte);
    void setzeZellenStatus(int ireihe, int ispalte, ZellenStatus zellenStatus);
    bool vergleicheZelle(int ireihe, int ispalte, ZellenStatus zellenStatus);
    void spielfeldAusgeben(bool schiffAnzeige);
    void istSchiffePlatzierenVonSpielerGueltig(int schiffLeange, int anzahl, std::string typ);
    void initSchiffePlatzierungVonSpieler(bool schiffePlatzieren);
    bool istSchiffePlatzierenVonSpielerGueltig(std::string eingabe, int schiffGroesse);
    bool istKoordinateGueltig(int reihe, int spalte);
    int KoordinatenInIndexUmwandeln(char buchstabe);
    void schiffePlatzierungVonKI(int schifflaenge, int anzahl);
    void initSchiffePlatzierungVonKI(bool schiffePlatzieren);
    void spielFeldInit();
    SpielFeld gibFeld();
};

#endif
