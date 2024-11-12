
#include <Servo.h> 

Servo myservo;

int pos = 90;

int trigPin_R = 5;
int echoPin_R = 4;

int trigPin_L = 7;
int echoPin_L = 6;

int threshold = 50;

long Lduration, Rduration, Lcm, Rcm;



void setup() {

   Serial.begin(9600);
   pinMode(9,OUTPUT); 
   myservo.attach(9);    

   myservo.write(pos);   

   pinMode(echoPin_L, INPUT);
   pinMode(trigPin_L, OUTPUT);

   pinMode(echoPin_R, INPUT);
   pinMode(trigPin_R, OUTPUT);

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

   

   follow();

   delay(100);

}



void follow(){

    if (Lcm <= threshold || Rcm <= threshold){

        if(Lcm + 4 < Rcm){

            pos = pos + 4;}

        if(Rcm + 4 < Lcm){

            pos = pos - 4;}

    }

    if (pos > 160){

        pos = 160;

    }

    if (pos < 20){

        pos = 20;

    }

    myservo.write(pos);

}