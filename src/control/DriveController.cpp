// Defined header
#include "control/DriveController.hpp"
#include "pros/misc.h"
#include "pros/rtos.hpp"

// Function declarations
void positionUpdateFunction(void *parameters)
{
    PositionSystem* positionSystem = (PositionSystem*)parameters;
    while (true)
    {
        positionSystem->updatePosition();
        pros::Task::delay(50);
    }
}

void positionPrintFunction(void *parameters)
{
    PositionSystem* positionSystem = (PositionSystem*)parameters;
    while (true)
    {
        Position* position = positionSystem->getPosition();
        pros::screen::print(pros::E_TEXT_LARGE, 20, 10, "X: %.2f", position->getX());
        pros::screen::print(pros::E_TEXT_LARGE, 20, 50, "Y: %.2f", position->getY());
        pros::screen::print(pros::E_TEXT_LARGE, 20, 90, "Theta: %.2f", position->getTheta() * 180.0 / 3.1415);
        delete position;
        position = nullptr;
        pros::Task::delay(50);
    }
}

void flywheelUpdateFunction(void* parameters)
{
    Flywheel* flywheel = (Flywheel*)parameters;
    while (true)
    {
        flywheel->update();
        pros::Task::delay(50);
    }
}

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
void DriveController::updateTankDrive(TankDrive* tankDrive, pros::Controller master)
{
    // Create the control variables
    double leftPower = 0.0;
    double rightPower = 0.0;

    switch (MenuData::getProfile())
    {
        case Menu::Profiles::HENRY:
            leftPower = (-master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) +
                master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
            rightPower = (-master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) -
                master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
            break;
        case Menu::Profiles::JOHN:
            leftPower = -master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
            rightPower = -master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
            break;
        case Menu::Profiles::NATHAN:
            leftPower = (-master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) +
                master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
            rightPower = (-master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) -
                master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
            break;
    }

    tankDrive->setDrive(leftPower, rightPower);
}

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

void DriveController::updateCatapult(Catapult* catapult, pros::Controller master)
{
    // Update the catapult loading
    switch (MenuData::getProfile())
    {
        case Menu::Profiles::HENRY:
            if (catapult->isLoaded() && master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1))
                catapult->load();
            break;
        case Menu::Profiles::JOHN:
            if (catapult->isLoaded() && master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1))
                catapult->load();
            break;
        case Menu::Profiles::NATHAN:
            if (catapult->isLoaded() && master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1))
                catapult->load();
            break;
    }

    // Hold the target position
    //catapult->holdPosition();

    // Pull back until loaded
    if (!catapult->isLoaded())
        catapult->setCatapult(127.0);
    else
        catapult->setCatapult(0.0);
}

void DriveController::updateFlywheel(Flywheel* flywheel, pros::Controller master)
{
    double adjust = 0.0;

    // Update the flywheel RPM
    switch (MenuData::getProfile())
    {
        case Menu::Profiles::HENRY:
            adjust = (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1) - master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) * 20;
            break;
        case Menu::Profiles::JOHN:
            adjust = (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1) - master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) * 20;
            break;
        case Menu::Profiles::NATHAN:
            adjust = (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1) - master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) * 20;
            break;
    }

    double targetRPM = flywheel->getTargetRPM();
    flywheel->setRPM(targetRPM + adjust);
    pros::screen::print(pros::E_TEXT_LARGE, 20, 130, "Current RPM: %.2f", flywheel->getRPM());
    pros::screen::print(pros::E_TEXT_LARGE, 20, 170, "Target RPM: %.2f", flywheel->getTargetRPM());
}

// Public method definitions

void DriveController::initialize()
{
    // Initialize the position system
    PositionSystem* positionSystem = robot->getPositionSystem();
    if (positionSystem != nullptr)
    {
        void* parameters = (void*)positionSystem;
        pros::Task positionUpdateTask(positionUpdateFunction, parameters, "positionUpdateTask");
        parameters = (void*)positionSystem;
        pros::Task positionPrintTask(positionPrintFunction, parameters, "positionPrintTask");
    }

    // Initialize the flywheel
    Flywheel* flywheel = robot->getFlywheel();
    if (flywheel != nullptr)
    {
        void* parameters = (void*)flywheel;
        pros::Task flywheelUpdateTask(flywheelUpdateFunction, parameters, "flywheelUpdateTask");
    }
}

void DriveController::update(pros::Controller master)
{
    // Update the tank drive
    TankDrive* tankDrive = robot->getTankDrive();
    if (tankDrive != nullptr)
        updateTankDrive(tankDrive, master);

    // Update the holonomic drive
    HoloDrive* holoDrive = robot->getHoloDrive();
    if (holoDrive != nullptr)
        updateHoloDrive(holoDrive, master);

    // Update the catapult
    Catapult* catapult = robot->getCatapult();
    if (catapult != nullptr)
        updateCatapult(catapult, master);
    
    // Update the flywheel
    Flywheel* flywheel = robot->getFlywheel();
    if (flywheel != nullptr)
        updateFlywheel(flywheel, master);
}