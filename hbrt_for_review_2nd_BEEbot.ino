 #include "Ultrasonic.h"
#include <Servo.h> 

//SENSORS & ACTUATORS
Ultrasonic ultrasonic(8);
Servo myservoL,myservoR;
byte IRindex=0;
byte IRs[5];
byte buttonState=1;
byte oldButtonState=0;

//BEHAVIOURS
int prob []={1,1,1}; //1st behaviour "hunter", 2nd "prey", 3rd "space lover"
byte oblivion []={0,0,0}; // oblivion counter
String behaviours[]={"hunter","prey","space_lover"};
String choice;
long tMarker=0;
long tMarkerTight=0;
bool reinforcementL=false;
  
void setup() {
  pinMode(6,INPUT_PULLUP);
  Serial.begin(9600);
  myservoL.attach(10); // - op retromarcia
  myservoR.attach(9); // - operator marcia in avanti
  //motorCTRL("stop"); //start in stop
  int dice=random(3);
  choice="prey"; //prey because robot starts in stop
  Serial.println(choice);
}

void loop() {
  IRsmoother();
  buttonSmoother();
  IRindex++;  
  if(IRindex>=4){
    IRindex=0;  //reset
    //IRs monitoring
    for(byte x=0;x<5;x++){
      Serial.print(IRs[x]);
      Serial.print(" ");
    }
    Serial.println(" ");
    //general clock
    if(millis()-tMarkerTight>=1000){
      tMarkerTight=millis();
      //Serial.println("!?");
      tone(7,210,50);
    }
    if(buttonState==0&&oldButtonState!=0&&reinforcementL==false){
      reinforcementL=true;
      Serial.println("RL happening!");
      for(int x=0;x<1000;x++){
        tone(7,210+x,50);
        delay(1);
      }
      if(choice=="hunter"){
        prob[0]++;
        oblivion[0]=0;
      }
      if(choice=="prey"){
        prob[1]++;
        oblivion[1]=0;
      }
      if(choice=="space_lover"){
        prob[2]++;    
        oblivion[2]=0;
      }
    }
    oldButtonState=buttonState;

    //reinforcement learning block
    if(millis()-tMarker>=5000){
      tMarker=millis();
      reinforcementL=false;
      //oblivion check
      for(byte x=0;x<3;x++){ 
        if(oblivion[x]==2){//2 is oblivion threshold
          Serial.print("oblivion happening on: ");
          Serial.println(behaviours[x]);
          oblivion[x]=0;
          prob[x]--;
          if(prob[x]<=1)
            prob[x]=1;          
        }
      }
      int pool=0;
      for(byte x=0;x<3;x++)
        pool+=prob[x];
      int dice=random(pool)+1; //escludiamo lo zero!
      Serial.print("this is prob distr: ");
      for(byte x=0;x<3;x++){
        Serial.print(prob[x]);
        Serial.print(" ");
      }
      Serial.println(" ");
      Serial.print("this is dice: ");
      Serial.println(dice);
      if(dice>=1&&dice<=prob[0]){
        choice="hunter";
        oblivion[0]++;
      }
      if(dice>prob[0]&&dice<=prob[0]+prob[1]){
        choice="prey";
        oblivion[1]++;
      }
      if(dice>prob[0]+prob[1]&&dice<=prob[0]+prob[1]+prob[2]){
        choice="space_lover";      
        oblivion[2]++;
      }
      Serial.println(choice);
    }
    
  }
  //insert actions-choice
  //if(choice=="prey){} OR if(choice=="hunter"){} ecc...
  delay(8);
}
