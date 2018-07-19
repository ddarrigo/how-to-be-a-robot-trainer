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

void motorCTRL(bool tempLdir,bool tempRdir,bool on_off){ //true to go forward, false backwards
  int Ldir,Rdir;
  byte spM=4; //speed vector module
  if(tempLdir)
    Ldir=+1;
  else
    Ldir=-1;
  if(tempRdir)
    Rdir=+1;
  else
    Rdir=-1;
  myservoL.write(90+Ldir*spM*on_off);  
  myservoR.write(90-Rdir*spM*on_off);
}


