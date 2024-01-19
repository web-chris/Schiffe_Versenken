#include <memory>
#include <iostream>
#include <fstream>
#include "Menu.hpp"
#include "Spieler.hpp"

int main()
{ // Spieler anlegen
    auto ki = std::make_shared<Spieler>(SpielerTyp::KI);
    auto spieler = std::make_shared<Spieler>(SpielerTyp::Spieler);

    // um das Spiel zu initialisieren, wird ein Menü angelegt
    Menu menu;
    // hier wird das Menü für den menschlichen Spieler angezeigt
    // und somit kann der Spieler eine der möglichen Optionen auswählen, um das Spiel beispielsweise zu starten
    menu.spielMenu(spieler, ki);
    std::cout << "\nAuf Wiedersehen!\n"<< std::endl;

    return 0;
}
