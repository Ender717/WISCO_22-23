// Included libraries
#include "subsystems/Claw.hpp"

// CLAW BUILDER

// Constructor definitions ----------------------------------------------------
Claw::ClawBuilder::ClawBuilder()
{
    motorList = nullptr;
    pistonList = nullptr;
    clawPID = nullptr;
    maxPosition = nullptr;
    minPosition = nullptr;
    openPosition = nullptr;
    closedPosition = nullptr;
}

// Destructor definitions -----------------------------------------------------
Claw::ClawBuilder::~ClawBuilder()
{
    if (motorList != nullptr)
    {
        delete motorList;
        motorList = nullptr;
    }
    if (pistonList != nullptr)
    {
        delete pistonList;
        pistonList = nullptr;
    }
    clawPID = nullptr;
    if (maxPosition != nullptr)
    {
        delete maxPosition;
        maxPosition = nullptr;
    }
    if (minPosition != nullptr)
    {
        delete minPosition;
        minPosition = nullptr;
    }
    if (openPosition != nullptr)
    {
        delete openPosition;
        openPosition = nullptr;
    }
    if (closedPosition != nullptr)
    {
        delete closedPosition;
        closedPosition = nullptr;
    }
}

// Public method definitions --------------------------------------------------
Claw::ClawBuilder* Claw::ClawBuilder::WithMotor(pros::Motor* motor)
{
    if (motorList == nullptr)
        motorList = new std::list<pros::Motor*>();
    motorList->push_back(motor);
    return this;
}

Claw::ClawBuilder* Claw::ClawBuilder::WithPiston(pros::ADIDigitalOut* piston)
{
    if (pistonList == nullptr)
        pistonList = new std::list<pros::ADIDigitalOut*>();
    pistonList->push_back(piston);
    return this;
}

Claw::ClawBuilder* Claw::ClawBuilder::WithPID(PID* pid)
{
    clawPID = pid;
    return this;
}

Claw::ClawBuilder* Claw::ClawBuilder::WithMinPosition(double minPosition)
{
    if (this->minPosition == nullptr)
        this->minPosition = new double;
    *this->minPosition = minPosition;
    return this;
}

Claw::ClawBuilder* Claw::ClawBuilder::WithMaxPosition(double maxPosition)
{
    if (this->maxPosition == nullptr)
        this->maxPosition = new double;
    *this->maxPosition = maxPosition;
    return this;
}

Claw::ClawBuilder* Claw::ClawBuilder::WithOpenPosition(double openPosition)
{
    if (this->openPosition == nullptr)
        this->openPosition = new double;
    *this->openPosition = openPosition;
    return this;
}

Claw::ClawBuilder* Claw::ClawBuilder::WithClosedPosition(double closedPosition)
{
    if (this->closedPosition == nullptr)
        this->closedPosition = new double;
    *this->closedPosition = closedPosition;
    return this;
}

Claw* Claw::ClawBuilder::Build()
{
    return new Claw(this);
}

// CLAW

// Constructor definitions ----------------------------------------------------
Claw::Claw(ClawBuilder* builder)
{
    // Create the pointers
    motorList = new std::list<pros::Motor*>();
    pistonList = new std::list<pros::ADIDigitalOut*>();
    minPosition = new double;
    maxPosition = new double;
    openPosition = new double;
    closedPosition = new double;
    isOpen = new bool;

    // Set the motors
    if (builder->motorList != nullptr)
        for (std::list<pros::Motor*>::iterator iterator = builder->motorList->begin(); 
            iterator != builder->motorList->end(); iterator++)
            this->motorList->push_back(*iterator);
    
    // Set the pistons
    if (builder->pistonList != nullptr)
        for (std::list<pros::ADIDigitalOut*>::iterator iterator = builder->pistonList->begin(); 
            iterator != builder->pistonList->end(); iterator++)
            this->pistonList->push_back(*iterator);

    // Set the direct transfer variables
    this->clawPID = builder->clawPID;

    if (builder->minPosition != nullptr)
        *this->minPosition = *builder->minPosition;
    else
        *this->minPosition = -DBL_MAX;

    if (builder->maxPosition != nullptr)
        *this->maxPosition = *builder->maxPosition;
    else
        *this->maxPosition = DBL_MAX;

    if (builder->openPosition != nullptr)
        *this->openPosition = *builder->openPosition;
    else
        *this->openPosition = DBL_MAX;

    if (builder->closedPosition != nullptr)
        *this->closedPosition = *builder->closedPosition;
    else
        *this->closedPosition = -DBL_MAX;

    // Set non-builder defaults
    *isOpen = false;
}

// Destructor definitions -----------------------------------------------------
Claw::~Claw()
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
    if (pistonList != nullptr)
    {
        for (std::list<pros::ADIDigitalOut*>::iterator iterator = pistonList->begin(); 
            iterator != pistonList->end(); iterator++)
        {
            delete *iterator;
            *iterator = nullptr;
        }
        delete pistonList;
        pistonList = nullptr;
    }
    if (clawPID != nullptr)
    {
        delete clawPID;
        clawPID = nullptr;
    }
    if (minPosition != nullptr)
    {
        delete minPosition;
        minPosition = nullptr;
    }
    if (maxPosition != nullptr)
    {
        delete maxPosition;
        maxPosition = nullptr;
    }
    if (openPosition != nullptr)
    {
        delete openPosition;
        openPosition = nullptr;
    }
    if (closedPosition != nullptr)
    {
        delete closedPosition;
        closedPosition = nullptr;
    }
    if (isOpen != nullptr)
    {
        delete isOpen;
        isOpen = nullptr;
    }
}

// Public method definitions --------------------------------------------------
void Claw::Initialize()
{
    // Set the positions to 0
    for (std::list<pros::Motor*>::iterator iterator = motorList->begin(); 
        iterator != motorList->end(); iterator++)
    {
        (*iterator)->tare_position();
        (*iterator)->set_brake_mode(E_MOTOR_BRAKE_BRAKE);
    }
    if (clawPID != nullptr)
        clawPID->SetTargetValue(0.0);
}

void Claw::SetClaw(double power)
{
    for (std::list<pros::Motor*>::iterator iterator = motorList->begin(); 
         iterator != motorList->end(); iterator++)
        (*iterator)->move(power);
}

void Claw::Open()
{
    if(!IsOpened())
        SetClaw(127.0);
    else
        SetClaw(0.0);

    if (clawPID != nullptr)
        clawPID->SetTargetValue(GetPosition());
}

void Claw::Close()
{
    if(!IsClosed())
        SetClaw(-127.0);
    else
        SetClaw(0.0);

    if (clawPID != nullptr)
        clawPID->SetTargetValue(GetPosition());
}

void Claw::HoldPosition()
{
    if(!IsOpened() && !IsClosed())
    {
        if (clawPID != nullptr)
            SetClaw(clawPID->GetControlValue(GetPosition()));
    }
    else
        SetClaw(0.0);
}

double Claw::GetPosition()
{
    if (!motorList->empty())
        return motorList->front()->get_position();
    else
        return 0.0;
}

void Claw::SetOpen()
{
    if (clawPID != nullptr)
        clawPID->SetTargetValue(*openPosition);
    for (std::list<pros::ADIDigitalOut*>::iterator iterator = pistonList->begin(); 
        iterator != pistonList->end(); iterator++)
        (*iterator)->set_value(true);
    *isOpen = true;
}

void Claw::SetClosed()
{
    if (clawPID != nullptr)
        clawPID->SetTargetValue(*closedPosition);
    for (std::list<pros::ADIDigitalOut*>::iterator iterator = pistonList->begin(); 
        iterator != pistonList->end(); iterator++)
        (*iterator)->set_value(false);
    *isOpen = false;
}

void Claw::TogglePosition()
{
    if (*isOpen)
        SetClosed();
    else
        SetOpen();
}

bool Claw::IsOpened()
{
    return GetPosition() >= *minPosition;
}

bool Claw::IsClosed()
{
    return GetPosition() <= *maxPosition;
}