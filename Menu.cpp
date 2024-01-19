#include "Menu.hpp"
#include <memory>
#include <iostream>
#include <fstream>
#include "Spieler.hpp"
#include "File.hpp"
#include "Spiel.hpp"
#include "Globals.hpp"
Menu::Menu()
{
    file = std::make_shared<File>();
    ersterAufruf = true;
}

Option Menu::startMenu()
{
    bool isInputValid = false;
    std::string eingabe;

    std::ifstream FileTest("save.txt");
    bool filetest = false;
    if (!FileTest)
    {
        filetest = false;
    }
    else
    {
        filetest = true;
    }

    FileTest.close();
    std::cout << " " << std::endl;
    std::cout << "***********************************************\n";
    std::cout << "*      Willkommen bei Schiffe Versenken!      *\n";
    std::cout << "***********************************************\n";
    std::cout << "*                [m] Menue                    *\n";
    if (!ersterAufruf)
    {
        std::cout << "*                [f] Fortsetzen               *\n";
        std::cout << "*                [s] Speichern                *\n";
        std::cout << "*                [c] Cheaten                  *\n";
    }
    std::cout << "*                [n] Neues Spiel              *\n";
    if (filetest)
    {

        std::cout << "*                [l] Laden                    *\n";
    }
    std::cout << "*                [e] Exit                     *\n";
    std::cout << "***********************************************\n";
    std::cout << " " << std::endl;

    bool flag;

    while (!isInputValid)
    {
        std::cout << "Ihre Eingabe: ";

        std::getline(std::cin, eingabe);
        if (ersterAufruf && (eingabe[0] == 's' || eingabe[0] == 'S' || eingabe[0] == 'f' || eingabe[0] == 'F' || eingabe[0] == 'c' || eingabe[0] == 'C'))
        {
            flag = false;
        }
        else
        {
            flag = true;
        }

        if (!std::cin.fail() && flag && (eingabe.length() == 1 || eingabe == "save" || eingabe == "SAVE" || eingabe == "exit" || eingabe == "EXIT" || eingabe == "load" || eingabe == "LOAD" || eingabe == "menue" || eingabe == "MENUE" || eingabe == "menü" || eingabe == "MENÜ" || eingabe == "cheat" || eingabe == "CHEAT"))
        {
            switch (eingabe[0])
            {
            case 'e':
            case 'E':
                return Option::EXIT;
            case 'n':
            case 'N':
                std::cout << "Spiel begint!" << std::endl;
                ersterAufruf = false;
                return Option::NEUES_SPIEL;
            case 's':
            case 'S':
                return Option::SPEICHERN;
            case 'l':
            case 'L':
                if (!filetest)
                {
                    std::cout << "Kein Gespeichertes Spiel gefunden!" << std::endl;
                    break;
                }
                else
                {
                    std::cout << "Spiel wird geladen!" << std::endl;
                    ersterAufruf = false;
                    return Option::LADEN;
                }

            case 'f':
            case 'F':
                std::cout << "Spiel wird fortgestzt!" << std::endl;
                return Option::FORTSETZEN;
            case 'm':
            case 'M':
                return startMenu();

            case 'C':
            case 'c':
                std::cout << "\nEin Spion hat die Position der Feindlichen Flotte erspaeht!" << std::endl;
                return CHEAT;
            default:

                std::cout << "Falsche Eingabe!" << std::endl;
            }
        }
        else
        {
            std::cout << "Falsche Eingabe!" << std::endl;
        }
    }
    return Option::UNDEFINIERT;
}

void Menu::spielMenu(std::shared_ptr<Spieler> spieler, std::shared_ptr<Spieler> ki)
{
    Spiel spiel;

    bool amZug;
    int Zugbegin = globalRandom.GetRandomNumberBetween(1, 2);
    switch (startMenu())
    {
    case Option::EXIT:
        return;
    case Option::NEUES_SPIEL: // Startet ein Neues Spiel
        ki = std::make_shared<Spieler>(SpielerTyp::KI);
        spieler = std::make_shared<Spieler>(SpielerTyp::Spieler);
        std::cout << "Alle Schiffe Platziert!" << std::endl;
        ki->ki_Schiffe_platzierbereit(true);
        spieler->spieler_Schiffe_platzieren(true);

        if (Zugbegin == 2)
        {
            amZug = true;
        }
        else
        {
            amZug = false;
        }
        if (spiel.spielen(spieler, ki, amZug))
        {
            spielMenu(spieler, ki);
        };
        break;

    case Option::SPEICHERN: // Speichert das Spiel

        if (spiel.alleSchiffeversenkt(ki) || spiel.alleSchiffeversenkt(spieler))
        {
            std::cout << "Kein Spiel zum Speichern!" << std::endl;
            spielMenu(spieler, ki);
        }
        else
        {
            std::cout << "Spiel wird gespeichert!" << std::endl;
            file->daten_speichern(ki, spieler);
            spielMenu(spieler, ki);
        }

        break;

    case Option::LADEN: // Ladet ein Spiel
        ki->spielFeldInit();
        spieler->spielFeldInit();
        file->string_in_Feld_Umwandeln(file->daten_laden()["Ki"], ki);
        file->string_in_Feld_Umwandeln(file->daten_laden()["Spieler"], spieler);
        amZug = true;
        if (spiel.spielen(spieler, ki, amZug))
        {
            spielMenu(spieler, ki);
        };
        break;
    case Option::FORTSETZEN: // Setzt das spiel fort

        if (spiel.alleSchiffeversenkt(ki) || spiel.alleSchiffeversenkt(spieler))
        {
            std::cout << "Kein Spiel zum Fortsetzen!" << std::endl;
            spielMenu(spieler, ki);
        }
        else
        {
            amZug = true;
            if (spiel.spielen(spieler, ki, amZug))
            {
                spielMenu(spieler, ki);
            };
        }
        break;

    case CHEAT: // cheat
        ki->spielfeldAusgebe(true);
        spielMenu(spieler, ki);

    default:
        break;
    }
}
