/*

runs forward and backward in const speed
seems not quite finished project

 http://www.bajdi.com
 L9110 motor driver controlling 2 small DC motors 
 */

const int AIA = 9;  // (pwm) pin 9 connected to pin A-IA 
const int AIB = 5;  // (pwm) pin 5 connected to pin A-IB 

byte speed = 255;  // change this (0-255) to control the speed of the motors 

void setup() {
  pinMode(AIA, OUTPUT); // set pins to output
  pinMode(AIB, OUTPUT);
}

void loop() {
  forward(); 
  delay(2000);
  backward();
  delay(2000);
}

void backward()
{
  analogWrite(AIA, 0);
  analogWrite(AIB, speed);
}

void forward()
{
  analogWrite(AIA, speed);
  analogWrite(AIB, 0);
}
