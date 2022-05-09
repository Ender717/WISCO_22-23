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
    carrierPID = nullptr;
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
Carrier::CarrierBuilder* Carrier::CarrierBuilder::WithMotor(pros::Motor* motor)
{
    if (motorList == nullptr)
        motorList = new std::list<pros::Motor*>();
    motorList->push_back(motor);
    return this;
}

Carrier::CarrierBuilder* Carrier::CarrierBuilder::WithPiston(pros::ADIDigitalOut* piston)
{
    if (pistonList == nullptr)
        pistonList = new std::list<pros::ADIDigitalOut*>();
    pistonList->push_back(piston);
    return this;
}

Carrier::CarrierBuilder* Carrier::CarrierBuilder::WithPID(PID* pid)
{
    carrierPID = pid;
    return this;
}

Carrier::CarrierBuilder* Carrier::CarrierBuilder::WithStartAngle(double startAngle)
{
    if (this->startAngle == nullptr)
        this->startAngle = new double;
    *this->startAngle = startAngle;
    return this;
}

Carrier::CarrierBuilder* Carrier::CarrierBuilder::WithMinAngle(double minAngle)
{
    if (this->minAngle == nullptr)
        this->minAngle = new double;
    *this->minAngle = minAngle;
    return this;
}

Carrier::CarrierBuilder* Carrier::CarrierBuilder::WithMaxAngle(double maxAngle)
{
    if (this->maxAngle == nullptr)
        this->maxAngle = new double;
    *this->maxAngle = maxAngle;
    return this;
}

Carrier::CarrierBuilder* Carrier::CarrierBuilder::WithStartHeight(double startHeight)
{
    if (this->startHeight == nullptr)
        this->startHeight = new double;
    *this->startHeight = startHeight;
    return this;
}

Carrier::CarrierBuilder* Carrier::CarrierBuilder::WithMinHeight(double minHeight)
{
    if (this->minHeight == nullptr)
        this->minHeight = new double;
    *this->minHeight = minHeight;
    return this;
}

Carrier::CarrierBuilder* Carrier::CarrierBuilder::WithMaxHeight(double maxHeight)
{
    if (this->maxHeight == nullptr)
        this->maxHeight = new double;
    *this->maxHeight = maxHeight;
    return this;
}

Carrier::CarrierBuilder* Carrier::CarrierBuilder::WithCountsPerDegree(double countsPerDegree)
{
    if (this->countsPerDegree == nullptr)
        this->countsPerDegree = new double;
    *this->countsPerDegree = countsPerDegree;
    return this;
}

Carrier::CarrierBuilder* Carrier::CarrierBuilder::WithCountsPerInch(double countsPerInch)
{
    if (this->countsPerInch == nullptr)
        this->countsPerInch = new double;
    *this->countsPerInch = countsPerInch;
    return this;
}

Carrier::CarrierBuilder* Carrier::CarrierBuilder::WithArmLength(double armLength)
{
    if (this->armLength == nullptr)
        this->armLength = new double;
    *this->armLength = armLength;
    return this;
}

Carrier::CarrierBuilder* Carrier::CarrierBuilder::WithDownPosition(double downPosition)
{
    if (this->downPosition == nullptr)
        this->downPosition = new double;
    *this->downPosition = downPosition;
    return this;
}

Carrier::CarrierBuilder* Carrier::CarrierBuilder::WithUpPosition(double upPosition)
{
    if (this->upPosition == nullptr)
        this->upPosition = new double;
    *this->upPosition = upPosition;
    return this;
}

Carrier* Carrier::CarrierBuilder::Build()
{
    return new Carrier(this);
}

// CARRIER

// Constructor definitions ----------------------------------------------------
Carrier::Carrier(CarrierBuilder* builder)
{
    // Initialize the pointers
    motorList = new std::list<pros::Motor*>();
    pistonList = new std::list<pros::ADIDigitalOut*>();
    startAngle = new double;
    startHeight = new double;
    countsPerDegree = new double;
    countsPerInch = new double;
    armLength = new double;
    minPosition = new double;
    maxPosition = new double;
    downPosition = new double;
    upPosition = new double;
    isDown = new bool;

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
    this->carrierPID = builder->carrierPID;

    if (builder->startAngle != nullptr)
        *this->startAngle = *builder->startAngle;
    else
        *this->startAngle = 0.0;

    if (builder->startHeight != nullptr)
        *this->startHeight = *builder->startHeight;
    else
        *this->startHeight = 0.0;

    if (builder->countsPerDegree != nullptr)
        *this->countsPerDegree = *builder->countsPerDegree;
    else
        *this->countsPerDegree = DBL_MIN;

    if (builder->countsPerInch != nullptr)
        *this->countsPerInch = *builder->countsPerInch;
    else
        *this->countsPerInch = DBL_MIN;

    if (builder->armLength != nullptr)
        *this->armLength = *builder->armLength;
    else
        *this->armLength = DBL_MIN;
    
    if (builder->downPosition != nullptr)
        *this->downPosition = *builder->downPosition;
    else
        *this->downPosition = -DBL_MAX;
    
    if (builder->upPosition != nullptr)
        *this->upPosition = *builder->upPosition;
    else
        *this->upPosition = DBL_MAX;
    
    // Set the minimum position
    if (builder->minAngle != nullptr)
        *minPosition = AngleToPosition(*builder->minAngle);
    else if (builder->minHeight != nullptr)
        *minPosition = HeightToPosition(*builder->minHeight);
    else
        *minPosition = -DBL_MAX;

    // Set the maximum position
    if (builder->maxAngle != nullptr)
        *maxPosition = AngleToPosition(*builder->maxAngle);
    else if (builder->maxHeight != nullptr)
        *maxPosition = HeightToPosition(*builder->maxHeight);
    else
        *maxPosition = DBL_MAX;

   // Set the starting position
   *isDown = false;
}

//-----------------------------------------------------------------------------
// Default destructor for the Carrier class
// v1: Created the destructor - Nathan S, 4-11-22
//-----------------------------------------------------------------------------
Carrier::~Carrier()
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
    if (startHeight != nullptr)
    {
        delete startHeight;
        startAngle = nullptr;
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
    if (isDown != nullptr)
    {
        delete isDown;
        isDown = nullptr;
    }
}

// Private method definitions -------------------------------------------------
double Carrier::AngleToPosition(double angle)
{
    double position = (angle * *countsPerDegree) - (*startAngle * *countsPerDegree);
    return position;
}

double Carrier::HeightToPosition(double height)
{
    double position = (height * *countsPerInch) - (*startHeight * *countsPerInch);
    position += *armLength * sin(GetAngle());
    return position;
}

// Public method definitions --------------------------------------------------
void Carrier::Initialize()
{
    // Set the positions to 0
    for (std::list<pros::Motor*>::iterator iterator = motorList->begin(); 
        iterator != motorList->end(); iterator++)
    {
        (*iterator)->tare_position();
        (*iterator)->set_brake_mode(E_MOTOR_BRAKE_BRAKE);
    }

    for (std::list<pros::ADIDigitalOut*>::iterator iterator = pistonList->begin(); 
        iterator != pistonList->end(); iterator++)
        (*iterator)->set_value(*isDown);

    if (carrierPID != nullptr)
        carrierPID->SetTargetValue(0.0);
}

void Carrier::SetCarrier(double power)
{
    for (std::list<pros::Motor*>::iterator iterator = motorList->begin(); 
         iterator != motorList->end(); iterator++)
        (*iterator)->move(power);
}

void Carrier::Raise()
{
    if(!AtTop())
        SetCarrier(127.0);
    else
        SetCarrier(0.0);

    if (carrierPID != nullptr)
        carrierPID->SetTargetValue(GetPosition());
}

void Carrier::Lower()
{
    if(!AtBottom())
        SetCarrier(-127.0);
    else
        SetCarrier(0.0);

    if (carrierPID != nullptr)
        carrierPID->SetTargetValue(GetPosition());
}

void Carrier::HoldPosition()
{
    if (motorList->size() > 0)
    {
        if(!AtBottom() && !AtTop())
        {
            if (carrierPID != nullptr)
                SetCarrier(carrierPID->GetControlValue(GetPosition()));
        }
        else
            SetCarrier(0.0);
    }
}

double Carrier::GetPosition()
{
    if (!motorList->empty())
        return motorList->front()->get_position();
    else
        return 0.0;
}

void Carrier::SetAngle(double targetAngle)
{
    double targetPosition = AngleToPosition(targetAngle);
    if (carrierPID != nullptr)
        carrierPID->SetTargetValue(targetPosition);
}

void Carrier::SetHeight(double targetHeight)
{
    double targetPosition = HeightToPosition(targetHeight);
    if (carrierPID != nullptr)
        carrierPID->SetTargetValue(targetPosition);
}

double Carrier::GetAngle()
{
    double angle = *startAngle;
    if(*countsPerDegree > 0.1)
        angle += GetPosition() / *countsPerDegree;
    return angle;
}

double Carrier::GetHeight()
{
    double height = *startHeight + (*armLength * sin(GetAngle()));
    if(*countsPerInch > 0.1)
        height += GetPosition() / *countsPerInch;
    return height;
}

void Carrier::SetDown()
{
    if (carrierPID != nullptr)
        carrierPID->SetTargetValue(*downPosition);
    for (std::list<pros::ADIDigitalOut*>::iterator iterator = pistonList->begin(); 
        iterator != pistonList->end(); iterator++)
        (*iterator)->set_value(true);
    *isDown = true;
}

void Carrier::SetUp()
{
    if (carrierPID != nullptr)
        carrierPID->SetTargetValue(*upPosition);
    for (std::list<pros::ADIDigitalOut*>::iterator iterator = pistonList->begin(); 
        iterator != pistonList->end(); iterator++)
        (*iterator)->set_value(false);
    *isDown = false;
}

void Carrier::TogglePosition()
{
    if (*isDown)
        SetUp();
    else
        SetDown();
}

bool Carrier::AtBottom()
{
    return GetPosition() <= *minPosition;
}

bool Carrier::AtTop()
{
    return GetPosition() >= *maxPosition;
}