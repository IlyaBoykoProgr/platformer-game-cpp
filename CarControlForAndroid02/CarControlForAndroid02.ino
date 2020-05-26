//test 1:2015.08.15
#include <car_bluetooth.h>
#include <SoftwareSerial.h>   //Software Serial Port
#include <string.h>
#include "MotorDriver.h"
#include <Ultrasonic.h>
#include "TM1637.h"
#define DISPLAY 0

#define TRIGGER_PIN  5//connect Trip of the Ultrasonic Sensor moudle to D5 of Arduino 
#define ECHO_PIN     3
Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);

#define CLK A5//connect CLK of the 4-Digit Display to A5 of Arduino and can be changed to other ports    
#define DIO A4//
#if DISPLAY==1
TM1637 disp(CLK,DIO);
#endif

#define RxD 2//D2 of Arduino should connect to TX of the Serial Bluetooth module
#define TxD 4//D4 of Arduino should connect to RX of the Serial Bluetooth module
CarBluetooth bluetooth(RxD, TxD);
#define CMD_INVALID     0XFF
#define CMD_FORWARD     'F'
#define CMD_RIGHT_FRONT 'R'
#define CMD_BACKWARD    'B'
#define CMD_LEFT_FRONT  'L'
#define CMD_STOP        'S'
#define SPEED_STEPS 10
uint8_t speed0 = 100;



void setup(){
  Serial.begin(9600);
  Serial.println("Initializing");
#if DISPLAY==1
  disp.init();
  disp.set(BRIGHT_TYPICAL);//BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
#endif
  motordriver.init();
  motordriver.setSpeed(10,MOTORA);
  motordriver.setSpeed(10,MOTORB);
}
uint8_t bt_command;
#define CAR_STOP 0
#define CAR_FORWARD 1
#define CAR_BACK 2

void loop(){
  bt_command = bluetooth.readByte();
  ultrasonicDisplay();
  if(bt_command != CMD_INVALID){
    controlCar(bt_command);
    Serial.println((char)bt_command);
  }
}


void controlCar(uint8_t cmd){
   switch(cmd)
  {
    case CMD_FORWARD:motordriver.goForward();break;
  case CMD_RIGHT_FRONT:
    motordriver.goRight();
    break;
  case CMD_BACKWARD:motordriver.goBackward(); break;
  case CMD_LEFT_FRONT:  
    motordriver.goLeft();
    break;
  case CMD_STOP:motordriver.stop();break;
  }
  delay(200);
  if((cmd>='0')&&(cmd<='9'))
  {
    speed0 = cmd-0x30;
    speed0 = map(speed0, 0, 9, 0, 255);
    Serial.println(speed0);
    motordriver.setSpeed(speed0,MOTORA);
    motordriver.setSpeed(speed0,MOTORB);
  }
}

void speedUp(){
  if(speed0 < 236)speed0 += SPEED_STEPS;
  else speed0 = 255;
  motordriver.setSpeed(speed0,MOTORA);
  motordriver.setSpeed(speed0,MOTORB);
  Serial.println(speed0);
}

void speedDown(){
  if(speed0 > 70)speed0 -= SPEED_STEPS;
  else speed0 = 50;
   motordriver.setSpeed(speed0,MOTORA);
  motordriver.setSpeed(speed0,MOTORB);
  Serial.println(speed0);
}

void ultrasonicDisplay()
{
  float cmMsec;
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
#if DISPLAY==1
  disp.display((int16_t)cmMsec);
#endif
    if ((bt_command=='F'|| bt_command==0xFF)&&cmMsec<11)
      motordriver.stop();
    else
       controlCar(bt_command);
}
