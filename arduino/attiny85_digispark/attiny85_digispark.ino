#define __AVR_ATtiny85__ 1
#include <ssd1306.h>
#define Wire   TinyWireM
SSD1306 oled;

void setup() {
  TinyWireM.begin();
  oled.begin();
  oled.fill(0x00);
  delay(300);
  //oled.print_digits(0, 0, 1, 1000, 2016, false);
  //oled.print_digits(34, 1, 3, 10, 10,  false);
  oled.draw_3x_digit(34, 1, 3, false);
   delay(3000);
}
void loop() {
oled.draw_3x_digit(34, 1, 4, false);

  delay(1000);
}


