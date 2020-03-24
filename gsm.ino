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
