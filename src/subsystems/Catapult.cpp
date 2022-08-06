// Defined header
#include "subsystems/Catapult.hpp"

// BUILDER CLASS

// Constructor definitions ----------------------------------------------------
Catapult::CatapultBuilder::CatapultBuilder()
{
    motorList = nullptr;
    catapultPID = nullptr;
    countsPerCycle = nullptr;
    loadedPosition = nullptr;
}

// Destructor definitions -----------------------------------------------------
Catapult::CatapultBuilder::~CatapultBuilder()
{
    // Delete the motor list but not the motors
    if (motorList != nullptr)
    {
        delete motorList;
        motorList = nullptr;
    }

    // Delete the PID controller
    if (catapultPID != nullptr)
    {
        delete catapultPID;
        catapultPID = nullptr;
    }

    // Delete the counts per cycle
    if (countsPerCycle != nullptr)
    {
        delete countsPerCycle;
        countsPerCycle = nullptr;
    }

    // Delete the loaded position
    if (loadedPosition != nullptr)
    {
        delete loadedPosition;
        loadedPosition = nullptr;
    }
}

// Public method definitions --------------------------------------------------
Catapult::CatapultBuilder* Catapult::CatapultBuilder::withMotor(pros::Motor* motor)
{
    if (motorList == nullptr)
        motorList = new std::list<pros::Motor*>();
    motorList->push_back(motor);
    return this;
}

Catapult::CatapultBuilder* Catapult::CatapultBuilder::withPID(PID* pid)
{
    catapultPID = pid;
    return this;
}

Catapult::CatapultBuilder* Catapult::CatapultBuilder::withCountsPerCycle(double countsPerCycle)
{
    if (this->countsPerCycle == nullptr)
        this->countsPerCycle = new double;
    *this->countsPerCycle = countsPerCycle;
    return this;
}

Catapult::CatapultBuilder* Catapult::CatapultBuilder::withLoadedPosition(double loadedPosition)
{
    if (this->loadedPosition == nullptr)
        this->loadedPosition = new double;
    *this->loadedPosition = loadedPosition;
    return this;
}

Catapult* Catapult::CatapultBuilder::build()
{
    return new Catapult(this);
}

// CATAPULT CLASS

// Constructor definitions ----------------------------------------------------
Catapult::Catapult(CatapultBuilder* builder)
{
    // Create the motor list
    motorList = new std::list<pros::Motor*>();

    // Set the motors
    if (builder->motorList != nullptr)
        for (std::list<pros::Motor*>::iterator iterator = builder->motorList->begin(); 
            iterator != builder->motorList->end(); iterator++)
            this->motorList->push_back(*iterator);

    // Set the PID controller
    if (builder->catapultPID != nullptr)
        this->catapultPID = new PID(*builder->catapultPID);

    // Set the counts per cycle
    if (builder->countsPerCycle != nullptr)
        this->countsPerCycle = *builder->countsPerCycle;
    else
        this->countsPerCycle = DEFAULT_COUNTS_PER_CYCLE;

    // Set the loaded position
    if (builder->loadedPosition != nullptr)
        this->loadedPosition = *builder->loadedPosition;
    else
        this->loadedPosition = DEFAULT_LOADED_POSITION;
}

// Destructor definitions -----------------------------------------------------
Catapult::~Catapult()
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
    if (catapultPID != nullptr)
    {
        delete catapultPID;
        catapultPID = nullptr;
    }
}

// Public method definitions --------------------------------------------------
void Catapult::initialize()
{
    // Set the positions to 0
    for (std::list<pros::Motor*>::iterator iterator = motorList->begin(); 
        iterator != motorList->end(); iterator++)
    {
        (*iterator)->tare_position();
        (*iterator)->set_brake_mode(E_MOTOR_BRAKE_BRAKE);
    }
    if (catapultPID != nullptr)
        catapultPID->setTargetValue(loadedPosition);
    currentPosition = loadedPosition;
}

void Catapult::setCatapult(double power)
{
    for (std::list<pros::Motor*>::iterator iterator = motorList->begin(); 
         iterator != motorList->end(); iterator++)
        (*iterator)->move(power);
}

void Catapult::load()
{
    currentPosition += countsPerCycle;
    if (catapultPID != nullptr)
        catapultPID->setTargetValue(currentPosition);
}

void Catapult::holdPosition()
{
    if(motorList != nullptr)
    {
        if (catapultPID != nullptr)
            setCatapult(catapultPID->getControlValue(getPosition()));
        else
            setCatapult(0.0);
    }
}

double Catapult::getPosition()
{
    double position = 0.0;
    if (motorList != nullptr)
        if (motorList->front() != nullptr)
            position = motorList->front()->get_position();
    return position;
}

bool Catapult::isLoaded()
{
    return (std::abs(getPosition() - currentPosition) < LOAD_ERROR_MARGIN);
}