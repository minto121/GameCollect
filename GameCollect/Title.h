#pragma once
#include "AbstractScene.h"

//タイトルメニュー
enum class TITLE_MENU
{
    GAME_START,
    GAME_END,
    TITLE_SIZE
};

class Title : public AbstractScene
{
private:
    const char* menu_items[static_cast<int>(TITLE_MENU::TITLE_SIZE)] = {
    "すたーと",
    "えんど"
    };

    //int Select;     //選択数
    //int OldKey;		//前の入力キー
    //int NowKey;		//今の入力キー
    //int KeyFlg;		//入力キー情報

    //bool Once;      //Lスティックでカーソルを動かす用

    //int TitleBGM;     //BGM用
    //int MenuSE;       //選択SE用
    //int TitleImg;     //タイトル画像
    //int CursorImg;    //カーソル画像

    int now_menu; //現在選択してるメニュー
    int MenuFont; //メニュー用のフォント
    int input_margin;  //操作時間間隔

public:
    //コンストラクタ
    Title();

    //デストラクタ
    ~Title();

    //描画以外の更新を実行
    AbstractScene* Update() override;

    //描画に関することを実装
    void Draw() const override;
};


