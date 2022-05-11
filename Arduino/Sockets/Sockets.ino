

float percent = 0;
float prevPercent = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  percent = round(analogRead(2)/1024.00*100);
  if(percent != prevPercent){
    Serial.println(percent);
    prevPercent = percent;
  }
  delay(100);
}
