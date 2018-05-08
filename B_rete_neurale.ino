bool controlloStato(){
  bool risposta;
  byte punteggio=0;
  int vettoreTemporaneo[5]={0,0,0,0,0};
  for(byte y=0;y<5;y++){
    for(byte x=0;x<5;x++){ //in questo caso x si ferma a tre, perché dobbiamo valutare solo i primi tre bit del vettore di stato, quelli dei sensori!
      if(x<3)
        vettoreTemporaneo[y]+=stato[x]*rete[x][y];
      if(x>=3)
        vettoreTemporaneo[y]+=0;
    }
  }
  for(byte x=0;x<5;x++){  //processo di normalizzazione
    if(vettoreTemporaneo[x]>=1)
      vettoreTemporaneo[x]=+1;
    if(vettoreTemporaneo[x]<=-1)
      vettoreTemporaneo[x]=-1;
    Serial.print(vettoreTemporaneo[x]);
    Serial.print("|");
  }
  //Serial.println(" ");
  for(byte y=0;y<4;y++){
    punteggio=0;
    for(byte x=0;x<3;x++){
      if(stato[x]==memoriaPrestabilita[y][x])
        punteggio++;
    }
    if(punteggio>=3){
      risposta=true;
      //Serial.println(punteggio);
      break;
    }
    else
      risposta=false;        
  }  
  //estrapola azione da vettore
  azione=0;
  for(byte x=0;x<2;x++){
    if(vettoreTemporaneo[4-x]>=1)
      bitSet(azione,x);
  }
  //Serial.println(azione);
  
  return risposta;  
}

