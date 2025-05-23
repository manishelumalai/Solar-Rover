

/* Fill in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPL3eXiFkXWx"
#define BLYNK_TEMPLATE_NAME "Rover Control"
#define BLYNK_AUTH_TOKEN "my9hU3ch9Xm1wYo23fKUh1W0fjqgAEh_"


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Realme 9 Pro 5G";
char pass[] = "manish32";


#define IN1 26 //18
#define IN2 27 //19
#define IN3 18 //26
#define IN4 19 //27
#define ENA 32  // PWM pin for Motor A
#define ENB 15  // PWM pin for Motor B // Relay connected to GPIO 2 for motor control
#define PUMP_RELAY_PIN 2

// Motor speed variables
int motorspeedA = 255; // Default max speed
int motorspeedB = 255;

// Motor Control Functions
void moveForward() {
  analogWrite(ENA,motorspeedA);
  analogWrite(ENB,motorspeedB);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
   Serial.println("moving forward");
}

void moveBackward() {
  analogWrite(ENA,motorspeedA);
  analogWrite(ENB,motorspeedB);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
   Serial.println("moving backward");
}

void turnLeft() {
  analogWrite(ENA,motorspeedA);
  analogWrite(ENB,motorspeedB);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
   Serial.println("turning left");
}

void turnRight() {
  analogWrite(ENA,motorspeedA);
  analogWrite(ENB,motorspeedB);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
   Serial.println("turning right");
}

void stopMotors() {
  analogWrite(ENA,0);
  analogWrite(ENB,0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
   Serial.println("parking");
}

// Blynk Functions
BLYNK_WRITE(V0) {  // Forward button
  if (param.asInt()) moveForward();
  else stopMotors();
}

BLYNK_WRITE(V1) {  // Backward button
  if (param.asInt()) moveBackward();
  else stopMotors();
}

BLYNK_WRITE(V2) {  // Left button
  if (param.asInt()) turnLeft();
  else stopMotors();
}

BLYNK_WRITE(V3) {  // Right button
  if (param.asInt()) turnRight();
  else stopMotors();
}

// Speed control for both motors
BLYNK_WRITE(V4) {  // Button for pump relay control
  if (param.asInt()) {
    digitalWrite(PUMP_RELAY_PIN, HIGH); // Turn pump relay ON
    Serial.println("Pump Relay ON");
  } else {
    digitalWrite(PUMP_RELAY_PIN, LOW); // Turn pump relay OFF
    Serial.println("Pump Relay OFF");
  }
}

void setup() {
  // Initialize serial and motor pins
  Serial.begin(115200);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(PUMP_RELAY_PIN, OUTPUT);

  stopMotors(); // Ensure motors are off initially // Ensure motor relay is off initially
  digitalWrite(PUMP_RELAY_PIN, LOW); 
  // Connect to Blynk
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();
}

