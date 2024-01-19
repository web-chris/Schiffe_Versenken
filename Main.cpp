#include <memory>
#include <iostream>
#include <fstream>
#include "Menu.hpp"
#include "Spieler.hpp"

int main()
{
    Menu menu;
    auto ki = std::make_shared<Spieler>(SpielerTyp::KI);
    auto spieler = std::make_shared<Spieler>(SpielerTyp::Spieler);
    menu.spielMenu(spieler, ki);
    std::cout << "\nAuf Wiedersehen!\n"<< std::endl;

    return 0;
}