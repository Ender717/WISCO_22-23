/*
#include "main.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 *
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 *
void initialize() {
	pros::lcd::initialize();
	
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 *
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 *
void competition_initialize() {}

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
 *
void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 *
void opcontrol() 
{
	pros::Controller master(pros::E_CONTROLLER_MASTER);

	pros::Motor frontLeftDrive(18);
	pros::Motor rearLeftDrive(11);
	pros::Motor frontRightDrive(20, true);
	pros::Motor rearRightDrive(13, true);

	pros::Rotation leftEncoder(14);
	pros::Rotation centerEncoder(15);
	pros::Rotation rightEncoder(16);
	pros::Imu inertial(17);

	leftEncoder.set_position(0.0);
	rightEncoder.set_position(0.0);
	centerEncoder.set_position(0.0);

	float leftDrive, rightDrive;
	PID *basePID = new PID(2.66, 0.00, 0.16, -125.0, 125.0, 0.002, 0.0);
	PositionCalculation *pos = new PositionCalculation(0.0, 0.0, 0.0);
	float leftInches, rightInches, centerInches, inertialRadians, drivePower;
	// basePID->SetTargetValue(360.0);
	pros::delay(5000);

	while (true) 
	{
		leftDrive = (master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y) 
					+ master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X));
		rightDrive = (master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y) 
					- master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X));
		
		frontLeftDrive.move(leftDrive);
		rearLeftDrive.move(leftDrive);
		frontRightDrive.move(rightDrive);
		rearRightDrive.move(rightDrive);

		leftInches = leftEncoder.get_position()*((2.807 * 3.1415) / 36000);
		rightInches = rightEncoder.get_position()*((2.807 * 3.1415) / -36000);
		centerInches = centerEncoder.get_position()*((2.807 * 3.1415) / -36000);
		inertialRadians = inertial.get_rotation() * (3.1415 / 180.0) * (360.0 / 355.3);
		pos->UpdatePosition(leftInches, rightInches, centerInches, inertialRadians);
		
		/*
		drivePower = basePID->GetControlValue(inertialRadians * (180.0 / 3.1415));
		frontLeftDrive.move(drivePower);
		rearLeftDrive.move(drivePower);
		frontRightDrive.move(-drivePower);
		rearRightDrive.move(-drivePower);
		*

		pros::lcd::set_text(1, std::to_string(pos->getX()));
		pros::lcd::set_text(2, std::to_string(pos->getY()));
		pros::lcd::set_text(3, std::to_string(pos->getAngle() * 180 / 3.1415));

		pros::delay(2);
	}
}
*/