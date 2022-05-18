// Included libraries
#include "subsystems/Carrier.hpp"

// CARRIER BUILDER

// Constructor definitions ----------------------------------------------------
Carrier::CarrierBuilder::CarrierBuilder()
{
    motorList = nullptr;
    pistonList = nullptr;
    carrierPID = nullptr;
    startAngle = nullptr;
    minAngle = nullptr;
    maxAngle = nullptr;
    startHeight = nullptr;
    minHeight = nullptr;
    maxHeight = nullptr;
    countsPerDegree = nullptr;
    countsPerInch = nullptr;
    armLength = nullptr;
    downPosition = nullptr;
    upPosition = nullptr;
}

// Destructor definitions -----------------------------------------------------
Carrier::CarrierBuilder::~CarrierBuilder()
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
    if (carrierPID != nullptr)
    {
        delete carrierPID;
        carrierPID = nullptr;
    }
    if (startAngle != nullptr)
    {
        delete startAngle;
        startAngle = nullptr;
    }
    if (minAngle != nullptr)
    {
        delete minAngle;
        minAngle = nullptr;
    }
    if (maxAngle != nullptr)
    {
        delete maxAngle;
        maxAngle = nullptr;
    }
    if (startHeight != nullptr)
    {
        delete startHeight;
        startHeight = nullptr;
    }
    if (minHeight != nullptr)
    {
        delete minHeight;
        minHeight = nullptr;
    }
    if (maxHeight != nullptr)
    {
        delete maxHeight;
        maxHeight = nullptr;
    }
    if (countsPerDegree != nullptr)
    {
        delete countsPerDegree;
        countsPerDegree = nullptr;
    }
    if (countsPerInch != nullptr)
    {
        delete countsPerInch;
        countsPerInch = nullptr;
    }
    if (armLength != nullptr)
    {
        delete armLength;
        armLength = nullptr;
    }
    if (downPosition != nullptr)
    {
        delete downPosition;
        downPosition = nullptr;
    }
    if (upPosition != nullptr)
    {
        delete upPosition;
        upPosition = nullptr;
    }
}

// Public method definitions --------------------------------------------------
Carrier::CarrierBuilder* Carrier::CarrierBuilder::withMotor(pros::Motor* motor)
{
    if (motorList == nullptr)
        motorList = new std::list<pros::Motor*>();
    motorList->push_back(motor);
    return this;
}

Carrier::CarrierBuilder* Carrier::CarrierBuilder::withPiston(pros::ADIDigitalOut* piston)
{
    if (pistonList == nullptr)
        pistonList = new std::list<pros::ADIDigitalOut*>();
    pistonList->push_back(piston);
    return this;
}

Carrier::CarrierBuilder* Carrier::CarrierBuilder::withPID(PID* pid)
{
    carrierPID = pid;
    return this;
}

Carrier::CarrierBuilder* Carrier::CarrierBuilder::withStartAngle(double startAngle)
{
    if (this->startAngle == nullptr)
        this->startAngle = new double;
    *this->startAngle = startAngle;
    return this;
}

Carrier::CarrierBuilder* Carrier::CarrierBuilder::withMinAngle(double minAngle)
{
    if (this->minAngle == nullptr)
        this->minAngle = new double;
    *this->minAngle = minAngle;
    return this;
}

Carrier::CarrierBuilder* Carrier::CarrierBuilder::withMaxAngle(double maxAngle)
{
    if (this->maxAngle == nullptr)
        this->maxAngle = new double;
    *this->maxAngle = maxAngle;
    return this;
}

Carrier::CarrierBuilder* Carrier::CarrierBuilder::withStartHeight(double startHeight)
{
    if (this->startHeight == nullptr)
        this->startHeight = new double;
    *this->startHeight = startHeight;
    return this;
}

Carrier::CarrierBuilder* Carrier::CarrierBuilder::withMinHeight(double minHeight)
{
    if (this->minHeight == nullptr)
        this->minHeight = new double;
    *this->minHeight = minHeight;
    return this;
}

Carrier::CarrierBuilder* Carrier::CarrierBuilder::withMaxHeight(double maxHeight)
{
    if (this->maxHeight == nullptr)
        this->maxHeight = new double;
    *this->maxHeight = maxHeight;
    return this;
}

Carrier::CarrierBuilder* Carrier::CarrierBuilder::withCountsPerDegree(double countsPerDegree)
{
    if (this->countsPerDegree == nullptr)
        this->countsPerDegree = new double;
    *this->countsPerDegree = countsPerDegree;
    return this;
}

Carrier::CarrierBuilder* Carrier::CarrierBuilder::withCountsPerInch(double countsPerInch)
{
    if (this->countsPerInch == nullptr)
        this->countsPerInch = new double;
    *this->countsPerInch = countsPerInch;
    return this;
}

Carrier::CarrierBuilder* Carrier::CarrierBuilder::withArmLength(double armLength)
{
    if (this->armLength == nullptr)
        this->armLength = new double;
    *this->armLength = armLength;
    return this;
}

Carrier::CarrierBuilder* Carrier::CarrierBuilder::withDownPosition(double downPosition)
{
    if (this->downPosition == nullptr)
        this->downPosition = new double;
    *this->downPosition = downPosition;
    return this;
}

Carrier::CarrierBuilder* Carrier::CarrierBuilder::withUpPosition(double upPosition)
{
    if (this->upPosition == nullptr)
        this->upPosition = new double;
    *this->upPosition = upPosition;
    return this;
}

Carrier* Carrier::CarrierBuilder::build()
{
    return new Carrier(this);
}

// CARRIER

// Constructor definitions ----------------------------------------------------
Carrier::Carrier(CarrierBuilder* builder)
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
    if (builder->carrierPID != nullptr)
        this->carrierPID = new PID(*builder->carrierPID);

    if (builder->startAngle != nullptr)
        this->startAngle = *builder->startAngle;
    else
        this->startAngle = 0.0;

    if (builder->startHeight != nullptr)
        this->startHeight = *builder->startHeight;
    else
        this->startHeight = 0.0;

    if (builder->countsPerDegree != nullptr)
        this->countsPerDegree = *builder->countsPerDegree;
    else
        this->countsPerDegree = DBL_MIN;

    if (builder->countsPerInch != nullptr)
        this->countsPerInch = *builder->countsPerInch;
    else
        this->countsPerInch = DBL_MIN;

    if (builder->armLength != nullptr)
        this->armLength = *builder->armLength;
    else
        this->armLength = DBL_MIN;
    
    if (builder->downPosition != nullptr)
        this->downPosition = *builder->downPosition;
    else
        this->downPosition = -DBL_MAX;
    
    if (builder->upPosition != nullptr)
        this->upPosition = *builder->upPosition;
    else
        this->upPosition = DBL_MAX;
    
    // Set the minimum position
    if (builder->minAngle != nullptr)
        minPosition = angleToPosition(*builder->minAngle);
    else if (builder->minHeight != nullptr)
        minPosition = heightToPosition(*builder->minHeight);
    else
        minPosition = -DBL_MAX;

    // Set the maximum position
    if (builder->maxAngle != nullptr)
        maxPosition = angleToPosition(*builder->maxAngle);
    else if (builder->maxHeight != nullptr)
        maxPosition = heightToPosition(*builder->maxHeight);
    else
        maxPosition = DBL_MAX;

   // Set the starting position
   isDown = false;
}

//-----------------------------------------------------------------------------
// Default destructor for the Carrier class
// v1: Created the destructor - Nathan S, 4-11-22
//-----------------------------------------------------------------------------
Carrier::~Carrier()
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
    if (carrierPID != nullptr)
    {
        delete carrierPID;
        carrierPID = nullptr;
    }
}

// Private method definitions -------------------------------------------------
double Carrier::angleToPosition(double angle)
{
    double position = (angle * countsPerDegree) - (startAngle * countsPerDegree);
    return position;
}

double Carrier::heightToPosition(double height)
{
    double position = (height * countsPerInch) - (startHeight * countsPerInch);
    position += armLength * sin(getAngle());
    return position;
}

// Public method definitions --------------------------------------------------
void Carrier::initialize()
{
    // Set the positions to 0
    for (std::list<pros::Motor*>::iterator iterator = motorList.begin(); 
        iterator != motorList.end(); iterator++)
    {
        (*iterator)->tare_position();
        (*iterator)->set_brake_mode(E_MOTOR_BRAKE_BRAKE);
    }

    for (std::list<pros::ADIDigitalOut*>::iterator iterator = pistonList.begin(); 
        iterator != pistonList.end(); iterator++)
        (*iterator)->set_value(isDown);

    if (carrierPID != nullptr)
        carrierPID->setTargetValue(0.0);
}

void Carrier::setCarrier(double power)
{
    for (std::list<pros::Motor*>::iterator iterator = motorList.begin(); 
         iterator != motorList.end(); iterator++)
        (*iterator)->move(power);
}

void Carrier::raise()
{
    if(!atTop())
        setCarrier(127.0);
    else
        setCarrier(0.0);

    if (carrierPID != nullptr)
        carrierPID->setTargetValue(getPosition());
}

void Carrier::lower()
{
    if(!atBottom())
        setCarrier(-127.0);
    else
        setCarrier(0.0);

    if (carrierPID != nullptr)
        carrierPID->setTargetValue(getPosition());
}

void Carrier::holdPosition()
{
    if(!atBottom())
    {
        if (carrierPID != nullptr)
            setCarrier(carrierPID->getControlValue(getPosition()));
        else
            setCarrier(0.0);
    }
    else
        setCarrier(0.0);
}

double Carrier::getPosition()
{
    double position = 0.0;
    if (!motorList.empty())
        position = motorList.front()->get_position();
    return position;
}

void Carrier::setAngle(double targetAngle)
{
    double targetPosition = angleToPosition(targetAngle);
    if (carrierPID != nullptr)
        carrierPID->setTargetValue(targetPosition);
}

void Carrier::setHeight(double targetHeight)
{
    double targetPosition = heightToPosition(targetHeight);
    if (carrierPID != nullptr)
        carrierPID->setTargetValue(targetPosition);
}

double Carrier::getAngle()
{
    double angle = startAngle;
    if(countsPerDegree > 0.1)
        angle += getPosition() / countsPerDegree;
    return angle;
}

double Carrier::getHeight()
{
    double height = startHeight + (armLength * sin(getAngle()));
    if(countsPerInch > 0.1)
        height += getPosition() / countsPerInch;
    return height;
}

void Carrier::setDown()
{
    if (carrierPID != nullptr)
        carrierPID->setTargetValue(downPosition);
    for (std::list<pros::ADIDigitalOut*>::iterator iterator = pistonList.begin(); 
        iterator != pistonList.end(); iterator++)
        (*iterator)->set_value(true);
    isDown = true;
}

void Carrier::setUp()
{
    if (carrierPID != nullptr)
        carrierPID->setTargetValue(upPosition);
    for (std::list<pros::ADIDigitalOut*>::iterator iterator = pistonList.begin(); 
        iterator != pistonList.end(); iterator++)
        (*iterator)->set_value(false);
    isDown = false;
}

void Carrier::togglePosition()
{
    if (isDown)
        setUp();
    else
        setDown();
}

bool Carrier::atBottom()
{
    return getPosition() <= minPosition;
}

bool Carrier::atTop()
{
    return getPosition() >= maxPosition;
}