// Inclusion guard
#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

// Included libraries
#include <string>
#include "Menu.hpp"
#include "MenuData.hpp"
#include "./main.h"

// Function prototypes
static lv_res_t startButtonEvent(lv_obj_t* button);
static lv_res_t autonButtonEvent(lv_obj_t* button);
static lv_res_t configButtonEvent(lv_obj_t* button);
static lv_res_t profileButtonEvent(lv_obj_t* button);

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
     * The text being displayed on the auton settings button
     */
    static const std::string AUTON_BUTTON_TEXT;

    /**
     * The text being displayed on the config settings button
     */
    static const std::string CONFIG_BUTTON_TEXT;

    /**
     * The text being displayed on the profile settings button
     */
    static const std::string PROFILE_BUTTON_TEXT;

    /**
     * The start button in the menu
     */
    lv_obj_t* startButton;

    /**
     * The label for the start button in the menu
     */
    lv_obj_t* startButtonLabel;

    /**
     * The auton settings button in the menu
     */
    lv_obj_t* autonButton;

    /**
     * The label for the auton settings button in the menu
     */
    lv_obj_t* autonButtonLabel;

    /**
     * The config settings button in the menu
     */
    lv_obj_t* configButton;

    /**
     * The label for the config settings button in the menu
     */
    lv_obj_t* configButtonLabel;

    /**
     * The profile settings button in the menu
     */
    lv_obj_t* profileButton;

    /**
     * The label for the profile settings button in the menu
     */
    lv_obj_t* profileButtonLabel;

    /**
     * The label for the current settings
     */
    lv_obj_t* settingsLabel;

    /**
     * Creates the background
     */
    void createBackground();

    /**
     * Creates the start button
     */
    void createStartButton();

    /**
     * Creates the auton settings button
     */
    void createAutonButton();

    /**
     * Creates the config settings button
     */
    void createConfigButton();

    /**
     * Creates the profile settings button
     */
    void createProfileButton();

    /**
     * Creates the current settings label
     */
    void createSettingsLabel();

public:
    /**
     * Default constructor for the MainMenu class
     */
    MainMenu();
};

#endif