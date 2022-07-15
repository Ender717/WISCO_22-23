// Defined header
#include "menu/AutonMenu.hpp"
#include "Menu.hpp"

// Static defaults
static AutonMenu* autonMenu = nullptr;

// Function declarations ------------------------------------------------------
static lv_res_t applyButtonEvent(lv_obj_t* button)
{
    MenuData::setAuton(autonMenu->getSelectedAuton());
    lv_obj_del(autonMenu->getContainer());

    return LV_RES_OK;
}

static lv_res_t cancelButtonEvent(lv_obj_t *button)
{
    lv_obj_del(autonMenu->getContainer());

    return LV_RES_OK;
}

static lv_res_t leftButtonEvent(lv_obj_t *button)
{
    autonMenu->decrementAuton();

    return LV_RES_OK;
}

static lv_res_t rightButtonEvent(lv_obj_t *button)
{
    autonMenu->incrementAuton();

    return LV_RES_OK;
}

// Constant definitions -------------------------------------------------------
const std::string AutonMenu::APPLY_BUTTON_TEXT = "APPLY";
const std::string AutonMenu::CANCEL_BUTTON_TEXT = "CANCEL";

// Private method definitions -------------------------------------------------
void AutonMenu::createBackground()
{
    // Create the background style
    static lv_style_t backgroundStyle;
    lv_style_copy(&backgroundStyle, &lv_style_pretty);
    backgroundStyle.body.main_color = LV_COLOR_ORANGE;

    container = lv_cont_create(lv_scr_act(), NULL);
    lv_obj_set_style(container, &backgroundStyle);
    lv_obj_set_size(container, 480, 240);
    lv_obj_align(container, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);
}

void AutonMenu::createApplyButton()
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

    // Create the apply button
    applyButton = lv_btn_create(container, NULL);
    lv_btn_set_action(applyButton, LV_BTN_ACTION_CLICK, applyButtonEvent);
    lv_btn_set_style(applyButton, LV_BTN_STYLE_REL, &buttonReleasedStyle);
    lv_btn_set_style(applyButton, LV_BTN_STYLE_PR, &buttonPressedStyle);
    lv_obj_set_size(applyButton, 120, 60);
    lv_obj_align(applyButton, NULL, LV_ALIGN_IN_TOP_LEFT, 260, 160);

    // Create the start button label
    applyButtonLabel = lv_label_create(applyButton, NULL);
    lv_label_set_text(applyButtonLabel, &(APPLY_BUTTON_TEXT[0]));
    lv_label_set_style(applyButtonLabel, &buttonLabelStyle);
}

void AutonMenu::createCancelButton()
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

    // Create the cancel button
    cancelButton = lv_btn_create(container, NULL);
    lv_btn_set_action(cancelButton, LV_BTN_ACTION_CLICK, cancelButtonEvent);
    lv_btn_set_style(cancelButton, LV_BTN_STYLE_REL, &buttonReleasedStyle);
    lv_btn_set_style(cancelButton, LV_BTN_STYLE_PR, &buttonPressedStyle);
    lv_obj_set_size(cancelButton, 120, 60);
    lv_obj_align(cancelButton, NULL, LV_ALIGN_IN_TOP_LEFT, 100, 160);

    // Create the start button label
    cancelButtonLabel = lv_label_create(cancelButton, NULL);
    lv_label_set_text(cancelButtonLabel, &(CANCEL_BUTTON_TEXT[0]));
    lv_label_set_style(cancelButtonLabel, &buttonLabelStyle);
}

// Constructor definitions ----------------------------------------------------
AutonMenu::AutonMenu()
{
    container = nullptr;
    applyButton = nullptr;
    applyButtonLabel = nullptr;
    cancelButton = nullptr;
    cancelButtonLabel = nullptr;
    leftButton = nullptr;
    leftButtonLabel = nullptr;
    rightButton = nullptr;
    rightButtonLabel = nullptr;
    autonLabel = nullptr;
    currentAutonIndex = static_cast<int>(MenuData::getAuton());

    autonMenu = this;
}

// Destructor definitions -----------------------------------------------------
AutonMenu::~AutonMenu()
{
    if (container != nullptr)
    {
        delete container;
        container = nullptr;
    }

    if (applyButton != nullptr)
    {
        delete applyButton;
        applyButton = nullptr;
    }
    
    if (applyButtonLabel != nullptr)
    {
        delete applyButtonLabel;
        applyButtonLabel = nullptr;
    }

    if (cancelButton != nullptr)
    {
        delete cancelButton;
        cancelButton = nullptr;
    }

    if (cancelButtonLabel != nullptr)
    {
        delete cancelButtonLabel;
        cancelButtonLabel = nullptr;
    }
    
    if (leftButton != nullptr)
    {
        delete leftButton;
        leftButton = nullptr;
    }
    
    if (leftButtonLabel != nullptr)
    {
        delete leftButtonLabel;
        leftButtonLabel = nullptr;
    }
    
    if (rightButton != nullptr)
    {
        delete rightButton;
        rightButton = nullptr;
    }
    
    if (rightButtonLabel != nullptr)
    {
        delete rightButtonLabel;
        rightButtonLabel = nullptr;
    }
    
    if (autonLabel != nullptr)
    {
        delete autonLabel;
        autonLabel = nullptr;
    }

    autonMenu = nullptr;
}

// Public method definitions --------------------------------------------------
void AutonMenu::draw()
{
    createBackground();
    createApplyButton();
    createCancelButton();
}

void AutonMenu::incrementAuton()
{

}

void AutonMenu::decrementAuton()
{

}

Menu::Autons AutonMenu::getSelectedAuton()
{
    return static_cast<Menu::Autons>(currentAutonIndex);
}

lv_obj_t* AutonMenu::getContainer()
{
    return container;
}