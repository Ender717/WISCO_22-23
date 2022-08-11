// Defined header
#include "./subsystems/Turret.hpp"

// BUILDER CLASS

// Constructor definitions ----------------------------------------------------
Turret::TurretBuilder::TurretBuilder()
{
    motorList = nullptr;
    turretPID = nullptr;
    startAngle = nullptr;
    countsPerDegree = nullptr;
    minAngle = nullptr;
    maxAngle = nullptr;
}

// Destructor definitions -----------------------------------------------------
Turret::TurretBuilder::~TurretBuilder()
{
    if (motorList != nullptr)
    {
        delete motorList;
        motorList = nullptr;
    }

    if (turretPID != nullptr)
    {
        delete turretPID;
        turretPID = nullptr;
    }

    if (startAngle != nullptr)
    {
        delete startAngle;
        startAngle = nullptr;
    }

    if (countsPerDegree != nullptr)
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
}

// Public method definitions --------------------------------------------------
Turret::TurretBuilder* Turret::TurretBuilder::withMotor(pros::Motor* motor)
{
    if (motorList == nullptr)
        motorList = new std::list<pros::Motor*>();
    motorList->push_back(motor);
    return this;
}

Turret::TurretBuilder* Turret::TurretBuilder::withPID(PID* pid)
{
    turretPID = pid;
    return this;
}

Turret::TurretBuilder* Turret::TurretBuilder::withStartAngle(double startAngle)
{
    if (this->startAngle == nullptr)
        this->startAngle = new double;
    *this->startAngle = startAngle;
    return this;
}

Turret::TurretBuilder* Turret::TurretBuilder::withCountsPerDegree(double countsPerDegree)
{
    if (this->countsPerDegree == nullptr)
        this->countsPerDegree = new double;
    *this->countsPerDegree = countsPerDegree;
    return this;
}

Turret::TurretBuilder* Turret::TurretBuilder::withMinAngle(double minAngle)
{
    if (this->minAngle == nullptr)
        this->minAngle = new double;
    *this->minAngle = minAngle;
    return this;
}

Turret::TurretBuilder* Turret::TurretBuilder::withMaxAngle(double maxAngle)
{
    if (this->maxAngle == nullptr)
        this->maxAngle = new double;
    *this->maxAngle = maxAngle;
    return this;
}

Turret* Turret::TurretBuilder::build()
{
    return new Turret(this);
}

// TURRET CLASS

// Constructor definitions ----------------------------------------------------
Turret::Turret()
{
    motorList = nullptr;
    turretPID = nullptr;
    startAngle = 0.0;
    countsPerDegree = 0.0;
    minPosition = 0.0;
    maxPosition = 0.0;
    targetAngle = 0.0;
}

Turret::Turret(TurretBuilder* builder)
{
    motorList = new std::list<pros::Motor*>();
    turretPID = nullptr;
    startAngle = 0.0;
    countsPerDegree = 0.0;
    minPosition = -DBL_MAX;
    maxPosition = DBL_MAX;
    targetAngle = 0.0;

    if (builder->motorList != nullptr)
        for (std::list<pros::Motor*>::iterator iterator = builder->motorList->begin(); 
            iterator != builder->motorList->end(); iterator++)
            this->motorList->push_back(*iterator);

    if (builder->turretPID != nullptr)
        turretPID = new PID(*builder->turretPID);

    if (builder->startAngle != nullptr)
        this->startAngle = *builder->startAngle;

    if (builder->countsPerDegree != nullptr)
        this->countsPerDegree = *builder->countsPerDegree;
    
    if (builder->minAngle != nullptr && builder->countsPerDegree != nullptr)
        this->minPosition = *builder->minAngle * *builder->countsPerDegree;

    if (builder->maxAngle != nullptr && builder->countsPerDegree != nullptr)
        this->maxPosition = *builder->maxAngle * *builder->countsPerDegree;
}

// Destructor definitions -----------------------------------------------------
Turret::~Turret()
{
    if (motorList != nullptr)
    {
        for (std::list<pros::Motor*>::iterator iterator = motorList->begin(); 
            iterator != motorList->end(); iterator++)
        {
            if (*iterator != nullptr)
            {
                delete *iterator;
                *iterator = nullptr;
            }
        }
        delete motorList;
        motorList = nullptr;
    }

    if (turretPID != nullptr)
    {
        delete turretPID;
        turretPID = nullptr;
    }
}

// Public method definitions --------------------------------------------------
void Turret::initialize()
{
    // Set the positions to 0
    if (motorList != nullptr)
        for (std::list<pros::Motor*>::iterator iterator = motorList->begin(); 
            iterator != motorList->end(); iterator++)
            if (*iterator != nullptr)
            {
                (*iterator)->tare_position();
                (*iterator)->set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
            }
    if (turretPID != nullptr)
        turretPID->setTargetValue(targetAngle);
}

void Turret::update()
{
    if (turretPID != nullptr)
        setTurret(turretPID->getControlValue(getPosition()));
}

void Turret::setTurret(double power)
{
    if (motorList != nullptr)
        for (std::list<pros::Motor*>::iterator iterator = motorList->begin(); 
            iterator != motorList->end(); iterator++)
            if (*iterator != nullptr)
                (*iterator)->move(power);
}

double Turret::getPosition()
{
    double position = 0.0;
    if (motorList != nullptr && !motorList->empty() && motorList->front() != nullptr)
        position = motorList->front()->get_position();
    return position;
}

void Turret::setAngle(double angle)
{
    double targetPosition = angle * countsPerDegree;

    if (targetPosition > maxPosition)
        targetPosition = maxPosition;
    else if (targetPosition < minPosition)
        targetPosition = minPosition;

    if (countsPerDegree != 0.0)
        targetAngle = targetPosition / countsPerDegree;
    else
        targetAngle = 0.0;

    if (turretPID != nullptr)
        turretPID->setTargetValue(targetPosition);
}

double Turret::getAngle()
{
    double angle = 0.0;
    if (countsPerDegree != 0.0)
        angle = getPosition() / countsPerDegree;
    return angle;
}

double Turret::getTargetAngle()
{
    return targetAngle;
}