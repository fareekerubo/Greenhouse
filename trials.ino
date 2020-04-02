#include <amt1001_ino.h>
#include <SoftwareSerial.h>
uint16_t temperature;
int tempPin=A0;

String dataMessage="";// Create global varibales to store temperature and humidity
float t; // temperature in celcius
//float f; // temperature in fahrenheit


SoftwareSerial SIM800(3, 2);

// Create variable to store incoming SMS characters
char incomingChar;

void setup() {
  
  pinMode(tempPin,INPUT);
  Serial.begin(9600);
  SIM800.begin(9600);


  // Give time to your GSM shield log on to network
  delay(20000);
  Serial.print("SIM800 ready...");

  // AT command to set SIM800 to SMS mode
  SIM800.print("AT+CMGF=1\r"); 
  delay(100);
  // Set module to send SMS data to serial out upon receipt 
  SIM800.print("AT+CNMI=2,2,0,0,0\r");
  delay(100);
}


void loop(){
   read_sensor();
   dataMessage = ("Temperature: " + String(t) + "*C " );
   Serial.print(dataMessage);
   query();
  
  }






  void query(){
  if (SMSRequest()){
  
   
    if(read_sensor()){
       delay(10);
        sms();
//      // Uncomment to change message with farenheit temperature
//      // String dataMessage = ("Temperature: " + String(f) + "*F " + " Humidity: " + String(h) + "%");      
//      
//      // Send the SMS text message
     //SIM800.print(dataMessage);
      Serial.println("Kwisha");
//      // Give module time to send SMS
      delay(1000);  
    }
  }
  delay(10); 
}
  
boolean read_sensor(){
uint16_t step = analogRead(tempPin); 
 t = amt1001_gettemperature(step);
Serial.print(t);
delay(100);
Serial.println(" ");
return true;
}

boolean SMSRequest() {
  if(SIM800.available() >0) {
    incomingChar=SIM800.read();
    if(incomingChar=='S') {
      delay(10);
      Serial.print(incomingChar);
      incomingChar=SIM800.read();
      if(incomingChar =='T') {
        delay(10);
        Serial.print(incomingChar);
        incomingChar=SIM800.read();
        if(incomingChar=='A') {
          delay(10);
          Serial.print(incomingChar);
          incomingChar=SIM800.read();
          if(incomingChar=='T') {
            delay(10);
            Serial.print(incomingChar);
            incomingChar=SIM800.read();
            if(incomingChar=='E') {
              delay(10);
              Serial.print(incomingChar);
              Serial.print("...Request Received \n");
              return true;
            }
          }
        }
      }
    }
  }
  return false;
}




void sms()
{
  SIM800.begin(9600);

  Serial.println("Initializing..."); 
  delay(1000);

  SIM800.println("AT"); //Once the handshake test is successful, it will back to OK
  //updateSerial();
  delay(1000);
  SIM800.println("AT+CMGF=1"); // Configuring TEXT mode
 // updateSerial();
    delay(1000);
  SIM800.println("AT+CMGS=\"+254703149329\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  //updateSerial();
    delay(1000);
  SIM800.print(dataMessage); //text content
 // updateSerial();
  SIM800.write(26);
}
