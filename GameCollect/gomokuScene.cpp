#include "gomokuScene.h"
#include"DxLib.h"
#include <stdio.h>

gomokuScene::gomokuScene()
{
	TitleImg = LoadGraph("../images/Gomoku/gomoku.png");
	wTopImg = LoadGraph("../images/Gomoku/BK.png");
	bTopImg = LoadGraph("../images/Gomoku/WK.png");
	gomoku_BackImg = LoadGraph("../images/Gomoku/BackGround02.png");
	cX = 0;
	cY = 0;
	bCount = 0;
	wCount = 0;
	for (int y = 0; y < 13; y++)
		for (int x = 0; x < 13; x++) {
			/*if (x == 6 && y == 6 || x == 7 && y == 7) {
				Banmen[x][y] = 1;
			}
			else if (x == 6 && y == 7 || x == 7 && y == 6) {
				Banmen[x][y] = 2;
			}
			else {*/
				gomoku_Banmen[x][y] = 0;
			}
	gomoku_Phase = 0;
	gomoku_Battle = 0;
}

gomokuScene::~gomokuScene()
{}

AbstractScene* gomokuScene::Update()
{
	if (gomoku_Battle == 0) { // �������Ȃ���s����

		g_OldKey = g_NowKey;
		g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		g_KeyFlg = g_NowKey & ~g_OldKey;

		// �J�[�\���𓮂�������
		if (gomoku_Phase == 0) {
			if (g_KeyFlg & PAD_INPUT_RIGHT && cX < 13) {
				cX += 1;
				if (g_KeyFlg & PAD_INPUT_RIGHT && cX == 13) {
					cX = 0;
				}
			}
			if (g_KeyFlg & PAD_INPUT_LEFT && cX > -1) {
				cX -= 1;
				if (g_KeyFlg & PAD_INPUT_LEFT && cX == -1) {
					cX = 12;
				}
			}
			if (g_KeyFlg & PAD_INPUT_DOWN && cY < 13) {
				cY += 1;
				if (g_KeyFlg & PAD_INPUT_DOWN && cY == 13) {
					cY = 0;
				}
			}
			if (g_KeyFlg & PAD_INPUT_UP && cY > -1) {
				cY -= 1;
				if (g_KeyFlg & PAD_INPUT_UP && cY == -1) {
					cY = 12;
				}
			}
		}

		// �܂��΂��u����Ă��Ȃ��Ֆʂɐ΂�u���A��Ԃ���シ��
		if (g_KeyFlg & PAD_INPUT_1 && gomoku_Banmen[cX][cY] == 0) {
			if (gomoku_Phase == 0) {
				bCount += 1;
				gomoku_Banmen[cX][cY] = 1;
				gomoku_Phase = 1;
			}
			/*else {
				gomoku_Banmen[cX][cY] = 2;
			}*/
			/*if (gomoku_Phase == 0) {
				gomoku_Phase = 1;
			}*/
			/*else {
				gomoku_Phase = 0;
			}*/
		}
		for (int y = 0; y < 13; y++) {
			for (int x = 0; x < 13; x++) {
				// ��(Banmen[x][y] = 1)�̏�������
				if (gomoku_Banmen[x][y] == 1 && gomoku_Banmen[x + 1][y] == 1 && gomoku_Banmen[x + 2][y] == 1 && gomoku_Banmen[x + 3][y] == 1 && gomoku_Banmen[x + 4][y] == 1 ||
					gomoku_Banmen[x][y] == 1 && gomoku_Banmen[x][y + 1] == 1 && gomoku_Banmen[x][y + 2] == 1 && gomoku_Banmen[x][y + 3] == 1 && gomoku_Banmen[x][y + 4] == 1 ||
					gomoku_Banmen[x][y] == 1 && gomoku_Banmen[x + 1][y + 1] == 1 && gomoku_Banmen[x + 2][y + 2] == 1 && gomoku_Banmen[x + 3][y + 3] == 1 && gomoku_Banmen[x + 4][y + 4] == 1 ||
					gomoku_Banmen[x][y] == 1 && gomoku_Banmen[x - 1][y - 1] == 1 && gomoku_Banmen[x - 2][y - 2] == 1 && gomoku_Banmen[x - 3][y - 3] == 1 && gomoku_Banmen[x - 4][y - 4] == 1 ||
					gomoku_Banmen[x][y] == 1 && gomoku_Banmen[x + 1][y - 1] == 1 && gomoku_Banmen[x + 2][y - 2] == 1 && gomoku_Banmen[x + 3][y - 3] == 1 && gomoku_Banmen[x + 4][y - 4] == 1 ||
					gomoku_Banmen[x][y] == 1 && gomoku_Banmen[x - 1][y + 1] == 1 && gomoku_Banmen[x - 2][y + 2] == 1 && gomoku_Banmen[x - 3][y + 3] == 1 && gomoku_Banmen[x - 4][y + 4] == 1) {
					gomoku_Battle = 1;
				}
			}
		}
		// ��������AI
		if (gomoku_Battle == 0)
			for (int y = 0; y < 13; y++)
				for (int x = 0; x < 13; x++)
					if (gomoku_Phase == 1)
						//// �Ֆʂɍ����O����ł��āA���[�ɐ΂��u����Ă��Ȃ��ꍇ����u���v���O���~���O
						//if (gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x][y + 1] == 1 && gomoku_Banmen[x][y + 2] && gomoku_Banmen[x][y + 3] ||
						//	gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x + 1][y] == 1 && gomoku_Banmen[x + 2][y] && gomoku_Banmen[x + 3][y] ||
						//	gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x + 1][y + 1] == 1 && gomoku_Banmen[x + 2][y + 2] && gomoku_Banmen[x + 3][y + 3] ||
						//	gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x - 1][y - 1] == 1 && gomoku_Banmen[x - 2][y - 2] && gomoku_Banmen[x - 3][y - 3] ||
						//	gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x + 1][y - 1] == 1 && gomoku_Banmen[x + 2][y - 2] && gomoku_Banmen[x + 3][y - 3] ||
						//	gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x - 1][y + 1] == 1 && gomoku_Banmen[x - 2][y + 2] && gomoku_Banmen[x - 3][y + 3]) {
						if (gomoku_Banmen[x][y] == 0 && gomoku_Phase == 1) {
							wCount += 1;
							gomoku_Banmen[x][y] = 2;
							gomoku_Phase = 0;
						}
		/*}
		else if()*/
		/*}*/

		for (int y = 0; y < 13; y++) {
			for (int x = 0; x < 13; x++) {
				// ��(Banmen[x][y] = 2)�̏�������
				if (gomoku_Banmen[x][y] == 2 && gomoku_Banmen[x + 1][y] == 2 && gomoku_Banmen[x + 2][y] == 2 && gomoku_Banmen[x + 3][y] == 2 && gomoku_Banmen[x + 4][y] == 2 ||
					gomoku_Banmen[x][y] == 2 && gomoku_Banmen[x][y + 1] == 2 && gomoku_Banmen[x][y + 2] == 2 && gomoku_Banmen[x][y + 3] == 2 && gomoku_Banmen[x][y + 4] == 2 ||
					gomoku_Banmen[x][y] == 2 && gomoku_Banmen[x + 1][y + 1] == 2 && gomoku_Banmen[x + 2][y + 2] == 2 && gomoku_Banmen[x + 3][y + 3] == 2 && gomoku_Banmen[x + 4][y + 4] == 2 ||
					gomoku_Banmen[x][y] == 2 && gomoku_Banmen[x - 1][y - 1] == 2 && gomoku_Banmen[x - 2][y - 2] == 2 && gomoku_Banmen[x - 3][y - 3] == 2 && gomoku_Banmen[x - 4][y - 4] == 2 ||
					gomoku_Banmen[x][y] == 2 && gomoku_Banmen[x + 1][y - 1] == 2 && gomoku_Banmen[x + 2][y - 2] == 2 && gomoku_Banmen[x + 3][y - 3] == 2 && gomoku_Banmen[x + 4][y - 4] == 2 ||
					gomoku_Banmen[x][y] == 2 && gomoku_Banmen[x - 1][y + 1] == 2 && gomoku_Banmen[x - 2][y + 2] == 2 && gomoku_Banmen[x - 3][y + 3] == 2 && gomoku_Banmen[x - 4][y + 4] == 2) {
					gomoku_Battle = 2;
				}

			}
		}
		
	}
	return this;
}

void gomokuScene::Draw() const
{
	DrawGraph(0, 0, gomoku_BackImg, FALSE);
	DrawFormatString(10, 10,0xffffff, "%d %d", cX, cY);
	DrawGraph(180, 0, TitleImg, TRUE);
	for (int y = 0; y < 13; y++) {
		for (int x = 0; x < 13; x++) {
			DrawFormatString(50, 300, 0xffffff, "%d", bCount);
			DrawFormatString(50, 400, 0xffffff, "%d", wCount);
			if (gomoku_Banmen[x][y] == 1) {
				DrawGraph(270 + (56 * x) + x, -25 + (56 * y) + y, bTopImg, TRUE);
			}
			else if (gomoku_Banmen[x][y] == 2) {
				DrawGraph(270 + (56 * x) + x , -25 + (56 * y) + y, wTopImg, TRUE);
			}
		}
	}
	if (gomoku_Phase == 0 && gomoku_Battle == 0) {
		SetFontSize(60);
		DrawFormatString(50, 300, 0xfffffff, "���̎��");
	}
	if (gomoku_Phase == 1 && gomoku_Battle == 0) {
		SetFontSize(60);
		DrawFormatString(50, 300, 0xfffffff, "���̎��");
	}
	if (gomoku_Battle == 0) {
		DrawBox(285 + (56 * cX), -15 + (56 * cY), 345 + (56 * cX), 45 + (56 * cY), 0xffff00, FALSE);
	}
	if (gomoku_Battle == 1) {
		SetFontSize(80);
		DrawFormatString(600, 300, 0xFF00FF, ("���̏���"));
	}
	else if (gomoku_Battle == 2) {
		SetFontSize(80);
		DrawFormatString(600, 300, 0xFF00FF, ("���̏���"));
	}
	
}
// if(x % 2 == 0 && y % 2 == 0)