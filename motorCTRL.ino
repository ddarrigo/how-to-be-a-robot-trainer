/*void motorCTRL(String dir){ 
  byte spM=4;  //modulo del vettore speed
  if(dir=="stop"){
    myservoL.write(90);
    myservoR.write(90);
  }
  if(dir=="forward"){
    myservoL.write(90+spM);
    myservoR.write(90-spM);
  }
  if(dir=="backwards"){
    myservoL.write(90-spM);
    myservoR.write(90+spM); 
  }
  if(dir=="clockwise"){
    myservoL.write(90+spM);
    myservoR.write(90+spM); 
  }
  if(dir=="counterclockwise"){
    myservoL.write(90-spM);
    myservoR.write(90-spM); 
  }
}
*/

void motorCTRLdir(bool Ldir,bool Rdir,bool on_off){
  byte speed_module=4;
  
  
}


