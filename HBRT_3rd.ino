#include "Ultrasonic.h"
#include <Servo.h> 
/*debug list
 * 1 perché space lover tartaglia? Forse perché non c'è filtraggio di ultrasonic, qual è la soglia?
 * 2 perché hunter a volte riconosce il moving object ma non si muove? 
 * 3  Ora ho dei problemi in prey
 */

//SENSORS & ACTUATORS
Ultrasonic ultrasonic(8);
byte ultraIn=0;  //ultrasonic incoming value
byte oldUltraIn;
byte threshold=20+5; 
Servo myservoL,myservoR;
byte motorState=3;
byte IRindex=0;
byte IRs[5];
byte buttonState=1;
byte oldButtonState=0;
bool audioOn=1;
byte click_tone_dur=50-20;

//BEHAVIOURS
int prob []={1,1,1}; //1st behaviour "hunter", 2nd "prey", 3rd "space lover"
byte oblivion []={0,0,0}; // oblivion counter
String behaviours[]={"hunter","prey","space_lover"};
String choice;
byte learningClock=0;
long tMarkerTight=0;
bool reinforcementL=false;

bool open_space_search_toggle=1; //reset handle for "go_for_open_spaces" behaviour
byte moving;//reset handle for "escape_from_moving_object---moving_object_detection" behaviour
//long oldU;
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
  ultrasonicSmoother();
  //u=ultrasonic.MeasureInCentimeters(); //i dati provenienti da ultrasonic non vengono filtrati
  //Serial.println(u);
  
  IRindex++;  
  if(IRindex>=4){ //ciclo generale di filtraggio a 4 cicli
    IRindex=0;  //reset
    //general clock assoluto
    if(millis()-tMarkerTight>=1000){
      tMarkerTight=millis();
      learningClock++;
      if(audioOn){
        if(learningClock<5)
          tone(7,210,click_tone_dur);
        else
          tone(7,210,click_tone_dur*3);
        //click_tone_dur=20;
      }
    }
    if(buttonState==0&&oldButtonState!=0&&reinforcementL==false){
      reinforcementL=true;
      //Serial.println("apprendimento in corso");
      for(int x=0;x<1000;x++){ //melodia di conferma
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

    //ogni 5 secondi il robot sceglie un nuovo behaviour
    if(learningClock>=5){
      learningClock=0;      
      reinforcementL=false;
      //oblivion check
      for(byte x=0;x<3;x++){ 
        if(oblivion[x]==2){//2 is oblivion threshold
          //Serial.print("oblivion happening on: ");
          //Serial.println(behaviours[x]);
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
      //Serial.print("this is prob distr: ");
      for(byte x=0;x<3;x++){
        //Serial.print(prob[x]);
        //Serial.print(" ");
      }
      //Serial.println(" ");
      //Serial.print("this is dice: ");
      //Serial.println(dice);
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
    //***
    //choice="space_lover";//just for debug
    //***
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
  motorCTRL(bitRead(motorState,1),bitRead(motorState,0),bitRead(motorState,2));
  delay(4); 
}
