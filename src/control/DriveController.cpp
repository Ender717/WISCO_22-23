// Defined header
#include "control/DriveController.hpp"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "pros/screen.h"

// Constructor definitions ----------------------------------------------------
DriveController::DriveController(Robot* robot)
{
    this->robot = robot;
}

DriveController::~DriveController()
{
    robot = nullptr;
}

// Private method definitions -------------------------------------------------
void DriveController::updateHoloDrive(HoloDrive* holoDrive, pros::Controller master)
{
    // Create the control variables
    double leftFrontPower = 0.0;
    double leftRearPower = 0.0;
    double rightFrontPower = 0.0;
    double rightRearPower = 0.0;

    switch (MenuData::getProfile())
    {
        case Menu::Profiles::HENRY:
            leftFrontPower = (master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) +
                master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X) +
                master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
            leftRearPower = (master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) -
                master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X) +
                master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
            rightFrontPower = (master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) -
                master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X) -
                master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
            rightRearPower = (master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) +
                master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X) -
                master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
            break;
        case Menu::Profiles::JOHN:
            leftFrontPower = (master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) +
                master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X));
            leftRearPower = (master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) -
                master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X));
            rightFrontPower = (master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y) -
                master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
            rightRearPower = (master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y) +
                master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
            break;
        case Menu::Profiles::NATHAN:
            leftFrontPower = (master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) +
                master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X) +
                master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
            leftRearPower = (master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) -
                master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X) +
                master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
            rightFrontPower = (master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) -
                master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X) -
                master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
            rightRearPower = (master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) +
                master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X) -
                master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
            break;
    }

    holoDrive->setDrive(leftFrontPower, leftRearPower, rightFrontPower, rightRearPower);
}

// Public method definitions
void DriveController::update(pros::Controller master)
{
    HoloDrive* holoDrive = robot->getHoloDrive();

    if (holoDrive != nullptr)
        updateHoloDrive(holoDrive, master);
}