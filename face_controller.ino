#include "DAConverterController.h"
#include "ADConverterController.h"

#define PIN_SPI_MOSI 11    //DIN
#define PIN_SPI_MISO 12    //DOUT
#define PIN_SPI_SCK 13     //SCK
#define LTC1660_CS1 6      //DAコンバータLTC1660のCS
#define LTC1660_CS2 7      //DAコンバータLTC1660のCS
#define MCP3208_CS1 8      //ADコンバータMCP3208のCS
#define MCP3208_CS2 9      //ADコンバータLTC3208のCS


#define FORWARD_ROTATION 1
#define REVERSE_ROTATION 2
#define NO_ROTATION 3

#define MV4000 816 // 10bit に 5V を対応させた場合 4V は 816
#define MV4200 1700
#define MV4250 867
#define MV4500 918


DAConverterController daCon1 = DAConverterController(LTC1660_CS1);
DAConverterController daCon2 = DAConverterController(LTC1660_CS2);

ADConverterController adCon1 = ADConverterController(MCP3208_CS1);
ADConverterController adCon2 = ADConverterController(MCP3208_CS2);


/*
 * フォトインタラプタをエンコーダとして使うためのクラス
 * 一回転につき 1 カウントし，1層のエンコーダ．遮るとカウントするようにしている． (※ 8/21 1周 2カウントする)
 * 回転の方向はソフトウェアで制御する．
 * PROBLEM: 
 *  光を遮る状態で止まってしまうとカウントが進んでしまい，おかしくなる
 *  
 */
class PhotoEncoder {
  public:
    PhotoEncoder () {
      value = 0;
      state = NO_ROTATION;
      t = millis();
      pt = millis();
    }
    int value;
    int state;
    void count();
    void setState(int target_val);

  protected:
    float t, pt;
};

void PhotoEncoder::count() {
  t = millis();
  if (state == FORWARD_ROTATION && (t - pt) > 10) {
    value++;
    pt = t;
  } else if (state == REVERSE_ROTATION && (t - pt) > 10) {
    value--;
    pt = t;
  }
  //Serial.println(value);
  return;
}

void PhotoEncoder::setState(int s) {
  state = s;
  return;
}


void setup(){ 
  Serial.begin(115200);
}

int target = 0;
int count;
PhotoEncoder photoEncoder;
void loop(){
  if (Serial.available() > 0) {
    String target_str = Serial.readString();
    target = target_str.toInt();
  }
  
  int dt1;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
  dt1 = adCon1.Read(1);
  Serial.println(dt1);

    //回転数カウント
  if (dt1 < MV4200) {
    photoEncoder.count();
  }

  //回転向き制御
  if (target > photoEncoder.value) {
    photoEncoder.setState(FORWARD_ROTATION);
    daCon1.Write(1, 0x3FF);
    daCon1.Write(2, 0);
  } else if (target < photoEncoder.value) {
    photoEncoder.setState(REVERSE_ROTATION);
    daCon1.Write(1, 0);
    daCon1.Write(2, 0x3FF);
  } else {
    daCon1.Write(1, 0x3FF);
    daCon1.Write(2, 0x3FF);
  }
  
  delay(500);
}
