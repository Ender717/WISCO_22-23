// Included libraries
#include "robot/Robot.hpp"

// ROBOTBUILDER CLASS

// Constructor definitions ----------------------------------------------------
Robot::RobotBuilder::RobotBuilder()
{
	tankDrive = nullptr;
	holoDrive = nullptr;
}

// Destructor definitions -----------------------------------------------------
Robot::RobotBuilder::~RobotBuilder()
{
	tankDrive = nullptr;
	holoDrive = nullptr;
}

// Public method definitions --------------------------------------------------
Robot::RobotBuilder* Robot::RobotBuilder::withTankDrive(TankDrive* tankDrive)
{
	this->tankDrive = tankDrive;
	return this;
}

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
	this->tankDrive = builder->tankDrive;
	this->holoDrive = builder->holoDrive;
}

// Destructor definitions -----------------------------------------------------
Robot::~Robot()
{
	if (tankDrive != nullptr)
	{
		delete tankDrive;
		tankDrive = nullptr;
	}

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
	if (tankDrive != nullptr)
		tankDrive->initialize();
	if (holoDrive != nullptr)
		holoDrive->initialize();
}

TankDrive* Robot::getTankDrive()
{
	return tankDrive;
}

HoloDrive* Robot::getHoloDrive()
{
	return holoDrive;
}