// Included libraries
#include "robot/Robot.hpp"

// ROBOTBUILDER CLASS

// Constructor definitions ----------------------------------------------------
Robot::RobotBuilder::RobotBuilder()
{
	configuration = nullptr;
}

// Destructor definitions -----------------------------------------------------
Robot::RobotBuilder::~RobotBuilder()
{
	if (configuration != nullptr)
	{
		delete configuration;
		configuration = nullptr;
	}
}

// Public method definitions --------------------------------------------------
Robot::RobotBuilder* Robot::RobotBuilder::withConfiguration(RobotConfigs configuration)
{
	if (this->configuration == nullptr)
		this->configuration = new RobotConfigs();
	*this->configuration = configuration;
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
	this->configuration = *builder->configuration;
}

Robot::~Robot()
{

}

// Private method definitions -------------------------------------------------

// Public method definitions --------------------------------------------------
void Robot::initialize()
{

}

void Robot::robotControl(pros::Controller& master)
{

}