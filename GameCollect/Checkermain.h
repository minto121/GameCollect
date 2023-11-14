#pragma once
#include "AbstractScene.h"
#include <DxLib.h>

class Checkermain : public AbstractScene
{
private:
    int Boardimg;     // �Ղ̉摜
    int PieceB;       // ��̉摜
    int PieceR;       // ��Ԃ̉摜
    int PieceBK;
    int PieceRK;
    int Checkerback;  // �w�i�̉摜
    int size = 100;   // �摜�̃T�C�Y

    int board[8][8] = {
        // �`�F�b�J�[�{�[�h�̏����z�u
        0, 1, 0, 0, 0, 2, 0, 2,
        1, 0, 1, 0, 0, 0, 2, 0,
        0, 1, 0, 0, 0, 2, 0, 2,
        1, 0, 1, 0, 0, 0, 2, 0,
        0, 1, 0, 0, 0, 2, 0, 2,
        1, 0, 1, 0, 0, 0, 2, 0,
        0, 1, 0, 0, 0, 2, 0, 2,
        1, 0, 1, 0, 0, 0, 2, 0
    };

    bool F_select = false;  // �I�𒆂̋���邩�ǂ���
    bool phase;             // ��U�i0�j��U�i1�j��\��

    int selectX;    // �J�[�\����X���W
    int selectY;    // �J�[�\����Y���W

    int g_OldKey;   // �O��̃L�[���͏��
    int g_NowKey;   // ���݂̃L�[���͏��
    int g_KeyFlg;   // �L�[�̕ω��������t���O

    int StartX;     // �ړ�����������̍��WX
    int StartY;     // �ړ�����������̍��WY
    int SelectX;    // ����ړ����������WX
    int SelectY;    // ����ړ����������WY
    int jumpedX;
    int jumpedY;

    int player1Pieces;
    int player2Pieces;

public:
    Checkermain();

    ~Checkermain();

    // �`��ȊO�̍X�V�����s
    AbstractScene* Update() override;

    // �`��Ɋւ��邱�Ƃ�����
    void Draw() const override;

    // �`�F�b�J�[�{�[�h�̏�����Ԃ�ݒ�
    void InitBoard();

    // �ړ�����
    bool IsMoveValid(int startX, int startY, int SelectX, int SelectY);

    void Gameover();
    bool CanTakeMore(int x, int y);

};
