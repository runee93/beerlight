//byte klappInn= 12;
//pinMode(klappInn, INPUT); 
//Disse må inn i main



int count=0;
long start=0;

void klappFunk(void){
  count=1;    
    Serial.println("Ett Klapp");
    delay(50);
    start=millis()/100;
        
    while(millis()/100<10+start){
       if(digitalRead(klappInn)){
        count=0;
        modus++;
        delay(50);
      }
    }
      
      if(count==1){
        count=0;
         Serial.println("Time Out Klapp");
         delay(10);  
      }      


}


