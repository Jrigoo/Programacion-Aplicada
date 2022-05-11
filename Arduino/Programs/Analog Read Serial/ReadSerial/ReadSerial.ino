int in = 9;        
// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);
  pinMode(in, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // set the brightness of pin 9:
  
  Serial.println(analogWrite(in, 5););

}
