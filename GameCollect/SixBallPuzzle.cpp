#include "SixBallPuzzle.h"
#include "DxLib.h"
#include <math.h>
#include "PadInput.h"
#include <cstdlib>  //�����_���֐��p
#include <ctime>    //srand�̏������Ɏg�p


SixBallPuzzle::SixBallPuzzle()
{
	//FPS�̌v���ƕ\�����s�����[�J���ϐ��̐錾
	LONGLONG nowTime = GetNowHiPerformanceCount();
	LONGLONG oldTime = nowTime;
	double deltaTime = 0;

	/*********************************�摜�̓Ǎ�****************************************************/
	
	//�{�[���̕����Ǎ�
	LoadDivGraph("../images/SixBallPuzzle/ball.png", 5, 5, 1, 64, 64, Ball_img);	//�摜�̑S�̃T�C�Y�F320px*64px

	//�w�i�摜�Ǎ�
	Back_Ground = LoadGraph("../images/SixBallPuzzle/square.png");

	oldTime = nowTime;
	nowTime = GetNowHiPerformanceCount();

	//�{�[��������NEXT�{�[���̈ړ�
	CreateBlock();

	// New�{�[���̍��W������
	gPosX = NEWBLOCK_X;
	gPosY = NEWBLOCK_Y;

	// �u���b�N�̈ړ�����
	ControlBoll();

	//��������
	nowTime = GetNowCount();

	if (nowTime >= (gStartTime )) {
		if (CheckOverlap(gPosX, gPosY + 1) == 0) {
			gPosY++;
		}
		else {
			//�@�u���b�N�̌Œ�
			LockBlock(gPosX, gPosY);

			//�@�u���b�N�����ƃu���b�N�����낷����
			CheckLines();

			//�@�V�����u���b�N�̍쐬
			CreateBlock();
		}

		//�X�e�[�W�̏������i�ǐݒ�ƃN���A�j
		for (int i = 0; i < HEIGHT; i++) {
			for (int j = 0; j < WIDTH; j++) {
				if (j == 0 || j == WIDTH - 1 || i == HEIGHT - 1) {
					gStage[i][j] = 9; //��
				}
				else {
					gStage[i][j] = 0; //������ �@�m�F(GetRand(9))
				}
			}
		}
	}

	// �{�[���̏����ʒu�Ƒ��x��ݒ�
	for (int i = 0; i < MaxBalls; i++)
	{
		Random = GetRand(9);			//�����_���̎擾
		ballX[i] = 32 + Random * 64;	// X���W
		ballY[i] = -64 * i;				// �{�[����Y���W�������_���ɐݒ�
		ballSpeed[i] = 2;				// �������x
		ballActive[i] = true;			// �{�[�����A�N�e�B�u���ǂ���
	}

	SRand(GetNowCount());

	//�����������������
	//srand(static_cast<unsigned int>(time(0)));
}

SixBallPuzzle::~SixBallPuzzle()
{

}

void SixBallPuzzle::CreateBlock(void)
{
	//�����_���Ƀu���b�N�I��
	int r = GetRand(3);

	//�V�����u���b�N���Z�b�g�����̃u���b�N�𐶐�
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			gNewBlock[i][j] = gNextBlock[i][j];
			gNextBlock[i][j] = gBlockList[r][i][j];
		}
	}

	//�@�V�����u���b�N�̏o���ʒu���Z�b�g
	gPosX = NEWBLOCK_X;		// New�u���b�N��X���W
	gPosY = NEWBLOCK_Y;		// New�u���b�N��Y���W

	//�@�Q�[���I�[�o�[�̔���
	if (CheckOverlap(gPosX, gPosY) != 0) {
		//gGameMode = GAMEOVER;
	}
}

void SixBallPuzzle::ControlBoll(void)
{
	//�\���L�[����������u���b�N�̌������s��
	// ���L�[�������Ă�����{�[���N�����Ɉړ�������
	if (CheckHitKey(KEY_INPUT_DOWN) == 1) BallY += 3;
}

int SixBallPuzzle::CheckOverlap(int x2, int y2)
{
	//�ڐG�̊m�F
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (gNewBlock[i][j] != 0) {
				if (gStage[y2 + i][x2 + j] != 0) {
					return 1;
				}
			}
		}
	}

	return 0;
}

void SixBallPuzzle::TurnBlock(void)
{
	//��Ɨp
	int temp[4][4] = { 0 };

	//�u���b�N�␳
	do {

		//�u���b�N����]���Ĉꎞ�ۑ�
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				temp[j][3 - i] = gNewBlock[i][j];
			}
		}

		//��]��̃f�[�^��]�L
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				gNewBlock[i][j] = temp[i][j];
			}
		}
		if (CheckOverlap(gPosX, gPosY) == 1 && gPosX >= 9) gPosX--;
		if (CheckOverlap(gPosX, gPosY) == 1 && gPosX <= 0) gPosX++;

	} while (CheckOverlap(gPosX, gPosY) == 1);
}

void SixBallPuzzle::LockBlock(int x2, int y2)
{
	 //�u���b�N���Œ肷��
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (gNewBlock[i][j] != 0) {
				gStage[y2 + i][x2 + j] = gNewBlock[i][j];
			}
		}
	}
}

void SixBallPuzzle::CheckLines(void)
{
	int flg;
	int lineCut = 0;

	// �u���b�N������񂾂������� flg �� 0
	for (int i = 0; i < HEIGHT - 1; i++) {
		flg = 0;
		for (int j = 1; j <= WIDTH - 1; j++) {
			if (gStage[i][j] == 0) {
				flg = 1;
				break;
			}
		}

		// flg��0�Ȃ�X�R�A���Z
		if (flg == 0) {
			//�@�܂Ƃ߂ď������郉�C�����̃J�E���g
			lineCut++;

			//�Œ�ς݃u���b�N�����낷
			for (int k = i; k > 0; k--) {
				for (int j = 1; j <= WIDTH - 1; j++) {
					gStage[k][j] = gStage[k - 1][j];
				}
			}
			//gScore += 1000;
		}
	}
}

//void SixBallPuzzle::ChangeBlock(void)
//{
//	// ��Ɨp
//	int temp[4][4] = { 0 };
//
//	//�X�g�b�N�Ȃ��Ȃ���s
//	if (gStokFlg == 0) {
//		gStokFlg = 1;
//		//�@�V�����u���b�N���X�g�b�N�ɕۊ�
//		for (int i = 0; i < 4; i++) {
//			for (int j = 0; j < 4; j++) {
//				gStokBlock[i][j] = gNewBlock[i][j];
//			}
//		}
//		//�@�V�����u���b�N�̃Z�b�g
//		CreateBlock();
//	}
//	else {
//		//�@�X�g�b�N����Ȃ�X�g�b�N�ƌ���
//		for (int i = 0; i < 4; i++) {
//			for (int j = 0; j < 4; j++) {
//				temp[i][j] = gNewBlock[i][j];
//				gNewBlock[i][j] = gStokBlock[i][j];
//				gStokBlock[i][j] = temp[i][j];
//			}
//		}
//	}
//}

AbstractScene* SixBallPuzzle::Update()
{
	// �����_���ȃ{�[���̃C���f�b�N�X�𐶐�
	//randomBallIndex = rand() % 5;  // 0����4�͈̔͂Ń����_���Ƀ{�[����I��

	// y���W�������I�ɍX�V���ĉ摜��`��
	// �摜�̍��W����ʓ��ɐ�������i��ʉ��[�Ń��Z�b�g����j

	// y���W�������I�ɍX�V���ă{�[����`��
	for (int i = 0; i < MaxBalls; i++)
	{
		// ��ʊO�ɏo����ė��p
		if (ballY[i] > HEIGHT)
		{
			ballY[i] = -64;			// ��ʏ㕔���痘�p
			ballX[i] = WIDTH - 64;  // �{�[����X���W�������_���ɐݒ�
			ballSpeed[i] = 1;		// �������x
			ballActive[i] = true;	// �{�[�����A�N�e�B�u���ǂ���
		}
	}

	// y���W�������I�ɍX�V���ă{�[����`��
	for (int i = 0; i < MaxBalls; i++)
	{
		if (ballActive[i])
		{
			ballY[i] += ballSpeed[i];  // �{�[���𗎉�������

			// ��ʉ����Őςݏグ
			if (ballY[i] > HEIGHT - 64)
			{
				ballY[i] = HEIGHT - 64;  // ��ʉ����Œ�~
				ballSpeed[i] = 0;  // �������x���~

				for (int j = 0; j < MaxBalls; j++)
				{
					// ���݂̃{�[�������̃{�[���Əd�Ȃ�Ȃ��悤�ɂ���
					if (i != j && ballActive[j] || ballY[j] < ballY[i] + 64 && ballY[j] + 64 > ballY[i])
					{
						ballY[i] = ballY[j];  // �ςݏグ��ʒu�𒲐�
						break;
					}
				}
			}
		}
	}

	return this;
}

void SixBallPuzzle::Draw() const
{
	//�I�����������_���ȃ{�[����`��
	//DrawGraph(100, FallingY, Ball_img[randomBallIndex], TRUE);

	//�w�i�摜�̕`��
	DrawGraph(10, 10, Back_Ground, FALSE);

	//�{�[���̕����`��
	for (int i = 0; i < MaxBalls; i++)
	{
		if (ballActive[i])
		{
			DrawGraph(ballX[i], ballY[i], Ball_img[0], TRUE);
		}
	}

	//�@���[�J���ϐ�
	//int posX, tempScore;

	//�X�e�[�W�̒l�Ńu���b�N��\��
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (gStage[i][j] != 9) {
				DrawGraph(BLOCKSIZE * j, BLOCKSIZE * i, gBlockImg[gStage[i][j]], TRUE);
			}
		}
	}

	//// New�u���b�N��`��
	//for (int i = 0; i < 4; i++) {
	//	for (int j = 0; j < 4; j++) {
	//		if (gNewBlock[i][j] != 0) {
	//			DrawGraph(BLOCKSIZE * (j + gPosX), BLOCKSIZE * (i + gPosY), gBlockImg[gNewBlock[i][j]], TRUE);
	//		}
	//	}
	//}

	// Next�u���b�N�ƃX�g�b�N�u���b�N��`��
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			//DrawGraph(BLOCKSIZE * j + 480, BLOCKSIZE * i + 350, gBlockImg[gNextBlock[i][j]], TRUE);
			DrawGraph(BLOCKSIZE * j + 360, BLOCKSIZE * i + 240, gBlockImg[gStokBlock[i][j]], TRUE);
		}
	}

	//	���x���\��
	//DrawGraph(400, 140, gNumberImg[gLevel], TRUE);
}


