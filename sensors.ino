void IRsmoother(){
  for(byte x=0;x<5;x++){
    if(analogRead(x)<512)
      bitClear(IRs[x],IRindex);
    else
      bitSet(IRs[x],IRindex);
  }
}

void buttonSmoother(){
  if(digitalRead(6)==1)
    bitSet(buttonState,IRindex);
  else
    bitClear(buttonState,IRindex);
}

void ultrasonicSmoother(){
  long inValue;
  inValue=ultrasonic.MeasureInCentimeters();
  if(inValue<threshold)
    bitSet(ultraIn,IRindex);   
  else
    bitClear(ultraIn,IRindex);  //u=0 significa via libera
}

