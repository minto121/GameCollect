#pragma once
#include "Checkermain.h"
#include "DxLib.h"

Checkermain::Checkermain() {
    // �摜��ǂݍ��݁A������
    Boardimg = LoadGraph("../images/Checkers/banmen.png");   // �{�[�h
    PieceB = LoadGraph("../images/Checkers/WK.png");         // �
    PieceR = LoadGraph("../images/Checkers/RD.png");         // ���
    PieceBK = LoadGraph("../images/Checkers/KB.png");        //kingkuro
    PieceRK=LoadGraph("../images/Checkers/KR.png");          //kingaka
    Checkerback = LoadGraph("../images/Checkers/back.png");  // �w�i
    selectX = 0;                                             // �J�[�\���ړ�X���W
    selectY = 0;                                             // �J�[�\���ړ�Y���W
    phase = 0;                                               // ��U��U�̃t���O
    F_select = false;                                        // ��̑I����Ԃ�������
    movevail = false;                                        // �ړ����L�����ǂ�����\��
    cantake = false;
    StartX = 0;                                              // �ړ���X���W
    StartY = 0;                                              // �ړ���Y���W
    SelectX = 0;                                             // �ړ���X���W
    SelectY = 0;                                             // �ړ���Y���W
    jumpedX = 0;
    jumpedY = 0;
    player1Pieces = 12;                                      // �v���C���[1�̋�̐�
    player2Pieces = 12;                                      // �v���C���[2�̋�̐�
}

Checkermain::~Checkermain() {
    // �f�X�g���N�^
}

AbstractScene* Checkermain::Update() {

    /*Gameover();*/
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
                if (g_KeyFlg & PAD_INPUT_1 && (board[selectX][selectY] == 1)) {
                    StartX = selectX;
                    StartY = selectY;
                    F_select = true;
                }
                else if (g_KeyFlg & PAD_INPUT_1 && (board[selectX][selectY] == 4)) {
                    StartX = selectX;
                    StartY = selectY;
                    F_select = true;
                }
                if (g_KeyFlg & PAD_INPUT_1 && board[selectX][selectY] == 0 ) {
                    SelectX = selectX;
                    SelectY = selectY;
                    F_select = false;
                    if (IsMoveValid(StartX, StartY, SelectX, SelectY)) {
                      
                        board[SelectX][SelectY] = board[StartX][StartY];
                        board[StartX][StartY] = 0;
                        CanTakeMore(SelectX, SelectY);
                      
                    }
                    // ����̏����Ő������鏈����ǉ�
                    if (board[SelectX][SelectY] == 1 && SelectY == 7) {
                        board[SelectX][SelectY] = 4; // 4�͐�����\��
                    }
                    if (cantake == true) {
                        phase = 0;
                    }
                    else {
                        phase = 1;
                    }
                }

            }
            else if (phase == 1) {
                if (g_KeyFlg & PAD_INPUT_1 && (board[selectX][selectY] == 2)) {
                    StartX = selectX;
                    StartY = selectY;
                    F_select = true;
                }
                else if (g_KeyFlg & PAD_INPUT_1 && (board[selectX][selectY] == 3)) {
                    StartX = selectX;
                    StartY = selectY;
                    F_select = true;
                }
                if (g_KeyFlg & PAD_INPUT_1 && board[selectX][selectY] == 0) {
                    SelectX = selectX;
                    SelectY = selectY;
                    F_select = false;
                    if (IsMoveValid(StartX, StartY, SelectX, SelectY)) {

                        board[SelectX][SelectY] = board[StartX][StartY];
                        board[StartX][StartY] = 0;
                        CanTakeMore(SelectX, SelectY);
                     
                    }
                    // ����̏����Ő������鏈����ǉ�
                    if (board[SelectX][SelectY] == 2 && SelectY == 0) {
                        board[SelectX][SelectY] = 3; // 4�͐�����\��
                    }
                    if (cantake == true) {
                        phase = 1;
                    }
                    else {
                        phase = 0;
                    }

                }

            }

        }
    }
    return this;
}

void Checkermain::Draw() const {
    // �w�i��`��
    DrawGraph(0, 0, Checkerback, FALSE);
    // �{�[�h��`��
    DrawGraph(180, 0, Boardimg, TRUE);

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
                DrawRotaGraph(x * 73 + 400, y * 72 + 108, 2,0, PieceR, TRUE);
            }
        }
    }

    // �����̋��`��
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (board[x][y] == 3) {
                DrawRotaGraph(x * 73 + 400, y * 72 + 108, 2, 0, PieceBK, TRUE);
            }
        }
    }
    // �����̋��`��
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (board[x][y] == 4) {
                DrawRotaGraph(x * 73 + 400, y * 72 + 108, 2, 0, PieceRK, TRUE);
            }
        }
    }

   

    // �J�[�\���̈ʒu�Ɏl�p�`��`��
    DrawBox(372 + (selectX * 71), 72 + (selectY * 71), 445 + (selectX * 71), 145 + (selectY * 71), GetColor(0, 250, 0), FALSE);

    // �f�o�b�O����\��
    DrawFormatString(0, 0, 0x000000, "Y: %d", selectY);                 // �J�[�\���ړ�Y
    DrawFormatString(0, 30, 0x000000, "X: %d", selectX);                // �J�[�\���ړ�X
    DrawFormatString(0, 100, 0x000000, "F_select: %d", F_select);
    DrawFormatString(0, 125, 0x000000, "cantake: %d", cantake);
    DrawFormatString(0, 150, 0x000000, "Phase: %d", phase);
    DrawFormatString(0, 200, 0x000000, "board: %d", board[selectX][selectY]);
    DrawFormatString(0, 300, 0x000000, " player1Pieces: %d", player1Pieces);
    DrawFormatString(0, 350, 0x000000, " player2Pieces: %d", player2Pieces);
}

void Checkermain::InitBoard() {
    // �`�F�b�J�[�{�[�h�̏�����
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = 0;
        }
    }
    player1Pieces = 12; // �v���C���[1�̋�̐�
    player2Pieces = 12; // �v���C���[2�̋�̐�
}

bool Checkermain::IsMoveValid(int StartX, int StartY, int SelectX, int SelectY) {
    // �ړ��悪�{�[�h�͈̔͊O�ł���ꍇ�A����
    if (SelectX < 0 || SelectY < 0 || SelectX >= 8 || SelectY >= 8) {
        return false;
    }

    // �ړ���ɂ��łɋ����ꍇ�A����
    if (board[SelectX][SelectY] != 0) {
        return false;
    }

   
    // �ԋ�G�w�n�̒[�ɓ��B�����琬���ɂȂ�


    // �ԋ�
    if (board[StartX][StartY] == 1){
    // �ړ��悪�אڂ��Ă���ꍇ�i�ʏ�̈ړ��j�ԋ�̉E�΂ߑO�ړ�
        if ((SelectX - StartX) == 1 && (SelectY - StartY) == 1) {
            // 1�O�ɐi�ނ��Ƃ�������������ǉ�
            if (board[StartX][StartY] == 1) {
                return true;
            }
        }
        // �ԋ�̍��΂ߑO�ړ�
        else if ((SelectX - StartX) == -1 && (SelectY - StartY) == 1) {
            // 1�O�ɐi�ނ��Ƃ�������������ǉ�
            if (board[StartX][StartY] == 1) {
                return true;
            }
        }
        //else if (SelectY==7) {
        //        board[StartX][StartY] = 0;
        //        board[SelectX][SelectY] = 4; // 4�͐�����\��
        //    return false;
        //}
    }
    // ����
    if (board[StartX][StartY] == 2) {
        // ����̉E�΂ߑO�ړ�
        if ((SelectX - StartX) == -1 && (SelectY - StartY) == -1) {
            // 1�O�ɐi�ނ��Ƃ�������������ǉ�
            if (board[StartX][StartY] == 2) {
                return true;
            }
        }
        // ����̍��΂ߑO�ړ�
        else  if ((SelectX - StartX) == 1 && (SelectY - StartY) == -1) {
            // 1�O�ɐi�ނ��Ƃ�������������ǉ�
            if (board[StartX][StartY] == 2) {
                return true;
            }
        }
        // ����G�w�n�̒[�ɓ��B�����琬���ɂȂ�
        //else if (SelectY == 0) {
        //    board[StartX][StartY] = 0;
        //    board[SelectX][SelectY] = 3; // 3�͐�����\��
        //    return false;
        //}
    }
    // ����
    if (board[StartX][StartY] == 3){
        if ((SelectX - StartX) == 1 && (SelectY - StartY) == 1) {
            // 1�O�ɐi�ނ��Ƃ�������������ǉ��i��������̈ړ��j
            if (board[StartX][StartY] == 3) {
                return true;
            }
        }
        else  if ((SelectX - StartX) == -1 && (SelectY - StartY) == 1) {
            // 1�O�ɐi�ނ��Ƃ�������������ǉ��i��������̈ړ��j
            if (board[StartX][StartY] == 3) {
                return true;
            }
        }
        else if ((SelectX - StartX) == -1 && (SelectY - StartY) == -1) {
            // 1�O�ɐi�ނ��Ƃ�������������ǉ��i��������΂ߌ��̈ړ��j
            if (board[StartX][StartY] == 3) {
                return true;
            }
        }
        else if ((SelectX - StartX) == 1 && (SelectY - StartY) == -1) {
            // 1�O�ɐi�ނ��Ƃ�������������ǉ��i��������E�΂ߌ��̈ړ��j
            if (board[StartX][StartY] == 3) {
                return true;
            }
        }

    }
    // �ԋ�
    if (board[StartX][StartY] == 4){
        if ((SelectX - StartX) == 1 && (SelectY - StartY) == 1) {
            // 1�O�ɐi�ނ��Ƃ�������������ǉ��i�����ԋ�΂ߌ��̈ړ��j
            if (board[StartX][StartY] == 4) {
                return true;
            }
        }
        else  if ((SelectX - StartX) == -1 && (SelectY - StartY) == 1) {
            // 1�O�ɐi�ނ��Ƃ�������������ǉ��i�����ԋ�E�΂ߌ��̈ړ��j
            if (board[StartX][StartY] == 4) {
                return true;
            }
        }
        else  if ((SelectX - StartX) == -1 && (SelectY - StartY) == -1) {
            // 1�O�ɐi�ނ��Ƃ�������������ǉ��i�����ԋ�̈ړ��j
            if (board[StartX][StartY] == 4) {
                return true;
            }
        }
        else    if ((SelectX - StartX) == 1 && (SelectY - StartY) == -1) {
            // 1�O�ɐi�ނ��Ƃ�������������ǉ��i�����ԋ�̈ړ��j
            if (board[StartX][StartY] == 4) {
                return true;
            }
        }
    }

 

    // �ړ��悪�΂߂�2��щz����ꍇ�i�W�����v�jaka
    // �ԋ�̃W�����v�������`�F�b�N
    if (board[StartX][StartY] == 1) {
        // �㉺���E�΂߂��ꂼ��̃W�����v�\�ȏꍇ���ʂɃ`�F�b�N
        if ((SelectX - StartX == -2 && SelectY - StartY == 2) || (SelectX - StartX == 2 && SelectY - StartY == 2)) {
            jumpedX = (SelectX + StartX) / 2;
            jumpedY = (SelectY + StartY) / 2;
            // ��щz�����ʒu�ɑ���̋���邩�m�F
            if (board[jumpedX][jumpedY] == 2 || (board[jumpedX][jumpedY] == 3)) {
                // ��щz��������̋���폜
                board[jumpedX][jumpedY] = 0;

                return true;
            }
        }


    }

    // �ړ��悪�΂߂�2��щz����ꍇ�i�W�����v�jkuro
   // ����̃W�����v�������`�F�b�N
    if (board[StartX][StartY] == 2) {
        // �㉺���E�΂߂��ꂼ��̃W�����v�\�ȏꍇ���ʂɃ`�F�b�N
        if ((SelectX - StartX == 2 && SelectY - StartY == -2) || (SelectX - StartX == -2 && SelectY - StartY == -2)) {
            jumpedX = (SelectX + StartX) / 2;
            jumpedY = (SelectY + StartY) / 2;
            // ��щz�����ʒu�ɑ���̋���邩�m�F
            if (board[jumpedX][jumpedY] == 1 ||(board[jumpedX][jumpedY] == 4)) {
                // ��щz��������̋���폜
                board[jumpedX][jumpedY] = 0;

                return true;
            }
        }


    }
   // ����̃W�����v�������`�F�b�N�i�����j
    if (board[StartX][StartY] == 3) {
        // �㉺���E�΂߂��ꂼ��̃W�����v�\�ȏꍇ���ʂɃ`�F�b�N
        if ((SelectX - StartX == 2 && SelectY - StartY == -2) || (SelectX - StartX == -2 && SelectY - StartY == -2)|| (SelectX - StartX == -2 && SelectY - StartY == 2) || (SelectX - StartX == 2 && SelectY - StartY == 2)) {
            jumpedX = (SelectX + StartX) / 2;
            jumpedY = (SelectY + StartY) / 2;
            // ��щz�����ʒu�ɑ���̋���邩�m�F
            if ((board[jumpedX][jumpedY] == 1)||(board[jumpedX][jumpedY] == 4)) {
                // ��щz��������̋���폜
                board[jumpedX][jumpedY] = 0;

                return true;
            }
        }

    }
    // �ԋ�̃W�����v�������`�F�b�N�i�����j
    if (board[StartX][StartY] == 4) {
        // �㉺���E�΂߂��ꂼ��̃W�����v�\�ȏꍇ���ʂɃ`�F�b�N
        if ((SelectX - StartX == 2 && SelectY - StartY == -2) || (SelectX - StartX == -2 && SelectY - StartY == -2) || (SelectX - StartX == -2 && SelectY - StartY == 2) || (SelectX - StartX == 2 && SelectY - StartY == 2)) {
            jumpedX = (SelectX + StartX) / 2;
            jumpedY = (SelectY + StartY) / 2;
            // ��щz�����ʒu�ɑ���̋���邩�m�F
            if ((board[jumpedX][jumpedY] == 2) || (board[jumpedX][jumpedY] == 3)) {
                // ��щz��������̋���폜
                board[jumpedX][jumpedY] = 0;

                return true;
            }
        }

    }
   
    return false; // ��L�̏����ɊY�����Ȃ��ꍇ�A�����Ȉړ�
}

void Checkermain::Gameover()
{
    // �v���C���[1�̋�̐����X�V
    player1Pieces = 0;
    // �v���C���[2�̋�̐����X�V
    player2Pieces = 0;

    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if (board[x][y] == 1 || board[x][y] == 3) {
                player1Pieces++;
            }
            else if (board[x][y] == 2 || board[x][y] == 4) {
                player2Pieces++;
            }
        }
    }
    // �ǂ��炩�̃v���C���[����������Ă��Ȃ��ꍇ�A���s�������Ɣ���
    if (player1Pieces == 0) {
        // �v���C���[2�̏���
        printf("bbb");
        // �܂��́A�K�v�ɉ����ĕʂ̏�����ǉ�
    }
    else if (player2Pieces == 0) {
        // �v���C���[1�̏���
        printf("aaaa");
        // �܂��́A�K�v�ɉ����ĕʂ̏�����ǉ�
    }
}



bool Checkermain::CanTakeMore(int SelectX, int SelectY)
{ // ������邩�ǂ����������t���O
    cantake = 0;

    // ��ՖʊO�ɂ���ꍇ�͎��Ȃ�
    if (SelectX < 0 || SelectY < 0 || SelectX >= 8 || SelectY >= 8) {
        return false;
    }
    // �ړ���ɂ��łɋ����ꍇ�A����
    if (board[SelectX+2][SelectY+2]|| board[SelectX - 2][SelectY - 2]|| board[SelectX - 2][SelectY + 2]|| board[SelectX + 2][SelectY - 2] != 0) {
        return false;
    }
     // �ԋ�̃W�����v�������`�F�b�N
    if (board[StartX][StartY] == 1) {
        if  (board[SelectX + 2][SelectY + 2] || board[SelectX - 2][SelectY + 2]) {
            return false;
        }
        // �㉺���E�΂߂��ꂼ��̃W�����v�\�ȏꍇ���ʂɃ`�F�b�N
        if (((SelectX + 2) - SelectX == -2 && (SelectY + 2) - SelectY == 2) || ((SelectX + 2) - SelectX == 2 && (SelectY + 2) - SelectY == 2)) {
            jumpedX = ((SelectX + 2) + SelectX) / 2;
            jumpedY = ((SelectY + 2) + SelectY) / 2;
            // ��щz�����ʒu�ɑ���̋���邩�m�F
            if (board[jumpedX][jumpedY] == 2 || (board[jumpedX][jumpedY] == 3)) {
                cantake = true;
          
                return false;
            }
            else if (board[jumpedX][jumpedY] == 0) {
                cantake = false;
             
                return false;
            }
        }
        else if (board[StartX][StartY] == 2) {
            if (board[SelectX - 2][SelectY - 2] || board[SelectX + 2][SelectY - 2]) {
                return false;
            }
            if (board[SelectX - 2][SelectY - 2] || board[SelectX + 2][SelectY - 2]) {
                return false;
            }
            // �㉺���E�΂߂��ꂼ��̃W�����v�\�ȏꍇ���ʂɃ`�F�b�N
            if (((SelectX+2) - SelectX == 2 && (SelectY+2) - SelectY == -2) || ((SelectX+2) - SelectX == -2 && (SelectY+2) - SelectY == -2)) {
                jumpedX = (SelectX + SelectX) / 2;
                jumpedY = (SelectY + SelectX) / 2;
                // ��щz�����ʒu�ɑ���̋���邩�m�F
                if (board[jumpedX][jumpedY] == 1 || (board[jumpedX][jumpedY] == 4)) {
                    // ��щz��������̋���폜
                    cantake = true;
                
                    
                    return true;
                }
                else if (board[jumpedX][jumpedY] == 0) {
                    cantake = false;
                  
                    return false;
                }
            }


        }

    }

    return false;
}
