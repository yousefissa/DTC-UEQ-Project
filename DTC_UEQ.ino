
// display requirements

// include the i2c display library
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

// set the display address since it isnt standard
#define I2C_ADDR 0x3F
// set to 16 chars, 2 line display
LiquidCrystal_I2C lcd(0x3F, 20, 4);

// initialize required sensor variables
// read input from analog in
int frontDiagnolLeft = A1, frontDiagnolRight = A0;;
// front left and front right
int readAmpsFL = 0, readAmpsFR = 0;
// ampage values
float ampsFL = 0.0, ampsFR = 0.0;

void setup() {
  // calls the startup screen function.
  startupPrint();
  // set the pins to take input
  pinMode(frontDiagnolLeft, INPUT);
  pinMode(frontDiagnolRight, INPUT);


}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  // print the number of seconds since reset:
  printAmpage();

}

void startupPrint() {
  // intitialize lcd
  lcd.init();
  lcd.backlight();
  // goes to the middle of the screen
  lcd.setCursor(5, 0);
  // print message to screen
  lcd.print("UEQ V1");
  // goes to the second row
  lcd.setCursor(6, 1);
  // prints date
  lcd.print("2017");
  // pauses the code for 5 seconds.
  delay(5000);
  // clears the lcd. we're done with displaying the startup screen.
  lcd.clear();
}

// function to get ampage, takes input
float fmap(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


void printAmpage() {
  // get the analog input
  readAmpsFL = analogRead(frontDiagnolLeft);
  readAmpsFR = analogRead(frontDiagnolRight);
  // call function to get ampage
  ampsFL = fabs(fmap(readAmpsFL, 0.0, 1023.0, 0.01, 5.0)) * 10;
  ampsFR = fabs(fmap(readAmpsFR, 0.0, 1023.0, 0.01, 5.0)) * 10;
  
  // print values to lcd
  lcd.setCursor(5, 0);
  delay(200);
  lcd.print(ampsFL);
  lcd.setCursor(5, 1);
  lcd.print(ampsFR);
  delay(500);

}



