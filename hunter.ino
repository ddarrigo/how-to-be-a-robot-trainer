void hunt_moving_objects (bool inhib,bool sup){
  //bool detection=
  //byte thres=25;
  if(!inhib){ //sensors state    
    //motorState=0; //stop
    if(ultraIn!=15){    
      hunt_movingO_toggle=true;
      if(IRs[0]==0||IRs[4]==0)
        motorState=5; //clockwise
      else 
        if(IRs[3]==0||IRs[2]==0)
          motorState=6; //counterclockwise
        else
          if(IRs[1]==0)
            motorState=byte(random(5,7));
          else
            motorState=0; //stop
    }
    if(ultraIn==15){
      Serial.println("moving object detected!");
      if(escape_from_movingO_toggle){
        hunt_movingO_toggle=false;
        motorState=7; //forward
      }        
    } 
  }
  if(!sup){ //following actions
    motorState=motorState;
  }
}
