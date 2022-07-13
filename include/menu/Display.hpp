// Standard inclusion guard
#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include "Menu.hpp"
#include <string>
#include "./main.h"

/**
 * This class manages the display on the V5 brain
 */
class Display
{
private:
    /**
     * The file name of the main menu background image
     */
    static const std::string MAIN_MENU_BACKGROUND;

    /**
     * The file name of the auton menu background image
     */
    static const std::string AUTON_MENU_BACKGROUND;

    /**
     * The file name of the config menu background image
     */
    static const std::string CONFIG_MENU_BACKGROUND;

    /**
     * The file name of the profile menu background image
     */
    static const std::string PROFILE_MENU_BACKGROUND;

public:

};

#endif