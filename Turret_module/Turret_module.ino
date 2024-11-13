#include <Servo.h> 

Servo myservo1;
Servo myservo2;

int pos = 90;

int mainSubmotor = 9; // 방향 전환 서브모터
int reloadSubmotor = 3; // 재장전 서브모터
const int pirPin = 2;  // PIR 센서가 연결된 핀

int trigPin_R = 5;
int echoPin_R = 4;

int trigPin_L = 7;
int echoPin_L = 6;

int threshold = 50;

long Lduration, Rduration, Lcm, Rcm;



void setup() {

  Serial.begin(9600);
  pinMode(pirPin, INPUT);
  pinMode(mainSubmotor,OUTPUT);
  myservo1.attach(mainSubmotor);
  pinMode(reloadSubmotor,OUTPUT);
  myservo2.attach(reloadSubmotor);

  myservo1.write(pos);   

  pinMode(echoPin_L, INPUT);
  pinMode(trigPin_L, OUTPUT);

  pinMode(echoPin_R, INPUT);
  pinMode(trigPin_R, OUTPUT);

  pinMode(A0, OUTPUT);              // 5번핀을 출력모드로 설정합니다.
  pinMode(A1, OUTPUT);              // 6번핀을 출력모드로 설정합니다.
  pinMode(A2, OUTPUT);             // 10번핀을 출력모드로 설정합니다.
  pinMode(A3, OUTPUT);           // 11번핀을 출력모드로 설정합니다.

}

 

void loop()

{
  digitalWrite(trigPin_R, HIGH); //trigPin에서 초음파 발생(echoPin도 HIGH)
  delayMicroseconds(10);
  digitalWrite(trigPin_R, LOW);
  Rduration = pulseIn(echoPin_R, HIGH); //echoPin 이 HIGH를 유지한 시간 저장
  Rcm = ((float)(340 * Rduration) / 10000) / 2;

  digitalWrite(trigPin_L, HIGH); //trigPin에서 초음파 발생(echoPin도 HIGH)
  delayMicroseconds(10);
  digitalWrite(trigPin_L, LOW);
  Lduration = pulseIn(echoPin_L, HIGH); //echoPin 이 HIGH를 유지한 시간 저장
  Lcm = ((float)(340 * Lduration) / 10000) / 2;

  Serial.print("Left = ");
  Serial.print(Lcm);
  Serial.print("cm || ");
  Serial.print("Right = ");
  Serial.print(Rcm);
  Serial.print("cm");
  Serial.println();

  follow();  //초음파 거리를 비교해서 추적
  motion_tracking(); //동작 감지 센서

  delay(100);

}



void follow(){

    if (Lcm <= threshold || Rcm <= threshold){

        if(Lcm + 3 < Rcm){

            pos = pos + 3;}

        if(Rcm + 3 < Lcm){

            pos = pos - 3;}

    }

    if (pos > 160){

        pos = 160;

    }

    if (pos < 20){

        pos = 20;

    }

    myservo1.write(pos);

}

//동작 감지 센서
void motion_tracking() {
  int motion = digitalRead(pirPin); //PIR 센서 감지
  if (motion == HIGH) {  // 움직임이 감지되면
    Serial.print("동작이 감지되었습니다.");
    launch_missile();
    delay(2000);
  }
}

void dc_motorON() {
  analogWrite(A0, 255);
  analogWrite(A1, 0);
  analogWrite(A2, 255);
  analogWrite(A3, 0);
}

// 미사일 발사 코드
void launch_missile() {
  int reload_pos = 0;
  dc_motorON();
  delay(100);
  dc_motorON();
  delay(100);
  dc_motorON();
  delay(100);
  dc_motorON();
  reload_pos = 130;
  myservo2.write(reload_pos);
  delay(150);
  dc_motorON();
  reload_pos = 0;
  myservo2.write(reload_pos);
  delay(100);
  dc_motorON();
  delay(100);
  analogWrite(A0, 0);
  analogWrite(A1, 0);
  analogWrite(A2, 0);
  analogWrite(A3, 0);
}