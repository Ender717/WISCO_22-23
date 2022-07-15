// Inclusion guard
#ifndef AUTON_MENU_HPP
#define AUTON_MENU_HPP

// Included libraries
#include "./main.h"

// Function prototypes
static lv_res_t applyButtonEvent(lv_obj_t* button);
static lv_res_t cancelButtonEvent(lv_obj_t* button);
static lv_res_t leftButtonEvent(lv_obj_t* button);
static lv_res_t rightButtonEvent(lv_obj_t* button);

/**
 * This class manages the auton menu system
 */
class AutonMenu
{
private:
    /**
     * The text being displayed on the apply button
     */
    static const std::string APPLY_BUTTON_TEXT;

    /**
     * The text being displayed on the cancel button
     */
    static const std::string CANCEL_BUTTON_TEXT;

    /**
     * The container holding this menu
     */
    lv_obj_t* container;

    /**
     * The apply button in the menu
     */
    lv_obj_t* applyButton;

    /**
     * The label for the apply button in the menu
     */
    lv_obj_t* applyButtonLabel;

    /**
     * The cancel button in the menu
     */
    lv_obj_t* cancelButton;

    /**
     * The label for the cancel button in the menu
     */
    lv_obj_t* cancelButtonLabel;

    /**
     * The left button in the menu
     */
    lv_obj_t* leftButton;

    /**
     * The label for the left button in the menu
     */
    lv_obj_t* leftButtonLabel;

    /**
     * The right button in the menu
     */
    lv_obj_t* rightButton;

    /**
     * The label for the right button in the menu
     */
    lv_obj_t* rightButtonLabel;

    /**
     * The label for the current auton
     */
    lv_obj_t* autonLabel;

    /**
     * Creates the background
     */
    void createBackground();

    /**
     * Creates the apply button
     */
    void createApplyButton();

    /**
     * Creates the cancel settings button
     */
    void createCancelButton();

    /**
     * Creates the left settings button
     */
    void createLeftButton();

    /**
     * Creates the right settings button
     */
    void createRightButton();

    /**
     * Creates the current auton label
     */
    void createAutonLabel();

public:
    /**
     * Constructor for AutonMenu
     * @param container The container holding this menu
     */
    AutonMenu(lv_obj_t* container);
};

#endif