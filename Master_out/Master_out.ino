//8ビット分まって1バイトにする
#define DATAPIN   (19)   // 74HC595のDSへ
#define LATCH_OUT (18)   // 74HC595のST_CPへ
#define CLOCKPIN  (5)    // 74HC595のSH_CPへ
#define HEAD_OUT  (17)   // 8bitの先頭を示すためのピン
  
#define OUTPUTDATA 127
bool flip = false;
void setup(){
  pinMode(DATAPIN, OUTPUT);
  pinMode(LATCH_OUT, OUTPUT);
  pinMode(CLOCKPIN, OUTPUT);
  pinMode(HEAD_OUT, OUTPUT);
  Serial.begin(9600);
}
void loop(){
  digitalWrite(HEAD_OUT, HIGH);
  delay(10);
  for( int i = 7; i >= 0; i-- ){
    digitalWrite(LATCH_OUT, LOW);
    myShiftOut( DATAPIN, CLOCKPIN, i, (byte)OUTPUTDATA );
    digitalWrite(LATCH_OUT, HIGH);
//    delay(10);
//    flip = !flip;
  }
  digitalWrite(HEAD_OUT, LOW);
}
void myShiftOut( int dataPin, int clockPin, int bitNo, byte value ){
  // valueのbitNo番目をdataPinから送信
  digitalWrite(dataPin, !!(value & (1L << bitNo)));
  digitalWrite(clockPin, HIGH);
  delay(10);
  digitalWrite(clockPin, LOW); 
}
