const int ledPIN = 9;
int i;
char data;
void setup(){
  Serial.begin(9600);
  pinMode(ledPIN , OUTPUT); 
}

void loop(){
  if (Serial.available()){
    data = Serial.parseInt();
    while(i < 5){
      digitalWrite(ledPIN , HIGH);
      delay(data*100);
      digitalWrite(ledPIN , LOW);
      delay(data*200);
      i++;
    }
    i = 0;
  }
}