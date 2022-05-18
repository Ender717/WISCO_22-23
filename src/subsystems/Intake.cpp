// Included libraries
#include "subsystems/Intake.hpp"

// Constructor definitions ----------------------------------------------------
Intake::IntakeBuilder::IntakeBuilder()
{
    motorList = nullptr;
    intakePID = nullptr;
    speed = nullptr;
}

// Destructor definitions -----------------------------------------------------
Intake::IntakeBuilder::~IntakeBuilder()
{
    if (motorList != nullptr)
    {
        delete motorList;
        motorList = nullptr;
    }
    if (intakePID != nullptr)
    {
        delete intakePID;
        intakePID = nullptr;
    }
    if (speed != nullptr)
    {
        delete speed;
        speed = nullptr;
    }
}

// Public method definitions --------------------------------------------------
Intake::IntakeBuilder* Intake::IntakeBuilder::withMotor(pros::Motor* motor)
{
    if (motorList == nullptr)
        motorList = new std::list<pros::Motor*>();
    motorList->push_back(motor);
    return this;
}

Intake::IntakeBuilder* Intake::IntakeBuilder::withPID(PID* pid)
{
    intakePID = pid;
    return this;
}

Intake::IntakeBuilder* Intake::IntakeBuilder::withSpeed(double speed)
{
    *this->speed = speed;
    return this;
}

Intake* Intake::IntakeBuilder::build()
{
    return new Intake(this);
}

// Constructor definitions ----------------------------------------------------
Intake::Intake(IntakeBuilder* builder)
{
    // Set the motors
    if (builder->motorList != nullptr)
        for (std::list<pros::Motor*>::iterator iterator = builder->motorList->begin(); 
            iterator != builder->motorList->end(); iterator++)
            this->motorList.push_back(*iterator);

    // Set the PID controller
    if (builder->intakePID != nullptr)
        this->intakePID = new PID(*builder->intakePID);

    // Set the intake speed
    if (builder->speed != nullptr)
        this->speed = *builder->speed;
    else
        this->speed = DEFAULT_SPEED;
}

// Destructor definitions -----------------------------------------------------
Intake::~Intake()
{

    for (std::list<pros::Motor*>::iterator iterator = motorList.begin(); 
        iterator != motorList.end(); iterator++)
    {
        delete *iterator;
        *iterator = nullptr;
    }
    if (intakePID != nullptr)
    {
        delete intakePID;
        intakePID = nullptr;
    }
}

// Public method definitions --------------------------------------------------
void Intake::initialize()
{
    for (std::list<pros::Motor*>::iterator iterator = motorList.begin(); 
        iterator != motorList.end(); iterator++)
    {
        (*iterator)->tare_position();
        (*iterator)->set_brake_mode(E_MOTOR_BRAKE_BRAKE);
    }

    if (intakePID != nullptr)
        intakePID->setTargetValue(0.0);
}

void Intake::setIntake(double power)
{
    for (std::list<pros::Motor*>::iterator iterator = motorList.begin(); 
        iterator != motorList.end(); iterator++)
        (*iterator)->move(power);
}

void Intake::setSpeed(double speed)
{
    this->speed = speed;
}

void Intake::suck()
{
    for (std::list<pros::Motor*>::iterator iterator = motorList.begin(); 
        iterator != motorList.end(); iterator++)
        (*iterator)->move(speed);
}

void Intake::blow()
{
    for (std::list<pros::Motor*>::iterator iterator = motorList.begin(); 
        iterator != motorList.end(); iterator++)
        (*iterator)->move(-speed);
}

void Intake::stop()
{
    for (std::list<pros::Motor*>::iterator iterator = motorList.begin(); 
        iterator != motorList.end(); iterator++)
        (*iterator)->move(0.0);
}