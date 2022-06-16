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
    const std::string profileStr[] = {"HENRY", "JOHN", "NATHAN"};
    const int NUM_PROFILES = 3;

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
    const std::string configurationStr[] = {"MATCH_BLUE", "MATCH_ORANGE", "SKILLS_BLUE", "SKILLS_ORANGE"};
    const int NUM_CONFIGURATIONS = 4;

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
    const std::string autonStr[] = {"BLUE_LEFT", "BLUE_RIGHT", "RED_LEFT", "RED_RIGHT", "SKILLS_LEFT", "SKILLS_RIGHT"};
    const int NUM_AUTONS = 6;
}

#endif