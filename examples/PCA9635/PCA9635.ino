#include <Wire.h>
#include <PCA963x.h>

const int ADDR = B01100010;

PCA963x leds = PCA963x(ADDR, PCA9633);

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  int ret = leds.begin();
  byte mode1 = leds.getMode1();
  leds.setMode1(mode1^SLEEP);
  Serial.println(ret);
  pinMode(13, OUTPUT);
}

void loop()
{
  digitalWrite(13, HIGH);
  leds.analogWrite(1, 0);
  leds.analogWrite(2, 0);
  leds.analogWrite(3, 0);
  leds.digitalWrite(0,1);
  delay(250);
  digitalWrite(13, LOW);
  leds.analogWrite(1, 16);
  leds.analogWrite(2, 16);
  leds.analogWrite(3, 16);
  delay(250);
  leds.analogWrite(1, 64);
  leds.analogWrite(2, 64);
  leds.analogWrite(3, 64);
  leds.digitalWrite(0,0);
  delay(250);
  leds.analogWrite(1, 255);
  leds.analogWrite(2, 255);
  leds.analogWrite(3, 255);
  delay(250);
}



