// Inclusion guard
#ifndef MAIN_MENU_H
#define MAIN_MENU_H

// Included libraries
#include <string>
#include "./main.h"

// Function prototypes
static lv_res_t startButtonEvent(lv_obj_t* button);

/**
 * This class manages the main menu screen of the menu system
 */
class MainMenu
{
private:
    /**
     * The text being displayed on the start button
     */
    static const std::string START_BUTTON_TEXT;

    /**
     * The start button in the menu
     */
    lv_obj_t* startButton;

    /**
     * The label for the start button in the menu
     */
    lv_obj_t* startButtonLabel;

public:
    /**
     * Default constructor for the MainMenu class
     */
    MainMenu();
};

#endif