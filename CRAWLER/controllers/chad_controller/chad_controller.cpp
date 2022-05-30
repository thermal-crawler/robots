// File:          chad_controller.cpp
#include <webots/Motor.hpp>
#include <webots/Robot.hpp>
#include <webots/PositionSensor.hpp>

#define TIME_STEP 64
using namespace webots;

// This is the main program of your controller.
// It creates an instance of your Robot instance, launches its
// function(s) and destroys it at the end of the execution.
// Note that only one instance of Robot should be created in
// a controller program.
// The arguments of the main function can be specified by the
// "controllerArgs" field of the Robot node
int main(int argc, char **argv) {
  // create the Robot instance.
  Robot *robot = new Robot();
  
  Motor *wheels[4];
  char wheels_names[3][15] = {"yaw_motor", "roll_motor", "pitch_motor"};
  //wheels[1] = robot->getMotor(wheels_names[1]);
  //wheels[1]->setPosition(INFINITY);
  
  wheels[2] = robot->getMotor(wheels_names[2]);
  wheels[2]->setPosition(INFINITY);
  
  //PositionSensor *r_sensor = wheels[1]->getPositionSensor();
  PositionSensor *p_sensor = wheels[2]->getPositionSensor();
  //r_sensor->enable(TIME_STEP);
  p_sensor->enable(TIME_STEP);
  
  //wheels[1]->setVelocity(0.0);
  wheels[2]->setVelocity(10.0);
  
  while (robot->step(TIME_STEP) != -1) {
    if(p_sensor->getValue() > 0.3){
      wheels[2]->setVelocity(-10.0);
    }
    else if(p_sensor->getValue() < -0.3){
      wheels[2]->setVelocity(10.0);
    }
  }
  delete robot;
  return 0;
}
