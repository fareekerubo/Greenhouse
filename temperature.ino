

void amt1001_sensor() {
 uint16_t step = analogRead(tempPin); 
float temperature = amt1001_gettemperature(step);
Serial.print(temperature);
Serial.print(" ");
uint16_t step1 = analogRead(humPin);
double volt = (double)step1 * (5.0 / 1023.0);
humidity = amt1001_gethumidity(volt);
Serial.print(humidity);
Serial.println(" ");
return true;
}
