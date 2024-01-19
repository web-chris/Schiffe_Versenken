#include "Spielfeld.hpp"
#include <vector>
#include <iostream>
#include "CppRandom.hpp"

SpielFeld Spielfeld::gibFeld()
{
    return spielfeld;
}

void Spielfeld::setzeZellenStatus(int ireihe, int ispalte, ZellenStatus zellenStatus)
{
    spielfeld[ireihe][ispalte] = zellenStatus;
}

bool Spielfeld::pruefeZellen(int ireihe, int ispalte, ZellenStatus zellenStatus)
{
    if (spielfeld[ireihe][ispalte] == zellenStatus)
    {
        return true;
    }
    else
    {
        return false;
    }
}

ZellenStatus Spielfeld::gibZellenStatus(int ireihe, int ispalte)
{
    return spielfeld[ireihe][ispalte];
}

void Spielfeld::spielfeldInitialisieren()
{
    for (int i = 0; i < SPIELFELD_GROESSE; ++i)
    {
        std::vector<ZellenStatus> reihe(SPIELFELD_GROESSE, LEER);
        spielfeld.push_back(reihe);
    }
}

void Spielfeld::spielfeldAusgebe(bool schiffAnzeige)
{
    std::cout << "   1  2  3  4  5  6  7  8  9  10" << std::endl;
    for (int i = 0; i < SPIELFELD_GROESSE; ++i)
    {
        std::cout << static_cast<char>('A' + i) << " ";
        for (int j = 0; j < SPIELFELD_GROESSE; ++j)
        {
            switch (spielfeld[i][j])
            {
            case LEER:
                std::cout << " ~ ";
                break;
            case SCHIFF:
                if (schiffAnzeige)
                {
                    std::cout << " # ";
                }
                else
                {
                    std::cout << " ~ ";
                }
                break;
            case TREFFER:
                std::cout << " X ";
                break;
            case VORBEI:
                std::cout << " O ";
                break;
            case VERSENKT:
                std::cout << " S ";
                break;
            }
        }
        std::cout << std::endl;
    }
}
bool Spielfeld::istPlatzierungGueltig(int reihe, int spalte, int groesse, bool vertikal)
{
    // Pruefen ob alle Felder des Schiffes sowie benachbarte Felder leer sind
    if (vertikal)
    {
        for (int i = reihe - 1; i < reihe + groesse + 1; ++i)
        {
            if (i > SPIELFELD_GROESSE)
            {
                return false;
            }
            for (int j = spalte - 1; j <= spalte + 1; ++j)
            {

                if (i >= 0 && i < SPIELFELD_GROESSE && j >= 0 && j < SPIELFELD_GROESSE)
                {
                    if (spielfeld[i][j] != LEER)
                    {
                        return false;
                    }
                }
            }
        }
    }
    else
    {
        for (int i = spalte - 1; i < spalte + groesse + 1; ++i)
        {
            if (i > SPIELFELD_GROESSE)
            {
                return false;
            }
            for (int j = reihe - 1; j <= reihe + 1; ++j)
            {
                if (i >= 0 && i < SPIELFELD_GROESSE && j >= 0 && j < SPIELFELD_GROESSE)
                {
                    if (spielfeld[j][i] != LEER)
                    {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}
bool Spielfeld::schiffPlatzieren(int reihe, int spalte, int groesse, bool vertikal)
{
    if (istPlatzierungGueltig(reihe, spalte, groesse, vertikal))
    {
        if (vertikal)
        {
            for (int i = reihe; i < reihe + groesse; ++i)
            {
                spielfeld[i][spalte] = SCHIFF;
            }
            return true;
        }
        else
        {
            for (int j = spalte; j < spalte + groesse; ++j)
            {
                spielfeld[reihe][j] = SCHIFF;
            }
            return true;
        }
    }
    else
    {
        return false;
    }
}

void Spielfeld::platziere_Schiffe(int schifflaenge, int anzahl)
{
    int schiffSpalte, schiffReihe, ausrichtung;
    bool vertikal;
    bool isInputValid = false;
    for (int i = 0; i < anzahl; ++i)
    {
        isInputValid = false;
        while (!isInputValid)
        {
            schiffReihe = rand.GetRandomNumberBetween(1, SPIELFELD_GROESSE);
            schiffSpalte = rand.GetRandomNumberBetween(1, SPIELFELD_GROESSE);
            ausrichtung = rand.GetRandomNumberBetween(1, 2);
            if (ausrichtung == 2)
            {
                vertikal = true;
            }
            else
            {
                vertikal = false;
            }
            if (schiffPlatzieren(schiffReihe - 1, schiffSpalte - 1, schifflaenge, vertikal))
            {
                isInputValid = true;
            }
            else
            {
                isInputValid = false;
            }
        }
    }
}
