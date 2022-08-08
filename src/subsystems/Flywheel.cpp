// Defined header
#include "subsystems/Flywheel.hpp"
#include "pros/motors.h"

// BUILDER CLASS

// Constructor definitions ----------------------------------------------------
Flywheel::FlywheelBuilder::FlywheelBuilder()
{
    motorList = nullptr;
    flywheelPID = nullptr;
    wheelSize = nullptr;
    countsPerRevolution = nullptr;
    maxRPM = nullptr;
}

// Destructor definitions -----------------------------------------------------
Flywheel::FlywheelBuilder::~FlywheelBuilder()
{
    // Delete the motor list but not the motors
    if (motorList != nullptr)
    {
        delete motorList;
        motorList = nullptr;
    }

    // Delete the PID controller
    if (flywheelPID != nullptr)
    {
        delete flywheelPID;
        flywheelPID = nullptr;
    }

    // Delete the counts per cycle
    if (wheelSize != nullptr)
    {
        delete wheelSize;
        wheelSize = nullptr;
    }

    // Delete the loaded position
    if (countsPerRevolution != nullptr)
    {
        delete countsPerRevolution;
        countsPerRevolution = nullptr;
    }

    // Delete the max RPM
    if (maxRPM != nullptr)
    {
        delete maxRPM;
        maxRPM = nullptr;
    }
}

// Public method definitions --------------------------------------------------
Flywheel::FlywheelBuilder* Flywheel::FlywheelBuilder::withMotor(pros::Motor* motor)
{
    if (motorList == nullptr)
        motorList = new std::list<pros::Motor*>();
    motorList->push_back(motor);
    return this;
}

Flywheel::FlywheelBuilder* Flywheel::FlywheelBuilder::withPID(PID* pid)
{
    flywheelPID = pid;
    return this;
}

Flywheel::FlywheelBuilder* Flywheel::FlywheelBuilder::withWheelSize(double wheelSize)
{
    if (this->wheelSize == nullptr)
        this->wheelSize = new double;
    *this->wheelSize = wheelSize;
    return this;
}

Flywheel::FlywheelBuilder* Flywheel::FlywheelBuilder::withCountsPerRevolution(double countsPerRevolution)
{
    if (this->countsPerRevolution == nullptr)
        this->countsPerRevolution = new double;
    *this->countsPerRevolution = countsPerRevolution;
    return this;
}

Flywheel::FlywheelBuilder* Flywheel::FlywheelBuilder::withMaxRPM(double maxRPM)
{
    if (this->maxRPM == nullptr)
        this->maxRPM = new double;
    *this->maxRPM = maxRPM;
    return this;
}

Flywheel* Flywheel::FlywheelBuilder::build()
{
    return new Flywheel(this);
}

// FLYWHEEL CLASS

// Constructor definitions ----------------------------------------------------
Flywheel::Flywheel(FlywheelBuilder* builder)
{
    // Create the motor list
    motorList = new std::list<pros::Motor*>();

    // Set the motors
    if (builder->motorList != nullptr)
        for (std::list<pros::Motor*>::iterator iterator = builder->motorList->begin(); 
            iterator != builder->motorList->end(); iterator++)
            this->motorList->push_back(*iterator);

    // Set the PID controller
    if (builder->flywheelPID != nullptr)
        this->flywheelPID = new PID(*builder->flywheelPID);

    // Set the wheel size
    if (builder->wheelSize != nullptr)
        this->wheelSize = *builder->wheelSize;
    else
        this->wheelSize = 0.0;

    // Set the counts per revolution
    if (builder->countsPerRevolution != nullptr)
        this->countsPerRevolution = *builder->countsPerRevolution;
    else
        this->countsPerRevolution = DBL_MAX;

    // Set the maximum RPM
    if (builder->maxRPM != nullptr)
        this->maxRPM = *builder->maxRPM;
    else
        this->maxRPM = DBL_MAX;

    motorPower = 0.0;
    lastPosition = 0.0;
    lastTime = 0.0;
    currentRPM = 0.0;
    targetRPM = 0.0;
}

// Destructor definitions -----------------------------------------------------
Flywheel::~Flywheel()
{
    // Delete the motor list
    if (motorList != nullptr)
    {
        // Delete each motor in the list
        for (std::list<pros::Motor*>::iterator iterator = motorList->begin(); 
            iterator != motorList->end(); iterator++)
        {
            delete *iterator;
            *iterator = nullptr;
        }
        delete motorList;
        motorList = nullptr;
    }

    // Delete the PID controller
    if (flywheelPID != nullptr)
    {
        delete flywheelPID;
        flywheelPID = nullptr;
    }
}

// Public method definitions --------------------------------------------------
void Flywheel::initialize()
{
    // Set the positions to 0
    for (std::list<pros::Motor*>::iterator iterator = motorList->begin(); 
        iterator != motorList->end(); iterator++)
    {
        (*iterator)->tare_position();
        (*iterator)->set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    }
    if (flywheelPID != nullptr)
        flywheelPID->setTargetValue(0.0);
    lastTime = pros::c::millis();
}

void Flywheel::update()
{
    if (motorList != nullptr && motorList->front() != nullptr)
    {
        double currentPosition = motorList->front()->get_position();
        double currentTime = pros::c::millis();

        double positionChange = currentPosition - lastPosition;
        double timeChange = currentTime - lastTime;

        double countsPerSecond = positionChange / (timeChange / 1000.0);
        currentRPM = countsPerSecond * 60.0 / countsPerRevolution;

        setFlywheel(flywheelPID->getControlValue(currentRPM / 60.0));

        lastPosition = currentPosition;
        lastTime = currentTime;
    }
}

void Flywheel::setFlywheel(double power)
{
    for (std::list<pros::Motor*>::iterator iterator = motorList->begin(); 
         iterator != motorList->end(); iterator++)
        (*iterator)->move(power);
}

void Flywheel::setRPM(double RPM)
{
    targetRPM = RPM;
    if (targetRPM > maxRPM)
        targetRPM = maxRPM;
    else if (targetRPM < 0.0)
        targetRPM = 0.0;
    if (flywheelPID != nullptr)
        flywheelPID->setTargetValue(RPM / 60.0);
}

double Flywheel::getRPM()
{
    return currentRPM;
}

double Flywheel::getTargetRPM()
{
    return targetRPM;
}

void Flywheel::setVelocity(double velocity)
{
    double RPM = velocity / (wheelSize * 3.1415);
    setRPM(RPM);
}

double Flywheel::getVelocity()
{
    double RPM = getRPM();
    return RPM * (wheelSize * 3.1415);
}