// Included libraries
#include "robot/Robot.hpp"
#include "processes/PositionSystem.hpp"

// ROBOTBUILDER CLASS

// Constructor definitions ----------------------------------------------------
Robot::RobotBuilder::RobotBuilder()
{
	positionSystem = nullptr;
	tankDrive = nullptr;
	holoDrive = nullptr;
	catapult = nullptr;
}

// Destructor definitions -----------------------------------------------------
Robot::RobotBuilder::~RobotBuilder()
{
	positionSystem = nullptr;
	tankDrive = nullptr;
	holoDrive = nullptr;
	catapult = nullptr;
}

// Public method definitions --------------------------------------------------
Robot::RobotBuilder* Robot::RobotBuilder::withPositionSystem(PositionSystem* positionSystem)
{
	this->positionSystem = positionSystem;
	return this;
}

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

Robot::RobotBuilder* Robot::RobotBuilder::withCatapult(Catapult* catapult)
{
	this->catapult = catapult;
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
	this->positionSystem = builder->positionSystem;
	this->tankDrive = builder->tankDrive;
	this->holoDrive = builder->holoDrive;
	this->catapult = builder->catapult;
}

// Destructor definitions -----------------------------------------------------
Robot::~Robot()
{
	if (positionSystem != nullptr)
	{
		delete positionSystem;
		positionSystem = nullptr;
	}

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

	if (catapult != nullptr)
	{
		delete catapult;
		catapult = nullptr;
	}
}

// Private method definitions -------------------------------------------------

// Public method definitions --------------------------------------------------
void Robot::initialize()
{
	if (positionSystem != nullptr)
		positionSystem->initialize();
	if (tankDrive != nullptr)
		tankDrive->initialize();
	if (holoDrive != nullptr)
		holoDrive->initialize();
	if (catapult != nullptr)
		catapult->initialize();
}

PositionSystem* Robot::getPositionSystem()
{
	return positionSystem;
}

TankDrive* Robot::getTankDrive()
{
	return tankDrive;
}

HoloDrive* Robot::getHoloDrive()
{
	return holoDrive;
}

Catapult* Robot::getCatapult()
{
	return catapult;
}