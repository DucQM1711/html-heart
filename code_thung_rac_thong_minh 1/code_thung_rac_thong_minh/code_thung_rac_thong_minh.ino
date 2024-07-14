#include <Servo.h>

Servo servo;
const int servoPin = 12;
const int openTrash = 160; // Góc mở (110 độ)
const int closeTrash = 0; // Góc đóng (0 độ)

const int trigPin = 5;
const int echoPin = 4;
const int distanceThreshold = 20; // Ngưỡng khoảng cách (20 cm)

const int readInterval = 100; // ms

float distance;
bool isOpen = false;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  servo.attach(servoPin);
  servo.write(closeTrash); // Đảm bảo servo ở vị trí đóng ban đầu
}

void loop() {
  distance = readDistance();
  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance <= distanceThreshold && !isOpen) {
    isOpen = true;
    Serial.println("Opening Trash...");
    servo.write(openTrash); // Mở ra góc 110 độ
    delay(2500); // Đợi 1 giây để servo hoàn thành quay
  } else if (distance > distanceThreshold && isOpen) {
    isOpen = false;
    Serial.println("Closing Trash...");
    servo.write(closeTrash); // Đóng lại góc 0 độ
    delay(1000); // Đợi 1 giây để servo hoàn thành quay
  }
}

float readDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  float distance = duration / 58.00; // Chuyển đổi thời gian thành khoảng cách (cm)

  return distance;
}
