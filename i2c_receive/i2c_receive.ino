#include <SoftwareSerial.h>
#define myAddress 11
#define CLOCKPIN  2
HardwareSerial mySerial(2); // UART2 : RX 16, TX 17
byte pinsData[16];
int inByte;
void setup() {
  Serial.begin(115200);
  mySerial.begin(115200);
  pinMode(CLOCKPIN, INPUT);
  attachInterrupt(CLOCKPIN, compareAddress, RISING);
}
void loop() {
  
}
void compareAddress(){
  Serial.println("interrupted by pin15");
  if(mySerial.available()){
    if((byte)mySerial.read()==(byte)myAddress){
      read16bytes();
    }else{
      ignore16bytes();
    }
  }
}
void read16bytes(){
  for(int i = 0; i < 16; i++){
    while(mySerial.available() == false){}
    pinsData[i] = mySerial.read();
  }
  for(int i = 0; i < 16; i++){
    Serial.print(i);
    Serial.print(": ");
    Serial.write(pinsData[i]);
    Serial.println();
  }
}
void ignore16bytes(){
  for(int i = 0; i < 16; i++){
    while(mySerial.available() == false){}
    mySerial.read();
  }
}
