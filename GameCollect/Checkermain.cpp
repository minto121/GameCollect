#pragma once
#include "Checkermain.h"
#include "DxLib.h"

Checkermain::Checkermain() {
    // �摜��ǂݍ��݁A������
    Boardimg = LoadGraph("../images/Checkers/banmen.png");    // �{�[�h
    PieceB = LoadGraph("../images/Checkers/WK.png");         // �
    PieceW = LoadGraph("../images/Checkers/BK.png");         // �
    Checkerback = LoadGraph("../images/Checkers/back.png");  // �w�i
    selectX = 0;                                             // �J�[�\���ړ�X���W
    selectY = 0;                                             // �J�[�\���ړ�Y���W
    phase = 0;                                               // ��U��U�̃t���O
    F_select = false; // ��̑I����Ԃ�������
    StartX = 0;      // �ړ���X���W
    StartY = 0;      // �ړ���Y���W
    SelectX = 0;     // �ړ���X���W
    SelectY = 0;     // �ړ���Y���W
    jumpedX = 0;
    jumpedY = 0;
}

Checkermain::~Checkermain() {
    // �f�X�g���N�^
}

AbstractScene* Checkermain::Update() {
    // �L�[���͂̏�Ԃ��X�V
    g_OldKey = g_NowKey;
    g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
    g_KeyFlg = g_NowKey & ~g_OldKey;

    // �J�[�\���𓮂�������
    if (g_KeyFlg & PAD_INPUT_RIGHT && selectX < 7) {
        selectX += 1;
    }
    if (g_KeyFlg & PAD_INPUT_LEFT && selectX > 0) {
        selectX -= 1;
    }
    if (g_KeyFlg & PAD_INPUT_DOWN && selectY < 7) {
        selectY += 1;
    }
    if (g_KeyFlg & PAD_INPUT_UP && selectY > 0) {
        selectY -= 1;
    }

    // ��̈ړ�
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if (phase == 0) {
                if (g_KeyFlg & PAD_INPUT_1 && board[selectX][selectY] == 1) {
                    StartX = selectX;
                    StartY = selectY;
                    F_select = true;
                }
                if (g_KeyFlg & PAD_INPUT_1 && board[selectX][selectY] == 0) {
                    SelectX = selectX;
                    SelectY = selectY;
                    F_select = false;
                    if (IsMoveValid(StartX, StartY, SelectX, SelectY)) {
                        board[SelectX][SelectY] = 1;
                        board[StartX][StartY] = 0;
                        phase = 1;
                    }
                }
            }
            else if (phase == 1) {
                if (g_KeyFlg & PAD_INPUT_1 && board[selectX][selectY] == 2) {
                    StartX = selectX;
                    StartY = selectY;
                    F_select = true;
                }
                if (g_KeyFlg & PAD_INPUT_1 && board[selectX][selectY] == 0) {
                    SelectX = selectX;
                    SelectY = selectY;
                    F_select = false;
                    if (IsMoveValid(StartX, StartY, SelectX, SelectY)) {
                        board[SelectX][SelectY] = 2;
                        board[StartX][StartY] = 0;
                        phase = 0;
                    }
                }
            }
            // �Q�[���I�[�o�[
            if (board[x][y] == 0) {

            }
        }
      
    }
   

    return this;
}

void Checkermain::Draw() const {
    // �w�i��`��
    DrawGraph(0, 0, Checkerback, FALSE);
    // �{�[�h��`��
    DrawGraph(300, 0, Boardimg, TRUE);

    // �v���C���[1�̋��`��
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (board[x][y] == 2) {
                DrawRotaGraph(x * 74 + 400, y * 72 + 108, 2, 0, PieceB, TRUE);
            }
        }
    }

    // �v���C���[2�̋��`��
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (board[x][y] == 1) {
                DrawCircle(x * 74 + 400, y * 72 + 105, 28, GetColor(255, 0, 0), TRUE);
            }
        }
    }
    // �����̋��`��
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (board[x][y] == 3) {
                DrawCircle(x * 74 + 400, y * 72 + 105, 28, GetColor(255,255, 0), TRUE);
            }
        }
    }

    // �J�[�\���̈ʒu�Ɏl�p�`��`��
    DrawBox(372 + (selectX * 71), 72 + (selectY * 71), 445 + (selectX * 71), 145 + (selectY * 71), GetColor(0, 250, 0), FALSE);

    // �f�o�b�O����\��
    DrawFormatString(0, 0, 0x000000, "Y: %d", selectY); // �J�[�\���ړ�Y
    DrawFormatString(0, 30, 0x000000, "X: %d", selectX); // �J�[�\���ړ�X
    DrawFormatString(0, 100, 0x000000, "F_select: %d", F_select);
}

void Checkermain::InitBoard() {
    // �`�F�b�J�[�{�[�h�̏�����
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = 0;
        }
    }
}

bool Checkermain::IsMoveValid(int startX, int startY, int SelectX, int SelectY) {
    // �ړ��悪�{�[�h�͈̔͊O�ł���ꍇ�A����
    if (SelectX < 0 || SelectY < 0 || SelectX >= 8 || SelectY >= 8) {
        return false;
    }

    // �ړ���ɂ��łɋ����ꍇ�A����
    if (board[SelectX][SelectY] != 0) {
        return false;
    }

   

    // �ړ��悪�אڂ��Ă���ꍇ�i�ʏ�̈ړ��j
    if (abs(SelectX - startX) == 1 && SelectY - startY == 1) {
        // 1�O�ɐi�ނ��Ƃ�������������ǉ�
        if (board[startX][startY] == 1 || board[startX][startY] == 3) {
            return true;
        }
    }
    if (abs(SelectX - startX) == -1 && SelectY - startY == 1) {
        // 1�O�ɐi�ނ��Ƃ�������������ǉ�
        if (board[startX][startY] == 1 || board[startX][startY] == 2) {
            return true;
        }
    }
    if (abs(SelectX - startX) == 1 && SelectY - startY == -1) {
        // 1�O�ɐi�ނ��Ƃ�������������ǉ�
        if (board[startX][startY] == 2 || board[startX][startY] == 3) {
            return true;
        }
    }
    if (abs(SelectX - startX) == -1 && SelectY - startY == -1) {
        // 1�O�ɐi�ނ��Ƃ�������������ǉ�
        if (board[startX][startY] == 2 || board[startX][startY] == 3) {
            return true;
        }
    }
    // �ړ��悪�΂߂�1���ړ�����ꍇ�i�����̈ړ��j
    if (abs(SelectX - startX) == 1 && abs(SelectY - startY) == 1) {
        if (board[startX][startY] == 3) {
            return true;
        }
    }
    // �ړ��悪�΂߂�2��щz����ꍇ�i�W�����v�j
    if (abs(SelectX - startX) == 2 && abs(SelectY - startY) == 2) {
        jumpedX = (SelectX + startX) / 2;
        jumpedY = (SelectY + startY) / 2;

        // ��щz�����ʒu�ɑ���̋���邩�m�F
        if (board[jumpedX][jumpedY] != 0) {
            // ��щz��������̋���폜
            board[jumpedX][jumpedY] = 0;

            // ����w�n�̒[�ɓ��B�����琬���ɂȂ�
            if (SelectY == 0 || SelectY==7) {
                board[SelectX][SelectY] = 3; // 3�͐�����\��
            }

            return true;
        }
    }
   
    return false; // ��L�̏����ɊY�����Ȃ��ꍇ�A�����Ȉړ�
}
