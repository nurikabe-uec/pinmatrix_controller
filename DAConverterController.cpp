#include <Arduino.h>
#include "DAConverterController.h"
#include <SPI.h>

DAConverterController::DAConverterController(int cs){
  this->cs = cs;

  SPI.begin(PIN_SPI_SCK, PIN_SPI_MISO, PIN_SPI_MOSI, cs);
  SPI.setFrequency(1000000);
  SPI.setDataMode(SPI_MODE0);
  SPI.setHwCs(true);

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
