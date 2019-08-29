#ifndef DACONVERTERCONTROLLER_H
#define DACONVERTERCONTROLLER_H

#define CHANNEL 8      //チャネル数

/*
 * LTC1600CNを用いてSPI通信を行うためのクラス
 */
class DAConverterController{
	public:
		DAConverterController(int cs);
   
    /*
     * LTC1660CNにデータを送信する
     * @param address アドレス(チャンネル) (1~8)
     * @param inputs マイコンに送信するデータ，送信データの範囲(0x000~0x3FF)
     * @return なし
     */
		void Write(int address, short input);
   private:
    int cs;      //Arduinoと接続しているピン
};

#endif
