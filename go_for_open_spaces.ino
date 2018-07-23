 void go_for_open_spaces(bool inhib,bool sup){
  //byte answer=0;
  if(!inhib){ //sensors state
    if(u>=20){
      open_space_search_toggle=1;
      motorState=7; //go forward
    }
    if(u<=5&&open_space_search_toggle){
      motorState=byte(random(5,7)); //clockwise or counterclockwise
      open_space_search_toggle=0;
    }
  }
  if(!sup){ //following actions
    motorState=motorState;
  }
}

