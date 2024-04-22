void temperature(){
  int Vo1 , Vo2 ;
  float  T1 , T2 ;
  
  Vo1 = analogRead(ThermistorPin1);
  Vo2 = analogRead(ThermistorPin2);

  T1 = Thermistor(analogRead(ThermistorPin1));
  T2 = Thermistor(analogRead(ThermistorPin2));

  Serial.print("Temperature: ");
  Serial.print(" T1: ");
  Serial.print(T1);
  Serial.print(" C ");
  Serial.print(" T2: ");
  Serial.print(T2);
  Serial.print(" C ");
  Serial.println();

  String a  = 'U' + String(T1) + '%';
  String b  = 'V' + String(T2) + '%';

  esp.print(a);
  esp.print(b);

//  Serial.println(a);
//  Serial.println(b);
//  Serial.println(c);
}

float Thermistor(int Vo) {
  float A = 1.009249522e-03, B = 2.378405444e-04, C = 2.019202697e-07, T = 0.0;
  float logRt = log(10000.0*((1024.0/Vo-1))); 
  T = (1.0 / (A + B*logRt + C*logRt*logRt*logRt));
  Serial.print(T);
  Serial.print('\t');
  T = -0.00015*T*T + 0.4533*T -123.57;
  Serial.print(T);
  Serial.print('\t');
  return T;
}
