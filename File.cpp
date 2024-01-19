#include <fstream>
#include <iostream>
#include "File.hpp"
#include <memory>
#include "Spieler.hpp"

File::File()
{
}
std::string File::feld_in_String_Umwandeln(std::shared_ptr<Spieler> spieler)
{
    std::string zelle, stringfeld;

    for (int i = 0; i < SPIELFELD_GROESSE; ++i)
    {
        for (int j = 0; j < SPIELFELD_GROESSE; ++j)
        {

            switch (spieler->gibZellenStatus(i, j))
            {
            case LEER:
                stringfeld.append("0");
                break;
            case SCHIFF:
                stringfeld.append("1");
                break;
            case TREFFER:
                stringfeld.append("2");
                break;
            case VERSENKT:
                stringfeld.append("3");
                break;
            case VORBEI:
                stringfeld.append("4");
                break;
            }
        }
    }
    return stringfeld;
}

void File::string_in_Feld_Umwandeln(std::string feld, std::shared_ptr<Spieler> spieler)
{
    int k = 0;
    for (int i = 0; i < SPIELFELD_GROESSE; ++i)
    {
        for (int j = 0; j < SPIELFELD_GROESSE; ++j)
        {
            switch (feld[k])
            {
            case '0':
                spieler->setzeZellenStatus(i, j, LEER);
                break;
            case '1':
                spieler->setzeZellenStatus(i, j, SCHIFF);
                break;
            case '2':
                spieler->setzeZellenStatus(i, j, TREFFER);
                break;
            case '3':
                spieler->setzeZellenStatus(i, j, VERSENKT);
                break;
            case '4':
                spieler->setzeZellenStatus(i, j, VORBEI);
                break;
            }
            ++k;
        }
    }
}

int File::daten_speichern(std::shared_ptr<Spieler> ki, std::shared_ptr<Spieler> spieler)
{

    std::string save, feld;
    data_store store;

    store["Ki"] = feld_in_String_Umwandeln(ki);
    store["Spieler"] = feld_in_String_Umwandeln(spieler);

    std::ofstream schreiben("save.txt");

    if (!schreiben)
    {
        std::cout << "Fehler beim Speichern!" << std::endl;

        return -1; // Signal fuer Programm-Exit
    }

    data_store::iterator it;

    for (it = store.begin(); it != store.end(); it++)
    {
        schreiben << it->first << " " << it->second << std::endl;
    }

    schreiben.close();
    std::cout << "Erfolgreich gespeichert!" << std::endl;

    return 0;
}

data_store File::daten_laden()
{
    data_store store;
    std::ifstream laden("save.txt");
    data_key key;
    data_value value;

    std::string line;
    if (laden.is_open())
    {
        while (laden)
        {
            laden >> key >> value;
            if (!laden.bad())
            {
                store[key] = value;
            }
        }
        laden.close();
    }
    else
    {
        std::cout << "Fehler beim Oeffnen der Datei!" << std::endl;
    }
    return store;
}