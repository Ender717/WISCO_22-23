// Included libraries
#include "subsystems/HoloDrive.hpp"
#include "pros/screen.h"

// BUILDER CLASS --------------------------------------------------------------

// Constructor definitions ------------------------------------------------
HoloDrive::HoloDriveBuilder::HoloDriveBuilder()
{
    leftFrontMotorList = nullptr;
    leftRearMotorList = nullptr;
    rightFrontMotorList = nullptr;
    rightRearMotorList = nullptr;
}

// Destructor definitions -------------------------------------------------
HoloDrive::HoloDriveBuilder::~HoloDriveBuilder()
{
    if (leftFrontMotorList != nullptr)
    {
        delete leftFrontMotorList;
        leftFrontMotorList = nullptr;
    }

    if (leftRearMotorList != nullptr)
    {
        delete leftRearMotorList;
        leftRearMotorList = nullptr;
    }

    if (rightFrontMotorList != nullptr)
    {
        delete rightFrontMotorList;
        rightFrontMotorList = nullptr;
    }

    if (rightRearMotorList != nullptr)
    {
        delete rightRearMotorList;
        rightRearMotorList = nullptr;
    }
}

// Public method definitions ----------------------------------------------
HoloDrive::HoloDriveBuilder* HoloDrive::HoloDriveBuilder::withLeftFrontMotor(pros::Motor motor)
{
    if (leftFrontMotorList == nullptr)
        leftFrontMotorList = new std::list<pros::Motor*>();

    leftFrontMotorList->push_back(&motor);
    return this;
}

HoloDrive::HoloDriveBuilder* HoloDrive::HoloDriveBuilder::withLeftRearMotor(pros::Motor motor)
{
    if (leftRearMotorList == nullptr)
        leftRearMotorList = new std::list<pros::Motor*>();

    leftRearMotorList->push_back(&motor);
    return this;
}

HoloDrive::HoloDriveBuilder* HoloDrive::HoloDriveBuilder::withRightFrontMotor(pros::Motor motor)
{
    if (rightFrontMotorList == nullptr)
        rightFrontMotorList = new std::list<pros::Motor*>();
        
    rightFrontMotorList->push_back(&motor);
    return this;
}

HoloDrive::HoloDriveBuilder* HoloDrive::HoloDriveBuilder::withRightRearMotor(pros::Motor motor)
{
    if (rightRearMotorList == nullptr)
        rightRearMotorList = new std::list<pros::Motor*>();

    rightRearMotorList->push_back(&motor);
    return this;
}

HoloDrive* HoloDrive::HoloDriveBuilder::build()
{
    return new HoloDrive(this);
}

// MAIN CLASS -----------------------------------------------------------------

// Constructor definitions ------------------------------------------------
HoloDrive::HoloDrive(HoloDriveBuilder* builder)
{
    if (builder->leftFrontMotorList != nullptr)
        for (std::list<pros::Motor*>::iterator iterator = builder->leftFrontMotorList->begin(); 
            iterator != builder->leftFrontMotorList->end(); iterator++)
            this->leftFrontMotorList.push_back(*iterator);

    if (builder->leftRearMotorList != nullptr)
        for (std::list<pros::Motor*>::iterator iterator = builder->leftRearMotorList->begin(); 
            iterator != builder->leftRearMotorList->end(); iterator++)
            this->leftRearMotorList.push_back(*iterator);

    if (builder->rightFrontMotorList != nullptr)
        for (std::list<pros::Motor*>::iterator iterator = builder->rightFrontMotorList->begin(); 
            iterator != builder->rightFrontMotorList->end(); iterator++)
            this->rightFrontMotorList.push_back(*iterator);

    if (builder->rightRearMotorList != nullptr)
        for (std::list<pros::Motor*>::iterator iterator = builder->rightRearMotorList->begin(); 
            iterator != builder->rightRearMotorList->end(); iterator++)
            this->rightRearMotorList.push_back(*iterator);
}

// Destructor definitions -------------------------------------------------
HoloDrive::~HoloDrive()
{
    for (std::list<pros::Motor*>::iterator iterator = leftFrontMotorList.begin(); 
        iterator != leftFrontMotorList.end(); iterator++)
    {
        delete *iterator;
        *iterator = nullptr;
    }

    for (std::list<pros::Motor*>::iterator iterator = leftRearMotorList.begin(); 
        iterator != leftRearMotorList.end(); iterator++)
    {
        delete *iterator;
        *iterator = nullptr;
    }

    for (std::list<pros::Motor*>::iterator iterator = rightFrontMotorList.begin(); 
        iterator != rightFrontMotorList.end(); iterator++)
    {
        delete *iterator;
        *iterator = nullptr;
    }

    for (std::list<pros::Motor*>::iterator iterator = rightRearMotorList.begin(); 
        iterator != rightRearMotorList.end(); iterator++)
    {
        delete *iterator;
        *iterator = nullptr;
    }
}

// Public method definitions ----------------------------------------------
void HoloDrive::initialize()
{
    for (std::list<pros::Motor*>::iterator iterator = leftFrontMotorList.begin(); 
        iterator != leftFrontMotorList.end(); iterator++)
    {
        (*iterator)->tare_position();
        (*iterator)->set_brake_mode(E_MOTOR_BRAKE_BRAKE);
    }

    for (std::list<pros::Motor*>::iterator iterator = leftRearMotorList.begin(); 
        iterator != leftRearMotorList.end(); iterator++)
    {
        (*iterator)->tare_position();
        (*iterator)->set_brake_mode(E_MOTOR_BRAKE_BRAKE);
    }

    for (std::list<pros::Motor*>::iterator iterator = rightFrontMotorList.begin(); 
        iterator != rightFrontMotorList.end(); iterator++)
    {
        (*iterator)->tare_position();
        (*iterator)->set_brake_mode(E_MOTOR_BRAKE_BRAKE);
    }

    for (std::list<pros::Motor*>::iterator iterator = rightRearMotorList.begin(); 
        iterator != rightRearMotorList.end(); iterator++)
    {
        (*iterator)->tare_position();
        (*iterator)->set_brake_mode(E_MOTOR_BRAKE_BRAKE);
    }
}

void HoloDrive::setDrive(double leftFrontPower, double leftRearPower, 
    double rightFrontPower, double rightRearPower)
{
    for (std::list<pros::Motor*>::iterator iterator = leftFrontMotorList.begin(); 
        iterator != leftFrontMotorList.end(); iterator++)
        (*iterator)->move(leftFrontPower);
    
    for (std::list<pros::Motor*>::iterator iterator = leftRearMotorList.begin(); 
        iterator != leftRearMotorList.end(); iterator++)
        (*iterator)->move(leftRearPower);

    for (std::list<pros::Motor*>::iterator iterator = rightFrontMotorList.begin(); 
        iterator != rightFrontMotorList.end(); iterator++)
        (*iterator)->move(rightFrontPower);

    for (std::list<pros::Motor*>::iterator iterator = rightRearMotorList.begin(); 
        iterator != rightRearMotorList.end(); iterator++)
        (*iterator)->move(rightRearPower);
}

void HoloDrive::goToPosition(double x, double y, double theta)
{

}

void HoloDrive::turnToAngle(double targetAngle)
{
    
}