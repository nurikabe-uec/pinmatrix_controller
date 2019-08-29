#ifndef ADCONVERTERCONTROLLER_H
#define ADCONVERTERCONTROLLER_H

#define CHANNEL 8      //チャネル数

/*
 * MCP3208を用いてSPI通信を行うためのクラス
 */
class ADConverterController{
  public:
    ADConverterController(int cs);
   
    /*
     * MCP3208からデータを受信する
     * @param address アドレス(チャネル) (1~8)
     * @return なし
     */
    int Read(int address);
   private:
    int cs;      //Arduinoと接続しているピン
};

#endif
