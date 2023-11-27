#include <MeMCore.h>
#include <Arduino.h>

MeDCMotor motor1(M1);

MeDCMotor motor2(M2);

uint8_t motorSpeed = 100;

MeLineFollower lineF(PORT_2);

MeRGBLed led(0, 30); // var for LED

long i = 0;

void moveR()
{
  motor1.run(100);
  motor2.run(-105.25);
  delay (10);

  i = i - .749; // forward
}

void leftR()
{
  motor1.run(100);
  motor2.run(-300);
  delay (100);
 
  i = i - .155; // left
}

void rightR()
{
  motor1.run(300);
  motor2.run(-100);
  delay (100);
 
  i = i - .155; // right
}

void backR()
{
  motor1.run(-100);
  motor2.run(100);
  delay (10);
 
  i ++; // back
}

void stopR()
{
 motor1.run(0);
 motor2.run(0);
 delay (10000); // stop
}

void followLD()
{
  // black = blue light off = 0
  // white = blue light on = 1

  if (i > 160){ // too much back and forward
    stopR(); // stop
  }
  
  else if (lineF.readSensor1() == 0 && lineF.readSensor2() == 0){ // both black
    Serial.println("Both Sensor 1 and 2 are on black.");

    moveR(); // forward
  }

  else if (lineF.readSensor1() == 1 && lineF.readSensor2() == 0){ // left black
    Serial.println("Sensor 1 on white but Sensor 2 is on black.");

    leftR(); // left
  }

  else if (lineF.readSensor1() == 0 && lineF.readSensor2() == 1){ // right black
    Serial.println("Sensor 1 on black but Sensor 2 is on white.");

    rightR(); // right
  }

  else if (lineF.readSensor1() == 1 && lineF.readSensor2() == 1){ // both white
    Serial.println("Both Sensor 1 and 2 are on white.");

    backR(); // back
  }
}

void setup()
{
 Serial.begin(9600);
}

void loop()
{
 followLD();
}
