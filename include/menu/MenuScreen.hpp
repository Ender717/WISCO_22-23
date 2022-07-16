// Inclusion guard
#ifndef MENU_SCREEN_HPP
#define MENU_SCREEN_HPP

// Included libraries
#include <string>

// Included headers
#include "Menu.hpp"
#include "MenuData.hpp"
#include "./main.h"

// Event handler prototypes
static lv_res_t startButtonEvent(lv_obj_t* button);
static lv_res_t autonButtonEvent(lv_obj_t* button);
static lv_res_t configButtonEvent(lv_obj_t* button);
static lv_res_t profileButtonEvent(lv_obj_t* button);
static lv_res_t applyButtonEvent(lv_obj_t* button);
static lv_res_t cancelButtonEvent(lv_obj_t* button);
static lv_res_t previousButtonEvent(lv_obj_t* button);
static lv_res_t nextButtonEvent(lv_obj_t* button);
 
/**
 * This class manages the menu system on the v5 brain screen
 * @author Nathan Sandvig
 */
class MenuScreen
{
private:
    /**
     * The string displayed on the start button
     */
    static const char* START_BUTTON_TEXT;

    /**
     * The string displayed on the auton button
     */
    static const char* AUTON_BUTTON_TEXT;

    /**
     * The string displayed on the config button
     */
    static const char* CONFIG_BUTTON_TEXT;

    /**
     * The string displayed on the profile button
     */
    static const char* PROFILE_BUTTON_TEXT;

    /**
     * The string displayed on the apply button
     */
    static const char* APPLY_BUTTON_TEXT;

    /**
     * The string displayed on the cancel button
     */
    static const char* CANCEL_BUTTON_TEXT;

    /**
     * The string displayed on the previous button
     */
    static const char* PREVIOUS_BUTTON_TEXT;

    /**
     * The string displayed on the next button
     */
    static const char* NEXT_BUTTON_TEXT;

    /**
     * The string displayed for the current settings
     */
    static const char* SETTINGS_TEXT;

    /**
     * The maximum number of characters for the settings label
     */
    static const int MAX_SETTINGS_LABEL_CHARS;

    /**
     * The current menu
     */
    static Menu::Menus menu;

    /**
     * The index of the selected auton
     */
    static int autonIndex;

    /**
     * The index of the selected configuration
     */
    static int configIndex;

    /**
     * The index of the selected profile
     */
    static int profileIndex;

public:
    /**
     * Initializes the menu
     */
    static void initialize();

    /**
     * Draws the main menu screen
     */
    static void drawMainMenu();

    /**
     * Draws the auton menu screen
     */
    static void drawAutonMenu();

    /**
     * Draws the configuration menu
     */
    static void drawConfigMenu();

    /**
     * Draws the profile menu
     */
    static void drawProfileMenu();

    /**
     * Sets the menu data using the current stored data
     */
    static void setMenuData();

    /**
     * Gets the menu data
     */
    static void getMenuData();

    /**
     * Increments the current menu index
     */
    static void incrementIndex();

    /**
     * Decrements the current menu index
     */
    static void decrementIndex();

    /**
     * Refreshes the screen
     */
    static void refresh();
};

#endif