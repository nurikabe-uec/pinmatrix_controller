
HardwareSerial Ser1(2);

#define CLK (2)
//#define TXPIN (1) //出す
//#define RXPIN (3) //入る

byte inByte1[17] = {(byte)11, (byte)21, (byte)31, (byte)41, (byte)51, (byte)61, (byte)71, (byte)81, (byte)91, (byte)101, (byte)111, (byte)121, (byte)131, (byte)141, (byte)151, (byte)161, (byte)171};
byte inByte2[17] = {(byte)12, (byte)22, (byte)32, (byte)42, (byte)52, (byte)62, (byte)72, (byte)82, (byte)92, (byte)102, (byte)112, (byte)122, (byte)132, (byte)142, (byte)152, (byte)162, (byte)172};
byte inByte3[17] = {(byte)13, (byte)23, (byte)33, (byte)43, (byte)53, (byte)63, (byte)73, (byte)83, (byte)93, (byte)103, (byte)113, (byte)123, (byte)133, (byte)143, (byte)153, (byte)163, (byte)173};

void setup(){
  pinMode(CLK, OUTPUT);
  Serial.begin(115200);
  Ser1.begin(115200);
}

void loop(){
  digitalWrite(CLK, HIGH);
  for(int i = 0; i < 17; i++){
    Ser1.write(inByte1[i]);
    if(i == 9){
      digitalWrite(CLK, LOW);
    }
  }
  digitalWrite(CLK, HIGH);
  for(int i = 0; i < 17; i++){
    Ser1.write(inByte2[i]);
    if(i == 9){
      digitalWrite(CLK, LOW);
    }
  }
  digitalWrite(CLK, HIGH);
  for(int i = 0; i < 17; i++){
    Ser1.write(inByte3[i]);
    if(i == 9){
      digitalWrite(CLK, LOW);
    }
  }
}
