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
    //Spieler(SpielerTyp pSpielerTyp, bool init);
//Umbenennen gibZellenstatusAnDerStelle
    ZellenStatus gibZellenStatus(int ireihe, int ispalte);
//Umbenennen setzeZielZellenstatus
    void setzeZellenStatus(int ireihe, int ispalte, ZellenStatus zellenStatus);
//Umbenennen vergleicheZelle
    bool pruefeZellen(int ireihe, int ispalte, ZellenStatus zellenStatus);
    void spielfeldAusgebe(bool schiffAnzeige);
//Umbenennen istSchiffePlatzierenVonSpielerGueltig
    void spieler_Schiffe_platzieren(int schiffLeange, int anzahl, std::string typ);
//Umbenennen initSchiffePlatzierungVonSpieler  bool  schiffePlatzieren
    void spieler_Schiffe_platzieren(bool platzierSchiffe);
//Umbenennen istSchiffePlatzierenVonSpielerGueltig
    bool pruefenPlatzieren(std::string eingabe, int schiffGroesse);
//Umbenennen istKoordinateGültig
    bool istGueltigeKoordinate(int reihe, int spalte);
//Umbenennen koordinatenInIndexUmwandeln
    int koordinateZuIndex(char buchstabe);
//Umbenennen schiffePlatzierungVonKI
    void ki_Schiffe_platzieren(int schifflaenge, int anzahl);
//Umbenennen initSchiffePlatzierungVonKI    bool  schiffePlatzieren
    void ki_Schiffe_platzierbereit(bool platzierSchiffe);
    void spielFeldInit();
    SpielFeld gibFeld();
};

#endif
