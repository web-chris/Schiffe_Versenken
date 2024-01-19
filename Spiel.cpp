#include <iostream>
#include <vector>
#include <memory>
#include "Spiel.hpp"
#include "Spieler.hpp"
#include "Spielfeld.hpp"
#include "Globals.hpp"

bool Spiel::spielerZug(std::shared_ptr<Spieler> spieler)
{
    std::string FehlerText = "Falsche Eingabe! Versuchen Sie es erneut!";
    std::string eingabe;
    bool isInputValid = false;
    int ispalte, ireihe; // Koordinaten
    char ausrichtung, reihe;

    while (!isInputValid)
    {
        std::cin.clear();
        std::cout << "Geben Sie die Zielkoordinaten ein (z. B. B3) oder exit um ins Menue zu gelangen: ";
        try
        {
            std::getline(std::cin, eingabe);

            if (eingabe == "m" || eingabe == "M" || eingabe == "menue" || eingabe == "MENUE" || eingabe == "exit" || eingabe == "EXIT")
            {
                return false;
            }
            if (eingabe.length() == 2 || eingabe.length() == 3)
            {
                // Reihe ermitteln und umwandeln
                ireihe = KoordinatenInIndexUmwandeln(eingabe[0]);
                // Spalte ermitteln und umwandeln
                ispalte = std::stoi(eingabe.substr(1, eingabe.length() - 1)) - 1;
                isInputValid = true;
            }
            else
            {
                std::cout << FehlerText << std::endl;
                isInputValid = false;
            }
        }
        catch (...)
        {
            std::cout << FehlerText << std::endl;
            isInputValid = false;
        }
    }
    if (istKoordinateGueltig(ireihe, ispalte) && !std::cin.fail())
    {

        switch (spieler->gibZellenStatus(ireihe, ispalte))
        {
        case LEER:
            std::cout << "Vorbei!" << std::endl;
            spieler->setzeZellenStatus(ireihe, ispalte, VORBEI);
            break;
        case SCHIFF:
            std::cout << "Treffer!" << std::endl;
            spieler->setzeZellenStatus(ireihe, ispalte, TREFFER);
            istSchiffVersenkt(spieler);
            break;
        case TREFFER:
        case VORBEI:
            std::cout << "Sie haben bereits dort geschossen. Versuchen Sie es erneut." << std::endl;
            return spielerZug(spieler);
        }
    }
    else
    {
        std::cout << "Ungueltige Koordinaten. Versuchen Sie es erneut." << std::endl;
        return spielerZug(spieler);
    }
    return true;
}

bool Spiel::hatKiGeschossen(std::shared_ptr<Spieler> gegener, int ireihe, int ispalte)
{

    if (istKoordinateGueltig(ireihe, ispalte) && !std::cin.fail())
    {
        switch (gegener->gibZellenStatus(ireihe, ispalte))
        {
        case LEER:
            std::cout << "Vorbei!" << std::endl;
            gegener->setzeZellenStatus(ireihe, ispalte, VORBEI);
            break;
        case SCHIFF:
            std::cout << "Treffer!" << std::endl;
            gegener->setzeZellenStatus(ireihe, ispalte, TREFFER);
            break;
        case TREFFER:
        case VERSENKT:
        case VORBEI:

            return false;
        }
    }
    else
    {
        return false;
    }
    return true;
}

// Spielzu der KI verbessert inteligenter
void Spiel::KIZug(std::shared_ptr<Spieler> gegener)
{
    int ispalteTreffer, ireiheTreffer, ispalte, ireihe;
    bool Schiffgetroffen = false;
    // prüfen ob schon ein treffer

    for (int i = 0; i < SPIELFELD_GROESSE; ++i)
    {
        for (int j = 0; j < SPIELFELD_GROESSE; ++j)
        {
            if (gegener->gibZellenStatus(i, j) == TREFFER)
            {
                Schiffgetroffen = true;
                ireiheTreffer = i;
                ispalteTreffer = j;
            }
        }
    }
    ireihe = ireiheTreffer;
    ispalte = ispalteTreffer;

    if (Schiffgetroffen)
    {
        int iFeld, schleife;
        bool moeglich = false;
        iFeld = 1;
        // iFeld = GetRandomNumberBetween(1, 4);
        while (!moeglich)
        {

            switch (iFeld)
            {
            case 1:
                iFeld = 1;
                --ireihe;

                if (istKoordinateGueltig(ireihe, ispalte) && gegener->gibZellenStatus(ireihe, ispalte) != VORBEI)
                {
                    break;
                }
                ireihe = ireiheTreffer;
                ispalte = ispalteTreffer;

            case 2:
                iFeld = 2;
                --ispalte;

                if (istKoordinateGueltig(ireihe, ispalte) && gegener->gibZellenStatus(ireihe, ispalte) != VORBEI)
                {
                    break;
                }
                ireihe = ireiheTreffer;
                ispalte = ispalteTreffer;
            case 3:
                iFeld = 3;
                ++ireihe;

                if (istKoordinateGueltig(ireihe, ispalte) && gegener->gibZellenStatus(ireihe, ispalte) != VORBEI)
                {
                    break;
                }
                ireihe = ireiheTreffer;
                ispalte = ispalteTreffer;
            case 4:
                iFeld = 4;
                ++ispalte;
                if (istKoordinateGueltig(ireihe, ispalte) && gegener->gibZellenStatus(ireihe, ispalte) != VORBEI)
                {
                    break;
                }
                ireihe = globalRandom.GetRandomNumberBetween(1, SPIELFELD_GROESSE) - 1;
                ispalte = globalRandom.GetRandomNumberBetween(1, SPIELFELD_GROESSE) - 1;
            }

            if (hatKiGeschossen(gegener, ireihe, ispalte))
            {
                moeglich = true;
            }
            else
            {
                moeglich = false;
            }
        }
    }
    else
    {
        ireihe = globalRandom.GetRandomNumberBetween(1, SPIELFELD_GROESSE) - 1;
        ispalte = globalRandom.GetRandomNumberBetween(1, SPIELFELD_GROESSE) - 1;
        if (hatKiGeschossen(gegener, ireihe, ispalte))
        {
            return;
        }
        else
        {
            KIZug(gegener);
        }
    }
}

// Prüft und kennzeichnet ob ein Schiff versenkt wurde
void Spiel::istSchiffVersenkt(std::shared_ptr<Spieler> spieler)
{

    int schiffGroesse = 0;
    int startreihe;
    int startspalte;
    bool schiffInTakt = false;

    // prüfung horizintal
    for (int i = 0; i < SPIELFELD_GROESSE; ++i)
    {
        schiffGroesse = 0;
        schiffInTakt = false;

        for (int j = 0; j < SPIELFELD_GROESSE; ++j)
        {
            if (spieler->gibZellenStatus(i, j) == SCHIFF || (schiffInTakt && spieler->gibZellenStatus(i, j) == TREFFER))
            {
                schiffInTakt = true;
            }
            else
            {
                schiffInTakt = false;
            }
            if (spieler->gibZellenStatus(i, j) == TREFFER && !schiffInTakt)
            {
                if (schiffGroesse == 0)
                {
                    startreihe = i;
                    startspalte = j;
                }
                ++schiffGroesse;
            }
            else
            {
                if (schiffGroesse > 1 && (spieler->gibZellenStatus(i, j) != SCHIFF))
                {
                    std::cout << "Ein Schiff wurde versenkt!" << std::endl;
                    for (int j = startspalte; j < startspalte + schiffGroesse; ++j)
                    {
                        if (spieler->gibZellenStatus(startreihe, j) == TREFFER)
                        {
                            spieler->setzeZellenStatus(startreihe, j, VERSENKT);
                        }
                    }
                }
                schiffGroesse = 0;
            }

            if (j >= SPIELFELD_GROESSE - 1 && schiffGroesse > 1 && !schiffInTakt)
            {
                std::cout << "Ein Schiff wurde versenkt!" << std::endl;
                for (int j = startspalte; j < startspalte + schiffGroesse; ++j)
                {
                    if (spieler->gibZellenStatus(startreihe, j) == TREFFER)
                    {
                        spieler->setzeZellenStatus(startreihe, j, VERSENKT);
                    }
                }
            }
        }
    }

    // prüfung vertikal
    for (int j = 0; j < SPIELFELD_GROESSE; ++j)
    {
        schiffGroesse = 0;
        schiffInTakt = false;

        for (int i = 0; i < SPIELFELD_GROESSE; ++i)
        {
            if (spieler->gibZellenStatus(i, j) == SCHIFF || (schiffInTakt && spieler->gibZellenStatus(i, j) == ZellenStatus::TREFFER))
            {
                schiffInTakt = true;
            }
            else
            {
                schiffInTakt = false;
            }
            if (spieler->gibZellenStatus(i, j) == TREFFER && !schiffInTakt)
            {
                if (schiffGroesse == 0)
                {
                    startreihe = i;
                    startspalte = j;
                }
                ++schiffGroesse;
            }

            else
            {
                if (schiffGroesse > 1 && (spieler->gibZellenStatus(i, j) != SCHIFF))
                {
                    std::cout << "Ein Schiff wurde versenkt!" << std::endl;
                    for (int i = startreihe; i < startreihe + schiffGroesse; ++i)
                    {
                        if (spieler->gibZellenStatus(i, startspalte) == TREFFER)
                        {
                            spieler->setzeZellenStatus(i, startspalte, VERSENKT);
                        }
                    }
                }
                schiffGroesse = 0;
            }

            if (i >= SPIELFELD_GROESSE - 1 && schiffGroesse > 1 && !schiffInTakt)
            {
                std::cout << "Ein Schiff wurde versenkt!" << std::endl;
                for (int i = startreihe; i < startreihe + schiffGroesse; ++i)
                {
                    if (spieler->gibZellenStatus(i, startspalte) == TREFFER)
                    {
                        spieler->setzeZellenStatus(i, startspalte, VERSENKT);
                    }
                }
            }
        }
    }
}

// Prüft ob alle schiffe versenkt wurden
bool Spiel::sindAlleSchiffeVersenkt(std::shared_ptr<Spieler> spieler)
{
    bool alleSchiffeversenkt = true;
    for (int i = 0; i < SPIELFELD_GROESSE; ++i)
    {
        for (int j = 0; j < SPIELFELD_GROESSE; ++j)
        {
            if (spieler->vergleicheZelle(i, j, SCHIFF))
            {
                alleSchiffeversenkt = false;
                return false;
                break;
            }
        }
    }

    if (alleSchiffeversenkt)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Spiel::istKoordinateGueltig(int reihe, int spalte)
{
    return reihe >= 0 && reihe < SPIELFELD_GROESSE && spalte >= 0 && spalte < SPIELFELD_GROESSE;
}
// Wandelt Buchstaben in Zahlen um
int Spiel::KoordinatenInIndexUmwandeln(char buchstabe)
{
    return std::toupper(buchstabe) - 'A';
}

bool Spiel::spielen(std::shared_ptr<Spieler> spieler, std::shared_ptr<Spieler> gegener, bool amZug)
{
    std::cout << "\nAuf in die Schlacht!" << std::endl;
    std::cout << "\nDas Feindliche Feld" << std::endl;
    gegener->spielfeldAusgeben(false);

    std::cout << "\nIhre Flotte!" << std::endl;
    spieler->spielfeldAusgeben(true);

    bool Spiel = true;
    while (Spiel)
    {

        if (sindAlleSchiffeVersenkt(gegener))
        {
            std::cout << "\nGlueckwunsch, Sie haben die Feindliche Flotte Besiegt!" << std::endl;
            Spiel = false;
            gegener->spielfeldAusgeben(true);
            std::cout << "------------------------------" << std::endl;
            return 0;
        }

        if (sindAlleSchiffeVersenkt(spieler))
        {
            std::cout << "\nSchade, Sie wurden versenkt!" << std::endl;
            Spiel = false;
            spieler->spielfeldAusgeben(true);
            std::cout << "------------------------------" << std::endl;
            return 0;
        }
        if (amZug)
        {
            std::cout << "\nSie sind am Zug!" << std::endl;

            if (!spielerZug(gegener))
            {
                return true;
            }
            istSchiffVersenkt(gegener);
            gegener->spielfeldAusgeben(false);
            std::cout << "------------------------------" << std::endl;
            amZug = false;
        }
        else
        {
            std::cout << "\nDer Feind ist am Zug!" << std::endl;
            KIZug(spieler);
            istSchiffVersenkt(spieler);
            spieler->spielfeldAusgeben(true);
            std::cout << "------------------------------" << std::endl;
            amZug = true;
        }
    }

    return 0;
}