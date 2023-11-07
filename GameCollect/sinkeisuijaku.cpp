#include "sinkeisuijaku.h"
#include "DxLib.h"
#include <stdlib.h>
#include <time.h>

sinkeisuijaku::sinkeisuijaku()
{
}

AbstractScene* sinkeisuijaku::Update()
{
    // �g�����v�̉摜�𕪊��ǂݍ���
    LoadDivGraph("images/Concentration/PlayingCards.png", 56, 14, 4, 128, 256, S_T);

    // �L�[���͏���
    // ���̓L�[�擾
    g_OldKey = g_NowKey;
    g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
    g_KeyFlg = g_NowKey & ~g_OldKey;

    // �Q�[�����W�b�N
    count++;

    // ���j���[�J�[�\���ړ�����
    // ��ړ�
    if (g_KeyFlg & PAD_INPUT_UP) {
        if (S_ber >= 0 && S_ber <= 4) {
            S_ber = S_ber - 1;
        }
        if (S_ber < 0) {
            S_ber = 3;
        }
    }

    // ���ړ�
    if (g_KeyFlg & PAD_INPUT_DOWN) {
        if (S_ber >= 0 && S_ber <= 4) {
            S_ber = S_ber + 1;
        }
        if (S_ber >= 4) {
            S_ber = 0;
        }
    }

    // �E�ړ�
    if (g_KeyFlg & PAD_INPUT_RIGHT) {
        S2_ber = S2_ber + 1;
        if (S2_ber == 5 || S2_ber == 9 || S2_ber == 14 || S2_ber == 19 || S2_ber == 24) {
            S2_ber = S2_ber - 5;
        }
    }

    // ���ړ�
    if (g_KeyFlg & PAD_INPUT_LEFT) {
        S2_ber = S2_ber - 1;
        if (S2_ber == -1 || S2_ber == 6 || S2_ber == 11 || S2_ber == 16 || S2_ber == 21) {
            S2_ber = S2_ber + 5;
        }
    }

    if (count >= 10) {
        // �J�[�h�I��
        if (g_KeyFlg & PAD_INPUT_1) {
            trumpflg = 1;
            rCount++;
        }
        if (trumpflg == 1) {
            trumps[S_ber][S2_ber].flg = 1;
        }
      
    }
    trumpflg = 0;

    // �g�����v�ɒl������
    if (count < 2) {
        int x = 1;
        for (int j = 0; j < 4; j++) {
            for (int i = 0; i < 5; i++) {
                trumps[j][i].syurui = x++;
            }
        }
    }

    // ��s��U����
    srand((unsigned int)time(NULL)); // ���݂̎��Ԃ��g���ď�����
    first = (rand() % 2) + 1; // 1�܂���2�������_���ɐ���
    srand((unsigned int)time(NULL));

    if (randend != 1) {
        for (int i = 0; i < 19; i++) {
            r = (rand() % 3) + 1;
            r2 = (rand() % 4) + 1;
            trumps[4][6].syurui = trumps[0][0].syurui;
            trumps[0][0].syurui = trumps[r][r2].syurui;
            trumps[r][r2].syurui = trumps[4][6].syurui;
        }
    }
    if (count >= 10) {
        randend = 1;
    }

    //�g�����v�̑I��3��ڂŗ��ʂɖ߂�

    if (rCount % 3 == 0) {
        for (int j = 0; j < 4; j++) {
            for (int i = 0; i < 5; i++) {
                    trumps[j][i].flg = 0;
            }
        }
    }

  

    return this;
}

void sinkeisuijaku::Draw() const
{
    //00��01�ł�������̕����ł����炠�Ƃ͐������������玗������
    if (trumps[0][1].flg == 1 && trumps[0][2].flg == 1) {
        DrawFormatString(100, 100, 0x0000ff, "����������I");
    }


  DrawFormatString(100, 260, 0xfff00f, "flg %d", trumps[0][1].flg);

    /*DrawFormatString(100, 260, 0xfff00f, "rCount %d", rCount);
    DrawFormatString(100, 280, 0xfff00f, "r2Count %d", r2Count);*/

    // �g�����v�̕\��
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 5; i++) {
            if (trumps[j][i].flg == 0 ) {
                // �J�[�h���I������Ă��Ȃ��ꍇ�A�J�[�h�̗���\��
                DrawRotaGraph(400 + i * 120, 130 + j * 150, 1, 0, S_T[0], TRUE);
            }
            else {
                if (trumps[j][i].syurui <= 10) {
                    // �J�[�h���I������Ă���ꍇ�A�J�[�h�̕\��\��
                    DrawGraph(340 + i * 120, 0 + j * 150, S_T[trumps[j][i].syurui], TRUE);
                }
                if (trumps[j][i].syurui > 10) {
                    DrawGraph(340 + i * 120, 0 + j * 150, S_T[trumps[j][i].syurui + 18], TRUE);
                }
            }
        }
    }

    // �I�𒆂̃g�����v�Ƀn�C���C�g��\��
    DrawBox(355 + S2_ber * 120, 55 + S_ber * 150, 450 + S2_ber * 120, 200 + S_ber * 150, 0xff0000, FALSE);

    // ���̑��̏��\��
    DrawFormatString(100, 180, 0xfff00f, "���%d", trumps[S_ber][S2_ber].syurui);

    // �^�[�����\��
    if (first == 1) {
        DrawFormatString(50, 30, 0xff00ff, "��s�ł��I");
    }
    else {
        DrawFormatString(50, 30, 0xff00ff, "��U�ł��I");
    }
}