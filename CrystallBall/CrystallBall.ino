#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 11, 4, 5, 6, 7);

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  lcd.print("Coucou !!!");
}

void loop() {
  // put your main code here, to run repeatedly:
}
