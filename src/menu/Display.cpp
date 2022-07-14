#include "menu/Display.hpp"

// Private method definitions -------------------------------------------------
void Display::mainMenu()
{
    MainMenu mainMenu;
}

void Display::autonMenu()
{

}

void Display::configMenu()
{

}

void Display::profileMenu()
{
    
}

// Public method definitions --------------------------------------------------
void Display::drawMenu(Menu::Menus menu)
{
    switch(menu)
    {
        case Menu::Menus::MAIN:
            mainMenu();
            break;
        case Menu::Menus::AUTON:
            autonMenu();
            break;
        case Menu::Menus::CONFIG:
            configMenu();
            break;
        case Menu::Menus::PROFILE:
            profileMenu();
            break;
    }
}