#ifndef DAConverterController_h
#define DAConverterController_h

#define CHANNEL 8      //チャンネル数

/*
 * LTC1600CNを用いてSPI通信を行うためのクラス
 */
class DAConverterController{
	public:
		DAConverterController(int cs);
   
    /*
     * 1つのみ or デイジーチェーンで接続されたスレーブにデータを転送する
     * @param address アドレス(チャンネル)
     * @param inputs マイコンに送信するデータ配列．要素番号が小さい先に送信される．送信データの範囲(0x000~0x3FF)
     * @return なし
     */
		void Write(int address, short input);
   private:
    int cs;      //使用するLTC1600CNの総数
};

#endif
