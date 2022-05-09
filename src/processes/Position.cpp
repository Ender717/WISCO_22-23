#include "processes/Position.hpp"

// Constructor Definitions ----------------------------------------------------
Position::PositionBuilder::PositionBuilder()
{
    leftTrackingDistance = nullptr;
    rightTrackingDistance = nullptr;
    strafeTrackingDistance = nullptr;
    startX = nullptr;
    startY = nullptr;
    startTheta = nullptr;
}

// Destructor Definitions -----------------------------------------------------
Position::PositionBuilder::~PositionBuilder()
{
    if (leftTrackingDistance != nullptr)
    {
        delete leftTrackingDistance;
        leftTrackingDistance = nullptr;
    }
    if (rightTrackingDistance != nullptr)
    {
        delete rightTrackingDistance;
        rightTrackingDistance = nullptr;
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
Position::PositionBuilder* Position::PositionBuilder::WithLeftDistance(double leftTrackingDistance)
{
    if (this->leftTrackingDistance == nullptr)
        this->leftTrackingDistance = new double;
    *this->leftTrackingDistance = leftTrackingDistance;
    return this;
}

Position::PositionBuilder* Position::PositionBuilder::WithRightDistance(double rightTrackingDistance)
{
    if (this->rightTrackingDistance == nullptr)
        this->rightTrackingDistance = new double;
    *this->rightTrackingDistance = rightTrackingDistance;
    return this;
}

Position::PositionBuilder* Position::PositionBuilder::WithStrafeDistance(double strafeTrackingDistance)
{
    if (this->strafeTrackingDistance == nullptr)
        this->strafeTrackingDistance = new double;
    *this->strafeTrackingDistance = strafeTrackingDistance;
    return this;
}

Position::PositionBuilder* Position::PositionBuilder::WithStartX(double startX)
{
    if (this->startX == nullptr)
        this->startX = new double;
    *this->startX = startX;
    return this;
}

Position::PositionBuilder* Position::PositionBuilder::WithStartY(double startY)
{
    if (this->startY == nullptr)
        this->startY = new double;
    *this->startY = startY;
    return this;
}

Position::PositionBuilder* Position::PositionBuilder::WithStartAngle(double startAngle)
{
    if (this->startTheta == nullptr)
        this->startTheta = new double;
    *this->startTheta = (startAngle * 3.1415 / 180.0);
    return this;
}

Position* Position::PositionBuilder::Build()
{
    return new Position(this);
}

// Constructor Definitions ----------------------------------------------------
Position::Position(PositionBuilder* builder)
{
    // Create the pointers
    leftTrackingDistance = new double;
    rightTrackingDistance = new double;
    strafeTrackingDistance = new double;
    currentX = new double;
    currentY = new double;
    currentTheta = new double;
    lastLeft = new double;
    lastRight = new double;
    lastStrafe = new double;
    lastTheta = new double;
    resetX = new double;
    resetY = new double;
    resetTheta = new double;

    // Initialize the builder variables
    if (builder->leftTrackingDistance != nullptr)
        *this->leftTrackingDistance = *builder->leftTrackingDistance;
    else
        *this->leftTrackingDistance = 0.0;
    
    if (builder->rightTrackingDistance != nullptr)
        *this->rightTrackingDistance = *builder->rightTrackingDistance;
    else
        *this->rightTrackingDistance = 0.0;

    if (builder->strafeTrackingDistance != nullptr)
        *this->strafeTrackingDistance = *builder->strafeTrackingDistance;
    else
        *this->strafeTrackingDistance = 0.0;

    if (builder->startX != nullptr)
        *this->currentX = *builder->startX;
    else
        *this->currentX = 0.0;

    if (builder->startY != nullptr)
        *this->currentY = *builder->startY;
    else
        *this->currentY = 0.0;

    if (builder->startTheta != nullptr)
        *this->currentTheta = *builder->startTheta;
    else
        *this->currentTheta = 0.0;

    // Initialize other variables
    *lastLeft = 0.0;
    *lastRight = 0.0;
    *lastStrafe = 0.0;
    *lastTheta = 0.0;
    *resetX = *currentX;
    *resetY = *currentY;
    *resetTheta = *currentTheta;
}

// Destructor Definitions -----------------------------------------------------
Position::~Position()
{
    if (leftTrackingDistance != nullptr)
    {
        delete leftTrackingDistance;
        leftTrackingDistance = nullptr;
    }
    if (rightTrackingDistance != nullptr)
    {
        delete rightTrackingDistance;
        rightTrackingDistance = nullptr;
    }
    if (strafeTrackingDistance != nullptr)
    {
        delete strafeTrackingDistance;
        strafeTrackingDistance = nullptr;
    }
    if (currentX != nullptr)
    {
        delete currentX;
        currentX = nullptr;
    }
    if (currentY != nullptr)
    {
        delete currentY;
        currentY = nullptr;
    }
    if (currentTheta != nullptr)
    {
        delete currentTheta;
        currentTheta = nullptr;
    }
    if (lastLeft != nullptr)
    {
        delete lastLeft;
        lastLeft = nullptr;
    }
    if (lastRight != nullptr)
    {
        delete lastRight;
        lastRight = nullptr;
    }
    if (lastStrafe != nullptr)
    {
        delete lastStrafe;
        lastStrafe = nullptr;
    }
    if (lastTheta != nullptr)
    {
        delete lastTheta;
        lastTheta = nullptr;
    }
    if (resetX != nullptr)
    {
        delete resetX;
        resetX = nullptr;
    }
    if (resetY != nullptr)
    {
        delete resetY;
        resetY = nullptr;
    }
    if (resetTheta != nullptr)
    {
        delete resetTheta;
        resetTheta = nullptr;
    }
}

// Private Method Definitions -------------------------------------------------
void Position::SetResetPosition()
{
    *lastLeft = 0.0;
    *lastRight = 0.0;
    *lastStrafe = 0.0;
    *lastTheta = *currentTheta;
    *resetX = *currentX;
    *resetY = *currentY;
    *resetTheta = *currentTheta;
}

// Public Method Definitions --------------------------------------------------
void Position::UpdatePosition(double leftValue, double rightValue, double strafeValue, double newTheta)
{
    // Calculate the distance moved by each wheel since the last cycle
    double leftDistance = leftValue - *lastLeft;
    double rightDistance = rightValue - *lastRight;
    double strafeDistance = strafeValue - *lastStrafe;

    // Calculate absolute theta
    double totalLeft = leftValue;
    double totalRight = rightValue;
    //*currentTheta = ((totalRight - totalLeft) / (*leftTrackingDistance + *rightTrackingDistance)) + *resetTheta;
    *currentTheta = newTheta;

    // Calculate the change in theta
    double thetaChange = *currentTheta - *lastTheta;

    // Calculate the local offset
    double forwardDistance = 0.0;
    double sidewaysDistance = 0.0;
    if (thetaChange == 0.0)
    {
        sidewaysDistance = strafeDistance;
        forwardDistance = rightDistance;
    }
    else
    {
        sidewaysDistance = (2.0 * sin(thetaChange / 2.0)) * ((strafeDistance / thetaChange) + *strafeTrackingDistance);
        forwardDistance = (2.0 * sin(thetaChange / 2.0)) * ((leftDistance / thetaChange) + *leftTrackingDistance);
    }

    // Calculate the average orientation
    double averageTheta = *lastTheta + (thetaChange / 2.0);

    // Calculate the global offset
    double xChange = sidewaysDistance * -sin(averageTheta) + forwardDistance * cos(averageTheta);
    double yChange = sidewaysDistance * cos(averageTheta) + forwardDistance * sin(averageTheta);

    // Calculate the new absolute position
    *currentX += xChange;
    *currentY += yChange;

    // Update the stored previous values
    *lastLeft = leftValue;
    *lastRight = rightValue;
    *lastStrafe = strafeValue;
    *lastTheta = *currentTheta;
}

void Position::SetX(double x)
{
    *currentX = x;
    SetResetPosition();
}

void Position::SetY(double y)
{
    *currentY = y;
    SetResetPosition();
}

void Position::SetAngle(double angle)
{
    *currentTheta = (angle * 3.1415 / 180.0);
    SetResetPosition();
}

void Position::SetPosition(double x, double y, double theta)
{
    *currentX = x;
    *currentY = y;
    *currentTheta = theta;
    SetResetPosition();
}

double Position::GetX() const
{
    return *currentX;
}

double Position::GetY() const
{
    return *currentY;
}

double Position::GetTheta() const
{
    return *currentTheta;
}

double Position::GetAngle() const
{
    return (*currentTheta * 180.0 / 3.1415);
}