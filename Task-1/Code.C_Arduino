#include <stdio.h>
#include <unistd.h> //By including the <unistd.h> header file we are able to use the sleep function

#define RED 3
#define YELLOW 2
#define GREEN 1

#define true 1
#define false 0

void statemachine(){
    
    int green_pass;
    int state = RED; // state definition (initial/starting state)
    
    switch(state){
        case RED:
            sleep(2); // event to initiate state transition
            state = YELLOW;
            green_pass = true;
            break;
        
        case YELLOW:
            if(green_pass==true){    //condition
              sleep(1);
              state = GREEN;
              break;
            }
            else if(green_pass==false){
                sleep(1);
                state = RED;
                break;
            }
            
        case GREEN:
            sleep(2);
            state = YELLOW;
            green_pass = false;
            break;
            
    }
}
