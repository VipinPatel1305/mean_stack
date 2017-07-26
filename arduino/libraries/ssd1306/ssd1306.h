/*
 * Ref.:
 * DigisparkOLED: https://github.com/digistump/DigistumpArduino/tree/master/digistump-avr/libraries/DigisparkOLED
 * SSD1306 data sheet: https://www.adafruit.com/datasheets/SSD1306.pdf
 */
#if defined(__AVR_ATtiny85__) || (__AVR_ATtiny2313__) || (__AVR_ATtiny45__)
#include <TinyWireM.h>    // include this if ATtiny85 or ATtiny2313
#define Wire   TinyWireM
#else 
#include <Wire.h>           // original lib include
#define send write
#define TinyWireM Wire
#endif

// custom I2C address by define SSD1306_I2C_ADDR
#ifndef SSD1306_I2C_ADDR
  #define SSD1306_I2C_ADDR 0x3C
#endif
#define SCREEN128X64 1
// custom screen resolution by define SCREEN128X64, SCREEN128X32 or SCREED64X32 (default)
#ifdef SCREEN128X64
  #define WIDTH 0x0100
  #define XOFFSET 0x00
  #define PAGES 0x8
#elif SCREEN128X32
  #define WIDTH 0x0100
  #define XOFFSET 0x00
  #define PAGES 0x04
#else //SCREED64X32
  #define WIDTH 0x40
  #define XOFFSET 0x20
  #define PAGES 0x04
#endif

class SSD1306 {

  public:
    SSD1306(void);
    void begin(void);
    void ssd1306_send_command_start(void);
    void ssd1306_send_command_stop(void);
    void ssd1306_send_command(uint8_t command);
    void ssd1306_send_data_start(void);
    void ssd1306_send_data_stop(void);
    void ssd1306_send_data_byte(uint8_t byte);
    void set_area(uint8_t col, uint8_t page, uint8_t col_range_minus_1, uint8_t page_range_minus_1);
    void fill(uint8_t fill);
    void v_line(uint8_t col, uint8_t fill);
    void draw_pattern(uint8_t col, uint8_t page, uint8_t width, uint8_t pattern);
    void draw_digit(uint8_t col, uint8_t page, uint8_t digit, bool invert_color);
    void draw_3x_digit(uint8_t col, uint8_t page, uint8_t digit, bool invert_color);
    void print_digits(uint8_t col, uint8_t page, uint8_t font_size, uint32_t factor, uint32_t digits, bool invert_color);
    void off();
    void on();
};

