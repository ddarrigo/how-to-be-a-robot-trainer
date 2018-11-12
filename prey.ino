void escape_from_moving_objects (bool inhib,bool sup){
  byte thres=15;
  if(!inhib){ //sensors state    
    if(ultraIn==15){
      Serial.println("moving object detected!");
      if(escape_from_movingO_toggle){
        escape_from_movingO_toggle=false;
        motorState=byte(random(4,7));
      }        
    }else{    
      escape_from_movingO_toggle=true;
      motorState=0;
    }
  }
  if(!sup){ //following actions
    motorState=motorState;
  }
}



