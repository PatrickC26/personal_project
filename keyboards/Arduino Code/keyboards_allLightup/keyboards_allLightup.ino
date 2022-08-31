const int allkeys[] = {2,3,4,5,6,7,8,9,15};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(10,OUTPUT);
  analogWrite(10, 10);

  for (int i = 0 ; i < 9 ; i++){
    pinMode(allkeys[i], OUTPUT);
    digitalWrite(allkeys[i],0);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("AD");
}
