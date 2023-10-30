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
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			(board[i][j] == 0);

		}
	}
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
	return this;
}

void Checkermain::Draw() const
{
	
	DrawGraph(0, 0, Checkerback, FALSE);	// �w�i
	DrawGraph(300, 0, Boardimg, TRUE);		// �{�[�h
	// �v���C���[1�̋��`��
	for (int y = 5; y < 8; y++) {
		for (int x = (y % 2 == 0) ? 1 : 0; x < 8; x += 2) {
			/*DrawCircle(x * 75 + 400, y * 73 + 100, 20, GetColor(0, 0, 255), TRUE);*/
			DrawRotaGraph(x * 74 + 400, y * 72 + 108, 2, 0, PieceB, TRUE);
		}
	}

	// �v���C���[2�̋��`��
	for (int y = 0; y < 3; y++) {
		for (int x = (y % 2 == 0) ? 1 : 0; x < 8; x += 2) {
			DrawCircle(x * 73 + 400, y * 75 + 100, 28, GetColor(255, 0, 0), TRUE);
			/*DrawRotaGraph(x * 75 + 400, y * 80 + 110, 2, 0, PieceW, TRUE);*/
		}
	}
	if (selectedPieceX != -1 && selectedPieceY != -1) {
		DrawBox(selectedPieceX * 50, selectedPieceY * 50, (selectedPieceX + 1) * 50, (selectedPieceY + 1) * 50, GetColor(255, 255, 0), TRUE);
	}

	DrawFormatString(0, 0, 0x000000, "%d", selectY);		//�J�[�\���ړ�Y
	DrawFormatString(0,30, 0x000000, "%d", selectX);		//�J�[�\���ړ�X
	DrawBox(372 + (selectX*71), 72 + (selectY * 71), 445+ (selectX * 71), 145 + (selectY * 71), GetColor(0, 250, 0), FALSE);    // �l�p�`��`��

	
}



