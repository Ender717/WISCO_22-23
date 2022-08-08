#include "processes/Position.hpp"

// Builder constructor definitions --------------------------------------------
Position::PositionBuilder::PositionBuilder()
{
    x = nullptr;
    y = nullptr;
    theta = nullptr;
    xVelocity = nullptr;
    yVelocity = nullptr;
    thetaVelocity = nullptr;
}

// Builder destructor definitions ---------------------------------------------
Position::PositionBuilder::~PositionBuilder()
{
    if (x != nullptr)
    {
        delete x;
        x = nullptr;
    }
    if (y != nullptr)
    {
        delete y;
        y = nullptr;
    }
    if (theta != nullptr)
    {
        delete theta;
        theta = nullptr;
    }
    if (xVelocity != nullptr)
    {
        delete xVelocity;
        xVelocity = nullptr;
    }
    if (yVelocity != nullptr)
    {
        delete yVelocity;
        yVelocity = nullptr;
    }
    if (thetaVelocity != nullptr)
    {
        delete thetaVelocity;
        thetaVelocity = nullptr;
    }
}

// Builder public method definitions ------------------------------------------
Position::PositionBuilder* Position::PositionBuilder::withX(double x)
{
    if (this->x == nullptr)
        this->x = new double();
    *this->x = x;
    return this;
}

Position::PositionBuilder* Position::PositionBuilder::withY(double y)
{
    if (this->y == nullptr)
        this->y = new double();
    *this->y = y;
    return this;
}

Position::PositionBuilder* Position::PositionBuilder::withTheta(double theta)
{
    if (this->theta == nullptr)
        this->theta = new double();
    *this->theta = theta;
    return this;
}

Position::PositionBuilder* Position::PositionBuilder::withXVelocity(double xVelocity)
{
    if (this->xVelocity == nullptr)
        this->xVelocity = new double();
    *this->xVelocity = xVelocity;
    return this;
}

Position::PositionBuilder* Position::PositionBuilder::withYVelocity(double yVelocity)
{
    if (this->yVelocity == nullptr)
        this->yVelocity = new double();
    *this->yVelocity = yVelocity;
    return this;
}

Position::PositionBuilder* Position::PositionBuilder::withThetaVelocity(double thetaVelocity)
{
    if (this->thetaVelocity == nullptr)
        this->thetaVelocity = new double();
    *this->thetaVelocity = thetaVelocity;
    return this;
}

Position* Position::PositionBuilder::build()
{
    return new Position(this);
}

// Constructor definitions
Position::Position()
{
    x = 0.0;
    y = 0.0;
    theta = 0.0;
    xVelocity = 0.0;
    yVelocity = 0.0;
    thetaVelocity = 0.0;
}

Position::Position(PositionBuilder* builder)
{
    if (builder->x != nullptr)
        this->x = *builder->x;
    else
        this->x = 0.0;

    if (builder->y != nullptr)
        this->y = *builder->y;
    else
        this->y = 0.0;
    
    if (builder->theta != nullptr)
        this->theta = *builder->theta;
    else
        this->theta = 0.0;

    if (builder->xVelocity != nullptr)
        this->xVelocity = *builder->xVelocity;
    else
        this->xVelocity = 0.0;

    if (builder->yVelocity != nullptr)
        this->yVelocity = *builder->yVelocity;
    else
        this->yVelocity = 0.0;
    
    if (builder->thetaVelocity != nullptr)
        this->thetaVelocity = *builder->thetaVelocity;
    else
        this->thetaVelocity = 0.0;
}

// Public method definitions --------------------------------------------------
double Position::getX()
{
    return x;
}

double Position::getY()
{
    return y;
}

double Position::getTheta()
{
    return theta;
}

double Position::getXVelocity()
{
    return xVelocity;
}

double Position::getYVelocity()
{
    return yVelocity;
}

double Position::getThetaVelocity()
{
    return thetaVelocity;
}