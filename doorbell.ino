#include <Servo.h>

Servo servo;  // create servo object to control a servo

int remaining = 0;
bool wasPressed = false;
unsigned long timerStart = 0;
unsigned long pressCount = 0;

void setup() {
  servo.attach(2);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
}

void loop() {
//  servo.write(4);
//  delay(2000);
//  servo.write(15);
//  delay(2000);
  
  int value = analogRead(A0);
  bool isPressed = value > 400;
  unsigned long time = millis();
  
  if (isPressed != wasPressed) {
    if (isPressed) Serial.print("open: "); 
    Serial.println(value);
  }

  if (isPressed && !wasPressed) {
    if (time - timerStart > 1000) {
      Serial.print("reset counter: ");
      Serial.println(time - timerStart);
      timerStart = time;
      pressCount = 0;
    }

    ++pressCount;
    Serial.print("counter: ");
    Serial.println(pressCount);

    if (pressCount >= 4) {
      remaining = 200;
    }
  }

  wasPressed = isPressed;

  if (remaining > 0) {
    servo.write(4);
    remaining -= 1;
  } else {
    servo.write(15);
  }

  delay(10);
}
