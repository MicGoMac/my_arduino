// L9110 connections
#define L9110_B_IA 10 // Pin D10 --> Motor B Input A
#define L9110_B_IB 11 // Pin D11 --> Motor B Input B
 
// Motor Speed & Direction
#define MOTOR_B_PWM L9110_B_IA // Motor PWM Speed
#define MOTOR_B_DIR L9110_B_IB // Motor Direction
  
 
void setup ()  { 
 pinMode( MOTOR_B_DIR, OUTPUT );
 pinMode( MOTOR_B_PWM, OUTPUT );
 digitalWrite( MOTOR_B_DIR, LOW ); // Set motor to off
 digitalWrite( MOTOR_B_PWM, LOW );
}
 
void loop ()  {
 	digitalWrite( MOTOR_B_DIR, LOW ); // turn motor off
	analogWrite( MOTOR_B_PWM, LOW );
	delay(1000);
	
	// forward
	for( int i=180; i<= 20; i--){
     
		digitalWrite( MOTOR_B_DIR, HIGH ); // direction = forward
		analogWrite( MOTOR_B_PWM, i ); // PWM speed = 180 and down
		delay(100);
		i=i+5;
	 }
	
	digitalWrite( MOTOR_B_DIR, LOW ); // turn motor off
	analogWrite( MOTOR_B_PWM, LOW );
	delay(1000);
	
	
	for( int i=20; i<= 200; i++){
		digitalWrite( MOTOR_B_DIR, LOW ); // direction = reverse
		analogWrite( MOTOR_B_PWM, i ); // PWM speed = 20 and up
		delay(100);
		i=i+5;
	}

}
