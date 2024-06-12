/*
@file: gimbal_stepper_test
@updated: 2024/06/02
@brief: Controls a pan/tilt gimbal system using NEMA17 stepper motors and A4988 drivers. Motion is controlled via a joystick.
*/

#include <AccelStepper.h>
#define NEMA17_MAX_SPEED      500.0     //steps per second
#define NEMA17_MAX_ACCEL      50.0      //steps per second^2
#define NEMA17_STEPS_PER_REV  200       //steps per one output revolution
#define SPEED_REDUCTION       5         //reduce speed by this factor

/******************************* global vars, objects ****************************************/
const int PAN_DIR_PIN     = 2;    //pan stepper motor pins
const int PAN_STEP_PIN    = 3;
const int TILT_DIR_PIN    = 4;    //tilt stepper motor pins
const int TILT_STEP_PIN   = 5;
const int PAN_PIN         = A0;   //joystick pins (Pan = VRX | Tilt = VRY)
const int TILT_PIN        = A1;

const int JOYSTICK_ZERO   = 430;  //joystick reading at zero position (after calibration)
const int THRESHOLD       = 100;   //minimum joystick movement needed to actuate

AccelStepper panStepper(AccelStepper::DRIVER, PAN_STEP_PIN, PAN_DIR_PIN);
AccelStepper tiltStepper(AccelStepper::DRIVER, TILT_STEP_PIN, TILT_DIR_PIN);

/******************************* void setup ****************************************/
void setup() {
  //init serial comms 
  Serial.begin(9600);
  while(!Serial){}

  //init joystick input pins
  pinMode(PAN_PIN, INPUT);
  pinMode(TILT_PIN, INPUT);

  //setup stepper motors
  panStepper.setMaxSpeed(NEMA17_MAX_SPEED);      
  panStepper.setAcceleration(NEMA17_MAX_ACCEL);      
  panStepper.setSpeed(200);             
  Serial.println("Pan Motor Ready => ");
  tiltStepper.setMaxSpeed(NEMA17_MAX_SPEED);        
  tiltStepper.setAcceleration(NEMA17_MAX_ACCEL);      
  tiltStepper.setSpeed(200);;
  Serial.println("Tilt Motor Ready => ");
  delay(250);

  Serial.println("Gimbal system ready; move joystick to direct platform.");
  Serial.println("Up/Down = TILT\tLEFT/RIGHT = PAN");
}

/******************************* void loop ****************************************/
void loop() {
  int panPos = analogRead(PAN_PIN);
  int tiltPos = analogRead(TILT_PIN);

  if( abs(panPos - JOYSTICK_ZERO) > THRESHOLD) {
    int panDirection = (panPos > JOYSTICK_ZERO) ? 1 : -1;
    panStepper.setSpeed(panDirection*NEMA17_MAX_SPEED/SPEED_REDUCTION);
  }
  else{
    panStepper.setSpeed(0);
  }

  if( abs(tiltPos - JOYSTICK_ZERO) > THRESHOLD) {
    int tiltDirection = (tiltPos > JOYSTICK_ZERO) ? 1 : -1;
    tiltStepper.setSpeed(tiltDirection*NEMA17_MAX_SPEED/SPEED_REDUCTION);
  }
  else{
    tiltStepper.setSpeed(0);
  }

//todo/ks: allow position control  
//  for( int i=0; i<180; i++){
//    panStepper.moveTo(panPos);
//    tiltStepper.moveTo(tiltPos);
//    panStepper.run();
//    tiltStepper.run();
//  }
//
//  for( int j=180; j>0; j-- ){
//    panStepper.moveTo(panPos);
//    tiltStepper.moveTo(tiltPos);
//    panStepper.run();
//    tiltStepper.run();
//    delay(100);
//  }

  panStepper.runSpeed();
  tiltStepper.runSpeed();
}