#include <LiquidCrystal.h>

const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void init_LCD() {
  lcd.begin(20, 4);

  lcd.setCursor(0, 0); // column,row
  lcd.print("Voltage:");
  lcd.setCursor(15, 0);
  lcd.print("volts");
  lcd.setCursor(0, 1);
  lcd.print("Current:");
  lcd.setCursor(15, 1);
  lcd.print("amps ");
  lcd.setCursor(0, 2);
  lcd.print("Angle  :");
  lcd.setCursor(15, 2);
  lcd.print("deg ");
  lcd.setCursor(0, 3);
  lcd.print("Power  :");
  lcd.setCursor(15, 3);
  lcd.print("watts");



}


void show_on_display() {
  lcd.setCursor(9, 0); // column,row
  lcd.print(V);
  lcd.setCursor(9, 1);
  lcd.print(I);
  lcd.setCursor(9, 2);
  lcd.print(degree);
  lcd.setCursor(9, 3);
  lcd.print(P);
}
