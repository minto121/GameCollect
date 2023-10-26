#include "sinkeisuijaku.h"
#include "DxLib.h"
#include <stdlib.h>
#include <time.h>



AbstractScene* sinkeisuijaku::Update()
{
	S_timg = LoadGraph("../images/sinkensuijaku/ura.png");
	S_back = LoadGraph("../images/sinkensuijaku/back.png");

	//�g�����v�̉摜
	S_D1 = LoadGraph("../images/sinkensuijaku/D1.png");
	S_D2 = LoadGraph("../images/sinkensuijaku/D2.png");
	S_D3 = LoadGraph("../images/sinkensuijaku/D3.png");
	S_D4 = LoadGraph("../images/sinkensuijaku/D4.png");
	S_D5 = LoadGraph("../images/sinkensuijaku/D5.png");
	S_D6 = LoadGraph("../images/sinkensuijaku/D6.png");
	S_D7 = LoadGraph("../images/sinkensuijaku/D7.png");
	S_D8 = LoadGraph("../images/sinkensuijaku/D8.png");
	S_D9 = LoadGraph("../images/sinkensuijaku/D9.png");
	S_D10 = LoadGraph("../images/sinkensuijaku/D10.png");
	
	S_H1 = LoadGraph("../images/sinkensuijaku/H1.png");
	S_H2 = LoadGraph("../images/sinkensuijaku/H2.png");
	S_H3 = LoadGraph("../images/sinkensuijaku/H3.png");
	S_H4 = LoadGraph("../images/sinkensuijaku/H4.png");
	S_H5 = LoadGraph("../images/sinkensuijaku/H5.png");
	S_H6 = LoadGraph("../images/sinkensuijaku/H6.png");
	S_H7 = LoadGraph("../images/sinkensuijaku/H7.png");
	S_H8 = LoadGraph("../images/sinkensuijaku/H8.png");
	S_H9 = LoadGraph("../images/sinkensuijaku/H9.png");
	S_H10 = LoadGraph("../images/sinkensuijaku/H10.png");


	// ���̓L�[�擾
	g_OldKey = g_NowKey;
	g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	g_KeyFlg = g_NowKey & ~g_OldKey;



	//���j���[�J�[�\���ړ�����
	
	//��ړ�
	if (g_KeyFlg & PAD_INPUT_UP) {
		if (S_ber >= 0 && S_ber <= 4) {
			S_ber = S_ber - 1;
		}
		if (S_ber <0) {
			S_ber = 3;
		}
	}


	//���ړ�
	if (g_KeyFlg & PAD_INPUT_DOWN) {
		if (S_ber >= 0 && S_ber <= 4) {
			S_ber = S_ber + 1;
		}
		if (S_ber >= 4) {
			S_ber = 0;
		}
	}
	
	//�E�ړ�
	if (g_KeyFlg & PAD_INPUT_RIGHT) {
		S2_ber = S2_ber + 1;
		if (S2_ber == 5 || S2_ber == 9 || S2_ber == 14 || S2_ber == 19 || S2_ber == 24) {
			S2_ber = S2_ber - 5;
		}
	}

	//���ړ�
	if (g_KeyFlg & PAD_INPUT_LEFT) {
			S2_ber = S2_ber - 1;
		if (S2_ber == -1 || S2_ber == 6 || S2_ber ==  11|| S2_ber == 16 || S2_ber == 21) {
			S2_ber = S2_ber + 5;
		}
	}

	//�J�[�h�I��
	if (g_KeyFlg & PAD_INPUT_1) {
		trumpflg = 1;
	}
	if (trumpflg == 1) trumps[S_ber][S2_ber].flg = 1;
	trumpflg = 0;


	////�g�����v�ɒl������
	//int x = 1;
	//for (int j = 0; j < 4; j++) {
	//	for (int i = 0; i < 5; i++) {
	//		trumps[j][i].syurui = x++;
	//	}
	//}

	////�g�����v�̃V���b�t��
	//int y;

	//if (shuffle_flg == 0) {
	//	for (int i = 0; i < 3; i++) {
	//		srand((unsigned int)time(NULL));
	//		s = (rand() % 5 ) + 1 ;

	//		y = trumps[i][s].syurui;
	//		trumps[i][s].syurui = trumps[s][i].syurui;
	//		trumps[s][i].syurui = y;

	//	}
	//	shuffle_flg = 1;
	//}


	return this;
}

void sinkeisuijaku::Draw() const
{
//test


	DrawFormatString(100, 150, 0xfff00f, "%d %d", S_ber,S2_ber);

	DrawFormatString(100, 180, 0xfff00f, "���%d", trumps[S_ber][S2_ber].syurui);
	DrawFormatString(100, 200, 0xfff00f, "%d", s);
	//test 

	if (first  == 1) {
		DrawFormatString(50, 30, 0xff00ff, "��s�ł��I");
	}
	else {
		DrawFormatString(50, 30, 0xff00ff, "��U�ł��I");
	}
	
	//DrawGraph(0,0, S_back, FALSE);
	
	for (int j = 1; j < 5; j++) {
		for (int i = 0; i < 5; i++) {
			DrawRotaGraph(450 + i * 110, 0+ j*140, 0.5, 0, S_timg, TRUE);
		}
	}
	DrawBox(395 + S2_ber * 110 , 70 +S_ber * 140 , 495 + S2_ber  * 110, 215 + S_ber * 140, 0x00ffff, TRUE);


	//�J�[�\���̎l�p
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 5; i++) {
			DrawBox(395 + i * 110, 70 + j * 140, 495 + i * 110, 215 + j * 140, 0x00ffff, FALSE);
		}
	}


}

void sinkeisuijaku::Select()
{
	// ���݂̎��Ԃ��g���ď�����
	srand((unsigned int)time(NULL));


	// 1�܂���2�������_���ɐ���
	first = (rand() % 2) + 1;
	

}

