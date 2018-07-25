#include "Ultrasonic.h"
#include <Servo.h> 

//SENSORS & ACTUATORS
Ultrasonic ultrasonic(8);
long u;  //ultrasonic incoming value
Servo myservoL,myservoR;
byte motorState=3;
byte IRindex=0;
byte IRs[5];
byte buttonState=1;
byte oldButtonState=0;
bool audioOn=true;
byte click_tone_dur=50;

//BEHAVIOURS
int prob []={1,1,1}; //1st behaviour "hunter", 2nd "prey", 3rd "space lover"
byte oblivion []={0,0,0}; // oblivion counter
String behaviours[]={"hunter","prey","space_lover"};
String choice;
long tMarker=0;
long tMarkerTight=0;
bool reinforcementL=false;

bool open_space_search_toggle=1; //reset handle for "go_for_open_spaces" behaviour
byte moving;//reset handle for "escape_from_moving_object---moving_object_detection" behaviour
long oldU;
byte moving_index=0; //as previous comment
bool escape_from_movingO_toggle=1;
bool hunt_movingO_toggle=1;
  
void setup() {
  pinMode(6,INPUT_PULLUP);
  Serial.begin(9600);
  myservoL.attach(10); // - op retromarcia
  myservoR.attach(9); // - operator marcia in avanti
  //motorCTRL("stop"); //start in stop
  int dice=random(3);
  choice="prey"; //prey because robot starts in stop
  Serial.println(choice);
  motorCTRL(1,1,0); //start in stop
}

void loop() {
  IRsmoother();
  buttonSmoother();
  u=ultrasonic.MeasureInCentimeters();
  /*
  Serial.print(u);//0~400cm
  Serial.println(" cm");
  */
  IRindex++;  
  if(IRindex>=4){
    IRindex=0;  //reset
    //IRs monitoring uncomment to check
    /*
    for(byte x=0;x<5;x++){
      Serial.print(IRs[x]);
      Serial.print(" ");
    }
    Serial.println(" ");
    */
    //general clock
    if(millis()-tMarkerTight>=1000){
      tMarkerTight=millis();
      if(audioOn){
        tone(7,210,click_tone_dur);
        click_tone_dur=50/5;
      }
    }
    if(buttonState==0&&oldButtonState!=0&&reinforcementL==false){
      reinforcementL=true;
      Serial.println("RL happening!");
      for(int x=0;x<1000;x++){
        if(audioOn){
          tone(7,210+x,50);
          delay(1);
        }
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
      tone(7,210,click_tone_dur*8);
    }
    //choice="prey"; //forcing choice just for arranging debugging
    //behaviours arranger tree, going top down based on competence level
    if(choice=="hunter")
      hunt_moving_objects(0,0);
    if(choice=="prey")
      escape_from_moving_objects(0,0);
    if(choice=="space_lover")
      go_for_open_spaces(0,0);
    
    if(choice=="hunter"||choice=="space_lover")
      obstacleDetection(1,0);
    else
      obstacleDetection(0,0);
    
  }
  //fare le somme vettoriali!!! devo fare una variabilie motorState per ogni behaviour
  motorCTRL(bitRead(motorState,1),bitRead(motorState,0),bitRead(motorState,2));
  delay(10); //10 by default
}
