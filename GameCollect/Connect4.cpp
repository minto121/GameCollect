#include "Connect4.h"
#include"PadInput.h"

#define POINTX 132.5
int Turn = 1;		//���

Connect4::Connect4()
{
	if ((gStageImg = LoadGraph("images/SixBallPazzle/Board2.png")) == -1);				//�X�e�[�W�摜�Ǎ�
	if ((gCursorImg = LoadGraph("images/SixBallPazzle/Arrow.png")) == -1);				//���摜�Ǎ�
	if ((gRedCoinImg = LoadGraph("images/SixBallPazzle/RedCoin.png")) == -1);			//�{�[���̕����摜�Ǎ�
	if ((gYellowCoinImg = LoadGraph("images/SixBallPazzle/YellowCoin.png")) == -1);		//�{�[���̕����摜�Ǎ�
}

Connect4::~Connect4()
{

}

AbstractScene* Connect4::Update()
{
	/****** �J�[�\���̈ړ����� *******/
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT)) {
		if (++Num > 7) Num = 1;	//�E��
	}

	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT)) {
		if (--Num < 1) Num = 7;	//����
	}

	Cursor = Num  * POINTX + 20;	//�J�[�\����X���W�𑝂₷

	/******** �{�^���ŐԐF�����F�ɐ؂�ւ��� *******/
	
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_B)) {

		switch (Turn)
		{
		case 1:
			printfDx("���F���� \n");
			for (int y = 5; y >= 0; y--) {	//���̏c�̗�ɉ��F��`�悳����
				if (Stage[Num - 1][y] == 0) {	//Num�͉��̍s�����Ă�
					Stage[Num - 1][y] = 1;
					//printfDx("%d", y);
					Check(y);
					CheckWidth(y,x,cnt,col);
					break;
				}
			}
			Turn = 2;
			break;
		case 2:
			printfDx("�ԐF���� \n");
				for (int y = 5; y >= 0; y--) {	//���̏c�̗�ɉ��F��`�悳����
					if (Stage[Num - 1][y] == 0) {	//Num�͉��̍s�����Ă�
						//printfDx("%d \n");
						Stage[Num - 1][y] = 2;
						Check(y);
						CheckWidth(y,x,cnt,col);
						break;
					}
				}
				Turn = 1;
				break;
		}
	}
	return this;
}

void Connect4::Draw() const
{
	DrawGraph(0, 0, gStageImg, TRUE);		//�X�e�[�W�摜
	DrawGraph(Cursor, 0, gCursorImg, TRUE);	//�J�[�\���摜
	DrawFormatString(0, 100, 0xf0f0f0, "%d", Cursor);	//�J�[�\���̒l
	
	//�{�[���̕`��
	for (int x = 6; x >= 0; x--) {
		for (int y = 5; y >= 0; y--) {
			if (Stage[x][y] == 1) {
				DrawGraph((x * POINTX) + POINTX, y * 100 + 65, gYellowCoinImg, TRUE);
			}
			if (Stage[x][y] == 2) {
				DrawGraph((x * POINTX) + POINTX, y * 100 + 65, gRedCoinImg, TRUE);
			}
		}
	}
}

void Connect4::Check(int y)
{
	int Height = y;	//y�̓Y���������������ė���
	
	//�c�̃`�F�b�N
	if ((Stage[Num - 1][Height] == Stage[Num - 1][Height + 1]) &&
		(Stage[Num - 1][Height] == Stage[Num - 1][Height + 2]) &&
		(Stage[Num - 1][Height] == Stage[Num - 1][Height + 3]))
	{
		printfDx("�N���A!! \n");
	}

}

void Connect4::CheckWidth(int y,int x,int cnt,int col)
{
	int Width = Num - 1;
	int c;
	/*int col;
	int cnt = 0;*/

	//���̃`�F�b�N
	//if (Stage[7][6] == 0)return 0;

	if (cnt >= 4) {

		Stage[Num][Width];
		col = Stage[Num][Width];
		c = Stage[Num][Width];
		(cnt)++;

		if (Stage[Num][Width + 1] == c)Check( Width - 1);

		printf("000");

	}
}


	
