int data;

// Left ultrasonic sensor pins
int l_trigPin = 13;
int l_echoPin = 12;

// Right ultrasonic sensor pins
int r_trigPin = 3;
int r_echoPin = 2;

// Motor pins
int RightMotor_E_pin = 5;   // Right motor PWM control pin
int LeftMotor_E_pin = 6;    // Left motor PWM control pin
int RightMotor_1_pin = 8;   // Right motor direction pin
int RightMotor_2_pin = 9;   // Right motor direction pin
int LeftMotor_3_pin = 10;   // Left motor direction pin
int LeftMotor_4_pin = 11;   // Left motor direction pin

int L_MotorSpeed = 250;     // Left motor speed
int R_MotorSpeed = 250;     // Right motor speed
int obstacleThreshold = 30; // Threshold distance in cm for obstacle detection

void setup() {
  pinMode(4, INPUT);
  // Motor pin setup
  pinMode(RightMotor_E_pin, OUTPUT);
  pinMode(LeftMotor_E_pin, OUTPUT);
  pinMode(RightMotor_1_pin, OUTPUT);
  pinMode(RightMotor_2_pin, OUTPUT);
  pinMode(LeftMotor_3_pin, OUTPUT);
  pinMode(LeftMotor_4_pin, OUTPUT);

  // Ultrasonic sensor pins setup
  pinMode(l_trigPin, OUTPUT);
  pinMode(l_echoPin, INPUT);
  pinMode(r_trigPin, OUTPUT);
  pinMode(r_echoPin, INPUT);

  Serial.begin(9600);
  Serial.println("Welcome Eduino!");
}

void loop() {
  data = digitalRead(4);
  if(data == 1)
  {
    L_MotorSpeed = 0;
    R_MotorSpeed = 0;
  }
  else if(data == 0)
  {
    L_MotorSpeed = 250;
    R_MotorSpeed = 250;
  }

  // Get distance from both ultrasonic sensors sequentially to avoid interference
  int l_Ultra_d = getDistance(l_trigPin, l_echoPin);
  delay(50);  // Small delay to avoid sensor interference
  int r_Ultra_d = getDistance(r_trigPin, r_echoPin);

  Serial.print("Left Distance: ");
  Serial.println(l_Ultra_d);
  Serial.print("Right Distance: ");
  Serial.println(r_Ultra_d);

  // Move forward by default
  motorControl(HIGH, HIGH);

  // Check for obstacles within the threshold distance
  if (l_Ultra_d < obstacleThreshold || r_Ultra_d < obstacleThreshold) {
    // Stop motors
    motorControl(LOW, LOW);
    delay(1000);  // Short delay before turning

    // Decide turn direction based on which side has more distance
    if (l_Ultra_d < r_Ultra_d) {
      Serial.println("Turning Right...");

      motorControl(HIGH, LOW);  // Turn right (set the right motor to move backward)
      delay(400);
    } else {
      Serial.println("Turning Left...");
   
      motorControl(LOW, HIGH);  // Turn left (set the left motor to move backward)
      delay(400);
    }
  }
}

// Function to control motor direction and speed
void motorControl(int R_motor, int L_motor) {
  // Control Right motor direction
  digitalWrite(RightMotor_1_pin, R_motor);
  digitalWrite(RightMotor_2_pin, !R_motor);

  // Control Left motor direction
  digitalWrite(LeftMotor_3_pin, L_motor);
  digitalWrite(LeftMotor_4_pin, !L_motor);

  // Control motor speed using PWM
  analogWrite(RightMotor_E_pin, R_MotorSpeed);
  analogWrite(LeftMotor_E_pin, L_MotorSpeed);
}

// Function to get distance from an ultrasonic sensor
int getDistance(int trigPin, int echoPin) {
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 30000);  // Timeout added for pulseIn

  // Calculate distance (in cm): duration * 0.0343 / 2
  distance = (duration * 0.0343) / 2;

  // Return a default high value if out of range or timeout occurred
  if (distance == 0 || distance > 400) {
    return 400;  // Maximum range for most ultrasonic sensors
  }
  return distance;
}