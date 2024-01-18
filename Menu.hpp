#ifndef MENU_H
#define MENU_H

#include <memory>
#include <iostream>
#include <fstream> //Filestream-Support
#include "Spieler.hpp"
#include "File.hpp"
#include "CppRandom.hpp"

class Menu
{

private:
    std::shared_ptr<File> file;
    bool ersterAufruf;

public:
    Random rand;
    Menu();
    int startMenu();
    void spielMenu(std::shared_ptr<Spieler> spieler, std::shared_ptr<Spieler> ki);
};

#endif