// File:          chad_controller.cpp
#include <webots/Motor.hpp>
#include <webots/Robot.hpp>
#include <webots/PositionSensor.hpp>
//#include <webots/Brake.hpp>

#define TIME_STEP 64
using namespace webots;

int main(int argc, char **argv) {
  Robot *robot = new Robot();
  
  Motor *wheels[4];
  char wheels_names[3][15] = {"yaw_motor", "pitch_motor", "roll_motor"};
  
  wheels[0] = robot->getMotor(wheels_names[0]);
  wheels[0]->setPosition(INFINITY);
  //wheels[1] = robot->getMotor(wheels_names[1]);
  //wheels[1]->setPosition(INFINITY);
  wheels[2] = robot->getMotor(wheels_names[2]);
  wheels[2]->setPosition(INFINITY);
  
  PositionSensor *y_sensor = wheels[0]->getPositionSensor();
  //PositionSensor *p_sensor = wheels[1]->getPositionSensor();
  PositionSensor *r_sensor = wheels[2]->getPositionSensor();
  y_sensor->enable(TIME_STEP);
  //p_sensor->enable(TIME_STEP);
  r_sensor->enable(TIME_STEP);
  
  wheels[0]->setVelocity(0.0);
  //wheels[1]->setVelocity(10.0);
  wheels[2]->setVelocity(5.0);
  
  while (robot->step(TIME_STEP) != -1) {
    //passes 0.3 limit
    if(r_sensor->getValue() >= 0.3){
      //yaw within 0.2 limit
      if(y_sensor->getValue() < 0.2){
        wheels[0]->setVelocity(5.0);
        wheels[2]->setVelocity(0.0);
      }
      //yaw is outside of limit
      else if (y_sensor->getValue() >= 0.2){ 
        wheels[0]->setVelocity(0.0);
        wheels[2]->setVelocity(-5.0);}
    }
    
    //passes -0.3 limit
    else if(r_sensor->getValue() <=-0.3){
      //yaw within -0.2 limit
      if(y_sensor->getValue() > -0.2){
        wheels[0]->setVelocity(-5.0);
        wheels[2]->setVelocity(0.0);
      }
      //yaw is outside of limit
      else if (y_sensor->getValue() <= -0.2){ 
        wheels[0]->setVelocity(0.0);
        wheels[2]->setVelocity(5.0);}
    }
  }
  delete robot;
  return 0;
}
