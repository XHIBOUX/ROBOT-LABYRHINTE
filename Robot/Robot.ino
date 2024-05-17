#include <Servo.h> // Inclure la bibliothèque du servo moteur

// Déclaration des broches de contrôle des moteurs
int speedPin_M1 = 5;     // Contrôle de vitesse M1
int speedPin_M2 = 6;     // Contrôle de vitesse M2
int directionPin_M1 = 4; // Contrôle de direction M1
int directionPin_M2 = 7; // Contrôle de direction M2

// Broches du capteur ultrason
const int trigPin = 9;  // Broche de déclenchement du capteur ultrason
const int echoPin = 10; // Broche de réception du capteur ultrason

// Broche du servo moteur
const int servoPin = 11; // Broche de contrôle du servo moteur

// Variables pour la distance mesurée par le capteur ultrason
long duration;
int distance;

Servo myServo; // Déclaration de l'objet servo moteur

void setup() {
  // Initialisation des broches de contrôle des moteurs en tant que sorties
  pinMode(speedPin_M1, OUTPUT);
  pinMode(speedPin_M2, OUTPUT);
  pinMode(directionPin_M1, OUTPUT);
  pinMode(directionPin_M2, OUTPUT);

  // Initialisation des broches du capteur ultrason
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Initialisation de la broche du servo moteur
  myServo.attach(servoPin);
  myServo.write(90);

  Serial.begin(9600);
}

void loop() {
  // Mesurer la distance avec le capteur ultrason
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  // Vérifier la distance mesurée et ajuster les mouvements du robot en conséquence
  if (distance > 20) { // Si la distance est supérieure à 20 cm, avancer
    carAdvance(100, 100);
  } else { // Sinon, tourner à gauche
    carTurnLeft(100, 100);
    delay(500); // Attendre un court instant pour tourner
  }
}

void carStop() {
  // Arrêter les moteurs
  digitalWrite(speedPin_M2, 0);
  digitalWrite(directionPin_M1, LOW);
  digitalWrite(speedPin_M1, 0);
  digitalWrite(directionPin_M2, LOW);
}

void carBack(int leftSpeed, int rightSpeed) {
  // Reculer
  analogWrite(speedPin_M2, leftSpeed);
  digitalWrite(directionPin_M1, HIGH);
  analogWrite(speedPin_M1, rightSpeed);
  digitalWrite(directionPin_M2, HIGH);
}

void carAdvance(int leftSpeed, int rightSpeed) {
  // Avancer
  analogWrite(speedPin_M2, leftSpeed);
  digitalWrite(directionPin_M1, LOW);
  analogWrite(speedPin_M1, rightSpeed);
  digitalWrite(directionPin_M2, LOW);
}

void carTurnLeft(int leftSpeed, int rightSpeed) {
  // Tourner à gauche
  analogWrite(speedPin_M2, leftSpeed);
  digitalWrite(directionPin_M1, LOW);
  analogWrite(speedPin_M1, rightSpeed);
  digitalWrite(directionPin_M2, HIGH);
}

void carTurnRight(int leftSpeed, int rightSpeed) {
  // Tourner à droite
  analogWrite(speedPin_M2, leftSpeed);
  digitalWrite(directionPin_M1, HIGH);
  analogWrite(speedPin_M1, rightSpeed);
  digitalWrite(directionPin_M2, LOW);
}
