#ifndef FILE_H
#define FILE_H
#include <iostream>
#include <memory>
#include "Spieler.hpp"
#include <vector>
#include <map>

using data_key = std::string;
using data_value = std::string;
using data_store = std::map<data_key, data_value>;

class File
{

private:
public:
    File();
    std::string feld_in_String_Umwandeln(std::shared_ptr<Spieler> spieler);
    void string_in_Feld_Umwandeln(std::string feld, std::shared_ptr<Spieler> spieler);
    int daten_speichern(std::shared_ptr<Spieler> ki, std::shared_ptr<Spieler> spieler);
    data_store daten_laden();
};

#endif