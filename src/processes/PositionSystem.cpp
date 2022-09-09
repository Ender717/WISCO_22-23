#include "processes/PositionSystem.hpp"

// Constructor Definitions ----------------------------------------------------
PositionSystem::PositionSystemBuilder::PositionSystemBuilder()
{
    linearTrackingSensor = nullptr;
    strafeTrackingSensor = nullptr;
    inertialSensor = nullptr;
    linearTrackingMultiplier = nullptr;
    strafeTrackingMultiplier = nullptr;
    inertialMultiplier = nullptr;
    wheelSize = nullptr;
    linearTrackingDistance = nullptr;
    strafeTrackingDistance = nullptr;
    startX = nullptr;
    startY = nullptr;
    startTheta = nullptr;
}

// Destructor Definitions -----------------------------------------------------
PositionSystem::PositionSystemBuilder::~PositionSystemBuilder()
{
    linearTrackingSensor = nullptr;
    strafeTrackingSensor = nullptr;
    inertialSensor = nullptr;
    if (linearTrackingMultiplier != nullptr)
    {
        delete linearTrackingMultiplier;
        linearTrackingMultiplier = nullptr;
    }
    if (strafeTrackingMultiplier != nullptr)
    {
        delete strafeTrackingMultiplier;
        strafeTrackingMultiplier = nullptr;
    }
    if (inertialMultiplier != nullptr)
    {
        delete inertialMultiplier;
        inertialMultiplier = nullptr;
    }
    if (wheelSize != nullptr)
    {
        delete wheelSize;
        wheelSize = nullptr;
    }
    if (linearTrackingDistance != nullptr)
    {
        delete linearTrackingDistance;
        linearTrackingDistance = nullptr;
    }
    if (strafeTrackingDistance != nullptr)
    {
        delete strafeTrackingDistance;
        strafeTrackingDistance = nullptr;
    }
    if (startX != nullptr)
    {
        delete startX;
        startX = nullptr;
    }
    if (startY != nullptr)
    {
        delete startY;
        startY = nullptr;
    }
    if (startTheta != nullptr)
    {
        delete startTheta;
        startTheta = nullptr;
    }
}

// Public Method Definitions --------------------------------------------------
PositionSystem::PositionSystemBuilder* PositionSystem::PositionSystemBuilder::withLinearSensor(pros::Rotation *linearTrackingSensor)
{
    this->linearTrackingSensor = linearTrackingSensor;
    return this;
}

PositionSystem::PositionSystemBuilder* PositionSystem::PositionSystemBuilder::withStrafeSensor(pros::Rotation *strafeTrackingSensor)
{
    this->strafeTrackingSensor = strafeTrackingSensor;
    return this;
}

PositionSystem::PositionSystemBuilder* PositionSystem::PositionSystemBuilder::withInertialSensor(pros::Imu *inertialSensor)
{
    this->inertialSensor = inertialSensor;
    return this;
}

PositionSystem::PositionSystemBuilder* PositionSystem::PositionSystemBuilder::withLinearTrackingMultiplier(double linearTrackingMultiplier)
{
    if (this->linearTrackingMultiplier == nullptr)
        this->linearTrackingMultiplier = new double;
    *this->linearTrackingMultiplier = linearTrackingMultiplier;
    return this;
}

PositionSystem::PositionSystemBuilder* PositionSystem::PositionSystemBuilder::withStrafeTrackingMultiplier(double strafeTrackingMultiplier)
{
    if (this->strafeTrackingMultiplier == nullptr)
        this->strafeTrackingMultiplier = new double;
    *this->strafeTrackingMultiplier = strafeTrackingMultiplier;
    return this;
}

PositionSystem::PositionSystemBuilder* PositionSystem::PositionSystemBuilder::withInertialMultiplier(double inertialMultiplier)
{
    if (this->inertialMultiplier == nullptr)
        this->inertialMultiplier = new double;
    *this->inertialMultiplier = inertialMultiplier;
    return this;
}

PositionSystem::PositionSystemBuilder* PositionSystem::PositionSystemBuilder::withWheelSize(double wheelSize)
{
    if (this->wheelSize == nullptr)
        this->wheelSize = new double;
    *this->wheelSize = wheelSize;
    return this;
}

PositionSystem::PositionSystemBuilder* PositionSystem::PositionSystemBuilder::withLinearDistance(double linearTrackingDistance)
{
    if (this->linearTrackingDistance == nullptr)
        this->linearTrackingDistance = new double;
    *this->linearTrackingDistance = linearTrackingDistance;
    return this;
}

PositionSystem::PositionSystemBuilder* PositionSystem::PositionSystemBuilder::withStrafeDistance(double strafeTrackingDistance)
{
    if (this->strafeTrackingDistance == nullptr)
        this->strafeTrackingDistance = new double;
    *this->strafeTrackingDistance = strafeTrackingDistance;
    return this;
}

PositionSystem::PositionSystemBuilder* PositionSystem::PositionSystemBuilder::withStartX(double startX)
{
    if (this->startX == nullptr)
        this->startX = new double;
    *this->startX = startX;
    return this;
}

PositionSystem::PositionSystemBuilder* PositionSystem::PositionSystemBuilder::withStartY(double startY)
{
    if (this->startY == nullptr)
        this->startY = new double;
    *this->startY = startY;
    return this;
}

PositionSystem::PositionSystemBuilder* PositionSystem::PositionSystemBuilder::withStartAngle(double startAngle)
{
    if (this->startTheta == nullptr)
        this->startTheta = new double;
    *this->startTheta = (startAngle * M_PI / 180.0);
    return this;
}

PositionSystem* PositionSystem::PositionSystemBuilder::build()
{
    return new PositionSystem(this);
}

// Constructor Definitions ----------------------------------------------------
PositionSystem::PositionSystem(PositionSystemBuilder* builder)
{
    // Initialize the builder variables
    this->linearTrackingSensor = builder->linearTrackingSensor;
    this->strafeTrackingSensor = builder->strafeTrackingSensor;
    this->inertialSensor = builder->inertialSensor;

    if (builder->linearTrackingMultiplier != nullptr)
        this->linearTrackingMultiplier = *builder->linearTrackingMultiplier;
    else
        this->linearTrackingMultiplier = 1.0;

    if (builder->strafeTrackingMultiplier != nullptr)
        this->strafeTrackingMultiplier = *builder->strafeTrackingMultiplier;
    else
        this->strafeTrackingMultiplier = 1.0;

    if (builder->inertialMultiplier != nullptr)
        this->inertialMultiplier = *builder->inertialMultiplier;
    else
        this->inertialMultiplier = 1.0;

    if (builder->wheelSize != nullptr)
        this->wheelSize = *builder->wheelSize;
    else
        this->wheelSize = DEFAULT_WHEEL_SIZE;

    if (builder->linearTrackingDistance != nullptr)
        this->linearTrackingDistance = *builder->linearTrackingDistance;
    else
        this->linearTrackingDistance = 0.0;

    if (builder->strafeTrackingDistance != nullptr)
        this->strafeTrackingDistance = *builder->strafeTrackingDistance;
    else
        this->strafeTrackingDistance = 0.0;

    if (builder->startX != nullptr)
        this->resetX = *builder->startX;
    else
        this->resetX = 0.0;

    if (builder->startY != nullptr)
        this->resetY = *builder->startY;
    else
        this->resetY = 0.0;

    if (builder->startTheta != nullptr)
        this->resetTheta = *builder->startTheta;
    else
        this->resetTheta = 0.0;

    // Initialize other variables
    lastLinear = 0.0;
    lastStrafe = 0.0;
    lastTheta = resetTheta;
    currentX = resetX;
    currentY = resetY;
    currentTheta = resetTheta;
}

// Destructor Definitions -----------------------------------------------------
PositionSystem::~PositionSystem()
{
    if (linearTrackingSensor != nullptr)
    {
        delete linearTrackingSensor;
        linearTrackingSensor = nullptr;
    }
    if (strafeTrackingSensor != nullptr)
    {
        delete strafeTrackingSensor;
        strafeTrackingSensor = nullptr;
    }
    if (inertialSensor != nullptr)
    {
        delete inertialSensor;
        inertialSensor = nullptr;
    }
}

// Private Method Definitions -------------------------------------------------
double PositionSystem::countsToInches(double counts)
{
    double rotations = counts / COUNTS_PER_ROTATION;
    double inchesPerRotation = wheelSize * M_PI;
    return rotations * inchesPerRotation;
}

void PositionSystem::setResetPosition()
{
    linearTrackingSensor->set_position(0.0);
    strafeTrackingSensor->set_position(0.0);
    inertialSensor->set_rotation(0.0);

    lastLinear = 0.0;
    lastStrafe = 0.0;
    resetX = currentX;
    resetY = currentY;
    resetTheta = currentTheta;
}

// Public Method Definitions --------------------------------------------------
void PositionSystem::initialize()
{
    // Initialize the tracking wheels
    linearTrackingSensor->set_position(0.0);
    linearTrackingSensor->set_reversed(true);
    strafeTrackingSensor->set_position(0.0);

    // Initialize the inertial sensor
    inertialSensor->reset();
    while(inertialSensor->is_calibrating())
        pros::delay(10);
    pros::delay(500);
    inertialSensor->set_rotation(0.0);
}

void PositionSystem::updatePosition()
{
    // Get write permissions from the database manager
    database.startWriting();

    // Calculate the distance moved by each wheel since the last cycle
    double linearDistance = countsToInches(linearTrackingSensor->get_position() * linearTrackingMultiplier) - lastLinear;
    double strafeDistance = countsToInches(strafeTrackingSensor->get_position() * strafeTrackingMultiplier) - lastStrafe;

    // Calculate the change in theta
    double uncappedTheta = -(inertialSensor->get_rotation() * inertialMultiplier * M_PI / 180.0);
    double cappedTheta = uncappedTheta;
    double cappedLastTheta = lastTheta;
    while (cappedTheta < -M_PI)
    {
        cappedTheta += 2 * M_PI;
        cappedLastTheta += 2 * M_PI;
    }
    while (cappedTheta > M_PI)
    {
        cappedTheta -= 2 * M_PI;
        cappedLastTheta -= 2 * M_PI;
    }
    currentTheta = cappedTheta;
    thetaVelocity = currentTheta - cappedLastTheta;

    // Calculate the local offset
    double forwardDistance = 0.0;
    double sidewaysDistance = 0.0;
    if (thetaVelocity == 0.0)
    {
        sidewaysDistance = strafeDistance;
        forwardDistance = linearDistance;
    }
    else
    {
        sidewaysDistance = (2.0 * sin(thetaVelocity / 2.0)) * ((strafeDistance / thetaVelocity) + strafeTrackingDistance);
        forwardDistance = (2.0 * sin(thetaVelocity / 2.0)) * ((linearDistance / thetaVelocity) + linearTrackingDistance);
    }

    // Calculate the average orientation
    double averageTheta = cappedLastTheta + (thetaVelocity / 2.0);

    // Calculate the global offset
    xVelocity = sidewaysDistance * -sin(averageTheta) + forwardDistance * cos(averageTheta);
    yVelocity = sidewaysDistance * cos(averageTheta) + forwardDistance * sin(averageTheta);

    // Calculate the new absolute PositionSystem
    currentX += xVelocity;
    currentY += yVelocity;

    // Update the stored previous values
    lastLinear += linearDistance;
    lastStrafe += strafeDistance;
    lastTheta = uncappedTheta;

    // Release write PositionSystems from the database manager
    database.stopWriting();
}

void PositionSystem::setPosition(double x, double y, double theta)
{
    database.startWriting();
    currentX = x;
    currentY = y;
    currentTheta = theta;
    setResetPosition();
    database.stopWriting();
}

Position* PositionSystem::getPosition()
{
    database.startReading();
    Position::PositionBuilder* builder = new Position::PositionBuilder();
    Position* position = builder->
        withX(currentX)->
        withY(currentY)->
        withTheta(currentTheta)->
        withXVelocity(xVelocity)->
        withYVelocity(yVelocity)->
        withThetaVelocity(thetaVelocity)->
        build();
    database.stopReading();
    return position;
}