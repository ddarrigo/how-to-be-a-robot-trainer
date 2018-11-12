//Obstacle detection riguarda solo i sensori IR
void obstacleDetection(bool inhib,bool sup){
  //byte answer=0;
  //byte score=0;
  if(!inhib){ //sensors state
    if(IRs[4]==0||IRs[3]==0)
      motorState=4; //backwards
    if(IRs[2]==0||IRs[1]==0||IRs[0]==0)
      motorState=7; //forward

    /*
    for(byte i=0;i<5;i++)
      if(IRs[i]==0)
        score++;
    if(score>=3)
      motorState=0; //emergency stop*/
  }
  if(!sup){ //following actions
    motorState=motorState;
    
  }
}
/*
bool moving_object_detection(){
  bool answer=false;
  if(abs(ultraIn-oldUltraIn>=2))
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
  //Serial.println(ultraIn);
  //Serial.println(oldUltraIn);
  oldUltraIn=ultraIn;  
}*/
