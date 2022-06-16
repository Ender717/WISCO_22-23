// Inclusion guard
#ifndef MENU_HPP
#define MENU_HPP

// Included libraries
#include "./main.h"

/**
 * This namespace manages the menu system data types
 */
namespace Menu
{
    /**
     * The driver profiles stored in the menu
     */
    enum class Profiles
    {
        HENRY,
        JOHN,
        NATHAN
    };

    /**
     * The robot configurations stored in the menu
     */
    enum class Configurations
    {
        MATCH_BLUE,
        MATCH_ORANGE,
        SKILLS_BLUE,
        SKILLS_ORANGE
    };

    /**
     * The autonomous routines stored in the menu
     */
    enum class Autons
    {
        BLUE_LEFT,
        BLUE_RIGHT,
        RED_LEFT,
        RED_RIGHT,
        SKILLS_LEFT,
        SKILLS_RIGHT
    };
}

#endif