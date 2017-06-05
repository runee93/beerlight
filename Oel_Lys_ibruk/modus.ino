int modusFunk(void){
  int counter=millis()/100;
  modus++;
  Serial.print("Modus: "); Serial.println(modus);
  delay(10);
  while(digitalRead(buttonPin)==1){
  if ((millis()/100)-counter>=10){
  modus=0;
  return modus;
  }
  }
  return modus; 

}
