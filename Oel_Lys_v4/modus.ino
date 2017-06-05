int modusFunk(void){
  modus++;
  Serial.print("Modus: "); Serial.println(modus);
  delay(10);
  while(digitalRead(buttonPin)==1) delay(1);
  return modus;
}
