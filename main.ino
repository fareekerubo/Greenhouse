#include <amt1001_ino.h>
#include <SoftwareSerial.h>
uint16_t humidity;
uint16_t temperature;
int tempPin=A0;
int humPin=A1;


SoftwareSerial SIM900(7, 8);
char incomingChar;//Create variable to store incoming SMS characters


void setup() {
  // put your setup code here, to run once:
pinMode(tempPin,INPUT);
pinMode(humPin,INPUT);
Serial.begin(9600);
SIM800.begin(9600);


 // AT command to set SIM800 to SMS mode
  SIM800.print("AT+CMGF=1\r"); 
  delay(100);
  // Set module to send SMS data to serial out upon receipt 
  SIM800.print("AT+CNMI=2,2,0,0,0\r");
  delay(100);
}


void loop(){
  if (SMSRequest()){
    if(amt1001_sensor()){
      delay(10);
      SIM900.println("AT + CMGS = \"+XXXXXXXXXX\"");
      delay(100);
      String dataMessage = ("Temperature: " + String(t) + "*C " + " Humidity: " + String(h) + "%");
      // incase we want data to be received in form of fahreint
      // String dataMessage = ("Temperature: " + String(f) + "*F " + " Humidity: " + String(h) + "%");      
      
      // Send the SMS text message
      SIM900.print(dataMessage);
      delay(100);
      // End AT command with a ^Z, ASCII code 26
      SIM900.println((char)26); 
      delay(100);
      SIM900.println();
      // Give module time to send SMS
      delay(5000);  
    }
  }
  delay(10); 
}
