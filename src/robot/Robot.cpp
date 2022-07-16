// Included libraries
#include "robot/Robot.hpp"
#include "subsystems/HoloDrive.hpp"

// ROBOTBUILDER CLASS

// Constructor definitions ----------------------------------------------------
Robot::RobotBuilder::RobotBuilder()
{
	holoDrive = nullptr;
}

// Destructor definitions -----------------------------------------------------
Robot::RobotBuilder::~RobotBuilder()
{
	holoDrive = nullptr;
}

// Public method definitions --------------------------------------------------
Robot::RobotBuilder* Robot::RobotBuilder::withHoloDrive(HoloDrive* holoDrive)
{
	this->holoDrive = holoDrive;
	return this;
}

Robot* Robot::RobotBuilder::build()
{
	return new Robot(this);
}

// ROBOT CLASS

// Constructor definitions ----------------------------------------------------
Robot::Robot(RobotBuilder* builder)
{
	this->holoDrive = builder->holoDrive;
}

// Destructor definitions -----------------------------------------------------
Robot::~Robot()
{
	if (holoDrive != nullptr)
	{
		delete holoDrive;
		holoDrive = nullptr;
	}
}

// Private method definitions -------------------------------------------------

// Public method definitions --------------------------------------------------
void Robot::initialize()
{
	if (holoDrive != nullptr)
		holoDrive->initialize();
}

HoloDrive* Robot::getHoloDrive()
{
	return holoDrive;
}