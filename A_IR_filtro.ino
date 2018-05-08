//non è necessario usare la media mobile in quanto il valore è binarizzato

void IRsinistroFiltro(byte indice){
  totaleIRsinistro+=digitalRead(11);
  if(indice>=4-1){
    if(totaleIRsinistro==0)
      ostacoloSX=true;
    else{
      ostacoloSX=false;
      totaleIRsinistro=0; //reset
    }
  }
  else{
    ostacoloSX=false;
  }
}

void IRdestroFiltro(byte indice){
  totaleIRdestro+=digitalRead(12);
  if(indice>=4-1){
    if(totaleIRdestro==0)
      ostacoloDX=true;
    else{
      ostacoloDX=false;
      totaleIRdestro=0;
    }
  }
  else{
    ostacoloDX=false;  
  }
}

