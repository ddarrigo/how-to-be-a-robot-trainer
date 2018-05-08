#include <Servo.h> 
#include "Ultrasonic.h"

byte indiceGenerale=0;
//sonar
Ultrasonic sonar(8);
const byte sogliaSonar=8;
bool ostacoloC,CpiuLontano; //aggiungere comunque divincolato
long lettureSonar[4];
float totaleSonar,mediaSonar,vecchiaMediaSonar;
byte condizione;
//IR laterali
byte totaleIRsinistro,totaleIRdestro;
bool ostacoloSX,ostacoloDX;
//stato del robot
bool libero, quasiLibero;
int stato[5]; //il byte tiene insieme stato dei sensori e vettori un un unico dato
//rete neurale
int rete[5][5];
int reteTemporanea[5][5];  //funge da buffer per la somma di matrici
int memoriaPrestabilita[4][5]={{-1,-1,-1,-1,-1},{-1,-1,1,1,1},
                               {-1,1,-1,1,-1},{1,-1,-1,-1,1}}; //azioni mappate sui quattro stati avanti, orario, indietro e antiorario 
//controllo motori
const byte posCentrale=90; //left and right central position
byte vel=6;
byte azione;
Servo servoSX,servoDX;

void setup(){
  Serial.begin(9600);
  vecchiaMediaSonar=1000; //valore arbitrario
  servoSX.attach(9); // - op retromarcia
  servoDX.attach(10); // - operator marcia in avanti
  for(byte y=0;y<5;y++){   //inizializzazione stato e rete neurale
    stato[y]=-1;
    for(byte x=0;x<5;x++){
      reteTemporanea[x][y];
      rete[x][y]=0;
    }
  }      
  //registrare nella rete neurale la memoria prestabilita dei quattro stati principali
  for(byte i=0;i<4;i++){
    //riempire la rete temporanea di valori
    for(byte y=0;y<5;y++){
      for(byte x=0;x<5;x++){
        reteTemporanea[x][y]=memoriaPrestabilita[i][x]*memoriaPrestabilita[i][y]; 
      }
    }
    //aggiungi la rete temporaea alla rete neurale, somma di matrici
    for(byte y=0;y<5;y++){
      for(byte x=0;x<5;x++){
        rete[x][y]+=reteTemporanea[x][y];       
      }
    }
  }
  for(byte y=0;y<5;y++){  //monitoraggio delle reti
    Serial.println(" ");
    for(byte x=0;x<5;x++){
      Serial.print("|");
      Serial.print(rete[x][y]);
    }
  }
  Serial.println(" ");
  azioni(5);       //il robot parte in stop
  Serial.println(" ");
}

void loop(){
  //reset//refresh di stato del robot sincronizzato con i filtri
  if(indiceGenerale>=4-1)
    for(byte i=0;i<5;i++)
      stato[i]=-1;
  //ora stato è pronto per aggiornarsi con gli input provenienti dai sensori
  //sonar
  sonar_filtro(indiceGenerale);
  if(ostacoloC){
    //Serial.println("ostacolo frontale rilevato!");
    stato[1]=1;
    if(CpiuLontano)
      Serial.println("situazione comunque migliorata: ostacolo frontale un po' + distante");
  }
  //IRsinistro
  IRsinistroFiltro(indiceGenerale);
  if(ostacoloSX){
    //Serial.println("ostacolo rilevato a sinistra!");
    stato[0]=1;
  }
  //IRdestro
  IRdestroFiltro(indiceGenerale);
  if(ostacoloDX){
    //Serial.println("ostacolo rilevato a destra!");
    stato[2]=1;
  }
  
  //
  if(indiceGenerale>=4-1){
    // lo stato attuale
    for(byte i=0;i<5;i++){
      Serial.print(stato[i]);
      Serial.print("|");    
    }
    Serial.println(" ");
    //blocco della rete neurale
    bool statoConosciuto=controlloStato();
    if(statoConosciuto){  //inserire qui le azioni
      Serial.println("stato conosciuto!");
      azioni(azione);
    }
    else{
      Serial.println("aiuto, stato sconosciuto!");
      azioni(4);
    }
  }
  // blocco clock spostamento media mobile per i filtro
  indiceGenerale++;
  if(indiceGenerale>=4)
    indiceGenerale=0;
  //
  
    
  /*
   * aggiungere un blocco di aggiornamento di "stato" direttamente in vettori di interi, è inutile passare dal byte
   */
  //
  /*
  //stato generale del robot, questo blocco tratta della condizione di ricompensa
  if(ostacoloSX==false&&ostacoloC==false&&ostacoloDX==false)
    libero=true;
  else
    libero=false;  
  if(ostacoloSX==false&&CpiuLontano==true&&ostacoloDX==false) //Attenzione CpiuLontano è uno stato transitorio!
    quasiLibero=true;
  else
    quasiLibero=false;
    */
  for(byte i=0;i<5;i++){
    //Serial.print(stato[i]);
    //Serial.print("|");    
  }
  //Serial.println(" ");
  delay(20);
}
