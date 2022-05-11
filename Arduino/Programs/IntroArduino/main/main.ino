#include <NewPing.h>

int TRIGGER_PIN = 10;  // Arduino pin tied to trigger pin on the ultrasonic sensor.
int ECHO_PIN = 11;  // Arduino pin tied to echo pin on the ultrasonic sensor.
int MAX_DISTANCE = 200; // Maximum distance we want to ping for (in centimeters). Maximum sensor distance 400-500cm.
float pingTime;
float distance;

int out = 7;
int s2 = 6;
int s3 = 5;

int rColor;
int gColor;
int bColor;
unsigned int pulseWidth;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

//Inicializamos funciones
int measureRed();
int measureGreen();
int measureBlue();

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  //Definimos los pines y cuales son outputs
  pinMode(s2,OUTPUT);
  pinMode(s3,OUTPUT);
  //En el sonar el ECHO es INPUT y trigger es OUTPUT
}

void loop() {        
/* ------COLOR SENSOR---------------------------------- */
  rColor = measureRed();
  gColor = measureGreen();
  bColor = measureBlue();
   
  /* 
  Nos interesa exagerar cada color
  Si verde es el mayor, y azul el menor. Me interesa el 255 de verde y dividir entre 2 el del medio, en este caso rojo
  SOn como 6 casos
  */
  if(rColor > gColor && gColor > bColor){
    rColor = 255;
    gColor = gColor/2;
    bColor = 0;
  }
  if(rColor > bColor && bColor > gColor){
    rColor = 255;
    bColor = bColor/2;
    gColor = 0;
  }
  if (gColor > rColor && rColor > bColor){
    gColor = 255;
    rColor = rColor/2;
    bColor = 0;
  }
  if (gColor > bColor && bColor > rColor){
    gColor = 255;
    bColor = bColor/2;
    rColor = 0;
  }
  if (bColor > gColor && gColor > rColor){
    bColor = 255;
    gColor = gColor/2;
    rColor = 0;
  }
  if (bColor > rColor && rColor > gColor){
    bColor = 255;
    rColor = rColor/2;
    gColor = 0;
  }
  

/* ------------------SONAR ----------------------------- */
  pingTime = sonar.ping(); //miliseconds
  pingTime = pingTime/1000000; //Seconds
  distance = (34300*pingTime)/2;

  /* ------- */
  Serial.print(rColor);
  Serial.print(",");
  Serial.print(gColor);
  Serial.print(",");
  Serial.print(bColor);
  Serial.print(",");
  Serial.print(distance);
  Serial.println("");
  delay(100);
}

int measureRed(){
  //let's start by reading Red component
  digitalWrite(s2,LOW);
  digitalWrite(s3,LOW);
  //El sensor envia un pulso y el length del mismo nos dice informacion
  pulseWidth = pulseIn(out,LOW); 
  //Measure pulsewidth of low pulse at outpin on color sensor
  //The longer the pulsewidth the bigger the number but weaker the color. Max pulse could be 102400
  rColor = 255 - pulseWidth/400 - 1; //Reverse so strong color is a large number
  return rColor;

}
int measureGreen(){
  digitalWrite(s2,HIGH);
  digitalWrite(s3,HIGH);
  pulseWidth = pulseIn(out,LOW);
  gColor = 255 - pulseWidth/400 - 1;
  return gColor;
}
int measureBlue(){
  digitalWrite(s2,LOW);
  digitalWrite(s3,HIGH);
  pulseWidth = pulseIn(out,LOW);
  bColor = 255 - pulseWidth/400 - 1;
  return bColor;
}
