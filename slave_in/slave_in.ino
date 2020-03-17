//8ビット分まって1バイトにする

#define LATCH_IN  (35) //子espの同期用 18とつながってる
#define INPUTPIN  (25)

int val_int;
short val = 0;
short count = 0;

void setup(){
  pinMode(LATCH_IN, INPUT);
  pinMode(INPUTPIN, INPUT);
  Serial.begin(115200);
  attachInterrupt(LATCH_IN, toint, RISING);
}

void loop(){

}

void toint(){
  val <<= 1;
  val += digitalRead(INPUTPIN);
  count++;
  
  if(count == 8){
    Serial.println("VAL: " + String(val));
    val = 0;
    count = 0;
  }
}
