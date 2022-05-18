// Included libraries
#include "subsystems/Lift.hpp"

// LIFT BUILDER

// Constructor definitions ----------------------------------------------------
Lift::LiftBuilder::LiftBuilder()
{
    leftMotorList = nullptr;
    rightMotorList = nullptr;
    liftPID = nullptr;
    startAngle = nullptr;
    minAngle = nullptr;
    maxAngle = nullptr;
    startHeight = nullptr;
    minHeight = nullptr;
    maxHeight = nullptr;
    countsPerDegree = nullptr;
    countsPerInch = nullptr;
    armLength = nullptr;
}

// Destructor definitions -----------------------------------------------------
Lift::LiftBuilder::~LiftBuilder()
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
    if (liftPID != nullptr)
    {
        delete liftPID;
        liftPID = nullptr;
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
}

// Public method definitions --------------------------------------------------
Lift::LiftBuilder* Lift::LiftBuilder::withLeftMotor(pros::Motor* motor)
{
    if (leftMotorList == nullptr)
        leftMotorList = new std::list<pros::Motor*>();
    leftMotorList->push_back(motor);
    return this;
}

Lift::LiftBuilder* Lift::LiftBuilder::withRightMotor(pros::Motor* motor)
{
    if (rightMotorList == nullptr)
        rightMotorList = new std::list<pros::Motor*>();
    rightMotorList->push_back(motor);
    return this;
}

Lift::LiftBuilder* Lift::LiftBuilder::withPID(PID* pid)
{
    liftPID = pid;
    return this;
}

Lift::LiftBuilder* Lift::LiftBuilder::withStartAngle(double startAngle)
{
    if (this->startAngle == nullptr)
        this->startAngle = new double;
    *this->startAngle = startAngle;
    return this;
}

Lift::LiftBuilder* Lift::LiftBuilder::withMinAngle(double minAngle)
{
    if (this->minAngle == nullptr)
        this->minAngle = new double;
    *this->minAngle = minAngle;
    return this;
}

Lift::LiftBuilder* Lift::LiftBuilder::withMaxAngle(double maxAngle)
{
    if (this->maxAngle == nullptr)
        this->maxAngle = new double;
    *this->maxAngle = maxAngle;
    return this;
}

Lift::LiftBuilder* Lift::LiftBuilder::withStartHeight(double startHeight)
{
    if (this->startHeight == nullptr)
        this->startHeight = new double;
    *this->startHeight = startHeight;
    return this;
}

Lift::LiftBuilder* Lift::LiftBuilder::withMinHeight(double minHeight)
{
    if (this->minHeight == nullptr) 
        this->minHeight = new double;
    *this->minHeight = minHeight;
    return this;
}

Lift::LiftBuilder* Lift::LiftBuilder::withMaxHeight(double maxHeight)
{
    if (this->maxHeight == nullptr)
        this->maxHeight = new double;
    *this->maxHeight = maxHeight;
    return this;
}

Lift::LiftBuilder* Lift::LiftBuilder::withCountsPerDegree(double countsPerDegree)
{
    if (this->countsPerDegree == nullptr)
        this->countsPerDegree = new double;
    *this->countsPerDegree = countsPerDegree;
    return this;
}

Lift::LiftBuilder* Lift::LiftBuilder::withCountsPerInch(double countsPerInch)
{
    if (this->countsPerInch == nullptr)
        this->countsPerInch = new double;
    *this->countsPerInch = countsPerInch;
    return this;
}

Lift::LiftBuilder* Lift::LiftBuilder::withArmLength(double armLength)
{
    if (this->armLength == nullptr)
        this->armLength = new double;
    *this->armLength = armLength;
    return this;
}

Lift* Lift::LiftBuilder::build()
{
    return new Lift(this);
}

// LIFT

// Constructor definitions ----------------------------------------------------
Lift::Lift(LiftBuilder* builder)
{
    // Set the motors
    if (builder->leftMotorList != nullptr)
        for (std::list<pros::Motor*>::iterator iterator = builder->leftMotorList->begin(); 
            iterator != builder->leftMotorList->end(); iterator++)
            this->leftMotorList.push_back(*iterator);

    if (builder->rightMotorList != nullptr)
        for (std::list<pros::Motor*>::iterator iterator = builder->rightMotorList->begin(); 
            iterator != builder->rightMotorList->end(); iterator++)
            this->rightMotorList.push_back(*iterator);

    // Set the PID controller
    if (builder->liftPID != nullptr)
        this->liftPID = new PID(*builder->liftPID);

    // Set the starting angle
    if (builder->startAngle != nullptr)
        this->startAngle = *builder->startAngle;
    else
        this->startAngle = 0.0;
    
    // Set the starting height
    if (builder->startHeight != nullptr)
        this->startHeight = *builder->startHeight;
    else
        this->startHeight = 0.0;
    
    // Set the number of counts per degree
    if (builder->countsPerDegree != nullptr)
        this->countsPerDegree = *builder->countsPerDegree;
    else
        this->countsPerDegree = DBL_MIN;

    // Set the number of counts per inch
    if (builder->countsPerInch != nullptr)
        this->countsPerInch = *builder->countsPerInch;
    else
        this->countsPerInch = DBL_MIN;

    // Set the arm length
    if (builder->armLength != nullptr)
        this->armLength = *builder->armLength;
    else
        this->armLength = DBL_MIN;

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
}

// Destructor definitions -----------------------------------------------------
Lift::~Lift()
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
    if (liftPID != nullptr)
    {
        delete liftPID;
        liftPID = nullptr;
    }
}

// Private method definitions -------------------------------------------------
double Lift::angleToPosition(double angle)
{
    double position = (angle * countsPerDegree) - (startAngle * countsPerDegree);
    return position;
}

double Lift::heightToPosition(double height)
{
    double position = (height * countsPerInch) - (startHeight * countsPerInch);
    position += armLength * sin(getAngle());
    return position;
}

// Public method definitions --------------------------------------------------
void Lift::initialize()
{
    // Set the positions to 0
    for (std::list<pros::Motor*>::iterator iterator = leftMotorList.begin(); 
        iterator != leftMotorList.end(); iterator++)
    {
        (*iterator)->tare_position();
        (*iterator)->set_brake_mode(E_MOTOR_BRAKE_COAST);
    }
    for (std::list<pros::Motor*>::iterator iterator = rightMotorList.begin(); 
        iterator != rightMotorList.end(); iterator++)
    {
        (*iterator)->tare_position();
        (*iterator)->set_brake_mode(E_MOTOR_BRAKE_COAST);
    }

    if (liftPID != nullptr)
        liftPID->setTargetValue(0.0);
}

void Lift::setLift(double power)
{
    for (std::list<pros::Motor*>::iterator iterator = leftMotorList.begin(); 
         iterator != leftMotorList.end(); iterator++)
        (*iterator)->move(power);
    for (std::list<pros::Motor*>::iterator iterator = rightMotorList.begin(); 
         iterator != rightMotorList.end(); iterator++)
        (*iterator)->move(power);
}

void Lift::raise()
{
    if(!atTop())
        setLift(127.0);
    else
        setLift(0.0);

    if (liftPID != nullptr)
        liftPID->setTargetValue(getPosition());
}

void Lift::lower()
{
    if(!atBottom())
        setLift(-127.0);
    else
        setLift(0.0);

    if (liftPID != nullptr)
        liftPID->setTargetValue(getPosition());
}

void Lift::stop()
{
    setLift(0.0);
}

void Lift::holdPosition()
{
    if (!atBottom())
    {
        if (liftPID != nullptr)
            setLift(liftPID->getControlValue(getPosition()));
        else
            setLift(0.0);
    }
    else 
    {
        setLift(0.0);
    }
}

double Lift::getPosition()
{
    double position = 0.0;
    if (leftMotorList.size() > 0)
        position = leftMotorList.front()->get_position();
    return position;
}

void Lift::setAngle(double targetAngle)
{
    double targetPosition = angleToPosition(targetAngle);
    if (liftPID != nullptr)
        liftPID->setTargetValue(targetPosition);
}

void Lift::setHeight(double targetHeight)
{
    double targetPosition = heightToPosition(targetHeight);
    if (liftPID != nullptr)
        liftPID->setTargetValue(targetPosition);
}

double Lift::getAngle()
{
    double angle = startAngle;
    if(countsPerDegree > 0.1)
        angle += getPosition() / countsPerDegree;
    return angle;
}

double Lift::getHeight()
{
    double height = startHeight + (armLength * sin(getAngle()));
    if(countsPerInch > 0.1)
        height += getPosition() / countsPerInch;
    return height;
}

bool Lift::atBottom()
{
    return getPosition() <= minPosition;
}

bool Lift::atTop()
{
    return getPosition() >= maxPosition;
}