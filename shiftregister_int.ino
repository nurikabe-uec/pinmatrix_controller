//8ビット分まって1バイトにする

#define DATAPIN   (19) // 74HC595のDSへ
#define LATCH_OUT  (18)  // 74HC595のST_CPへ
#define LATCH_IN  (35) //子espの同期用 18とつながってる
#define CLOCKPIN  (5) // 74HC595のSH_CPへ
#define OUTPUT1   (25)
#define OUTPUT2   (26)
#define OUTPUT3   (16)
#define OUTPUT4   (17)

String val_string;
int val_int;

void setup(){
  pinMode(DATAPIN, OUTPUT);
  pinMode(LATCH_OUT, OUTPUT);
  pinMode(LATCH_IN, INPUT);
  pinMode(CLOCKPIN, OUTPUT);
  pinMode(OUTPUT1, INPUT);
  pinMode(OUTPUT2, INPUT);
  pinMode(OUTPUT3, INPUT);
  pinMode(OUTPUT4, INPUT);
  Serial.begin(115200);
  attachInterrupt(35, toint, RISING);
}
 
void loop(){
  for( int i = 0; i < 4; i++ ){
    digitalWrite(LATCH_OUT, LOW);    // 送信中はLATCHPINをLOWに
 
    // シフト演算を使って点灯するLEDを選択しています
    shiftOut( DATAPIN, CLOCKPIN, MSBFIRST, B10101011 );
 
    digitalWrite(LATCH_OUT, HIGH);   // 送信後はLATCHPINをHIGHに戻す
 
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

void toint(){
  val_string += digitalRead(OUTPUT1);
  if(val_string.length() == 8){
    //string,intにして出力
    val_int = 0;
    for(int i = 0; i < val_string.length(); i++){
      val_int *= 2;
      if(val_string.charAt(i) == '1'){
        val_int += 1;
      }
    }

      Serial.print("string: ");
      Serial.println(val_string);
      Serial.print("int: ");
      Serial.println(val_int);
      val_int = 0;

    //初期化
    val_string = "";
  }
}
