//8ビット分まって1バイトにする

#define DATAPIN   (19) // 74HC595のDSへ
#define LATCH_OUT  (18)  // 74HC595のST_CPへ
#define CLOCKPIN  (5) // 74HC595のSH_CPへ

#define OUTPUTDATA 127

bool flip = false;

void setup(){
  pinMode(DATAPIN, OUTPUT);
  pinMode(LATCH_OUT, OUTPUT);
  pinMode(CLOCKPIN, OUTPUT);
  Serial.begin(115200);
}

void loop(){
  for( int i = 7; i >= 0; i-- ){
    digitalWrite(LATCH_OUT, LOW);
    myShiftOut( DATAPIN, CLOCKPIN, i, (byte)OUTPUTDATA );
//    byte out_data = flip ? B11111111 : B00000000;
//    shiftOut( DATAPIN, CLOCKPIN, MSBFIRST, out_data );
    digitalWrite(LATCH_OUT, HIGH);
    delay(100);
//    flip = !flip;
  }
}

void myShiftOut( int dataPin, int clockPin, int bitNo, byte value ){
  // valueのbitNo番目をdataPinから送信
  digitalWrite(dataPin, !!(value & (1L << bitNo)));
  digitalWrite(clockPin, HIGH);
  delay(10);
  digitalWrite(clockPin, LOW); 
}
