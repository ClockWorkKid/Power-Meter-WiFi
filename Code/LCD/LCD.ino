#include <LiquidCrystal.h>
const int RS = 12, EN = 14, d4 = 2, d5 = 0, d6 = 4, d7 = 5;   
LiquidCrystal lcd(RS, EN, d4, d5, d6, d7);

void setup() {
                         // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
                      // Print a message to the LCD.
  lcd.print("hello, world!");
  Serial.begin(115200);
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis() / 1000);
  Serial.println(millis()/1000);
  
}
