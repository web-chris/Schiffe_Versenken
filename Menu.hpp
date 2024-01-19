#ifndef MENU_H
#define MENU_H

#include <memory>
#include <iostream>
#include <fstream>
#include "Spieler.hpp"
#include "File.hpp"

enum Option
{
    MENU,
    FORTSETZEN,
    SPEICHERN,
    NEUES_SPIEL,
    LADEN,
    EXIT,
    CHEAT,
    UNDEFINIERT
};

class Menu
{

private:
    std::shared_ptr<File> file;
    bool ersterAufruf;

public:
    Menu();
    Option startMenu();
    void spielMenu(std::shared_ptr<Spieler> spieler, std::shared_ptr<Spieler> ki);
};

#endif