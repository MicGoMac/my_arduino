
/*
project start on 2023-07-27
the stepper motor is ready be installed in the turning shooting platform

this is based on:
stepper_motor_for_turning_table.ino

fine speed control are added to control the turning speed of the turn table
there are gears between the stepper and the table, some additional calculation 
is expected

gear number of stepper shank: 16
gear number of intermediate gear: 12 ,64
gear number of a full round of the table:210, 110
number of turns of stepper to cause a full round of the table:

stepper 4 pins color code white, yellow green blue
map to pin 8-11

added all zero output in idle time
so to keep the temperature of the stepper motor down

*/

#define IN1  8
#define IN2  9
#define IN3  10
#define IN4  11
int Steps;
boolean Direction;
boolean idleState;
unsigned long last_time;
unsigned long currentMillis;
int steps_left;
int delayMillis;

//test use to track time for a full round
unsigned long startMillis;

String highlow=String("00000111000001");
int stepnum=0;

void setup()
{
	Serial.begin(9600);	
	Serial.println ("starting...");
	pinMode(IN1, OUTPUT); 
	pinMode(IN2, OUTPUT); 
	pinMode(IN3, OUTPUT); 
	pinMode(IN4, OUTPUT); 
	startMillis = micros();
  last_time=micros();
	Steps = 0;
  Direction = true;
  //number of steps for a rev, 64x64
  //useful to track angle of rotation
	steps_left=4095;

  //how many mill sec delay in each loop
  delayMillis=4550;
  idleState=false;
}

void loop(){
  while (steps_left>0){

    currentMillis = micros();

    //put all pins to zero to save energy and heat. 1100 millsec push time is just made to make the stepper turn
    //if delayMillis <= 1100 this if check never valid
    if(delayMillis > 1100 and currentMillis-last_time > 1100 and idleState==false){
      allzero();
      idleState=true;
    }
  
    //due to various reason, time check might be delayed
    //trigger once pass the check point instead of = 
    if(currentMillis-last_time > delayMillis){

      //make this a function
        if ( Direction ){
      	  stepnum++;
          if ( stepnum >= 8){stepnum=0;}
        }else{
          stepnum--;
          if ( stepnum <= 0){stepnum=8;}
        }
        
      	String p1= spstr( 1 );
      	String p2= spstr( 2 );
      	String p3= spstr( 3 );
      	String p4= spstr( 4 );
      	
      	////Serial.println (stepnum);
      	//Serial.println (p1);
      	//Serial.println ( "p4-" + p4);
      	////Serial.println (p1+p2+p3+p4);
      	
      	digitalWrite(IN1, p1.toInt() ); 
      	digitalWrite(IN2, p2.toInt() );
      	digitalWrite(IN3, p3.toInt() );
      	digitalWrite(IN4, p4.toInt() );
       
        idleState=false;
        steps_left--;
      //end make this a function
      
     //after all job done, reset last_time
     //set it as an increment of delayMillis
     last_time = last_time + delayMillis;

     //input checking
      char inChar = (char)Serial.read();
      if (inChar == '\n') {
        Serial.println ( inChar);
        Serial.println ( "change dir");
        Direction = !Direction;
      }
      
     }
   }

  if(steps_left==0){  //just finished a cycle, report time
    steps_left=4095;
    currentMillis = micros();
    //Serial.println ((currentMillis - startMillis)/1000);
  }
}

String spstr( int pin ){
  //for pin 1, start with char 1, pin 2 start with 2
  //dependency - stepnum
  
  int os = (pin-1)*2;
 
    String chop=highlow.substring( os+stepnum, os + stepnum + 1);
    //int state = chop.toInt();
	return chop;
}

void allzero(){
  digitalWrite(IN1, 0); 
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 0);
}

void gotoAngle(float ang){
  //steps_left number of the destinate ang
  int destinate_step = ang/360 * 4069;

  //choose a fast direction
  whichDir(  destinate_step);

  while(destinate_step!=steps_left){

    delay(1000);
    }
  return 1;
}

int whichDir(int destinate_step){
  //make out if the difference from curr position is greater that 180 degree
  //once over, go the 'backward' direction
  boolean overhalf = abs(destinate_step-steps_left) > 4069/2;
  
  int dir;
  if ( destinate_step>steps_left ) { 
    if ( overhalf ) {  dir = -1; } else { dir = 1;}
  }else{ 
    if ( overhalf ) { dir = 1;  } else { dir = -1;}
  }
  return dir;
}

/* note

to do:
function to go to certain angle
function to pause and go on


delayMillis 900 -> 3685
975 -> 3992 near 4S
1000-> 4095
8190
12285
16380

10000-- 40950
*/
