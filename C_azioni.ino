void azioni(byte qualeAzione){
  switch(qualeAzione){
    case 0: //avanti
      servoSX.write(posCentrale+vel); 
      servoDX.write(posCentrale-vel);
      Serial.println("vado avanti");
      break;  
    case 1: //orario
      servoSX.write(posCentrale+vel); 
      servoDX.write(posCentrale+vel);
      Serial.println("giro in senso orario");
      break;  
    case 2: //indietro
      servoSX.write(posCentrale-vel); 
      servoDX.write(posCentrale+vel);
      Serial.println("vado indietro");
      break;  
    case 3: //antiorario
      servoSX.write(posCentrale-vel); 
      servoDX.write(posCentrale-vel);
      Serial.println("giro in senso antiorario");
      break;  
    case 4: //stop, fuori da rete neurale
      servoSX.write(posCentrale); 
      servoDX.write(posCentrale);
      Serial.println("sto fermo");
      break;               
  }  
}

