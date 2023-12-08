#include "Arduino.h"

#include "U8g2lib.h"


#define D1_I2C_ADDR 0x3C
#define D23_RST 33
#define D23_DC 32
#define D2_CS 5
#define D3_CS 15

#define COUNT(a) (sizeof(a) / sizeof(a[0]))


U8G2_SSD1306_128X64_NONAME_F_HW_I2C disp1(U8G2_R0);
U8G2_SSD1306_128X64_NONAME_F_4W_HW_SPI disp2(U8G2_R3, D2_CS, D23_DC, U8X8_PIN_NONE);
//U8G2_SH1107_64X128_F_4W_HW_SPI disp2(U8G2_R0, D2_CS, D23_DC, U8X8_PIN_NONE);
U8G2_SSD1309_128X64_NONAME0_F_4W_HW_SPI disp3(U8G2_R3, D3_CS, D23_DC, U8X8_PIN_NONE);

U8G2 *displays[] = {&disp1, &disp2, &disp3};

void picture(U8G2 *disp, int n) {
//  disp->setDisplayRotation(U8G2_R1);
  disp->setFont(u8g2_font_6x12_mf);
  disp->clearBuffer();
  disp->drawFrame(0, 0, disp->getWidth(), disp->getHeight());
  disp->setCursor(0, 15);
  disp->printf("%u:Hello World!", n);
  disp->setCursor(0, 30);
  disp->printf("%ux%u", disp->getWidth(), disp->getHeight());
  disp->sendBuffer();
}

void setup() {
  int n;

  disp1.setI2CAddress(D1_I2C_ADDR << 1);
  pinMode(D23_RST, OUTPUT);
  pinMode(D23_DC, OUTPUT);
  pinMode(D2_CS, OUTPUT);
  pinMode(D3_CS, OUTPUT);
  digitalWrite(D2_CS, HIGH);
  digitalWrite(D3_CS, HIGH);
  digitalWrite(D23_DC, HIGH);
  digitalWrite(D23_RST, LOW);
  delay(200);
  digitalWrite(D23_RST, HIGH);

  for (n = 0; n < COUNT(displays); n++) {
    displays[n]->begin();
  }
  
  //disp2.sendF("ca", 0xA0, 0xC8);
  disp2.sendF("c", 0xC0);
}


void loop() {
  int n;

  for (n = 0; n < COUNT(displays); n++) {
    picture(displays[n], n + 1);
  }

  delay(10);
}