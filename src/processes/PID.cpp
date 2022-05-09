// Included libraries
#include "processes/PID.hpp"

// Constructor definitions ------------------------------------------------
PID::PIDBuilder::PIDBuilder()
{
    kp = nullptr;
    ki = nullptr;
    kd = nullptr;
    min = nullptr;
    max = nullptr;
    integralLimit = nullptr;
    startTarget = nullptr;
}

// Destructor definitions -------------------------------------------------
PID::PIDBuilder::~PIDBuilder()
{
    if (kp != nullptr)
    {
        delete kp;
        kp = nullptr;
    }
    if (ki != nullptr)
    {
        delete ki;
        ki = nullptr;
    }
    if (kd != nullptr)
    {
        delete kd;
        kd = nullptr;
    }
    if (min != nullptr)
    {
        delete min;
        min = nullptr;
    }
    if (max != nullptr)
    {
        delete max;
        max = nullptr;
    }
    if (integralLimit != nullptr)
    {
        delete integralLimit;
        integralLimit = nullptr;
    }
    if (startTarget != nullptr)
    {
        delete startTarget;
        startTarget = nullptr;
    }
}

// Public method definitions ----------------------------------------------
PID::PIDBuilder* PID::PIDBuilder::WithKp(double kp)
{
    if (this->kp == nullptr)
        this->kp = new double;
    *this->kp = kp;
    return this;
}

PID::PIDBuilder* PID::PIDBuilder::WithKi(double ki)
{
    if (this->ki == nullptr)
        this->ki = new double;
    *this->ki = ki;
    return this;
}

PID::PIDBuilder* PID::PIDBuilder::WithKd(double kd)
{
    if (this->kd == nullptr)
        this->kd = new double;
    *this->kd = kd;
    return this;
}

PID::PIDBuilder* PID::PIDBuilder::WithMin(double min)
{
    if (this->min == nullptr)
        this->min = new double;
    *this->min = min;
    return this;
}

PID::PIDBuilder* PID::PIDBuilder::WithMax(double max)
{
    if (this->max == nullptr)
        this->max = new double;
    *this->max = max;
    return this;
}

PID::PIDBuilder* PID::PIDBuilder::WithIntegralLimit(double integralLimit)
{
    if (this->integralLimit == nullptr)
        this->integralLimit = new double;
    *this->integralLimit = integralLimit;
    return this;
}

PID::PIDBuilder* PID::PIDBuilder::WithStartTarget(double startTarget)
{
    if (this->startTarget == nullptr)
        this->startTarget = new double;
    *this->startTarget = startTarget;
    return this;
}

PID* PID::PIDBuilder::Build()
{
    return new PID(this);
}

// Constructor definitions ----------------------------------------------------
PID::PID(PIDBuilder* builder)
{
    // Create the pointers
    kp = new double;
    ki = new double;
    kd = new double;
    min = new double;
    max = new double;
    integralLimit = new double;
    targetValue = new double;
    pastTime = new double;
    iValue = new double;
    pastError = new double;

    // Initialize builder variables
    if (builder->kp != nullptr)
        *this->kp = *builder->kp;
    else
        *this->kp = 0.0;

    if (builder->ki != nullptr)
        *this->ki = *builder->ki;
    else
        *this->ki = 0.0;

    if (builder->kd != nullptr)
        *this->kd = *builder->kd;
    else
        *this->kd = 0.0;

    if (builder->min != nullptr)
        *this->min = *builder->min;
    else
        *this->min = -DBL_MAX;

    if (builder->max != nullptr)
        *this->max = *builder->max;
    else
        *this->max = DBL_MAX;

    if (builder->integralLimit != nullptr)
        *this->integralLimit = *builder->integralLimit;
    else
        *this->integralLimit = DBL_MAX;

    if (builder->startTarget != nullptr)
        *this->targetValue = *builder->startTarget;
    else
        *this->targetValue = 0.0;

    // Initialize other variables
    *pastTime = pros::c::millis();
    *iValue = 0.0;
    *pastError = 0.0;
}

// Destructor definitions -------------------------------------------------
PID::~PID()
{
    if (kp != nullptr)
    {
        delete kp;
        kp = nullptr;
    }
    if (ki != nullptr)
    {
        delete ki;
        ki = nullptr;
    }
    if (kd != nullptr)
    {
        delete kd;
        kd = nullptr;
    }
    if (min != nullptr)
    {
        delete min;
        min = nullptr;
    }
    if (max != nullptr)
    {
        delete max;
        max = nullptr;
    }
    if (integralLimit != nullptr)
    {
        delete integralLimit;
        integralLimit = nullptr;
    }
    if (targetValue != nullptr)
    {
        delete targetValue;
        targetValue = nullptr;
    }
    if (pastTime != nullptr)
    {
        delete pastTime;
        pastTime = nullptr;
    }
    if (iValue != nullptr)
    {
        delete iValue;
        iValue = nullptr;
    }
    if (pastError != nullptr)
    {
        delete pastError;
        pastError = nullptr;
    }
}

// Public methods -------------------------------------------------------------
double PID::GetControlValue(double currentValue)
{
    // Calculate the current error
    double error = *targetValue - currentValue;

    // Calculate the loop time
    double currentTime = pros::c::millis();
    double loopTime = (currentTime - *pastTime) / 1000;

    // Set the proportional control value
    double pValue = error;

    // Set the integral control value
    if (pValue > *min && pValue < *max)
        *iValue += error * loopTime;
    if (fabs(*iValue) > *integralLimit)
        *iValue = (*iValue / fabs(*iValue)) * *integralLimit;

    // Set the derivative control value
    double dValue = (error - *pastError) / loopTime;

    // Calculate the control value
    double rawValue = (*kp * pValue) + (*ki * *iValue) + (*kd * dValue);
    double satValue = rawValue;

    // Saturate the control value
    if (satValue < *min)
        satValue = *min;
    else if (satValue > *max)
        satValue = *max;

    // Update the stored previous values
    *pastError = error;
    *pastTime = currentTime;

    // Return the result
    return satValue;
}

void PID::SetTargetValue(double targetValue)
{
    *this->targetValue = targetValue;
}