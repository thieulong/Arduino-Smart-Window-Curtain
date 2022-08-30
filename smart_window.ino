             #include <AFMotor.h>
#include <Servo.h>

// Light sensor
int light_sensor = A0; 

// Rain sensor
const int capteur_D = 13;
const int capteur_A = A1;

// DC motor 
AF_DCMotor dc_motor(1, MOTOR12_64KHZ);
int motorFlag = 0;

// Servo motor 
Servo servo1;
Servo servo2;
int servoFlag = 0;

void setup() {
  
  Serial.begin(9600);
  
  pinMode(capteur_D, INPUT);
  pinMode(capteur_A, INPUT);

  dc_motor.setSpeed(70);

  servo1.attach(9);
  servo2.attach(10);
  
}

void loop() {
  int raw_light = analogRead(light_sensor); 
  int light = map(raw_light, 0, 1023, 0, 100); 
 
  Serial.print("Light sensor: "); 
  Serial.println(light); 
  Serial.print("Rain sensor: ");
  Serial.println(digitalRead(capteur_D));

   if(digitalRead(capteur_D) == HIGH) {
      if (light > 10){
        openWindow();
        delay(500);
        if (motorFlag == 0){
          openCurtain();
          stopCurtain();
          motorFlag++;
        }
      }else{
        if (motorFlag == 1){
          closeCurtain();
          stopCurtain();
          motorFlag--;
        }
        closeWindow();
        delay(500);
      }
   }else{
      Serial.println("Rain sensor : WET");
      closeWindow();
      delay(500);
   }
}

void openWindow() {
  servo1.write(0);
  servo2.write(180);
}

void closeWindow() {
  servo1.write(90);
  servo2.write(90);
}

void openCurtain() {
  dc_motor.run(FORWARD);
  delay(400);
}

void closeCurtain() {
  dc_motor.run(BACKWARD);
  delay(300);
}

void stopCurtain() {
  dc_motor.run(RELEASE);
}
