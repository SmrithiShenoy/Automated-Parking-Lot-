#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);
Servo myservo;

#define TRIG 9
#define ECHO 8
#define ir_car1 5
#define ir_car2 6

int S1 = 0, S2 = 0, pos = 0;
int slot = 2;
long duration, distance;

void setup() {
  pinMode(ir_car1, INPUT);
  pinMode(ir_car2, INPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  Serial.begin(9600);

  myservo.attach(3);
  myservo.write(90);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("  Car  parking  ");
  Serial.println("System initializing...");
  lcd.setCursor(0, 1);
  lcd.print("     System     ");
  delay(2000);
  lcd.clear();

  Read_Sensor();

  int total = S1 + S2;
  Serial.print("Total cars detected: ");
  Serial.println(total);
  slot = slot - total;
  Serial.print("Available parking slots: ");
  Serial.println(slot);
}

void loop() {
  Read_Sensor();

  lcd.setCursor(0, 0);
  lcd.print("Available: ");
  lcd.print(slot);
  Serial.print("Available parking slots: ");
  Serial.println(slot);
  delay(1500);
  lcd.clear();

  lcd.setCursor(0, 0);
  if (S1 == 1) {
    lcd.print("S1:Filled");
    Serial.println("Slot 1 is filled.");
  } else {
    lcd.print("S1:Empty");
    Serial.println("Slot 1 is empty.");
  }

  lcd.setCursor(0, 1);
  if (S2 == 1) {
    lcd.print("S2:Filled");
    Serial.println("Slot 2 is filled.");
  } else {
    lcd.print("S2:Empty");
    Serial.println("Slot 2 is empty.");
  }

  delay(1500);
  lcd.clear();

  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  duration = pulseIn(ECHO, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distance measured: ");
  Serial.println(distance);

  if (distance < 5) {
    if (slot == 0) {
      lcd.setCursor(0, 0);
      lcd.print("  Parking Full  ");
      Serial.println("Parking Full.");
      delay(1500);
      lcd.clear();
    } else {
      Serial.println("Parking slot available. Opening gate...");
      myservo.write(90);
      for (pos =90 ; pos <= 180; pos++) {
        myservo.write(pos);
        delay(15);
      }
      for (pos = 180; pos >= 90; pos--) {
        myservo.write(pos);
        delay(15);
      }
      slot--;
      Serial.print("Slot reduced, available slots: ");
      Serial.println(slot);
    }
  }

  delay(1);
}

void Read_Sensor() {
  S1 = 0;
  S2 = 0;

  if (digitalRead(ir_car1) == 0) {
    S1 = 1;
    Serial.println("Car detected in Slot 1.");
  }
  if (digitalRead(ir_car2) == 0) {
    S2 = 1;
    Serial.println("Car detected in Slot 2.");
  }

  int total = S1 + S2;
  Serial.print("Total cars detected: ");
  Serial.println(total);
  slot = 2 - total;
  Serial.print("Updated available slots: ");
  Serial.println(slot);
}
