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
}

Checkermain::~Checkermain()
{
}


AbstractScene* Checkermain::Update()
{
	g_OldKey = g_NowKey;
	g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	g_KeyFlg = g_NowKey & ~g_OldKey;
	//��ړ�
	if (g_KeyFlg & PAD_INPUT_UP) {
		if (selectY >= 0 && selectY <= 7) {
			selectY = selectY - 1;
		}
		if (selectY < 0) {
			selectY = 7;
		}
	}
	//���ړ�
	if (g_KeyFlg & PAD_INPUT_DOWN) {
		if (selectY >=0  && selectY < 8) {
			selectY = selectY + 1;
		}
		if (selectY > 7 ) {
			selectY = 0;
		}
	}
	//�E�ړ�
	if (g_KeyFlg & PAD_INPUT_LEFT) {
		if (selectX >= 0 && selectX <= 7) {
			selectX = selectX - 1;
		}
		if (selectX < 0) {
			selectX = 7;
		}
	}
	//���ړ�
	if (g_KeyFlg & PAD_INPUT_RIGHT) {
		if (selectX >= 0 && selectX < 8) {
			selectX = selectX + 1;
		}
		if (selectX > 7) {
			selectX = 0;
		}
	}
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			if (g_KeyFlg & PAD_INPUT_1) {

				if (phase == 0 && board[x][y] == 1) {
					F_select = TRUE;

				}
			}
			if (F_select == TRUE && board[x-1][y-1]) {
				board[x - 1][y - 1] = 1;
				board[x][y] = 0;
			}
			if (F_select == TRUE && board[x - 1][y - 1]) {
				board[x + 1][y + 1] = 1;
				board[x][y] = 0;
			}
		}
		int padx, pady;
		// �J�[�\���̈ʒu����N���b�N���ꂽ�Z�������
		int clickedX = selectX;
		int clickedY = selectY;
		
		// �v���C���[���I��������̍��W�� (selectedX, selectedY) �ɂ���܂�
        // �����ňړ��̑Ó������`�F�b�N���A��̈ړ����������܂�
		//IsMoveValid(selectX,  selectY,  clickedX,  clickedY);
	
	}


	return this;
}

void Checkermain::Draw() const
{
	
	DrawGraph(0, 0, Checkerback, FALSE);	// �w�i
	DrawGraph(300, 0, Boardimg, TRUE);		// �{�[�h
	 //�v���C���[1�̋��`��
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			if(board[x][y]==2)
			DrawRotaGraph(x * 74 + 400, y * 72 + 108, 2, 0, PieceB, TRUE);
		}
	}
	// �v���C���[2�̋��`��
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			if (board[x][y] == 1)
				DrawCircle(x * 74 + 400, y * 72 + 105, 28, GetColor(255, 0, 0), TRUE);
		}
	}

	//for (int y = 0; y < 3; y++) {
	//	for (int x = (y % 2 == 0) ? 1 : 0; x < 8; x += 2) {
	//		DrawCircle(x * 73 + 400, y * 75 + 100, 28, GetColor(255, 0, 0), TRUE);
	//		/*DrawRotaGraph(x * 75 + 400, y * 80 + 110, 2, 0, PieceW, TRUE);*/
	//	}
	//}
	DrawBox(372 + (selectX * 71), 72 + (selectY * 71), 445 + (selectX * 71), 145 + (selectY * 71), GetColor(0, 250, 0), FALSE);    // �l�p�`��`��

	DrawFormatString(0, 0, 0x000000, "%d", selectY);		//�J�[�\���ړ�Y
	DrawFormatString(0,30, 0x000000, "%d", selectX);		//�J�[�\���ړ�X
	DrawFormatString(0, 100, 0x000000, "%d", F_select);


	
}

void Checkermain::InitBoard()
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			(board[i][j] == 0);

		}
	}
}
bool Checkermain::IsMoveValid(int startX, int startY, int endX, int endY)
{
	// �ړ��̑Ó������`�F�b�N���郍�W�b�N�������ɒǉ�
	// ��щz���郋�[���Ȃǂ������\

	if (endX < 0 || endY < 0 || endX >= 8 || endY >= 8) {
		return false; // �{�[�h�O�ւ̈ړ��͖���
	}

	if (board[endY][endX] != 0) {
		return false; // �ړ���ɋ����ꍇ�͖���
	}

	// 1�O�㍶�E�Ɉړ�����ꍇ
	if (abs(endX - startX) == 1 && abs(endY - startY) == 1) {
		return true;
	}

	// ��̈ړ����[���ɍ��v���Ȃ��ꍇ�������Ń`�F�b�N
	// ���̃J�X�^�����[������������ȂǁA���̏����ɂ��]�����Ƃ��ł��܂�

	return false; // �f�t�H���g�ł͖����Ȉړ��Ƃ��Ĉ���
}



