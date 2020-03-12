//下位4ビットを分ける？

#define DATAPIN   (19) // 74HC595のDSへ
#define LATCHPIN  (18)  // 74HC595のST_CPへ
#define CLOCKPIN  (5) // 74HC595のSH_CPへ
#define OUTPUT1   (25)
#define OUTPUT2   (26)
#define OUTPUT3   (16)
#define OUTPUT4   (17)


void setup(){
  pinMode(DATAPIN, OUTPUT);
  pinMode(LATCHPIN, OUTPUT);
  pinMode(CLOCKPIN, OUTPUT);
  pinMode(OUTPUT1, INPUT);
  pinMode(OUTPUT2, INPUT);
  pinMode(OUTPUT3, INPUT);
  pinMode(OUTPUT4, INPUT);
  Serial.begin(115200);
}
 
void loop(){
  for( int i = 0; i < 4; i++ ){
    digitalWrite(LATCHPIN, LOW);    // 送信中はLATCHPINをLOWに
 
    // シフト演算を使って点灯するLEDを選択しています
    shiftOut( DATAPIN, CLOCKPIN, MSBFIRST, B10101010 );
 
    digitalWrite(LATCHPIN, HIGH);   // 送信後はLATCHPINをHIGHに戻す
 
    Serial.print("OUTPUT1: ");
    Serial.print(digitalRead(OUTPUT1));
    Serial.println();
    Serial.print("OUTPUT2: ");
    Serial.print(digitalRead(OUTPUT2));
    Serial.println();
    Serial.print("OUTPUT3: ");
    Serial.print(digitalRead(OUTPUT3));
    Serial.println();
    Serial.print("OUTPUT4: ");
    Serial.print(digitalRead(OUTPUT4));
    Serial.println();
    delay(100);
  }
}
