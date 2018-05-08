void sonar_filtro(byte indice){
  totaleSonar-=lettureSonar[indice];
  lettureSonar[indice]=sonar.MeasureInCentimeters();
  totaleSonar+=lettureSonar[indice];
  mediaSonar=totaleSonar/4;
  //Serial.println(mediaSonar);
  if(indice>=4-1)
    if(mediaSonar<sogliaSonar){
      ostacoloC= true;
      if(mediaSonar>vecchiaMediaSonar&&abs(mediaSonar-vecchiaMediaSonar)>=1*0.7) //differenza minima 
        CpiuLontano=true;
      else
        CpiuLontano=false;
      vecchiaMediaSonar=mediaSonar;
    }
    else  
      ostacoloC=false;      
  else
    ostacoloC= false;
  //Serial.println(risposta);
}



