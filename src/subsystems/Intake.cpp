// Included libraries
#include "subsystems/Intake.hpp"

// Constructor definitions ----------------------------------------------------
Intake::IntakeBuilder::IntakeBuilder()
{
    motorList = nullptr;
    intakePID = nullptr;
}

// Destructor definitions -----------------------------------------------------
Intake::IntakeBuilder::~IntakeBuilder()
{
    if (motorList != nullptr)
    {
        delete motorList;
        motorList = nullptr;
    }
    intakePID = nullptr;
}

// Public method definitions --------------------------------------------------
Intake::IntakeBuilder* Intake::IntakeBuilder::WithMotor(pros::Motor* motor)
{
    if (motorList == nullptr)
        motorList = new std::list<pros::Motor*>();
    motorList->push_back(motor);
    return this;
}

Intake::IntakeBuilder* Intake::IntakeBuilder::WithPID(PID* pid)
{
    intakePID = pid;
    return this;
}

Intake* Intake::IntakeBuilder::Build()
{
    return new Intake(this);
}

// Constructor definitions ----------------------------------------------------
Intake::Intake(IntakeBuilder* builder)
{
    // Create the pointers
    motorList = new std::list<pros::Motor*>();
    intakeSpeed = new double;

    // Set the motors
    if (builder->motorList != nullptr)
        for (std::list<pros::Motor*>::iterator iterator = builder->motorList->begin(); 
            iterator != builder->motorList->end(); iterator++)
            this->motorList->push_back(*iterator);

    // Set the PID controller
    this->intakePID = builder->intakePID;

    // Set the intake speed
    *intakeSpeed = 127.0;
}

// Destructor definitions -----------------------------------------------------
Intake::~Intake()
{
    if (motorList != nullptr)
    {
        for (std::list<pros::Motor*>::iterator iterator = motorList->begin(); 
            iterator != motorList->end(); iterator++)
        {
            delete *iterator;
            *iterator = nullptr;
        }
        delete motorList;
        motorList = nullptr;
    }
    if (intakePID != nullptr)
    {
        delete intakePID;
        intakePID = nullptr;
    }
    if (intakeSpeed != nullptr)
    {
        delete intakeSpeed;
        intakeSpeed = nullptr;
    }
}

// Public method definitions --------------------------------------------------
void Intake::Initialize()
{
    for (std::list<pros::Motor*>::iterator iterator = motorList->begin(); 
        iterator != motorList->end(); iterator++)
    {
        (*iterator)->tare_position();
        (*iterator)->set_brake_mode(E_MOTOR_BRAKE_BRAKE);
    }
}

void Intake::SetSpeed(double speed)
{
    *intakeSpeed = speed;
}

void Intake::Suck()
{
    for (std::list<pros::Motor*>::iterator iterator = motorList->begin(); 
        iterator != motorList->end(); iterator++)
        (*iterator)->move(*intakeSpeed);
}

void Intake::Blow()
{
    for (std::list<pros::Motor*>::iterator iterator = motorList->begin(); 
        iterator != motorList->end(); iterator++)
        (*iterator)->move(-*intakeSpeed);
}

void Intake::Stop()
{
    for (std::list<pros::Motor*>::iterator iterator = motorList->begin(); 
        iterator != motorList->end(); iterator++)
        (*iterator)->move(0.0);
}