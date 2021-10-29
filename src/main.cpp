#include "../include/main.h"
#include  "../include/autonomous.h"


void leftBtn(){

}
void centerBtn(){

}
void rightBtn(){

}
void initialize() {
	pros::lcd::initialize();

	pros::lcd::register_btn0_cb(leftBtn);
	pros::lcd::register_btn1_cb(centerBtn);
	pros::lcd::register_btn2_cb(rightBtn);
	Clamp.set_brake_mode(MOTOR_BRAKE_HOLD);
	FBarL.set_brake_mode(MOTOR_BRAKE_HOLD);
	FBarR.set_brake_mode(MOTOR_BRAKE_HOLD);
  autonSelector();

	//autonSelector();
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
  switch(selected){
     case 0:
		 	disabledAuton();
     case 1:
		 	pop();
     case 2:

     case 3:

     case 4:

     case 5:

     case 6:

     case 7:

		 case 8:
     	skills();
   }
}

const int NUM_HEIGHTS = 3;
const int height1 = 0;
const int height2 = 700;
const int height3 = 1500;


const int heights[NUM_HEIGHTS] = {height1, height2,height3};
const int heights2[NUM_HEIGHTS] = {0, 700,1800};



void opcontrol() {
	Clamp.tare_position();
  int goalHeight = 0;
	double prevr = 0;
	double prevl = 0;
  while (true){
		master.clear();
		std::string fl = std::to_string(FrontLeft.get_temperature());
		control.print(1,1, fl.c_str());
		std::string fr = std::to_string(FrontRight.get_temperature());
		control.print(1,2, fl.c_str());
		std::string bl = std::to_string(BackLeft.get_temperature());
		control.print(2,1, fl.c_str());
		std::string br = std::to_string(BackRight.get_temperature());
		control.print(2,2, fl.c_str());
		double left = control.get_analog(ANALOG_LEFT_Y);
		double right = control.get_analog(ANALOG_RIGHT_Y);
		prevr = (right+prevr)/2;
		prevl = (left+prevl)/2;
		driverControl(prevl, prevr);
		if (up.changedToPressed()){
			Clamp.move(100);
		}
		if (down.changedToPressed()){
			Clamp.move(-100);
		}
    if (RUp.changedToPressed() && goalHeight < NUM_HEIGHTS - 1) {
      goalHeight++;
      liftControl->setTarget(heights[goalHeight]);
    } else if (RDown.changedToPressed() && goalHeight > 0) {
      goalHeight--;
      liftControl->setTarget(heights[goalHeight]);
    }
		if (control.get_digital(E_CONTROLLER_DIGITAL_L1)) {
      fourbarmove(200);

    } else if (control.get_digital(E_CONTROLLER_DIGITAL_L2)) {
      fourbarmove(-86);
    } else {
			fourbarmove(0);
		}
    pros::delay(20);
  }
}
