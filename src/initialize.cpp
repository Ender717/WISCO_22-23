#include "initialize.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {

}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() 
{
	if (!pros::competition::is_connected())
	{
		RobotManager manager;
		manager.CreateRobot(RobotConfigs::BLUE);
		RobotState::robot = manager.GetRobot();
		RobotState::robot->Initialize();
		AutonController::robot = RobotState::robot;
	}
	
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() 
{
	RobotManager manager;

	Menu::DrawMenuSelect();
	Menu::AutonSelect();
	Menu::Erase(0, 0, 480, 272);

	Menu::DrawMenuSelect();
	Menu::RobotSelect();
	Menu::Erase(0, 0, 480, 272);

	manager.CreateRobot(*RobotState::configuration);
	RobotState::robot = manager.GetRobot();
	RobotState::robot->Initialize();
	AutonController::robot = RobotState::robot;
}