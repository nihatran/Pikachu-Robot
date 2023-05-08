/*
  Motor Wiring Guide:
  up left: OUT4
  down left: OUT3
  up right: OUT2
  down right: OUT1
*/

int trigPin = 12;
int echoPin = 11;
int leftSpeed = 9; // ENB
int leftB = 8; // IN4
int leftA = 7; // IN3
int rightSpeed = 6; // ENA
int rightB = 5; // IN2
int rightA = 4; // IN1
int leftLED = 3; // for LEDs, use right side (output pin side) ground pin
int rightLED = 2;
float duration_us, distance_cm;
int turnVal = 0;

/*
  forward
  moves the robot forwards and turns on both LEDs.
*/

void forward()
{
  // Adjustments to motor speed may be necessary for robot to move in a straight line.
  // Max speed for motor == 255
  digitalWrite(leftA, HIGH);
  digitalWrite(leftB, LOW);
  analogWrite(leftSpeed, 210); // left speed is less than right speed due to uneven motor speeds.
  digitalWrite(rightA, HIGH);
  digitalWrite(rightB, LOW);
  analogWrite(rightSpeed, 255);
  digitalWrite(leftLED,HIGH);
  digitalWrite(rightLED,HIGH);
  Serial.println("Moving!");//debug
}

/*
  stop
  stops the robot, turns off LEDs, and waits 0.5 seconds.
*/

void stop()
{
  digitalWrite(leftA, LOW);
  digitalWrite(leftB, LOW);
  digitalWrite(rightA, LOW);
  digitalWrite(rightB, LOW);
  digitalWrite(leftLED,LOW);
  digitalWrite(rightLED,LOW);
  delay(500);
  Serial.println("Stopped.");//debug
}

/*
  turn
  Turns the robot ~135 degrees either left or right.
  If variable turnVal == 0, turn to the right. If turnVal == 1, turn to the left.
  When turning left, only the left LED will be on.
  When turning right, only the right LED will be on.
*/

void turn()
{
  if (turnVal == 0)
  {
    // Turn right
    Serial.println("RIGHT");//debug
    
    // Turn on right side LED
    digitalWrite(rightLED,HIGH);

    // Left wheel goes forwards

    digitalWrite(leftA, HIGH);
    digitalWrite(leftB, LOW);
    analogWrite(leftSpeed, 255);

    // Right wheel goes backwards

    digitalWrite(rightA, LOW);
    digitalWrite(rightB, HIGH);
    analogWrite(rightSpeed, 255);
    
    delay(1000);
    
    stop();
    
    Serial.println("Turn right complete.");
    turnVal = 1; // Change turnVal to 1
  } else
  {
    // Turn left
    Serial.println("LEFT");//debug
    
    // turn on left LED
    digitalWrite(leftLED,HIGH);
    
    // Left wheel goes backwards
    
    digitalWrite(leftA, LOW);
    digitalWrite(leftB, HIGH);
    analogWrite(leftSpeed, 255);
    
    // Right wheel goes forwards

    digitalWrite(rightA, HIGH);
    digitalWrite(rightB, LOW);
    analogWrite(rightSpeed, 255);
    
    delay(1000);
    
    stop();
    
    Serial.println("Turn left complete.");
    turnVal = 0; // Change turnVal back to 0
  }
}

void setup()
{
  // begin serial communication with 9600 baudrate speed
  Serial.begin (9600);

  // configure the trigger pin to output mode
  pinMode(trigPin, OUTPUT);
  // configure the echo pin to input mode
  pinMode(echoPin, INPUT);

  // Pins for Motor
  pinMode(leftA, OUTPUT);
  pinMode(leftB, OUTPUT);
  pinMode(leftSpeed, OUTPUT);
  pinMode(rightA, OUTPUT);
  pinMode(rightB, OUTPUT);
  pinMode(rightSpeed, OUTPUT);
  // Pins for LEDs
  pinMode(leftLED,OUTPUT);
  pinMode(rightLED,OUTPUT);
}

void loop()
{
  // generate 10-microsecond pulse to TRIG pin
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // measure duration of pulse from ECHO pin
  duration_us = pulseIn(echoPin, HIGH);

  // calculate the distance
  distance_cm = 0.017 * duration_us;// Speed of sound wave, 0.034m/us divided by 2

  // print the value to Serial Monitor
  Serial.print("distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  // if sensor distance reads above 30cm, move forwards. Else, stop and turn

  if (distance_cm > 30)
  {
    forward();
  } else
  {
    stop();
    turn();
  }
  
  delay(500);
}
