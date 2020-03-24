//#include <SoftwareSerial.h>
#define myAddress 11
#define CLOCKPIN  2
HardwareSerial mySerial(2); // UART2 : RX 16, TX 17
volatile byte pinsData[16];
int inByte;
void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(CLOCKPIN, INPUT);
  attachInterrupt(CLOCKPIN, compareAddress, RISING);
}

void loop() {
}

void compareAddress(){
  Serial.println("interrupted by pin15");
  if(mySerial.available()){
    if((byte)mySerial.read()==(byte)myAddress){
      Serial.println("read16bytes");
      read16bytes();
    }else{
      Serial.println("ignore16bytes");
      ignore16bytes();
    }
  } else {
    Serial.println("my Serial is not available");
  }
}
void read16bytes(){
  for(int i = 0; i < 16; i++){
    pinsData[i] = mySerial.read();
    Serial.println(pinsData[i]);
  }
//  for(int i = 0; i < 16; i++){
//    Serial.print(i);
//    Serial.print(": ");
//    Serial.write(pinsData[i]);
//    Serial.println();
//  }
}
void ignore16bytes(){
  for(int i = 0; i < 16; i++){
//    while(mySerial.available() == false){}
    mySerial.read();
  }
}
