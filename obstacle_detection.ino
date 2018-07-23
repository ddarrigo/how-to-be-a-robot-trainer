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

