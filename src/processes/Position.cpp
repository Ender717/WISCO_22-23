#include "processes/Position.hpp"

// Constructor Definitions ----------------------------------------------------
Position::PositionBuilder::PositionBuilder()
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
Position::PositionBuilder::~PositionBuilder()
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
Position::PositionBuilder* Position::PositionBuilder::withLinearSensor(pros::Rotation *linearTrackingSensor)
{
    this->linearTrackingSensor = linearTrackingSensor;
    return this;
}

Position::PositionBuilder* Position::PositionBuilder::withStrafeSensor(pros::Rotation *strafeTrackingSensor)
{
    this->strafeTrackingSensor = strafeTrackingSensor;
    return this;
}

Position::PositionBuilder* Position::PositionBuilder::withInertialSensor(pros::Imu *inertialSensor)
{
    this->inertialSensor = inertialSensor;
    return this;
}

Position::PositionBuilder* Position::PositionBuilder::withLinearDistance(double linearTrackingDistance)
{
    if (this->linearTrackingDistance == nullptr)
        this->linearTrackingDistance = new double;
    *this->linearTrackingDistance = linearTrackingDistance;
    return this;
}

Position::PositionBuilder* Position::PositionBuilder::withStrafeDistance(double strafeTrackingDistance)
{
    if (this->strafeTrackingDistance == nullptr)
        this->strafeTrackingDistance = new double;
    *this->strafeTrackingDistance = strafeTrackingDistance;
    return this;
}

Position::PositionBuilder* Position::PositionBuilder::withStartX(double startX)
{
    if (this->startX == nullptr)
        this->startX = new double;
    *this->startX = startX;
    return this;
}

Position::PositionBuilder* Position::PositionBuilder::withStartY(double startY)
{
    if (this->startY == nullptr)
        this->startY = new double;
    *this->startY = startY;
    return this;
}

Position::PositionBuilder* Position::PositionBuilder::withStartAngle(double startAngle)
{
    if (this->startTheta == nullptr)
        this->startTheta = new double;
    *this->startTheta = (startAngle * 3.1415 / 180.0);
    return this;
}

Position* Position::PositionBuilder::build()
{
    return new Position(this);
}

// Constructor Definitions ----------------------------------------------------
Position::Position(PositionBuilder* builder)
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
Position::~Position()
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
void Position::setResetPosition()
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
void Position::updatePosition()
{
    // Calculate the distance moved by each wheel since the last cycle
    double linearDistance = linearTrackingSensor->get_position() - lastLinear;
    double strafeDistance = strafeTrackingSensor->get_position() - lastStrafe;

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

    // Calculate the new absolute position
    currentX += xVelocity;
    currentY += yVelocity;

    // Update the stored previous values
    lastLinear += linearDistance;
    lastStrafe += strafeDistance;
    lastTheta = currentTheta;
}

void Position::setPosition(double x, double y, double theta)
{
    currentX = x;
    currentY = y;
    currentTheta = theta;
    setResetPosition();
}

double Position::getPositionX() const
{
    return currentX;
}

double Position::getPositionY() const
{
    return currentY;
}

double Position::getPositionTheta() const
{
    return currentTheta;
}

double Position::getVelocityX() const
{
    return xVelocity;
}

double Position::getVelocityY() const
{
    return yVelocity;
}

double Position::getVelocityTheta() const
{
    return thetaVelocity;
}