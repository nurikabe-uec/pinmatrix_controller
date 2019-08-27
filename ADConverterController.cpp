#include "ADConverterController.h"
#include <SPI.h>

ADConverterController::ADConverterController(int cs){
  this->cs = cs;
  
  pinMode(cs, OUTPUT);
  digitalWrite(cs, HIGH);
}

int ADConverterController::Read(int address){
  int data1, data2;
  digitalWrite(this->cs, LOW);
  data1 = SPI.transfer( 0x06 | (address >> 2) ) ;
  data1 = SPI.transfer( address << 6 ) ;
  data2 = SPI.transfer(0x00) ;
  digitalWrite(this->cs, HIGH);
  //Serial.println(data2);

  return (data1 & 0x0F)*256 +data2;
}
