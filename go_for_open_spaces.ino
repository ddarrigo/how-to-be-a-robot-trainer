 void go_for_open_spaces(bool inhib,bool sup){
  //byte answer=0;
  if(!inhib){ //sensors state
    if(u>=20){
      open_space_search_toggle=1;
      motorState=7; //go forward
    }
    //else
      //motorState=byte(random(5,7));
    else if(open_space_search_toggle){
      motorState=byte(random(5,7)); //clockwise or counterclockwise
      open_space_search_toggle=0;
    }
    if(IRs[4]==0)  //a valle perché è obstacle detection
      motorState=6;  //counterclockwise
    if(IRs[3]==0)  //a valle perché è obstacle detection
      motorState=5;  //clockwise
  }
  if(!sup){ //following actions
    motorState=motorState;
  }
}

