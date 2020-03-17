#include "DAConverterController.h"
#include <SPI.h>
#include <Arduino.h>

DAConverterController::DAConverterController(int cs){
  this->cs = cs;
  
  pinMode(cs, OUTPUT);
  digitalWrite(cs, HIGH);

  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV8);
  SPI.setDataMode(SPI_MODE0);
  SPI.begin();

  //全てのアドレスの出力を0に設定する
  for(int address = 1; address < CHANNEL; address++){
    Write(address, 0);
  }
}

void DAConverterController::Write(int address, short input){
  short spiData = 0;
  
  digitalWrite(this->cs, LOW);
  spiData = (address << 12) | ((input & 0x3FF) << 2);
  SPI.transfer16(spiData);
	digitalWrite(this->cs, HIGH);
}
