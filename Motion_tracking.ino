const int pirPin = 7;  // PIR 센서가 연결된 핀

void setup() {
  pinMode(pirPin, INPUT);
  Serial.begin(9600);  // Raspberry Pi와 통신을 위해 Serial 시작
}

void loop() {
  int motion = digitalRead(pirPin);
  
  if (motion == HIGH) {  // 움직임이 감지되면
    Serial.println("Motion Detected");  // 신호 전송
    delay(17000);  // 17초 대기 후 다시 체크 (감지 후 재감지까지의 시간 설정)
  }
}