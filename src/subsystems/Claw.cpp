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
    if (clawPID != nullptr)
    {
        delete clawPID;
        clawPID = nullptr;
    }
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
Claw::ClawBuilder* Claw::ClawBuilder::withMotor(pros::Motor* motor)
{
    if (motorList == nullptr)
        motorList = new std::list<pros::Motor*>();
    motorList->push_back(motor);
    return this;
}

Claw::ClawBuilder* Claw::ClawBuilder::withPiston(pros::ADIDigitalOut* piston)
{
    if (pistonList == nullptr)
        pistonList = new std::list<pros::ADIDigitalOut*>();
    pistonList->push_back(piston);
    return this;
}

Claw::ClawBuilder* Claw::ClawBuilder::withPID(PID* pid)
{
    clawPID = pid;
    return this;
}

Claw::ClawBuilder* Claw::ClawBuilder::withMinPosition(double minPosition)
{
    if (this->minPosition == nullptr)
        this->minPosition = new double;
    *this->minPosition = minPosition;
    return this;
}

Claw::ClawBuilder* Claw::ClawBuilder::withMaxPosition(double maxPosition)
{
    if (this->maxPosition == nullptr)
        this->maxPosition = new double;
    *this->maxPosition = maxPosition;
    return this;
}

Claw::ClawBuilder* Claw::ClawBuilder::withOpenPosition(double openPosition)
{
    if (this->openPosition == nullptr)
        this->openPosition = new double;
    *this->openPosition = openPosition;
    return this;
}

Claw::ClawBuilder* Claw::ClawBuilder::withClosedPosition(double closedPosition)
{
    if (this->closedPosition == nullptr)
        this->closedPosition = new double;
    *this->closedPosition = closedPosition;
    return this;
}

Claw* Claw::ClawBuilder::build()
{
    return new Claw(this);
}

// CLAW

// Constructor definitions ----------------------------------------------------
Claw::Claw(ClawBuilder* builder)
{
    // Set the motors
    if (builder->motorList != nullptr)
        for (std::list<pros::Motor*>::iterator iterator = builder->motorList->begin(); 
            iterator != builder->motorList->end(); iterator++)
            this->motorList.push_back(*iterator);
    
    // Set the pistons
    if (builder->pistonList != nullptr)
        for (std::list<pros::ADIDigitalOut*>::iterator iterator = builder->pistonList->begin(); 
            iterator != builder->pistonList->end(); iterator++)
            this->pistonList.push_back(*iterator);

    // Set the direct transfer variables
    if (builder->clawPID != nullptr)
        this->clawPID = new PID(*builder->clawPID);

    if (builder->minPosition != nullptr)
        this->minPosition = *builder->minPosition;
    else
        this->minPosition = -DBL_MAX;

    if (builder->maxPosition != nullptr)
        this->maxPosition = *builder->maxPosition;
    else
        this->maxPosition = DBL_MAX;

    if (builder->openPosition != nullptr)
        this->openPosition = *builder->openPosition;
    else
        this->openPosition = DBL_MAX;

    if (builder->closedPosition != nullptr)
        this->closedPosition = *builder->closedPosition;
    else
        this->closedPosition = -DBL_MAX;

    // Set non-builder defaults
    isOpen = false;
}

// Destructor definitions -----------------------------------------------------
Claw::~Claw()
{
    for (std::list<pros::Motor*>::iterator iterator = motorList.begin(); 
        iterator != motorList.end(); iterator++)
    {
        delete *iterator;
        *iterator = nullptr;
    }
    for (std::list<pros::ADIDigitalOut*>::iterator iterator = pistonList.begin(); 
        iterator != pistonList.end(); iterator++)
    {
        delete *iterator;
        *iterator = nullptr;
    }
    if (clawPID != nullptr)
    {
        delete clawPID;
        clawPID = nullptr;
    }
}

// Public method definitions --------------------------------------------------
void Claw::initialize()
{
    // Set the positions to 0
    for (std::list<pros::Motor*>::iterator iterator = motorList.begin(); 
        iterator != motorList.end(); iterator++)
    {
        (*iterator)->tare_position();
        (*iterator)->set_brake_mode(E_MOTOR_BRAKE_BRAKE);
    }
    if (clawPID != nullptr)
        clawPID->setTargetValue(0.0);
}

void Claw::setClaw(double power)
{
    for (std::list<pros::Motor*>::iterator iterator = motorList.begin(); 
         iterator != motorList.end(); iterator++)
        (*iterator)->move(power);
}

void Claw::open()
{
    if(!isOpened())
        setClaw(127.0);
    else
        setClaw(0.0);

    if (clawPID != nullptr)
        clawPID->setTargetValue(getPosition());
}

void Claw::close()
{
    if(!isClosed())
        setClaw(-127.0);
    else
        setClaw(0.0);

    if (clawPID != nullptr)
        clawPID->setTargetValue(getPosition());
}

void Claw::holdPosition()
{
    if(!isOpened() && !isClosed())
    {
        if (clawPID != nullptr)
            setClaw(clawPID->getControlValue(getPosition()));
        else
            setClaw(0.0);
    }
    else
        setClaw(0.0);
}

double Claw::getPosition()
{
    double position = 0.0;
    if (!motorList.empty())
        position = motorList.front()->get_position();
    return position;
}

void Claw::setOpen()
{
    if (clawPID != nullptr)
        clawPID->setTargetValue(openPosition);
    for (std::list<pros::ADIDigitalOut*>::iterator iterator = pistonList.begin(); 
        iterator != pistonList.end(); iterator++)
        (*iterator)->set_value(true);
    isOpen = true;
}

void Claw::setClosed()
{
    if (clawPID != nullptr)
        clawPID->setTargetValue(closedPosition);
    for (std::list<pros::ADIDigitalOut*>::iterator iterator = pistonList.begin(); 
        iterator != pistonList.end(); iterator++)
        (*iterator)->set_value(false);
    isOpen = false;
}

void Claw::togglePosition()
{
    if (isOpen)
        setClosed();
    else
        setOpen();
}

bool Claw::isOpened()
{
    return getPosition() >= minPosition;
}

bool Claw::isClosed()
{
    return getPosition() <= maxPosition;
}