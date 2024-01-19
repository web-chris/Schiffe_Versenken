#include "Spieler.hpp"
#include <vector>
#include <iostream>
#include <memory>
#include "Spielfeld.hpp"
#include "Globals.hpp"

Spieler::Spieler(SpielerTyp pSpielerTyp) : spielerTyp(pSpielerTyp)
{
    spielfeld = std::make_shared<Spielfeld>();
}
void Spieler::spielFeldInit()
{
    spielfeld->spielfeldInitialisieren();
}
void Spieler::ki_Schiffe_platzierbereit(bool platzierSchiffe)
{
    if (platzierSchiffe)
    {
        std::cout << " " << std::endl;
        std::cout << "Spielfeld des Gengners" << std::endl;
        spielFeldInit();
        ki_Schiffe_platzieren(5, 1); // Schlachtschiff 1
        ki_Schiffe_platzieren(4, 2); // Kreuzer 2
        ki_Schiffe_platzieren(3, 3); // Zerstörer 3
        ki_Schiffe_platzieren(2, 4); // U-Boote 4
        spielfeldAusgebe(false);     // Schiffe ausgeblendet!
    }
}
void Spieler::spieler_Schiffe_platzieren(bool platzierSchiffe)
{
    if (platzierSchiffe)
    {
        std::cout << " " << std::endl;
        std::cout << "Spielfeld des Spielers" << std::endl;
        spielFeldInit();
        spielfeldAusgebe(true);                             // Schiffe sichtbar!
        spieler_Schiffe_platzieren(5, 1, "Schlachtschiff"); // Schlachtschiff 1
        spieler_Schiffe_platzieren(4, 2, "Kreuzer");        // Kreuzer 2
        spieler_Schiffe_platzieren(3, 3, "Zerstoerer");     // Zerstörer 3
        spieler_Schiffe_platzieren(2, 2, "U-Boote");        // U-Boote 4
    }
}

void Spieler::setzeZellenStatus(int ireihe, int ispalte, ZellenStatus zellenStatus)
{
    spielfeld->setzeZellenStatus(ireihe, ispalte, zellenStatus);
}

ZellenStatus Spieler::gibZellenStatus(int ireihe, int ispalte)
{
    return spielfeld->gibZellenStatus(ireihe, ispalte);
}
SpielFeld Spieler::gibFeld()
{
    return spielfeld->gibFeld();
}
void Spieler::spielfeldAusgebe(bool schiffAnzeige)
{
    spielfeld->spielfeldAusgebe(schiffAnzeige);
}

bool Spieler::pruefeZellen(int ireihe, int ispalte, ZellenStatus zellenStatus)
{
    if (spielfeld->gibZellenStatus(ireihe, ispalte) == zellenStatus)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Spieler::pruefenPlatzieren(std::string eingabe, int schiffGroesse)
{ // gehört zur Spieler-Definition
    char ausrichtung, reihe;
    bool vertikal;
    int ispalte, ireihe;
    std::string FehlerText = "Falsche Eingabe! Versuchen Sie es erneut!";

    try
    {
        // Prüfen ob richtige Eingabelänge
        if (eingabe.length() == 3 || eingabe.length() == 4)
        {
            // Reihe ermitteln und umwandeln
            reihe = eingabe[0];
            ireihe = koordinateZuIndex(reihe);

            // Spalte ermitteln und umwandeln
            ispalte = std::stoi(eingabe.substr(1, eingabe.length() - 2));

            // ausrichtung, ob das Schiff vertikal oder Horizontal ist, prüfen und ermitteln
            ausrichtung = eingabe[eingabe.length() - 1];

            if (ausrichtung == 'v' || ausrichtung == 'V' || ausrichtung == 'h' || ausrichtung == 'H')
            {
                if (ausrichtung == 'v' || ausrichtung == 'V')
                {
                    vertikal = true;
                }
                else
                {
                    vertikal = false;
                }
            }
            else
            {
                std::cout << FehlerText << std::endl;
                return false;
            }

            // Prüft ob die Koordinate im Spielfeld liegt
            if (!istGueltigeKoordinate(ireihe, ispalte - 1))
            {
                std::cout << FehlerText << std::endl;
                return false;
            }
        }
        else
        {
            std::cout << FehlerText << std::endl;
            return false;
        }

        // Platziert die Schiffe im Feld wenn möglich
        if (spielfeld->schiffPlatzieren(ireihe, ispalte - 1, schiffGroesse, vertikal))
        {
            spielfeldAusgebe(true);
            return true;
        }
        else
        {
            std::cout << "Ungueltige Platzierung. Schiffe duerfen nicht ueberlappen oder Aneinander stossen!" << std::endl;
            std::cout << "Versuchen Sie es erneut!" << std::endl;
            return false;
        }
    }
    catch (...)
    {
        std::cout << FehlerText << std::endl;
        return false;
    }
}

void Spieler::spieler_Schiffe_platzieren(int schiffLeange, int anzahl, std::string typ)
{ // gehört zur Spieler-Definition

    for (int i = 0; i < anzahl; ++i)
    {
        bool isInputValid = false;
        while (!isInputValid)
        {
            std::cout << "Es gibt insgesamt " << anzahl << " " << typ << ". Platzieren Sie Ihr " << i + 1 << ". (Kaestchen " << schiffLeange << "): ";
            std::string eingabe;
            std::getline(std::cin, eingabe);

            if (pruefenPlatzieren(eingabe, schiffLeange))
            {
                isInputValid = true;
            }
            std::cin.clear();
        }
    }
}

void Spieler::ki_Schiffe_platzieren(int schifflaenge, int anzahl)
{
    int schiffSpalte, schiffReihe, ausrichtung;
    bool vertikal;
    bool isInputValid = false;

    for (int i = 0; i < anzahl; ++i)
    {
        isInputValid = false;
        while (!isInputValid)
        {
            schiffReihe = globalRandom.GetRandomNumberBetween(1, SPIELFELD_GROESSE);
            schiffSpalte = globalRandom.GetRandomNumberBetween(1, SPIELFELD_GROESSE);
            ausrichtung = globalRandom.GetRandomNumberBetween(1, 2);
            if (ausrichtung == 2)
            {
                vertikal = true;
            }
            else
            {
                vertikal = false;
            }

            if (spielfeld->schiffPlatzieren(schiffReihe - 1, schiffSpalte - 1, schifflaenge, vertikal))
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

bool Spieler::istGueltigeKoordinate(int reihe, int spalte)
{
    return reihe >= 0 && reihe < SPIELFELD_GROESSE && spalte >= 0 && spalte < SPIELFELD_GROESSE;
}
// Wandelt Buchstaben in Zahlen um
int Spieler::koordinateZuIndex(char buchstabe)
{
    return std::toupper(buchstabe) - 'A';
}
