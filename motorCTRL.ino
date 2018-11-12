void motorCTRL(bool tempLdir,bool tempRdir,bool on_off){ //true to go forward, false backwards
  int Ldir,Rdir;
  byte spM=4+1; //speed vector module
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


