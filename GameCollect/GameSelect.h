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
    //�R���X�g���N�^
    GameSelect();

    //�f�X�g���N�^
    ~GameSelect();

    //�`��ȊO�̍X�V�����s
    AbstractScene* Update() override;

    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;
};

