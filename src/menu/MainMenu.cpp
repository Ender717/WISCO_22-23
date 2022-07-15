// Defined header
#include "menu/MainMenu.hpp"
#include "display/lv_core/lv_obj.h"
#include <string>

// Function declarations ------------------------------------------------------
static lv_res_t startButtonEvent(lv_obj_t* button)
{
    lv_obj_clean(lv_scr_act());
    initialize();

    return LV_RES_OK;
}

static lv_res_t autonButtonEvent(lv_obj_t* button)
{
    

    return LV_RES_OK;
}

static lv_res_t configButtonEvent(lv_obj_t *button)
{


    return LV_RES_OK;
}

static lv_res_t profileButtonEvent(lv_obj_t *button)
{


    return LV_RES_OK;
}

// Constant definitions -------------------------------------------------------
const std::string MainMenu::START_BUTTON_TEXT = "START";
const std::string MainMenu::AUTON_BUTTON_TEXT = "AUTON";
const std::string MainMenu::CONFIG_BUTTON_TEXT = "CONFIG";
const std::string MainMenu::PROFILE_BUTTON_TEXT = "PROFILE";

// Private method definitions
void MainMenu::createBackground()
{
    // Create the background style
    static lv_style_t backgroundStyle;
    lv_style_copy(&backgroundStyle, &lv_style_pretty);
    backgroundStyle.body.main_color = LV_COLOR_ORANGE;

    lv_obj_set_style(lv_scr_act(), &backgroundStyle);
}

void MainMenu::createStartButton()
{
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

    // Create the start button
    startButton = lv_btn_create(lv_scr_act(), NULL);
    lv_btn_set_action(startButton, LV_BTN_ACTION_CLICK, startButtonEvent);
    lv_btn_set_style(startButton, LV_BTN_STYLE_REL, &buttonReleasedStyle);
    lv_btn_set_style(startButton, LV_BTN_STYLE_PR, &buttonPressedStyle);
    lv_obj_set_size(startButton, 200, 100);
    lv_obj_align(startButton, NULL, LV_ALIGN_IN_TOP_LEFT, 20, 30);

    // Create the start button label
    startButtonLabel = lv_label_create(startButton, NULL);
    lv_label_set_text(startButtonLabel, &(START_BUTTON_TEXT[0]));
    lv_label_set_style(startButtonLabel, &buttonLabelStyle);
}

void MainMenu::createAutonButton()
{
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

    // Create the auton button
    autonButton = lv_btn_create(lv_scr_act(), NULL);
    lv_btn_set_action(autonButton, LV_BTN_ACTION_CLICK, autonButtonEvent);
    lv_btn_set_style(autonButton, LV_BTN_STYLE_REL, &buttonReleasedStyle);
    lv_btn_set_style(autonButton, LV_BTN_STYLE_PR, &buttonPressedStyle);
    lv_obj_set_size(autonButton, 120, 60);
    lv_obj_align(autonButton, NULL, LV_ALIGN_IN_TOP_LEFT, 20, 160);

    // Create the start button label
    autonButtonLabel = lv_label_create(autonButton, NULL);
    lv_label_set_text(autonButtonLabel, &(AUTON_BUTTON_TEXT[0]));
    lv_label_set_style(autonButtonLabel, &buttonLabelStyle);
}

void MainMenu::createConfigButton()
{
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

    // Create the config button
    configButton = lv_btn_create(lv_scr_act(), NULL);
    lv_btn_set_action(configButton, LV_BTN_ACTION_CLICK, configButtonEvent);
    lv_btn_set_style(configButton, LV_BTN_STYLE_REL, &buttonReleasedStyle);
    lv_btn_set_style(configButton, LV_BTN_STYLE_PR, &buttonPressedStyle);
    lv_obj_set_size(configButton, 120, 60);
    lv_obj_align(configButton, NULL, LV_ALIGN_IN_TOP_LEFT, 180, 160);

    // Create the start button label
    configButtonLabel = lv_label_create(configButton, NULL);
    lv_label_set_text(configButtonLabel, &(CONFIG_BUTTON_TEXT[0]));
    lv_label_set_style(configButtonLabel, &buttonLabelStyle);
}

void MainMenu::createProfileButton()
{
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

    // Create the profile button
    profileButton = lv_btn_create(lv_scr_act(), NULL);
    lv_btn_set_action(profileButton, LV_BTN_ACTION_CLICK, profileButtonEvent);
    lv_btn_set_style(profileButton, LV_BTN_STYLE_REL, &buttonReleasedStyle);
    lv_btn_set_style(profileButton, LV_BTN_STYLE_PR, &buttonPressedStyle);
    lv_obj_set_size(profileButton, 120, 60);
    lv_obj_align(profileButton, NULL, LV_ALIGN_IN_TOP_LEFT, 340, 160);

    // Create the start button label
    profileButtonLabel = lv_label_create(profileButton, NULL);
    lv_label_set_text(profileButtonLabel, &(PROFILE_BUTTON_TEXT[0]));
    lv_label_set_style(profileButtonLabel, &buttonLabelStyle);
}

void MainMenu::createSettingsLabel()
{
    static lv_style_t labelStyle;
    lv_style_copy(&labelStyle, &lv_style_plain);
    labelStyle.text.color = LV_COLOR_WHITE;

    std::string settings = "SETTINGS:\nAuton: " +
        Menu::autonStr[static_cast<int>(MenuData::getAuton())] + "\nConfig: " +
        Menu::configurationStr[static_cast<int>(MenuData::getConfiguration())] + "\nProfile: " +
        Menu::profileStr[static_cast<int>(MenuData::getProfile())];
    const char* settingsText = &settings[0];

    settingsLabel = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(settingsLabel, settingsText);
    lv_label_set_style(settingsLabel, &labelStyle);
    lv_obj_align(settingsLabel, NULL, LV_ALIGN_IN_TOP_RIGHT, -20, 40);
}

// Constructor definitions ----------------------------------------------------
MainMenu::MainMenu()
{
    createBackground();
    createStartButton();
    createAutonButton();
    createConfigButton();
    createProfileButton();
    createSettingsLabel();
}