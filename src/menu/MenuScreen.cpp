// Defined header
#include "menu/MenuScreen.hpp"
#include "Menu.hpp"
#include "display/lv_core/lv_obj.h"

// Event handler declarations -------------------------------------------------
static lv_res_t startButtonEvent(lv_obj_t* button)
{
    lv_obj_clean(lv_scr_act());
    initialize();

    return LV_RES_INV;
}

static lv_res_t autonButtonEvent(lv_obj_t* button)
{
    lv_obj_clean(lv_scr_act());
    MenuScreen::drawAutonMenu();

    return LV_RES_INV;
}

static lv_res_t configButtonEvent(lv_obj_t *button)
{
    lv_obj_clean(lv_scr_act());
    MenuScreen::drawConfigMenu();

    return LV_RES_INV;
}

static lv_res_t profileButtonEvent(lv_obj_t *button)
{
    lv_obj_clean(lv_scr_act());
    MenuScreen::drawProfileMenu();

    return LV_RES_INV;
}

static lv_res_t applyButtonEvent(lv_obj_t* button)
{
    MenuScreen::setMenuData();
    lv_obj_clean(lv_scr_act());
    MenuScreen::drawMainMenu();

    return LV_RES_INV;
}

static lv_res_t cancelButtonEvent(lv_obj_t *button)
{
    MenuScreen::getMenuData();
    lv_obj_clean(lv_scr_act());
    MenuScreen::drawMainMenu();

    return LV_RES_INV;
}

static lv_res_t previousButtonEvent(lv_obj_t *button)
{
    MenuScreen::decrementIndex();
    MenuScreen::refresh();

    return LV_RES_INV;
}

static lv_res_t nextButtonEvent(lv_obj_t *button)
{
    MenuScreen::incrementIndex();
    MenuScreen::refresh();

    return LV_RES_INV;
}

// Constant attribute declarations --------------------------------------------
const char* MenuScreen::START_BUTTON_TEXT = "START";
const char* MenuScreen::AUTON_BUTTON_TEXT = "AUTON";
const char* MenuScreen::CONFIG_BUTTON_TEXT = "CONFIG";
const char* MenuScreen::PROFILE_BUTTON_TEXT = "PROFILE";
const char* MenuScreen::APPLY_BUTTON_TEXT = "APPLY";
const char* MenuScreen::CANCEL_BUTTON_TEXT = "CANCEL";
const char* MenuScreen::PREVIOUS_BUTTON_TEXT = "<";
const char* MenuScreen::NEXT_BUTTON_TEXT = ">";
const char* MenuScreen::SETTINGS_TEXT = "SETTINGS:\nAuton: %s\nConfig: %s\nProfile: %s";
const int MenuScreen::MAX_SETTINGS_LABEL_CHARS = 100;

// Static attribute declarations ----------------------------------------------
Menu::Menus MenuScreen::menu = Menu::Menus::MAIN;
int MenuScreen::autonIndex = 0;
int MenuScreen::configIndex = 0;
int MenuScreen::profileIndex = 0;

// Public method declarations -------------------------------------------------
void MenuScreen::initialize()
{
    menu = Menu::Menus::MAIN;
    getMenuData();
    drawMainMenu();
}

void MenuScreen::drawMainMenu()
{
    // Set the current menu
    menu = Menu::Menus::MAIN;

    // Create the background style
    static lv_style_t backgroundStyle;
    lv_style_copy(&backgroundStyle, &lv_style_pretty);
    backgroundStyle.body.main_color = LV_COLOR_ORANGE;
    
    // Create the label style
    static lv_style_t labelStyle;
    lv_style_copy(&labelStyle, &lv_style_plain);
    labelStyle.text.color = LV_COLOR_WHITE;

    // Create the released button style
    static lv_style_t buttonReleasedStyle;
    lv_style_copy(&buttonReleasedStyle, &lv_style_btn_rel);

    // Create the pressed button style
    static lv_style_t buttonPressedStyle;
    lv_style_copy(&buttonPressedStyle, &lv_style_btn_pr);

    // Create the button label style
    static lv_style_t buttonLabelStyle;
    lv_style_copy(&buttonLabelStyle, &lv_style_plain);
    buttonLabelStyle.text.color = LV_COLOR_WHITE;

    // Create the background
    lv_obj_set_style(lv_scr_act(), &backgroundStyle);

    // Create the start button
    lv_obj_t* startButton = lv_btn_create(lv_scr_act(), NULL);
    lv_btn_set_action(startButton, LV_BTN_ACTION_CLICK, startButtonEvent);
    lv_btn_set_style(startButton, LV_BTN_STYLE_REL, &buttonReleasedStyle);
    lv_btn_set_style(startButton, LV_BTN_STYLE_PR, &buttonPressedStyle);
    lv_obj_set_size(startButton, 200, 100);
    lv_obj_align(startButton, NULL, LV_ALIGN_IN_TOP_LEFT, 20, 30);

    // Create the start button label
    lv_obj_t* startButtonLabel = lv_label_create(startButton, NULL);
    lv_label_set_text(startButtonLabel, START_BUTTON_TEXT);
    lv_label_set_style(startButtonLabel, &buttonLabelStyle);

    // Create the auton button
    lv_obj_t* autonButton = lv_btn_create(lv_scr_act(), NULL);
    lv_btn_set_action(autonButton, LV_BTN_ACTION_CLICK, autonButtonEvent);
    lv_btn_set_style(autonButton, LV_BTN_STYLE_REL, &buttonReleasedStyle);
    lv_btn_set_style(autonButton, LV_BTN_STYLE_PR, &buttonPressedStyle);
    lv_obj_set_size(autonButton, 120, 60);
    lv_obj_align(autonButton, NULL, LV_ALIGN_IN_TOP_LEFT, 20, 160);

    // Create the auton button label
    lv_obj_t* autonButtonLabel = lv_label_create(autonButton, NULL);
    lv_label_set_text(autonButtonLabel, AUTON_BUTTON_TEXT);
    lv_label_set_style(autonButtonLabel, &buttonLabelStyle);

    // Create the config button
    lv_obj_t* configButton = lv_btn_create(lv_scr_act(), NULL);
    lv_btn_set_action(configButton, LV_BTN_ACTION_CLICK, configButtonEvent);
    lv_btn_set_style(configButton, LV_BTN_STYLE_REL, &buttonReleasedStyle);
    lv_btn_set_style(configButton, LV_BTN_STYLE_PR, &buttonPressedStyle);
    lv_obj_set_size(configButton, 120, 60);
    lv_obj_align(configButton, NULL, LV_ALIGN_IN_TOP_LEFT, 180, 160);

    // Create the config button label
    lv_obj_t* configButtonLabel = lv_label_create(configButton, NULL);
    lv_label_set_text(configButtonLabel, CONFIG_BUTTON_TEXT);
    lv_label_set_style(configButtonLabel, &buttonLabelStyle);

    // Create the profile button
    lv_obj_t* profileButton = lv_btn_create(lv_scr_act(), NULL);
    lv_btn_set_action(profileButton, LV_BTN_ACTION_CLICK, profileButtonEvent);
    lv_btn_set_style(profileButton, LV_BTN_STYLE_REL, &buttonReleasedStyle);
    lv_btn_set_style(profileButton, LV_BTN_STYLE_PR, &buttonPressedStyle);
    lv_obj_set_size(profileButton, 120, 60);
    lv_obj_align(profileButton, NULL, LV_ALIGN_IN_TOP_LEFT, 340, 160);

    // Create the profile button label
    lv_obj_t* profileButtonLabel = lv_label_create(profileButton, NULL);
    lv_label_set_text(profileButtonLabel, PROFILE_BUTTON_TEXT);
    lv_label_set_style(profileButtonLabel, &buttonLabelStyle);

    // Create the settings label text
    char settingsText[MAX_SETTINGS_LABEL_CHARS];
    snprintf(settingsText, MAX_SETTINGS_LABEL_CHARS, SETTINGS_TEXT,
        Menu::autonStr[static_cast<int>(MenuData::getAuton())],
        Menu::configurationStr[static_cast<int>(MenuData::getConfiguration())], 
        Menu::profileStr[static_cast<int>(MenuData::getProfile())]);

    // Create the settings label
    lv_obj_t* settingsLabel = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(settingsLabel, settingsText);
    lv_label_set_style(settingsLabel, &labelStyle);
    lv_obj_align(settingsLabel, NULL, LV_ALIGN_IN_TOP_RIGHT, -20, 40);
}

void MenuScreen::drawAutonMenu()
{
    // Set the current menu
    menu = Menu::Menus::AUTON;

    // Create the background style
    static lv_style_t backgroundStyle;
    lv_style_copy(&backgroundStyle, &lv_style_pretty);
    backgroundStyle.body.main_color = LV_COLOR_ORANGE;
    
    // Create the label style
    static lv_style_t labelStyle;
    lv_style_copy(&labelStyle, &lv_style_plain);
    labelStyle.text.color = LV_COLOR_WHITE;

    // Create the released button style
    static lv_style_t buttonReleasedStyle;
    lv_style_copy(&buttonReleasedStyle, &lv_style_btn_rel);

    // Create the pressed button style
    static lv_style_t buttonPressedStyle;
    lv_style_copy(&buttonPressedStyle, &lv_style_btn_pr);

    // Create the button label style
    static lv_style_t buttonLabelStyle;
    lv_style_copy(&buttonLabelStyle, &lv_style_plain);
    buttonLabelStyle.text.color = LV_COLOR_WHITE;

    // Create the background
    lv_obj_set_style(lv_scr_act(), &backgroundStyle);

    // Create the apply button
    lv_obj_t* applyButton = lv_btn_create(lv_scr_act(), NULL);
    lv_btn_set_action(applyButton, LV_BTN_ACTION_CLICK, applyButtonEvent);
    lv_btn_set_style(applyButton, LV_BTN_STYLE_REL, &buttonReleasedStyle);
    lv_btn_set_style(applyButton, LV_BTN_STYLE_PR, &buttonPressedStyle);
    lv_obj_set_size(applyButton, 140, 60);
    lv_obj_align(applyButton, NULL, LV_ALIGN_IN_TOP_LEFT, 250, 160);

    // Create the apply button label
    lv_obj_t* applyButtonLabel = lv_label_create(applyButton, NULL);
    lv_label_set_text(applyButtonLabel, APPLY_BUTTON_TEXT);
    lv_label_set_style(applyButtonLabel, &buttonLabelStyle);

    // Create the cancel button
    lv_obj_t* cancelButton = lv_btn_create(lv_scr_act(), NULL);
    lv_btn_set_action(cancelButton, LV_BTN_ACTION_CLICK, cancelButtonEvent);
    lv_btn_set_style(cancelButton, LV_BTN_STYLE_REL, &buttonReleasedStyle);
    lv_btn_set_style(cancelButton, LV_BTN_STYLE_PR, &buttonPressedStyle);
    lv_obj_set_size(cancelButton, 140, 60);
    lv_obj_align(cancelButton, NULL, LV_ALIGN_IN_TOP_LEFT, 90, 160);

    // Create the cancel button label
    lv_obj_t* cancelButtonLabel = lv_label_create(cancelButton, NULL);
    lv_label_set_text(cancelButtonLabel, CANCEL_BUTTON_TEXT);
    lv_label_set_style(cancelButtonLabel, &buttonLabelStyle);

    // Create the previous button
    lv_obj_t* previousButton = lv_btn_create(lv_scr_act(), NULL);
    lv_btn_set_action(previousButton, LV_BTN_ACTION_CLICK, previousButtonEvent);
    lv_btn_set_style(previousButton, LV_BTN_STYLE_REL, &buttonReleasedStyle);
    lv_btn_set_style(previousButton, LV_BTN_STYLE_PR, &buttonPressedStyle);
    lv_obj_set_size(previousButton, 80, 80);
    lv_obj_align(previousButton, NULL, LV_ALIGN_IN_TOP_LEFT, 20, 60);

    // Create the left button label
    lv_obj_t* previousButtonLabel = lv_label_create(previousButton, NULL);
    lv_label_set_text(previousButtonLabel, PREVIOUS_BUTTON_TEXT);
    lv_label_set_style(previousButtonLabel, &buttonLabelStyle);

    // Create the right button
    lv_obj_t* nextButton = lv_btn_create(lv_scr_act(), NULL);
    lv_btn_set_action(nextButton, LV_BTN_ACTION_CLICK, nextButtonEvent);
    lv_btn_set_style(nextButton, LV_BTN_STYLE_REL, &buttonReleasedStyle);
    lv_btn_set_style(nextButton, LV_BTN_STYLE_PR, &buttonPressedStyle);
    lv_obj_set_size(nextButton, 80, 80);
    lv_obj_align(nextButton, NULL, LV_ALIGN_IN_TOP_LEFT, 380, 60);

    // Create the profile button label
    lv_obj_t* nextButtonLabel = lv_label_create(nextButton, NULL);
    lv_label_set_text(nextButtonLabel, NEXT_BUTTON_TEXT);
    lv_label_set_style(nextButtonLabel, &buttonLabelStyle);

    // Create the auton label
    lv_obj_t* autonLabel = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(autonLabel, Menu::autonStr[autonIndex]);
    lv_label_set_style(autonLabel, &labelStyle);
    lv_obj_align(autonLabel, NULL, LV_ALIGN_CENTER, 0, -20);
}

void MenuScreen::drawConfigMenu()
{
    // Set the current menu
    menu = Menu::Menus::CONFIG;

    // Create the background style
    static lv_style_t backgroundStyle;
    lv_style_copy(&backgroundStyle, &lv_style_pretty);
    backgroundStyle.body.main_color = LV_COLOR_ORANGE;
    
    // Create the label style
    static lv_style_t labelStyle;
    lv_style_copy(&labelStyle, &lv_style_plain);
    labelStyle.text.color = LV_COLOR_WHITE;

    // Create the released button style
    static lv_style_t buttonReleasedStyle;
    lv_style_copy(&buttonReleasedStyle, &lv_style_btn_rel);

    // Create the pressed button style
    static lv_style_t buttonPressedStyle;
    lv_style_copy(&buttonPressedStyle, &lv_style_btn_pr);

    // Create the button label style
    static lv_style_t buttonLabelStyle;
    lv_style_copy(&buttonLabelStyle, &lv_style_plain);
    buttonLabelStyle.text.color = LV_COLOR_WHITE;

    // Create the background
    lv_obj_set_style(lv_scr_act(), &backgroundStyle);

    // Create the apply button
    lv_obj_t* applyButton = lv_btn_create(lv_scr_act(), NULL);
    lv_btn_set_action(applyButton, LV_BTN_ACTION_CLICK, applyButtonEvent);
    lv_btn_set_style(applyButton, LV_BTN_STYLE_REL, &buttonReleasedStyle);
    lv_btn_set_style(applyButton, LV_BTN_STYLE_PR, &buttonPressedStyle);
    lv_obj_set_size(applyButton, 140, 60);
    lv_obj_align(applyButton, NULL, LV_ALIGN_IN_TOP_LEFT, 250, 160);

    // Create the apply button label
    lv_obj_t* applyButtonLabel = lv_label_create(applyButton, NULL);
    lv_label_set_text(applyButtonLabel, APPLY_BUTTON_TEXT);
    lv_label_set_style(applyButtonLabel, &buttonLabelStyle);

    // Create the cancel button
    lv_obj_t* cancelButton = lv_btn_create(lv_scr_act(), NULL);
    lv_btn_set_action(cancelButton, LV_BTN_ACTION_CLICK, cancelButtonEvent);
    lv_btn_set_style(cancelButton, LV_BTN_STYLE_REL, &buttonReleasedStyle);
    lv_btn_set_style(cancelButton, LV_BTN_STYLE_PR, &buttonPressedStyle);
    lv_obj_set_size(cancelButton, 140, 60);
    lv_obj_align(cancelButton, NULL, LV_ALIGN_IN_TOP_LEFT, 90, 160);

    // Create the cancel button label
    lv_obj_t* cancelButtonLabel = lv_label_create(cancelButton, NULL);
    lv_label_set_text(cancelButtonLabel, CANCEL_BUTTON_TEXT);
    lv_label_set_style(cancelButtonLabel, &buttonLabelStyle);

    // Create the previous button
    lv_obj_t* previousButton = lv_btn_create(lv_scr_act(), NULL);
    lv_btn_set_action(previousButton, LV_BTN_ACTION_CLICK, previousButtonEvent);
    lv_btn_set_style(previousButton, LV_BTN_STYLE_REL, &buttonReleasedStyle);
    lv_btn_set_style(previousButton, LV_BTN_STYLE_PR, &buttonPressedStyle);
    lv_obj_set_size(previousButton, 80, 80);
    lv_obj_align(previousButton, NULL, LV_ALIGN_IN_TOP_LEFT, 20, 60);

    // Create the left button label
    lv_obj_t* previousButtonLabel = lv_label_create(previousButton, NULL);
    lv_label_set_text(previousButtonLabel, PREVIOUS_BUTTON_TEXT);
    lv_label_set_style(previousButtonLabel, &buttonLabelStyle);

    // Create the right button
    lv_obj_t* nextButton = lv_btn_create(lv_scr_act(), NULL);
    lv_btn_set_action(nextButton, LV_BTN_ACTION_CLICK, nextButtonEvent);
    lv_btn_set_style(nextButton, LV_BTN_STYLE_REL, &buttonReleasedStyle);
    lv_btn_set_style(nextButton, LV_BTN_STYLE_PR, &buttonPressedStyle);
    lv_obj_set_size(nextButton, 80, 80);
    lv_obj_align(nextButton, NULL, LV_ALIGN_IN_TOP_LEFT, 380, 60);

    // Create the profile button label
    lv_obj_t* nextButtonLabel = lv_label_create(nextButton, NULL);
    lv_label_set_text(nextButtonLabel, NEXT_BUTTON_TEXT);
    lv_label_set_style(nextButtonLabel, &buttonLabelStyle);

    // Create the configuration label
    lv_obj_t* configLabel = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(configLabel, Menu::configurationStr[configIndex]);
    lv_label_set_style(configLabel, &labelStyle);
    lv_obj_align(configLabel, NULL, LV_ALIGN_CENTER, 0, -20);
}

void MenuScreen::drawProfileMenu()
{
    // Set the current menu
    menu = Menu::Menus::PROFILE;

    // Create the background style
    static lv_style_t backgroundStyle;
    lv_style_copy(&backgroundStyle, &lv_style_pretty);
    backgroundStyle.body.main_color = LV_COLOR_ORANGE;
    
    // Create the label style
    static lv_style_t labelStyle;
    lv_style_copy(&labelStyle, &lv_style_plain);
    labelStyle.text.color = LV_COLOR_WHITE;

    // Create the released button style
    static lv_style_t buttonReleasedStyle;
    lv_style_copy(&buttonReleasedStyle, &lv_style_btn_rel);

    // Create the pressed button style
    static lv_style_t buttonPressedStyle;
    lv_style_copy(&buttonPressedStyle, &lv_style_btn_pr);

    // Create the button label style
    static lv_style_t buttonLabelStyle;
    lv_style_copy(&buttonLabelStyle, &lv_style_plain);
    buttonLabelStyle.text.color = LV_COLOR_WHITE;

    // Create the background
    lv_obj_set_style(lv_scr_act(), &backgroundStyle);

    // Create the apply button
    lv_obj_t* applyButton = lv_btn_create(lv_scr_act(), NULL);
    lv_btn_set_action(applyButton, LV_BTN_ACTION_CLICK, applyButtonEvent);
    lv_btn_set_style(applyButton, LV_BTN_STYLE_REL, &buttonReleasedStyle);
    lv_btn_set_style(applyButton, LV_BTN_STYLE_PR, &buttonPressedStyle);
    lv_obj_set_size(applyButton, 140, 60);
    lv_obj_align(applyButton, NULL, LV_ALIGN_IN_TOP_LEFT, 250, 160);

    // Create the apply button label
    lv_obj_t* applyButtonLabel = lv_label_create(applyButton, NULL);
    lv_label_set_text(applyButtonLabel, APPLY_BUTTON_TEXT);
    lv_label_set_style(applyButtonLabel, &buttonLabelStyle);

    // Create the cancel button
    lv_obj_t* cancelButton = lv_btn_create(lv_scr_act(), NULL);
    lv_btn_set_action(cancelButton, LV_BTN_ACTION_CLICK, cancelButtonEvent);
    lv_btn_set_style(cancelButton, LV_BTN_STYLE_REL, &buttonReleasedStyle);
    lv_btn_set_style(cancelButton, LV_BTN_STYLE_PR, &buttonPressedStyle);
    lv_obj_set_size(cancelButton, 140, 60);
    lv_obj_align(cancelButton, NULL, LV_ALIGN_IN_TOP_LEFT, 90, 160);

    // Create the cancel button label
    lv_obj_t* cancelButtonLabel = lv_label_create(cancelButton, NULL);
    lv_label_set_text(cancelButtonLabel, CANCEL_BUTTON_TEXT);
    lv_label_set_style(cancelButtonLabel, &buttonLabelStyle);

    // Create the previous button
    lv_obj_t* previousButton = lv_btn_create(lv_scr_act(), NULL);
    lv_btn_set_action(previousButton, LV_BTN_ACTION_CLICK, previousButtonEvent);
    lv_btn_set_style(previousButton, LV_BTN_STYLE_REL, &buttonReleasedStyle);
    lv_btn_set_style(previousButton, LV_BTN_STYLE_PR, &buttonPressedStyle);
    lv_obj_set_size(previousButton, 80, 80);
    lv_obj_align(previousButton, NULL, LV_ALIGN_IN_TOP_LEFT, 20, 60);

    // Create the left button label
    lv_obj_t* previousButtonLabel = lv_label_create(previousButton, NULL);
    lv_label_set_text(previousButtonLabel, PREVIOUS_BUTTON_TEXT);
    lv_label_set_style(previousButtonLabel, &buttonLabelStyle);

    // Create the right button
    lv_obj_t* nextButton = lv_btn_create(lv_scr_act(), NULL);
    lv_btn_set_action(nextButton, LV_BTN_ACTION_CLICK, nextButtonEvent);
    lv_btn_set_style(nextButton, LV_BTN_STYLE_REL, &buttonReleasedStyle);
    lv_btn_set_style(nextButton, LV_BTN_STYLE_PR, &buttonPressedStyle);
    lv_obj_set_size(nextButton, 80, 80);
    lv_obj_align(nextButton, NULL, LV_ALIGN_IN_TOP_LEFT, 380, 60);

    // Create the profile button label
    lv_obj_t* nextButtonLabel = lv_label_create(nextButton, NULL);
    lv_label_set_text(nextButtonLabel, NEXT_BUTTON_TEXT);
    lv_label_set_style(nextButtonLabel, &buttonLabelStyle);

    // Create the configuration label
    lv_obj_t* profileLabel = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(profileLabel, Menu::profileStr[profileIndex]);
    lv_label_set_style(profileLabel, &labelStyle);
    lv_obj_align(profileLabel, NULL, LV_ALIGN_CENTER, 0, -20);
}

void MenuScreen::setMenuData()
{
    MenuData::setAuton(static_cast<Menu::Autons>(autonIndex));
    MenuData::setConfiguration(static_cast<Menu::Configurations>(configIndex));
    MenuData::setProfile(static_cast<Menu::Profiles>(profileIndex));
}

void MenuScreen::getMenuData()
{
    autonIndex = static_cast<int>(MenuData::getAuton());
    configIndex = static_cast<int>(MenuData::getConfiguration());
    profileIndex = static_cast<int>(MenuData::getProfile());
}

void MenuScreen::incrementIndex()
{
    switch(menu)
    {
        case Menu::Menus::MAIN:
            break;
        case Menu::Menus::AUTON:
            autonIndex = (autonIndex + 1) % Menu::NUM_AUTONS;
            break;
        case Menu::Menus::CONFIG:
            configIndex = (configIndex + 1) % Menu::NUM_CONFIGURATIONS;
            break;
        case Menu::Menus::PROFILE:
            profileIndex = (profileIndex + 1) % Menu::NUM_PROFILES;
            break;
    }
}

void MenuScreen::decrementIndex()
{
    switch(menu)
    {
        case Menu::Menus::MAIN:
            break;
        case Menu::Menus::AUTON:
            if (autonIndex == 0)
                autonIndex = Menu::NUM_AUTONS;
            autonIndex--;
            break;
        case Menu::Menus::CONFIG:
            if (configIndex == 0)
                configIndex = Menu::NUM_CONFIGURATIONS;
            configIndex--;
            break;
        case Menu::Menus::PROFILE:
            if (profileIndex == 0)
                profileIndex = Menu::NUM_PROFILES;
            profileIndex--;
            break;
    }
}

void MenuScreen::refresh()
{
    lv_obj_clean(lv_scr_act());
    switch(menu)
    {
        case Menu::Menus::MAIN:
            drawMainMenu();
            break;
        case Menu::Menus::AUTON:
            drawAutonMenu();
            break;
        case Menu::Menus::CONFIG:
            drawConfigMenu();
            break;
        case Menu::Menus::PROFILE:
            drawProfileMenu();
            break;
    }
}