/*
 * this code specified for my vgear remote
 * to do: map result to diff actions
 * IRremote: IRrecvDump - dump details of IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 
 revised for V gear remote with buttons in 4 x 8 matrix
 
 */

#include <IRremote.h>

int RECV_PIN = 11;
String btn_code;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);
    while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  irrecv.enableIRIn(); // Start the receiver
    Serial.println("serial open");
}

// Dumps out the decode_results structure.
// Call this after IRrecv::decode()
// void * to work around compiler issue
//void dump(void *v) {
//  decode_results *results = (decode_results *)v
void dump(decode_results *results) {
  int count = results->rawlen;
  if (results->decode_type == UNKNOWN) {
    btn_code="bad";
    action(btn_code);
    Serial.println("Could not decode message");
  } 
  else {
    //report model
    if (results->decode_type == NEC) {
      //skip this for the vgear remote
      //Serial.print("NEC: ");
    } 
    else if (results->decode_type == SONY) {
      Serial.print("Decoded SONY: ");
    } 
    else if (results->decode_type == RC5) {
      Serial.print("Decoded RC5: ");
    } 
    else if (results->decode_type == RC6) {
      Serial.print("Decoded RC6: ");
    }
    
    switch (results->value) {
	case 1641433271:
		btn_code="1:1";
		break;
	
	case 1641476111:
		btn_code="1:2";
		break;
	
	case 1641427151:
		btn_code="1:3";
		break;
	
	case 1641467951:
		btn_code="1:4";
		break;
	
	case 1641416951:
		btn_code="2:1";
		break;
	
	case 1641447551:
		btn_code="2:2";
		break;
	
	case 1641431231:
		btn_code="2:3";
		break;
	
	case 1641463871:
		btn_code="2:4";
		break;
	
	case 1641421031:
		btn_code="3:1";
		break;
	
	case 1641423071:
		btn_code="3:2";
		break;
	
	case 1641455711:
		btn_code="3:3";
		break;
	
	case 1641439391:
		btn_code="3:4";
		break;
	
	case 1641429191:
		btn_code="4:1";
		break;
	
	case 1641472031:
		btn_code="4:2";
		break;
	
	case 1641418991:
		btn_code="4:3";
		break;
	
	case 1641451631:
		btn_code="4:4";
		break;
	
	case 1641465911:
		btn_code="5:1";
		break;
	
	case 1641414911:
		btn_code="5:2";
		break;
	
	case 1641435311:
		btn_code="5:3";
		break;
	
	case 1641474071:
		btn_code="5:4";
		break;
	
	case 1641441431:
		btn_code="6:1";
		break;
	
	case 1641461831:
		btn_code="6:2";
		break;
	
	case 1641437351:
		btn_code="6:3";
		break;
	
	case 1641449591:
		btn_code="6:4";
		break;
	
	case 1641443471:
		btn_code="7:1";
		break;
	
	case 1641478151:
		btn_code="7:2";
		break;
	
	case 1641425111:
		btn_code="7:3";
		break;
	
	case 1641469991:
		btn_code="7:4";
		break;
	
	case 1641459791:
		btn_code="8:1";
		break;
	
	case 1641453671:
		btn_code="8:2";
		break;
	
	case 1641445511:
		btn_code="8:3";
		break;
	
        //this is the FFFFFF blank code
	case 1641457751:
		btn_code="8:4";
		break;
        default:
          btn_code="0:0";
	 
    }   
 
    if ( btn_code!= "0:0"){
      action(btn_code);
      //Serial.print(results->value, DEC);
      //Serial.print(" (");
      //Serial.println(btn_code);
      //Serial.println(" )");
    }
  }
  //Serial.print("Raw (");
  //Serial.print(count, DEC);
  //Serial.print("): "); 
  
  //Serial.println("end======");
}


void loop() {
  if (irrecv.decode(&results)) {
    //this prints the hex result
    //Serial.println(results.value, HEX);
    dump(&results);
    irrecv.resume(); // Receive the next value
  }
}

void action( String btn_code){
   Serial.println(btn_code);
}


