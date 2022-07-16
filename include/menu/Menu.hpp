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
     * The possible menus
     */
    enum class Menus
    {
        MAIN,
        AUTON,
        CONFIG,
        PROFILE
    };
    extern const char* menuStr[];
    extern const int NUM_MENUS;

    /**
     * The driver profiles stored in the menu
     */
    enum class Profiles
    {
        HENRY,
        JOHN,
        NATHAN
    };
    extern const char* profileStr[];
    extern const int NUM_PROFILES;

    /**
     * The robot configurations stored in the menu
     */
    enum class Configurations
    {
        MATCH_BLUE,
        MATCH_ORANGE,
        SKILLS_BLUE,
        SKILLS_ORANGE,
        TEST
    };
    extern const char* configurationStr[];
    extern const int NUM_CONFIGURATIONS;

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
    extern const char* autonStr[];
    extern const int NUM_AUTONS;
}

#endif