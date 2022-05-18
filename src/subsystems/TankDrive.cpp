// Included libraries
#include "subsystems/TankDrive.hpp"

// Constructor definitions ----------------------------------------------------
TankDrive::TankDriveBuilder::TankDriveBuilder()
{
    leftMotorList = nullptr;
    rightMotorList = nullptr;
    distancePID = nullptr;
    anglePID = nullptr;
    turnPID = nullptr;
}

// Destructor definitions -----------------------------------------------------
TankDrive::TankDriveBuilder::~TankDriveBuilder()
{
    if (leftMotorList != nullptr)
    {
        delete leftMotorList;
        leftMotorList = nullptr;
    }
    if (rightMotorList != nullptr)
    {
        delete rightMotorList;
        rightMotorList = nullptr;
    }
    if (distancePID != nullptr)
    {
        delete distancePID;
        distancePID = nullptr;
    }
    if (anglePID != nullptr)
    {
        delete anglePID;
        anglePID = nullptr;
    }
    if (turnPID != nullptr)
    {
        delete turnPID;
        turnPID = nullptr;
    }
}

// Public method definitions --------------------------------------------------
TankDrive::TankDriveBuilder* TankDrive::TankDriveBuilder::withLeftMotor(pros::Motor* motor)
{
    if (leftMotorList == nullptr)
        leftMotorList = new std::list<pros::Motor*>();
    leftMotorList->push_back(motor);
    return this;
}

TankDrive::TankDriveBuilder* TankDrive::TankDriveBuilder::withRightMotor(pros::Motor* motor)
{
    if (rightMotorList == nullptr)
        rightMotorList = new std::list<pros::Motor*>();
    rightMotorList->push_back(motor);
    return this;
}

TankDrive::TankDriveBuilder* TankDrive::TankDriveBuilder::withDistancePID(PID* pid)
{
    distancePID = pid;
    return this;
}

TankDrive::TankDriveBuilder* TankDrive::TankDriveBuilder::withAnglePID(PID* pid)
{
    anglePID = pid;
    return this;
}

TankDrive::TankDriveBuilder* TankDrive::TankDriveBuilder::withTurnPID(PID* pid)
{
    turnPID = pid;
    return this;
}

TankDrive* TankDrive::TankDriveBuilder::build()
{
    return new TankDrive(this);
}

// Constructor definitions ----------------------------------------------------
TankDrive::TankDrive(TankDriveBuilder* builder)
{
    // Set the left motors
    if (builder->leftMotorList != nullptr)
        for (std::list<pros::Motor*>::iterator iterator = builder->leftMotorList->begin(); 
            iterator != builder->leftMotorList->end(); iterator++)
            this->leftMotorList.push_back(*iterator);

    // Set the right motors
    if (builder->rightMotorList != nullptr)
        for (std::list<pros::Motor*>::iterator iterator = builder->rightMotorList->begin(); 
            iterator != builder->rightMotorList->end(); iterator++)
            this->rightMotorList.push_back(*iterator);

    // Set the PID controllers
    if (builder->distancePID != nullptr)
        this->distancePID = new PID(*builder->distancePID);
    if (builder->anglePID != nullptr)
        this->anglePID = new PID(*builder->anglePID);
    if (builder->turnPID != nullptr)
        this->turnPID = new PID(*builder->turnPID);
}

// Destructor definitions -------------------------------------------------
TankDrive::~TankDrive()
{
    for (std::list<pros::Motor*>::iterator iterator = leftMotorList.begin(); 
        iterator != leftMotorList.end(); iterator++)
    {
        delete *iterator;
        *iterator = nullptr;
    }
    for (std::list<pros::Motor*>::iterator iterator = rightMotorList.begin(); 
        iterator != rightMotorList.end(); iterator++)
    {
        delete *iterator;
        *iterator = nullptr;
    }
    if (distancePID != nullptr)
    {
        delete distancePID;
        distancePID = nullptr;
    }
    if (anglePID != nullptr)
    {
        delete anglePID;
        anglePID = nullptr;
    }
    if (turnPID != nullptr)
    {
        delete turnPID;
        turnPID = nullptr;
    }
}

// Public method definitions ----------------------------------------------
void TankDrive::initialize()
{
    // Initialize the motors
    for (std::list<pros::Motor*>::iterator iterator = leftMotorList.begin(); 
        iterator != leftMotorList.end(); iterator++)
    {
        (*iterator)->tare_position();
        (*iterator)->set_brake_mode(E_MOTOR_BRAKE_BRAKE);
    }
    for (std::list<pros::Motor*>::iterator iterator = rightMotorList.begin(); 
        iterator != rightMotorList.end(); iterator++)
    {
        (*iterator)->tare_position();
        (*iterator)->set_brake_mode(E_MOTOR_BRAKE_BRAKE);
    }
}

void TankDrive::setDrive(double leftPower, double rightPower)
{
    // Move the left side of the drive
    for (std::list<pros::Motor*>::iterator iterator = leftMotorList.begin(); 
        iterator != leftMotorList.end(); iterator++)
        (*iterator)->move(leftPower);

    // Move the right side of the drive
    for (std::list<pros::Motor*>::iterator iterator = rightMotorList.begin(); 
        iterator != rightMotorList.end(); iterator++)
        (*iterator)->move(rightPower);
}

void TankDrive::goToPosition(double x, double y, double theta)
{

}

void TankDrive::turnToAngle(double targetAngle)
{
    
}