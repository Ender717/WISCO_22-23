#include "processes/PositionSystem.hpp"

// Constructor Definitions ----------------------------------------------------
PositionSystem::PositionSystemBuilder::PositionSystemBuilder()
{
    linearTrackingSensor = nullptr;
    strafeTrackingSensor = nullptr;
    inertialSensor = nullptr;
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
    *this->startTheta = (startAngle * 3.1415 / 180.0);
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
    double inchesPerRotation = WHEEL_SIZE * PI;
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
    double linearDistance = countsToInches(linearTrackingSensor->get_position()) - lastLinear;
    double strafeDistance = countsToInches(strafeTrackingSensor->get_position()) - lastStrafe;

    // Calculate the change in theta
    currentTheta = inertialSensor->get_rotation() + resetTheta;
    thetaVelocity = currentTheta - lastTheta;

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
    double averageTheta = lastTheta + (thetaVelocity / 2.0);

    // Calculate the global offset
    xVelocity = sidewaysDistance * -sin(averageTheta) + forwardDistance * cos(averageTheta);
    yVelocity = sidewaysDistance * cos(averageTheta) + forwardDistance * sin(averageTheta);

    // Calculate the new absolute PositionSystem
    currentX += xVelocity;
    currentY += yVelocity;

    // Update the stored previous values
    lastLinear += linearDistance;
    lastStrafe += strafeDistance;
    lastTheta = currentTheta;

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

Position PositionSystem::getPosition()
{
    database.startReading();
    Position::PositionBuilder* builder = new Position::PositionBuilder();
    Position position = builder->
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