#include <Arduino.h>
#include "ADConverterController.h"
#include <SPI.h>

ADConverterController::ADConverterController(int cs){
  this->cs = cs;
  
  SPI.begin(PIN_SPI_SCK, PIN_SPI_MISO, PIN_SPI_MOSI, cs);
  SPI.setFrequency(1000000);
  SPI.setDataMode(SPI_MODE0);
  SPI.setHwCs(true);
}

int ADConverterController::Read(int address){
  int data1, data2;
  digitalWrite(this->cs, LOW);
  data1 = SPI.transfer( 0x06 | ((address - 1) >> 2) ) ;
  data1 = SPI.transfer( (address - 1) << 6 ) ;
  data2 = SPI.transfer(0x00) ;
  digitalWrite(this->cs, HIGH);
  //Serial.println(data2);

  return (data1 & 0x0F)*256 +data2;
}
