#pragma once
#include "AbstractScene.h"
enum class SELECT {
    Mankara,
    Hitblow,
    DotBox,
    Checker,
    Gomoku,
    Osero,
    Hekusu,
    Hanafuda,
    poker,
    sixballpuzzle,
    sinnkeisuizyaku,
    takoyaki,
    rabbitdog,
    lastcard,
    MENU_SIZE,
};
class GameSelect :
    public AbstractScene
{
private:
    const char* menu_items[static_cast<int>(SELECT::MENU_SIZE)] = {
       "Mankara",
    "Hitblow",
    "DotBox",
    "Checker",
    "Gomoku",
    "Osero",
    "Hekusu",
    "Hanafuda",
    "poker",
    "sixballpuzzle",
    "sinnkeisuizyaku",
    "takoyaki",
    "rabbitdog",
    "lastcard",
    };
    int now_menu;
    int font_handle;
    int input_margin;
    int Select;
    bool Once;

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

