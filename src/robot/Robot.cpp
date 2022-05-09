// Included libraries
#include "robot/Robot.hpp"

// ROBOTBUILDER CLASS

// Constructor definitions ----------------------------------------------------
Robot::RobotBuilder::RobotBuilder()
{
	configuration = nullptr;
	carrier = nullptr;
	claw = nullptr;
	drive = nullptr;
	intake = nullptr;
	lift = nullptr;
}

// Destructor definitions -----------------------------------------------------
Robot::RobotBuilder::~RobotBuilder()
{
	configuration = nullptr;
	carrier = nullptr;
	claw = nullptr;
	drive = nullptr;
	intake = nullptr;
	lift = nullptr;
}

// Public method definitions --------------------------------------------------
Robot::RobotBuilder* Robot::RobotBuilder::WithConfiguration(RobotConfigs *configuration)
{
	this->configuration = configuration;
	return this;
}

Robot::RobotBuilder* Robot::RobotBuilder::WithCarrier(Carrier* carrier)
{
	this->carrier = carrier;
	return this;
}

Robot::RobotBuilder* Robot::RobotBuilder::WithClaw(Claw* claw)
{
	this->claw = claw;
	return this;
}

Robot::RobotBuilder* Robot::RobotBuilder::WithDrive(Drive* drive)
{
	this->drive = drive;
	return this;
}

Robot::RobotBuilder* Robot::RobotBuilder::WithIntake(Intake* intake)
{
	this->intake = intake;
	return this;
}

Robot::RobotBuilder* Robot::RobotBuilder::WithLift(Lift* lift)
{
	this->lift = lift;
	return this;
}

Robot* Robot::RobotBuilder::Build()
{
	return new Robot(this);
}

// ROBOT CLASS

// Constructor definitions ----------------------------------------------------
Robot::Robot(RobotBuilder* builder)
{
	this->configuration = builder->configuration;
	this->carrier = builder->carrier;
	this->claw = builder->claw;
	this->drive = builder->drive;
	this->intake = builder->intake;
	this->lift = builder->lift;
}

Robot::~Robot()
{
	if (configuration != nullptr)
	{
		delete configuration;
		configuration = nullptr;
	}
	if (carrier != nullptr)
	{
		delete carrier;
		carrier = nullptr;
	}
	if (claw != nullptr)
	{
		delete claw;
		claw = nullptr;
	}
	if (drive != nullptr)
	{
		delete drive;
		drive = nullptr;
	}
	if (intake != nullptr)
	{
		delete intake;
		intake = nullptr;
	}
	if (lift != nullptr)
	{
		delete lift;
		lift = nullptr;
	}
}

// Private method definitions -------------------------------------------------
void Robot::UpdateCarrier(pros::Controller& master)
{
	if (master.get_digital_new_press(E_CONTROLLER_DIGITAL_RIGHT))
		carrier->TogglePosition();
	carrier->HoldPosition();
}

void Robot::UpdateClaw(pros::Controller& master)
{
	if (*configuration == RobotConfigs::BLUE)
	{
		if (master.get_digital_new_press(E_CONTROLLER_DIGITAL_B))
			claw->TogglePosition();
	}
	else if (*configuration == RobotConfigs::ORANGE)
	{
		if (master.get_digital_new_press(E_CONTROLLER_DIGITAL_Y))
			claw->TogglePosition();
	}
	claw->HoldPosition();
}

void Robot::UpdateDrive(pros::Controller& master)
{
	// Arcade drive mode
	double leftDrivePower = 0.0;
	double rightDrivePower = 0.0;

	if (*configuration == RobotConfigs::BLUE)
	{
		leftDrivePower = master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y) 
			+ master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X);
		rightDrivePower = master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y)
			- master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X);
	}
	else if (*configuration == RobotConfigs::ORANGE)
	{
		double leftDrivePower = master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
		double rightDrivePower = master.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);
	}

	// Update
	drive->SetDrive(leftDrivePower, rightDrivePower);
}

void Robot::UpdateIntake(pros::Controller& master)
{
	if (master.get_digital(E_CONTROLLER_DIGITAL_L1))
		intake->Suck();
	else if (master.get_digital(E_CONTROLLER_DIGITAL_L2))
		intake->Blow();
	else
		intake->Stop();
}

void Robot::UpdateLift(pros::Controller& master)
{
	if(master.get_digital(E_CONTROLLER_DIGITAL_R1))
		lift->Raise();
	else if (master.get_digital(E_CONTROLLER_DIGITAL_R2))
		lift->Lower();
	else
		lift->HoldUp();
}

// Public method definitions --------------------------------------------------
void Robot::Initialize()
{
	carrier->Initialize();
	claw->Initialize();
	drive->Initialize();
	intake->Initialize();
	lift->Initialize();
}

void Robot::RobotControl(pros::Controller& master)
{
	UpdateCarrier(master);
	UpdateClaw(master);
	UpdateDrive(master);
	UpdateIntake(master);
	UpdateLift(master);

	// Delay for the next loop
	pros::Task::delay(30);
}