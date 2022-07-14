// Standard inclusion guard
#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include "Menu.hpp"
#include "MainMenu.hpp"
#include "./main.h"

/**
 * This class manages the display on the V5 brain
 */
class Display
{
private:
    /**
     * The main menu function
     */
    static void mainMenu();

    /**
     * The auton menu function
     */
    static void autonMenu();

    /**
     * The config menu function
     */
    static void configMenu();

    /**
     * The profile menu function
     */
    static void profileMenu();

public:
    /**
     * Draws the selected menu
     */
    static void drawMenu(Menu::Menus menu);
};

#endif