#pragma once
#include "AbstractScene.h"
#include <DxLib.h>

class Checkermain : public AbstractScene {
private:
    // �摜�f�[�^��ID�ƃT�C�Y�Ȃǂ̕ϐ�
    int Boardimg;      // �Ղ̉摜
    int PieceB;        // ��̉摜
    int PieceR;        // ��Ԃ̉摜
    int PieceBK;
    int PieceRK;
    int Checkerback;   // �w�i�̉摜
    int size = 100;    // �摜�̃T�C�Y

    // �`�F�b�J�[�{�[�h�̏�� 0:��1:��
    int board[8][8] = {
        // �`�F�b�J�[�{�[�h�̏����z�u
        // ���l�̈Ӗ��F
        // 0: ��Ȃ��A1: �ԋ�A2: ����A3: �Ԃ̐����A4: ���̐���
        0, 1, 0, 0, 0, 2, 0, 2,
        1, 0, 1, 0, 0, 0, 2, 0,
        0, 1, 0, 0, 0, 2, 0, 2,
        1, 0, 1, 0, 0, 0, 2, 0,
        0, 1, 0, 0, 0, 2, 0, 2,
        1, 0, 1, 0, 0, 0, 2, 0,
        0, 1, 0, 0, 0, 2, 0, 2,
        1, 0, 1, 0, 0, 0, 2, 0
    };

    // �Q�[���̏�Ԃ��Ǘ�����ϐ�
    bool F_select = false;  // �I�𒆂̋���邩�ǂ���
    bool movevail;          // �ړ����L�����ǂ�����\��
    bool cantake = false;
    bool F_totteta = false;
    // �J�[�\���̈ʒu�ƃL�[���͊֘A�̕ϐ�
    int selectX;    // �J�[�\����X���W
    int selectY;    // �J�[�\����Y���W
    int g_OldKey;   // �O��̃L�[���͏��
    int g_NowKey;   // ���݂̃L�[���͏��
    int g_KeyFlg;   // �L�[�̕ω��������t���O
    int phase = 0;
    // ��̈ړ��Ɋւ���ϐ�
    int StartX;     // �ړ�����������̍��WX
    int StartY;     // �ړ�����������̍��WY
    int SelectX;    // ����ړ����������WX
    int SelectY;    // ����ړ����������WY
    int jumpedX;    // �W�����v�����ۂ�X���W
    int jumpedY;    // �W�����v�����ۂ�Y���W
    int SjumpedX;   // �W�����v�����ۂ�X���W
    int SjumpedY;   // �W�����v�����ۂ�Y���W
    // �v���C���[�̋��\���ϐ�
    int player1Pieces;
    int player2Pieces;

public:
    Checkermain(); // �R���X�g���N�^

    ~Checkermain(); // �f�X�g���N�^

    // �`��ȊO�̍X�V�����s����
    AbstractScene* Update() override;

    // �`��Ɋւ��鏈�����s��
    void Draw() const override;

    // �`�F�b�J�[�{�[�h�̏�����Ԃ�ݒ肷��
    void InitBoard();

    // �ړ��̑Ó����𔻒肷��
    bool IsMoveValid(int StartX, int StartY, int SelectX, int SelectY);

    // �Q�[���I���̔�����s��
    void Gameover();

    // �W�����v��ɂ���ɋ�����邩�ǂ����𔻒肷��
    bool CanTakeMore(int startX, int startY, int SelectX, int SelectY);

    
  
};
