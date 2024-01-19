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
    Spieler(SpielerTyp pSpielerTyp, bool init);
    ZellenStatus gibZellenStatus(int ireihe, int ispalte);
    void setzeZellenStatus(int ireihe, int ispalte, ZellenStatus zellenStatus);
    bool pruefeZellen(int ireihe, int ispalte, ZellenStatus zellenStatus);
    void spielfeldAusgebe(bool schiffAnzeige);
    void spieler_Schiffe_platzieren(int schiffLeange, int anzahl, std::string typ);
    bool pruefenPlatzieren(std::string eingabe, int schiffGroesse);
    bool istGueltigeKoordinate(int reihe, int spalte);
    int koordinateZuIndex(char buchstabe);
    void ki_Schiffe_platzieren(int schifflaenge, int anzahl);
    void ki_Schiffe_platzierbereit(bool platzierSchiffe);
    void spieler_Schiffe_platzieren(bool platzierSchiffe);
    void spielFeldInit();
    SpielFeld gibFeld();
};

#endif