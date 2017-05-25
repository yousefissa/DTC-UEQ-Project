
// display requirements

// include the i2c display library
#include <LiquidCrystal_I2C.h>
// set the display address since it isnt standard
#define I2C_ADDR 0x3F 
// set to 16 chars, 2 line display 
LiquidCrystal_I2C lcd(0x3F, 20, 4); 


void setup() {
  // calls the startup screen function.
  startupPrint();
  
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  // print the number of seconds since reset:

}

void startupPrint(){
    // intitialize lcd
  lcd.init();
  lcd.backlight();
  // goes to the middle of the screen
  lcd.setCursor(5,0);
  // print message to screen
  lcd.print("UEQ V1");
  // goes to the second row 
  lcd.setCursor(6,1);
  // prints date
  lcd.print("2017");
  // pauses the code for 5 seconds.
  delay(5000);
  // clears the lcd. we're done with displaying the startup screen.
  lcd.clear(); 
}

