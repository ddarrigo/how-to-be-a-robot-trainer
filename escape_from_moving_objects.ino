void escape_from_moving_objects (bool inhib,bool sup){
  //bool detection=
  byte thres=15;
  if(!inhib){ //sensors state    
    //motorState=0; //stop
    if(!moving_object_detection()&&u>thres){    
      escape_from_movingO_toggle=true;
      Serial.println("nothing is moving");
      motorState=0;
    }
    if(moving_object_detection()&&u<=thres){
      Serial.println("moving object detected!");
      if(escape_from_movingO_toggle){
        escape_from_movingO_toggle=false;
        motorState=byte(random(4,7));
      }        
    }
  }
  if(!sup){ //following actions
    motorState=motorState;
  }
}

bool moving_object_detection(){
  bool answer=false;
  if(abs(u-oldU>=2))
    bitSet(moving,moving_index);
  else  
    bitClear(moving,moving_index);
  moving_index++;
  if(moving_index>=4){
    moving_index=0;
    if(moving>=3)
      answer=true;
    return answer;
  }  
  oldU=u;
  //Serial.println(moving);
  
}

