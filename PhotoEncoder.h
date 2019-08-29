#ifndef PHOTOENCODER_H
#define PHOTOENCODER_H

#define MV4000 816 // 10bit に 5V を対応させた場合 4V は 816
#define MV4200 1700
#define MV4250 867
#define MV4500 918

enum State{
  FORWARD_ROTATION = 1,
  REVERSE_ROTATION,
  NO_ROTATION
};

/*
 * フォトインタラプタをエンコーダとして使うためのクラス
 * 一回転につき 1 カウントし，1層のエンコーダ．遮るとカウントするようにしている． (※ 8/21 1周 2カウントする)
 * 回転の方向はソフトウェアで制御する．
 * PROBLEM: 
 *  光を遮る状態で止まってしまうとカウントが進んでしまい，おかしくなる
 *  
 */
class PhotoEncoder{
  public:
    PhotoEncoder();
    PhotoEncoder(unsigned long t);

    int value;
    int state;

    /*
     * ネジの回転数を数える
     * @param t プログラムを起動してからこのメソッドを呼び出すときまでの時間．millis()を渡すことを推奨
     * @return なし
     */
    void Count(unsigned long t);

    /*
     * ネジの回転方向を設定する
     * @param state 設定するネジの回転方向
     * @return なし
     */
    void SetState(State state);

  protected:
    unsigned long countTime;    //最後にネジの回転数を数えたときの時間を保持
};

#endif
