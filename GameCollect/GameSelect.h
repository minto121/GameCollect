#pragma once
#include "AbstractScene.h"
enum class  SELECT {
    Mankara,
    Hitblow,
    Dotbox,
    Checker,
    Gomoku,
    Osero,
    Hekusu,
    Hanafuda,
    poker,
    sixballpuzzle,
    sinnkeisuizyaku,
    takoyaaki,
    rabbiitdog,
    lastcard,
    MENU_SIZE
};
class GameSelect :
    public AbstractScene
{
private:
    const char* menu_items[static_cast<int>(SELECT::MENU_SIZE)] = {
      "Mankara",
      "Hitblow",
      "Dotbox",
      "Checker",
      "Gomoku",
      "Osero",
      "Hekusu",
      "Hanafuda",
      "poker",
      "sixballpuzzle",
      "sinnkeisuizyaku",
      "takoyaaki",
      "rabbiitdog",
      "lastcard"
    };
    int now_menu; //現在選択しているメニュー
    int font_handle;  //フォント
    int input_margin;  //操作時間間隔
public:
    //コンストラクタ
    GameSelect();

    //デストラクタ
    ~GameSelect();

    //描画以外の更新を実行
    AbstractScene* Update() override;

    //描画に関することを実装
    void Draw() const override;
};

