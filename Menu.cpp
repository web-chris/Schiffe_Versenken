#include "Menu.hpp"
#include <memory>
#include <iostream>
#include <fstream> //Filestream-Support
#include "Spieler.hpp"
#include "File.hpp"
#include "CppRandom.hpp"
#include "Spiel.hpp"

Menu::Menu()
{
    file = std::make_shared<File>();
    ersterAufruf = true;
}

int Menu::startMenu()
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

    std::cout << "Willkommen bei Schiffe versenken!" << std::endl;
    std::cout << "~~~Menue~~~" << std::endl;
    std::cout << " " << std::endl;
    std::cout << "(m)enue (um in diese Menue zu gelangen)" << std::endl;
    if (!ersterAufruf)
    {
        std::cout << "(f)ortsetzen (setzt das Spiel fort)" << std::endl;
        std::cout << "(s)peichern (speichert das Spiel!)" << std::endl;
    }

    std::cout << "(n)eues Spiel (um ein neues Spiel zu Starten)" << std::endl;
    if (filetest)
    {
        std::cout << "(l)aden (um ein gespeichertes Spiel zu laden)" << std::endl;
    }
    std::cout << "(e)xit (um das Spiel zu Beenden)" << std::endl;
    std::cout << " " << std::endl;
    bool flag;

    while (!isInputValid)
    {
        std::cout << "Ihre Eingabe: ";

        std::getline(std::cin, eingabe);
        if (!ersterAufruf)
        {
            std::cout << "TEst! ist False!!" << std::endl;
        }

        if (ersterAufruf && (eingabe[0] == 's' || eingabe[0] == 'S' || eingabe[0] == 'f' || eingabe[0] == 'F'))
        {
            flag = false;
        }
        else
        {
            flag = true;
        }

        if (!std::cin.fail() && flag && (eingabe.length() == 1 || eingabe == "save" || eingabe == "SAVE" || eingabe == "exit" || eingabe == "EXIT" || eingabe == "load" || eingabe == "LOAD" || eingabe == "menue" || eingabe == "MENUE" || eingabe == "menü" || eingabe == "MENÜ"))
        {
            switch (eingabe[0])
            {
            case 'e':
            case 'E':
                std::cout << "Auf Wiedersehen!" << std::endl;
                return 0;
            case 'n':
            case 'N':
                std::cout << "Spiel begint!" << std::endl;
                ersterAufruf = false;
                return 1;
            case 's':
            case 'S':
                return 2;
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
                    return 3;
                }

            case 'f':
            case 'F':
                std::cout << "Spiel wird fortgestzt!" << std::endl;
                return 4;
            case 'm':
            case 'M':
                return startMenu();

            default:

                std::cout << "Falsche Eingabe!" << std::endl;
            }
        }
        else
        {
            std::cout << "Falsche Eingabe!" << std::endl;
        }
    }
    return -1;
}

void Menu::spielMenu(std::shared_ptr<Spieler> spieler, std::shared_ptr<Spieler> ki)
{
    Spiel spiel;

    bool amZug;
    int Zugbegin = rand.GetRandomNumberBetween(1, 2);
    switch (startMenu())
    {
    case 0:
        return;
    case 1: // Startet ein Neues Spiel
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

    case 2: // Speichert das Spiel

        if (spiel.alleSchiffeversenkt(ki) || spiel.alleSchiffeversenkt(spieler))
        {
            std::cout << "Kein Spiel zum Speichern!" << std::endl;
            spielMenu(spieler, ki);
        }
        else
        {
            std::cout << "Spiel wird gespeichert!" << std::endl;
            file->save_data(ki, spieler);
        }

        break;

    case 3: // Ladet ein Spiel
        ki->spielFeldInit();
        spieler->spielFeldInit();
        file->stirnginfeld(file->load_data()["Ki"], ki);
        file->stirnginfeld(file->load_data()["Spieler"], spieler);
        amZug = true;
        if (spiel.spielen(spieler, ki, amZug))
        {
            spielMenu(spieler, ki);
        };
        break;
    case 4: // Setzt das spiel fort

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

    default:
        break;
    }
}
int main()
{
    Menu menu;
    auto ki = std::make_shared<Spieler>(SpielerTyp::KI);
    auto spieler = std::make_shared<Spieler>(SpielerTyp::Spieler);
    menu.spielMenu(spieler, ki);

    return 0;
}
