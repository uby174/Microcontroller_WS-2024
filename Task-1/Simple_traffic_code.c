#define GREEN 10
#define YELLOW 11
#define RED 12
int state=0 ;


void setup()
{
  pinMode(GREEN, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(RED, OUTPUT);
}

void loop()  
{  
  trafficLight();  
}



void trafficLight()
{ 
  state= RED;
  
  switch (state)
  {    
	case RED:
	redON();
    delay(2000);
    
    case YELLOW:
    yellowON();
    delay(2000);
       
    case GREEN:
	greenON();
    delay(2000);
    yellowON();
    delay(2000);
    }
}

void greenON()
{
  digitalWrite(GREEN, HIGH);
  digitalWrite(YELLOW, LOW);
  digitalWrite(RED, LOW);
}

void yellowON()
{
  digitalWrite(GREEN, LOW);
  digitalWrite(YELLOW, HIGH);
  digitalWrite(RED, LOW);
}

void redON()
{
  digitalWrite(GREEN, LOW);
  digitalWrite(YELLOW, LOW);
  digitalWrite(RED, HIGH);
}
