#include "autonomous.h"

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() 
{
	/*
	AutonController::robot = RobotState::robot;
    // Run the selected auton
	switch(Autons::selectedAuton)
	{
		default:
			pros::screen::print(text_format_e_t::E_TEXT_LARGE, 50, 70, "No Auton Selected");
			break;
	}
	*/
}