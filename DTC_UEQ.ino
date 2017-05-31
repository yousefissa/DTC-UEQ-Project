
// display requirements

// include the i2c display library
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <HX711.h>

// set the display address since it isnt standard
#define I2C_ADDR 0x3F
// set to 16 chars, 2 line display
LiquidCrystal_I2C lcd(0x3F, 20, 4);

// define what pins the sensors are connected to
#define DOUT    A1
#define CLK     A0
// initialize the scale being used
HX711 scale(DOUT, CLK);

// value passed into scale after calibrating.
float calibration_factor = 15500;
// average weight variable
float average_weight;
// class for updating weight displayed
class weight {
  public:
    // current weight
    float curr;
    // old weight
    float old;
    weight() {
      curr = -6.0;
      old = -20.0;
    }
};

// weight object
weight w;

void setup() {
  // serial info
  Serial.begin(9600);
  // calls the startup screen function.
  startupPrint();
  // get the lcd ready for displaying weight
  lcd.setCursor(0, 0);

  // initialize scale after finding calibration factor
  scale.set_scale(calibration_factor);
  // tare the scale so there is 0 weight.
  scale.tare();
  // get a baseline average reading
  long zero_factor = scale.read_average(); // we should use this
}


void loop() {
  // code to print to the serial. Good for debugging. 
//  Serial.print("one reading:\t");
//  Serial.print(scale.get_units(), 1);
//  Serial.print("\t| average:\t");

  // ge tthe average weight by taking 10 measruments
  average_weight = (scale.get_units(10));
  // set the current weight to the average weight
  w.curr = average_weight;
  // check if the weight is less than half a pound. we just print 0
  if (w.curr < 0.5) {
    scale.power_down();              // put the ADC in sleep mode
    delay(500);
    lcd.clear();
    scale.power_up();
    Serial.println(0.0, 1);
    lcd.setCursor(4,0);
    lcd.print(0.0);
    lcd.print(" lbs");
  }
  // we don't want to print while the current weight is less than half a pound.
  while (w.curr < 0.5 ) {
    average_weight = (scale.get_units(10));
    w.curr = average_weight;
  }
  // only print the weight if the difference is substantial. We used 5%.
  if (difference(w)) {
    scale.power_down();              // put the ADC in sleep mode
    delay(500);
    lcd.clear();
    scale.power_up();
    w.old = average_weight;
    Serial.println(w.curr, 1);
    lcd.setCursor(4,0);
    lcd.print(w.old);
    lcd.print(" lbs");
  }
  // if no substantial difference is present, keep on taking measurments but don't print.
  while (!difference(w)) {
    average_weight = (scale.get_units(10));
    w.curr = average_weight;
  }
}

// function for welcome screen.
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

// function that returns if difference is substantial or not.
bool difference(weight w) {
  float diff = (w.old - w.curr) / w.old;
  // if difference is greater than 5%, return true.
  return (fabs(diff)) > 0.05;
}




