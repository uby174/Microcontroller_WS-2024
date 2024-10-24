include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define TRUE 1
#define FALSE 0

#define TG 1
#define TY 2
#define TR 3
#define Traffic_waiting 4

int T_state = TG;
  
#define PR 1
#define PG 2
#define Pedestrian_waiting 3
  
int P_state = PR;
  
int Button = 2;

int pass;
  
int green_pass;
  
  
int Pin_T_red=13;
int Pin_T_yellow =12;
int Pin_T_green = 11;

int Pin_P_red=9;
int Pin_P_green=8;

int Button = 2;

int msg

  
  void* P_switch_machine(){

  switch(P_state){
  case PR:
      P_state = PG;
    //turn pedestrian light to green
    LED(Pin_P_red, HIGH);
    delay(10000);
    if(Button ==TRUE){
              P_state = Pedestrian_waiting;
    pass = FALSE
  }
   case PG:
     P_state = PR;
     delay(10000);
     //turn pedestrian light to red
     LED(P_green, HIGH);
     if(Button ==TRUE){
              P_state = Pedestrian_waiting;
    
  }
    
    case Pedestrian_waiting:
      if(pass == TRUE{
        P_state = PG;
      }
}

} 
 
  
  
  void* T_switch_machine(){

  switch(T_state){
  case TG:
    //turn Trafic red light
    LED(Pin_T_green, HIGH);
    delay(10000);
    if(Button==FALSE){
        T_state = TY;
    msg = FALSE
    }
  case TY:
    delay(5000);
    green_pass = TRUE;
     //turn traffic yellow light
      LED(Pin_T_yellow, HIGH);
      if(green_pass){
        T_state = TR;
    }
    else if((!green_pass)&& (msg1 ==TRUE)){
    T_state = TG;
      //turn traffic yellow light
      LED(Pin_T_yellow, HIGH);
    }
    
  case TR:
    delay(10000);
    //trun traffic red light
    LED(Pin_T_red, HIGH);
    
    
    T_state = TY;
    green_pass = FALSE;
    Button = FALSE; //reset button
    pass = TRUE;
    msg = TRUE;
}
  }

  void LED(int pinId, int level){
    digitalWrite(pinId, level);
  }

void* tloop(){
  while(TRUE){
    T_switch_machine;
  }
}

void* plloop(){
  while(TRUE){
    P_switch_machine;
  }
}


int main(int argc, char* argv[]){
    pthread_t t1, t2;
    
    if(pthread_create(&t1, NULL, tloop,NULL)!=0){
        return 1;
        printf("Error 1");
    }
    if(pthread_create(&t2, NULL, plloop,NULL) !=0){
        return 2;
        printf("Error 2");
    }
    if(pthread_join(t1, NULL) != 0){
        return 3;
        printf("Error 3");
    }
    if(pthread_join(t2, NULL) !=0){
        return 4;
        printf("Error 4");
    }
    
    
    return 0;
}  

void setup()
{
  pinMode(Button, INPUT); 
  attachInterrupt(digitalPinToInterrupt(Button), ISR_Button, CHANGE);
  
  pinMode(Pin_T_red,OUTPUT);
  pinMode(Pin_T_yellow,OUTPUT);
  pinMode(Pin_T_green,OUTPUT);
  
  pinMode(Pin_P_red,OUTPUT);
  pinMode(Pin_P_green,OUTPUT);
}


void loop(){


}

void ISR_Button(){ /*Definition of interrupt function for pedestrian push button*/
  digitalWrite(Pin_P_green, HIGH);
  digitalWrite(Pin_P_red, LOW); //off
  
  digitalWrite(Pin_T_red, HIGH); //on
  digitalWrite(Pin_T_yellow, LOW); //off
  digitalWrite(Pin_T_green, LOW); //off
  
}
