#include "DAConverterController.h"
#include "ADConverterController.h"
#include "PhotoEncoder.h"

#define myAddress 11
#define CLOCKPIN  2
HardwareSerial mySerial(2); // UART2 : RX 16, TX 17

#define PIN_SPI_MOSI 11    //DIN
#define PIN_SPI_MISO 12    //DOUT
#define PIN_SPI_SCK 13     //SCK

// TODO:接続しやすいピン番号に変更
#define LTC1660_CS1 10      //DAコンバータLTC1660のCS
#define LTC1660_CS2 5      //DAコンバータLTC1660のCS
#define LTC1660_CS3 6      //DAコンバータLTC1660のCS
#define LTC1660_CS4 7      //DAコンバータLTC1660のCS

#define MCP3208_CS1 8      //ADコンバータMCP3208のCS
#define MCP3208_CS2 9      //ADコンバータLTC3208のCS

DAConverterController daCon1 = DAConverterController(LTC1660_CS1);
DAConverterController daCon2 = DAConverterController(LTC1660_CS2);
DAConverterController daCon3 = DAConverterController(LTC1660_CS3);
DAConverterController daCon4 = DAConverterController(LTC1660_CS4);

ADConverterController adCon1 = ADConverterController(MCP3208_CS1);
ADConverterController adCon2 = ADConverterController(MCP3208_CS2);

/* モータを制御
 * @param photoEncoder 読み取るエンコーダ
 * @param adCon 制御したいモータに接続しているDAコンバータ
 * @param address 制御したモータのピン番号(0, 2, 4, 6)
 * @param target 目標値
  */

void SetMotor(PhotoEncoder photoEncoder, DAConverterController daCon, int address, int target){
  if (target > photoEncoder.value) {
      photoEncoder.SetState(FORWARD_ROTATION);
      daCon.Write(address, 0x3FF);
      daCon.Write(address + 1, 0);
  } else if (target < photoEncoder.value) {
      photoEncoder.SetState(REVERSE_ROTATION);
      daCon.Write(address, 0);
      daCon.Write(address + 1, 0x3FF);
  } else {
      daCon.Write(address, 0x3FF);
      daCon.Write(address + 1, 0x3FF);
  }
}


//int target = 0;
int targets[16];
PhotoEncoder photoEncoder[16];

//割り込み:アドレスの確認
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

//目標値の更新
void read16bytes(){
  for(int i = 0; i < 16; i++){
    targets[i] = (int)mySerial.read();
    Serial.println(targets[i]);
  }
}

//違うアドレスは無視
void ignore16bytes(){
  for(int i = 0; i < 16; i++){
    mySerial.read();
  }
}

/*******************************************************************************************************************************/

void setup(){ 
  Serial.begin(115200);
  mySerial.begin(115200);
  for(int index = 0; index < 16; index++){
    photoEncoder[index] = PhotoEncoder(millis());
  }
  pinMode(CLOCKPIN, INPUT);
  attachInterrupt(CLOCKPIN, compareAddress, RISING);
}

void loop(){

  //16個のフォトインタラプタからデータを受信する
  int receivedData[16];
  for(int index = 0; index < 16; index++){
    if(index < 8) receivedData[index] = adCon1.Read(index+1);   //adCon1の1~8ピンの受信データを格納
    else  receivedData[index] = adCon2.Read(index-7);           //adCon2の1~8ピンの受信データを格納                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
  }
  //Serial.println(dt1[0]);

  //16個のモータを制御する(16個のモータに制御信号を送信する)
  for(int index = 0; index < 16; index++){
    if(receivedData[index] < MV4200){
      photoEncoder[index].Count(millis());
    }

    // TODO:目標値targetの変更
    if(index < 4){
      SetMotor(photoEncoder[index], daCon1, index * 2, targets[index]);
    }else if(index < 8){
      SetMotor(photoEncoder[index], daCon2, (index - 4) * 2, targets[index]);
    }else if(index < 12){
      SetMotor(photoEncoder[index], daCon3, (index - 8) * 2, targets[index]);
    }else{
      SetMotor(photoEncoder[index], daCon4, (index - 12) * 2, targets[index]);
    }
  }
  
  delay(500);
}
