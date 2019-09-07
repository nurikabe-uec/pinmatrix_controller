#include "DAConverterController.h"
#include "ADConverterController.h"
#include "PhotoEncoder.h"

#define PIN_SPI_MOSI 11    //DIN
#define PIN_SPI_MISO 12    //DOUT
#define PIN_SPI_SCK 13     //SCK

// TODO:接続しやすいピン番号に変更
#define LTC1660_CS1 4      //DAコンバータLTC1660のCS
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
   @param photoEncoder 読み取るエンコーダ
   @param adCon 制御したいモータに接続しているDAコンバータ
   @param address 制御したモータのピン番号(0, 2, 4, 6)
   @param target 目標値
*/
void SetMotor(PhotoEncoder photoEncoder, DAConverterController daCon, int address, int target) {
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

void _debug_SetMotor_NC(PhotoEncoder pE, DAConverterController daCon, int address, int flag) {
  if (flag == 1) {
    pE.SetState(FORWARD_ROTATION);
    daCon.Write(address, 0x3FF);
    daCon.Write(address + 1, 0);
  } else if (flag == -1) {
    pE.SetState(REVERSE_ROTATION);
    daCon.Write(address, 0);
    daCon.Write(address + 1, 0x3FF);
  } else {
    daCon.Write(address, 0x3FF);
    daCon.Write(address + 1, 0x3FF);
  }
}

void _debug_SetMotor(PhotoEncoder pE, DAConverterController daCon, int address, int target) {
  if (target > pE.value) {
    pE.SetState(FORWARD_ROTATION);
    daCon.Write(address, 0x3FF);
    daCon.Write(address + 1, 0);
  } else if (target < pE.value) {
    pE.SetState(REVERSE_ROTATION);
    daCon.Write(address, 0);
    daCon.Write(address + 1, 0x3FF);
  } else {
    daCon.Write(address, 0x3FF);
    daCon.Write(address + 1, 0x3FF);
  }
}



int target = 0;
PhotoEncoder photoEncoder[16];

/*******************************************************************************************************************************/

void setup() {
  Serial.begin(115200);
  for (int index = 0; index < 16; index++) {
    photoEncoder[index] = PhotoEncoder(millis());
  }
}

// for debug ***********************************************************************************************************************/
int debug_target = 100;
int _time = 0;
int dir = 1;

void _debug_Up() {
  _debug_SetMotor_NC(photoEncoder[0], daCon1, 1, 1);
  _debug_SetMotor_NC(photoEncoder[1], daCon1, 3, 1);
  _debug_SetMotor_NC(photoEncoder[2], daCon1, 5, -1);
  _debug_SetMotor_NC(photoEncoder[3], daCon1, 7, -1);

  _debug_SetMotor_NC(photoEncoder[4], daCon2, 1, 1);
  _debug_SetMotor_NC(photoEncoder[5], daCon2, 3, 1);
  _debug_SetMotor_NC(photoEncoder[6], daCon2, 5, -1);
  _debug_SetMotor_NC(photoEncoder[7], daCon2, 7, -1);
}

void _debug_Down() {

  _debug_SetMotor_NC(photoEncoder[0], daCon1, 1, -1);
  _debug_SetMotor_NC(photoEncoder[1], daCon1, 3, -1);
  _debug_SetMotor_NC(photoEncoder[2], daCon1, 5, 1);
  _debug_SetMotor_NC(photoEncoder[3], daCon1, 7, 1);

  _debug_SetMotor_NC(photoEncoder[4], daCon2, 1, -1);
  _debug_SetMotor_NC(photoEncoder[5], daCon2, 3, -1);
  _debug_SetMotor_NC(photoEncoder[6], daCon2, 5, 1);
  _debug_SetMotor_NC(photoEncoder[7], daCon2, 7, 1);
}

int breaking = 1;
void _debug_Breaking() {
  for (int index = 1; index <= 8; index++) {
    if (index <= 4) {
      _debug_SetMotor_NC(photoEncoder[index - 1], daCon1, 2 * index - 1, 2);
    } else if (index <= 8) {
      _debug_SetMotor_NC(photoEncoder[index - 1], daCon2, 2 * (index - 4) - 1, 2);
    }
  }
}

int upanddown_start = 0;
int upanddown_counter = 0;
int upanddown_dir = 1;
void movie_UpAndDown() {
  upanddown_counter = (upanddown_counter + 1) % 5000;
  if (upanddown_counter == 0) {
    upanddown_dir *= -1;
  }

  _debug_SetMotor_NC(photoEncoder[0], daCon1, 1, upanddown_dir);
  _debug_SetMotor_NC(photoEncoder[1], daCon1, 3, upanddown_dir);
  _debug_SetMotor_NC(photoEncoder[2], daCon1, 5, -upanddown_dir);
  _debug_SetMotor_NC(photoEncoder[3], daCon1, 7, -upanddown_dir);

  _debug_SetMotor_NC(photoEncoder[4], daCon2, 1, upanddown_dir);
  _debug_SetMotor_NC(photoEncoder[5], daCon2, 3, upanddown_dir);
  _debug_SetMotor_NC(photoEncoder[6], daCon2, 5, -upanddown_dir);
  _debug_SetMotor_NC(photoEncoder[7], daCon2, 7, -upanddown_dir);
}

int upanddown2_start = 0;
int upanddown2_counter = 0;
int upanddown2_dir = 1;
void movie_UpAndDown2() {
  upanddown2_counter = (upanddown2_counter + 1) % 5000;
  if (upanddown2_counter == 0) {
    upanddown2_dir *= -1;
  }

  _debug_SetMotor_NC(photoEncoder[0], daCon1, 1, upanddown2_dir);
  _debug_SetMotor_NC(photoEncoder[1], daCon1, 3, -upanddown2_dir);
  _debug_SetMotor_NC(photoEncoder[2], daCon1, 5, -upanddown2_dir);
  _debug_SetMotor_NC(photoEncoder[3], daCon1, 7, upanddown2_dir);

  _debug_SetMotor_NC(photoEncoder[4], daCon2, 1, upanddown2_dir);
  _debug_SetMotor_NC(photoEncoder[5], daCon2, 3, -upanddown2_dir);
  _debug_SetMotor_NC(photoEncoder[6], daCon2, 5, -upanddown2_dir);
  _debug_SetMotor_NC(photoEncoder[7], daCon2, 7, upanddown2_dir);
}



int pin_start[8];
int pin_dir[8];
int pin_count[8];
long wave_counter = 0;
int wave_start = 0;
void movie_Wave() {
  wave_counter = wave_counter + 1;
  if (pin_start[0] == 0 && wave_counter > 0) {
    pin_start[0] = 1;
    pin_dir[0] = 1;
  } else if (pin_start[1] == 0 && wave_counter > 6000) {
    pin_start[1] = 1;
    pin_dir[1] = 1;
  } else if (pin_start[2] == 0 && wave_counter > 12000) {
    pin_start[2] = 1;
    pin_dir[2] = -1;
  } else if (pin_start[3] == 0 && wave_counter > 18000) {
    pin_start[3] = 1;
    pin_dir[3] = -1;
  } else if (pin_start[4] == 0 && wave_counter > 24000) {
    pin_start[4] = 1;
    pin_dir[4] = 1;
  } else if (pin_start[5] == 0 && wave_counter > 30000) {
    pin_start[5] = 1;
    pin_dir[5] = 1;
  } else if (pin_start[6] == 0 && wave_counter > 34000) {
    pin_start[6] = 1;
    pin_dir[6] = -1;
  } else if (pin_start[7] == 0 && wave_counter > 38000) {
    pin_start[7] = 1;
    pin_dir[7] = -1;
  }

  for (int index = 1; index <= 8; index++) {
    if (pin_start[index - 1] == 0) continue;

    pin_count[index - 1] = (pin_count[index - 1] + 1) % 8000;

    if (pin_count[index - 1] == 0) pin_dir[index - 1] *= -1;

    if (index <= 4) {
      _debug_SetMotor_NC(photoEncoder[index - 1], daCon1, 2 * index - 1, pin_dir[index - 1]);
    } else if (index <= 8) {
      _debug_SetMotor_NC(photoEncoder[index - 1], daCon2, 2 * (index - 4) - 1, pin_dir[index - 1]);
    }
  }

}

int debug_up = 0;
int debug_down = 0;
void loop() {

  _time = int(millis()) % 5000;
  signed char c = 'e';

  if ((c = Serial.read()) != -1) {
    if (c == 'w') {
      _debug_Breaking();
      wave_start = 1;
      wave_counter = 0;
      upanddown_start = 0;
      upanddown2_start = 0;
      breaking = 0;
      for (int index = 0; index < 8; index++) {
        pin_start[index] = 0;
        pin_dir[index] = 0;
        pin_count[index] = 0;
      }
    } else if (c == 'u') {
      upanddown_start = 1;
      upanddown2_start = 0;
      wave_start = 0;
      breaking = 0;
    } else if (c == 'i') {
      upanddown_start = 0;
      upanddown2_start = 1;
      upanddown2_counter = 0;
      wave_start = 0;
      debug_up = 0;
      debug_down = 0;
      breaking = 0;
    } else if (c == 'e') {
      upanddown_start = 0;
      wave_start = 0;
      upanddown2_start = 0;
      breaking = 1;
      debug_up = 0;
      debug_down = 0;
    } else if (c == 'a') {
      debug_up = 1;
      upanddown2_start = 0;
      wave_start = 0;
      upanddown_start = 0;
      breaking = 0;
      debug_down = 0;
    } else if (c == 'd') {
      debug_up = 0;
      wave_start = 0;
      upanddown2_start = 0;
      upanddown_start = 0;
      breaking = 0;
      debug_down = 1;
    }
  }

  //8個のモータを制御する(8個のモータに制御信号を送信する)
  //
  //
  //  int receivedData[16];
  //  for (int index = 0; index < 16; index++) {
  //    if (index < 8) receivedData[index] = adCon1.Read(index + 1); //adCon1の1~8ピンの受信データを格納
  //    else  receivedData[index] = adCon2.Read(index - 7);         //adCon2の1~8ピンの受信データを格納
  //  }
  //  //Serial.println(dt1[0]);
  //  Serial.println(receivedData[1]);
  //  //16個のモータを制御する(16個のモータに制御信号を送信する)
  //  for (int index = 1; index <= 8; index++) {
  //    if (receivedData[index] < MV2000) {
  //      photoEncoder[index - 1].Count(millis());
  //    }
  //
  //    // TODO:目標値targetの変更
  //    if (index <= 4) {
  //      _debug_SetMotor(photoEncoder[index], daCon1, 2 * index - 1, debug_target);
  //    } else if (index <= 8) {
  //      _debug_SetMotor(photoEncoder[index], daCon2, 2 * (index - 4) - 1, debug_target);
  //    } else if (index <= 12) {
  //      _debug_SetMotor(photoEncoder[index], daCon3, 2 * (index - 8) - 1, debug_target);
  //    } else {
  //      _debug_SetMotor(photoEncoder[index], daCon4, 2 * (index - 12) - 1, debug_target);
  //    }
  //  }


  if (wave_start) {
    movie_Wave();
  } else if (upanddown_start) {
    movie_UpAndDown();
  } else if (breaking) {
    _debug_Breaking();
  } else if (debug_up) {
    _debug_Up();
  } else if (debug_down) {
    _debug_Down();
  } else if (upanddown2_start) {
    movie_UpAndDown2();
  }
  delayMicroseconds(1);
}

//
//void loop(){
//
//  // TODO:目標値の設定方法を変更
//  if (Serial.available() > 0) {
//    String target_str = Serial.readString();
//    target = target_str.toInt();
//  }
//
//  //16個のフォトインタラプタからデータを受信する
//  int receivedData[16];
//  for(int index = 0; index < 16; index++){
//    if(index < 8) receivedData[index] = adCon1.Read(index+1);   //adCon1の1~8ピンの受信データを格納
//    else  receivedData[index] = adCon2.Read(index-7);           //adCon2の1~8ピンの受信データを格納
//  }
//  //Serial.println(dt1[0]);
//
//  //16個のモータを制御する(16個のモータに制御信号を送信する)
//  for(int index = 0; index < 16; index++){
//    if(receivedData[index] > MV2350){
//      photoEncoder[index].Count(millis());
//    }
//
//    // TODO:目標値targetの変更
//    if(index < 4){
//      SetMotor(photoEncoder[index], daCon1, index * 2, target);
//    }else if(index < 8){
//      SetMotor(photoEncoder[index], daCon2, (index - 4) * 2, target);
//    }else if(index < 12){
//      SetMotor(photoEncoder[index], daCon3, (index - 8) * 2, target);
//    }else{
//      SetMotor(photoEncoder[index], daCon4, (index - 12) * 2, target);
//    }
//  }
//
//  delay(500);
//}
