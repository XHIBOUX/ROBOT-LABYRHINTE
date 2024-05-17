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

long readUltrasonicDistance() {
  // Mesurer la distance avec le capteur ultrason
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2;
}

void loop() {

  // Lire la distance en face
  myServo.write(90);
  delay(500);
  distance = readUltrasonicDistance();
  
  // Vérifier la distance mesurée et ajuster les mouvements du robot en conséquence
  if (distance > 20) { // Si la distance est supérieure à 20 cm, avancer
    carAdvance(100, 100);
  } else { // Sinon, stop 
    carStop();
    delay(500); // Attendre un court instant pour tourner

    // Lire la distance à gauche
    myServo.write(0);
    delay(500);
    int distanceLeft = readUltrasonicDistance();

     // Lire la distance à droite
    myServo.write(180);
    delay(500);
    int distanceRight = readUltrasonicDistance();

    // Ramener le servo en position centrale
    myServo.write(90);
    delay(500);

    if (distanceLeft > 20) {
      carTurnLeft(100, 100);
      delay(500); // Attendre un court instant pour tourner
    } else if (distanceRight > 20) {
      carTurnRight(100, 100);
      delay(500); // Attendre un court instant pour tourner
    } else {
      // Si aucune direction n'est libre, faire demi-tour
      carTurnRight(100, 100);
      delay(1000); // Attendre plus longtemps pour faire un demi-tour
    }
  }
  delay(100);
}

void carStop() {
  // Arrêter les moteurs
  analogWrite(speedPin_M1, 0);
  analogWrite(speedPin_M2, 0);
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
