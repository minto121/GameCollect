
#include "sinkeisuijaku.h"
#include "DxLib.h"
#include <stdlib.h>
#include <time.h>

AbstractScene* sinkeisuijaku::Update()
{
   
    // �g�����v�̉摜�𕪊��ǂݍ���
    LoadDivGraph("../images/Concentration/PlayingCards.png", 56, 14, 4, 120, 200, S_T);

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

    // �J�[�h�I��
    if (g_KeyFlg & PAD_INPUT_1) {
        trumpflg = 1;
    }
    if (trumpflg == 1) trumps[S_ber][S2_ber].flg = 1;

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
        for (int i = 0; i < 20; i++) {
            r = (rand() % 4) + 1;
            r2 = (rand() % 5) + 1;
            trumps[0][1].syurui = trumps[0][0].syurui;
            trumps[0][0].syurui = trumps[r][r2].syurui;
            trumps[r][r2].syurui = trumps[0][1].syurui;
        }
    }
    if (count >= 10) {
        randend = 1;
    }

    return this;
}

void sinkeisuijaku::Draw() const
{
    // �g�����v�̕\��
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 5; i++) {
            if (trumps[j][i].flg == 0) {
                // �J�[�h���I������Ă��Ȃ��ꍇ�A�J�[�h�̕\��\��
                DrawRotaGraph(430 + i * 120, 100 + j * 150, 1, 0, S_T[0], TRUE);
            }
            else {
                // �J�[�h���I������Ă���ꍇ�A�J�[�h�̗��ʁi��\���j��\��
                //DrawGraph(430 + i * 120, 0 + j * 150, S_T[4], TRUE);
            }
        }
    }
  

    // �I�𒆂̃g�����v�Ƀn�C���C�g��\��
    DrawBox(390 + S2_ber * 120, 110 + S_ber * 150, 480 + S2_ber * 120, 250 + S_ber * 150, 0x00ffff, TRUE);

    // ���̑��̏��\��
    DrawFormatString(100, 100, 0xfff00f, "flg %d", trumps[S_ber][S2_ber].flg);
    DrawFormatString(100, 150, 0xfff00f, "%d %d", S_ber, S2_ber);
    DrawFormatString(100, 180, 0xfff00f, "���%d", trumps[S_ber][S2_ber].syurui);
    DrawFormatString(100, 230, 0xfff00f, "count %d", count);

    // �^�[�����\��
    if (first == 1) {
        DrawFormatString(50, 30, 0xff00ff, "��s�ł��I");
    }
    else {
        DrawFormatString(50, 30, 0xff00ff, "��U�ł��I");
    }
}