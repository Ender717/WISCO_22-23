// Defined header
#include "menu/MainMenu.hpp"
#include "display/lv_core/lv_obj.h"
#include "display/lv_objx/lv_btnm.h"
#include "pros/screen.h"

// Function declarations ------------------------------------------------------
static lv_res_t startButtonEvent(lv_obj_t* button)
{
    pros::screen::print(pros::E_TEXT_LARGE, 30, 80, "Button was pressed");

    return LV_RES_OK;
}

// Constant definitions -------------------------------------------------------
const std::string MainMenu::START_BUTTON_TEXT = "START";

// Constructor definitions ----------------------------------------------------
MainMenu::MainMenu()
{
    startButton = lv_btn_create(lv_scr_act(), NULL);
    lv_btn_set_action(startButton, LV_BTN_ACTION_CLICK, startButtonEvent);

    startButtonLabel = lv_label_create(startButton, NULL);
    lv_label_set_text(startButtonLabel, &(START_BUTTON_TEXT[0]));
}