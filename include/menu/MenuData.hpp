// Standard inclusion guard
#ifndef MENU_DATA_HPP
#define MENU_DATA_HPP

#include "Menu.hpp"
#include <string>
#include <fstream>

/**
 * This class manages all the data stored by the menu system
 */
class MenuData
{
private:
    /**
     * The name of the file being used for data storage
     */
    static const std::string DATA_FILE;

    /**
     * Whether or not the system has been initialized
     */
    static bool initialized;

    /**
     * The selected driver profile
     */
    static Menu::Profiles profile;

    /**
     * The selected robot configuration
     */
    static Menu::Configurations configuration;

    /**
     * The selected autonomous routine
     */
    static Menu::Autons auton;

public:
    /**
     * Sets the status of initialized
     */
    static void setInitialized(bool _initialized);

    /**
     * Checks if the menu system is initialized
     */
    static bool isInitialized();

    /**
     * Selects a profile
     */
    static void setProfile(Menu::Profiles _profile);

    /**
     * Gets the selected profile
     */
    static Menu::Profiles getProfile();

    /**
     * Selects a configuration
     */
    static void setConfiguration(Menu::Configurations _configuration);

    /**
     * Gets the selected configuration
     */
    static Menu::Configurations getConfiguration();

    /**
     * Selects an autonomous
     */
    static void setAuton(Menu::Autons _auton);

    /**
     * Gets the selected autonomous
     */
    static Menu::Autons getAuton();

    /**
     * Reads the stored menu data from the SD card
     */
    static void readData();

    /**
     * Writes the stored menu data to the SD card
     */
    static void writeData();
};

#endif