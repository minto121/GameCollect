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
    int now_menu; //���ݑI�����Ă郁�j���[
    int font_handle;  //�t�H���g
    int input_margin;  //���쎞�ԊԊu
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

