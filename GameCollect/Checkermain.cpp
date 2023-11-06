#include "Checkermain.h"
#include "DxLib.h"
#include "PadInput.h"

Checkermain::Checkermain() {

	Boardimg = LoadGraph("../images/Checkers/banmen.png");		 // �{�[�h
	PieceB = LoadGraph("../images/Checkers/WK.png");			 // �
	PieceW = LoadGraph("../images/Checkers/BK.png");			 // �
	Checkerback = LoadGraph("../images/Checkers/back.png");		 // �w�i
	selectX = 0;												 // �J�[�\���ړ�X���W
	selectY = 0;												 // �J�[�\���ړ�Y���W
	phase = 0;
}

Checkermain::~Checkermain()
{
}


AbstractScene* Checkermain::Update()
{
	g_OldKey = g_NowKey;
	g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	g_KeyFlg = g_NowKey & ~g_OldKey;

	// �J�[�\���𓮂�������
	if (phase == 0) {
		if (g_KeyFlg & PAD_INPUT_RIGHT && selectX < 8) {
			selectX += 1;
		}
		if (g_KeyFlg & PAD_INPUT_LEFT && selectX > 0) {
			selectX -= 1;
		}
		if (g_KeyFlg & PAD_INPUT_DOWN && selectY < 8) {
			selectY += 1;
		}
		if (g_KeyFlg & PAD_INPUT_UP && selectY > 0) {
			selectY -= 1;
		}
	}

	// ��̈ړ�
	 // ��̈ړ�
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			if (g_KeyFlg & PAD_INPUT_1) {
				if (board[x][y] == 1 && phase == 0) {
				/*	int StartX = x;
					int StartY = y;
					int SelectX = selectX;
					int SelectY = selectY;*/
					//if (IsMoveValid(StartX, StartY, SelectX, SelectY)) {
						board[selectX][selectY] = 0;  // ������ = ���g���Ēl��������
						F_select = TRUE;
					//}
				}
				/*else if (board[x][y] == 0 && F_select) {
					if (IsPlaceValid(x, y)) {
						board[x][y] = 1;
						F_select = FALSE;
					}
				}*/
			}
			
		}
	}

	/*for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			if (g_KeyFlg & PAD_INPUT_1 && board[selectX][selectY] == 1) {
				if (phase==0) {
					board[selectX][selectY] == 0;
					F_select = TRUE;
				}
			}
			if (g_KeyFlg & PAD_INPUT_1&& board[selectX][selectY] == 0) {
				if (F_select == TRUE) {
					board[selectX][selectY] = 1;
					
					F_select = FALSE;
				}
			}
		}
	}*/

	


	return this;
}

void Checkermain::Draw() const
{
	DrawGraph(0, 0, Checkerback, FALSE);    // �w�i
	DrawGraph(300, 0, Boardimg, TRUE);      // �{�[�h

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

	// �J�[�\���̈ʒu�Ɏl�p�`��`��
	DrawBox(372 + (selectX * 71), 72 + (selectY * 71), 445 + (selectX * 71), 145 + (selectY * 71), GetColor(0, 250, 0), FALSE);

	DrawFormatString(0, 0, 0x000000, "Y: %d", selectY); // �J�[�\���ړ�Y
	DrawFormatString(0, 30, 0x000000, "X: %d", selectX); // �J�[�\���ړ�X
	DrawFormatString(0, 100, 0x000000, "F_select: %d", F_select);
}

void Checkermain::InitBoard()
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			(board[i][j] = 0);

		}
	}
}
bool Checkermain::IsMoveValid(int startX, int startY, int SelectX, int SelectY)
{
	// �ړ��悪�{�[�h�͈̔͊O�ł���ꍇ�A����
	if (SelectX < 0 || SelectY < 0 || SelectX >= 8 || SelectY >= 8) {
		return false;
	}

	// �ړ���ɂ��łɋ����ꍇ�A����
	if (board[SelectY][SelectX] != 0) {
		return false;
	}

	// �ړ��悪�אڂ��Ă���ꍇ�i�ʏ�̈ړ��j
	if (abs(SelectX - startX) == 1 && abs(SelectY - startY) == 1) {
		return true;
	}

	// �ړ��悪�΂߂�2��щz����ꍇ�i�W�����v�j
	if (abs(SelectX - startX) == 2 && abs(SelectY - startY) == 2) {
		int jumpedX = (SelectX + startX) / 2;
		int jumpedY = (SelectY + startY) / 2;

		// ��щz�����ʒu�ɑ���̋���邩�m�F
		if (board[jumpedY][jumpedX] == 1) {
			return true;
		}
	}

	return false; // ��L�̏����ɊY�����Ȃ��ꍇ�A�����Ȉړ�
}
bool Checkermain::IsPlaceValid(int i, int j)
{
	// �ړ��悪�{�[�h�͈̔͊O�ł���ꍇ�A����
	if (i < 0 || j < 0 || i >= 8 || j >= 8) {
		return false;
	}

	// �ړ���ɂ��łɋ����ꍇ�A����
	if (board[j][i] != 0) {
		return false;
	}

	return true; // ��L�̏����ɊY�����Ȃ��ꍇ�A�L���Ȉʒu
	
}




