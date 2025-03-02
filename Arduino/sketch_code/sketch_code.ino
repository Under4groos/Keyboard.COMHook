void setup() {

  Serial.begin(9600);
  Serial.print("asd");
}

char inData[3];
void loop() {

  if (Serial.available()) {
    Serial.readBytes(inData, 3);

    int value_1 =  (int)inData[1];
    Serial.println(value_1);
  }
}
