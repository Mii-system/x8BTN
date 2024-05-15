#include <Wire.h>

//--------------------
//  Const / Define
//--------------------
#define SDA_PIN (26)  // SDA  M5ATOM
#define SCL_PIN (32)  // SCL  M5ATOM

//--  PCA9557 registers
#define REG_INPUT (0x00)
#define REG_OUTPUT (0x01)
#define REG_INVERSION (0x02)
#define REG_CONFIG (0x03)

#define PCA9557_ADDR (0x19) // A0/1/2:HLL

#define IOMODE (0xFF)       // b7-0:SW8,SW7,SW6,SW5,SW4,SW3,SW2,SW1
#define INV_DEFAULT (0xFF)  // ALL ON

//--------------------
//  Private Variable
//--------------------

//----------------------------------------
//-- SetUP
void setup() {
  //--  Serial Setting
  Serial.begin(115200);
  Serial.print("Setup\n");

  //--  i2c
  pinMode(SDA_PIN, INPUT_PULLUP);        // SDA
  pinMode(SCL_PIN, INPUT_PULLUP);        // SCL
  Wire.begin(SDA_PIN, SCL_PIN, 400000);  // 400k

  //--  PANEL
  PCA9557_init();  // PCA9557
}

//----------------------------------------
//--  loop
void loop() {
  //--  INPUT
  Serial.println(PCA9557_INP());
  delay(100);
}

//----  PCA9557
//--  Init
void PCA9557_init() {
  Wire.beginTransmission(PCA9557_ADDR);
  Wire.write(REG_INVERSION);
  Wire.write(INV_DEFAULT);
  Wire.endTransmission();

  Wire.beginTransmission(PCA9557_ADDR);
  Wire.write(REG_CONFIG);
  Wire.write(IOMODE);
  Wire.endTransmission();
}

//--  Input
uint8_t PCA9557_INP() {
  uint8_t w = 0;

  Wire.beginTransmission(PCA9557_ADDR);
  Wire.write(REG_INPUT);
  Wire.endTransmission(false);

  Wire.requestFrom(PCA9557_ADDR, 1);  // Read 1 byte
  w = Wire.read();

  return (w);
}
