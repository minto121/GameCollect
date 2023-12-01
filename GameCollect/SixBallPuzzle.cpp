#include "SixBallPuzzle.h"
#include "DxLib.h"
#include "PadInput.h"
#include <cstdlib>  //�����_���֐��p
#include <ctime>    //srand�̏������Ɏg�p


SixBallPuzzle::SixBallPuzzle()
{
	//�w�i�摜�Ǎ�
	Back_Ground = LoadGraph("../images/SixBallPuzzle/square.png");
	
	//�{�[���̕����Ǎ�
	LoadDivGraph("../images/SixBallPuzzle/ball.png", 5, 5, 1, 64, 64, Ball_img);	//�摜�̑S�̃T�C�Y�F320px*64px

	// �{�[���̏����ʒu�Ƒ��x��ݒ�
	for (int i = 0; i < MaxBalls; i++)
	{
		ballX[i] = rand() % (ScreenWidth - 64);  // X���W
		ballY[i] = - 64 * i;  // �{�[����Y���W�������_���ɐݒ�
		ballSpeed[i] = 2;  // �������x
		ballActive[i] = true;  // �{�[�����A�N�e�B�u���ǂ���
	}
	//�����������������
	//srand(static_cast<unsigned int>(time(0)));
}

SixBallPuzzle::~SixBallPuzzle()
{

}

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
		if (ballY[i] > ScreenHeight)
		{
			ballY[i] = -64;  // ��ʏ㕔����ė��p
			ballX[i] = rand() % (ScreenWidth - 64);  // �{�[����X���W�������_���ɐݒ�
			ballSpeed[i] = 1;  // �������x
			ballActive[i] = true;  // �{�[�����A�N�e�B�u���ǂ���
		}
	}
	// y���W�������I�ɍX�V���ă{�[����`��
	for (int i = 0; i < MaxBalls; i++)
	{
		if (ballActive[i])
		{
			ballY[i] += ballSpeed[i];  // �{�[���𗎉�������

			// ��ʉ����Őςݏグ
			if (ballY[i] > ScreenHeight - 64)
			{
				ballY[i] = ScreenHeight - 64;  // ��ʉ����Œ�~
				ballSpeed[i] = 0;  // �������x���~

				for (int j = 0; j < MaxBalls; j++)
				{
					// ���݂̃{�[�������̃{�[���Əd�Ȃ�Ȃ��悤�ɂ���
					if (i != j && ballActive[j] && ballY[j] < ballY[i] + 64 && ballY[j] + 64 > ballY[i])
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

	//�{�[���̕����`��
	//DrawGraph(100, FallingY, Ball_img[1],FALSE);

	//�w�i�摜�̕`��
	//DrawGraph(10, 10, Back_Ground, TRUE);

	//�{�[���̕����`��
	for (int i = 0; i < MaxBalls; i++)
	{
		if (ballActive[i])
		{
			DrawGraph(ballX[i], ballY[i], Ball_img[i], TRUE);
		}
	}
}

void SixBallPuzzle::StageInit(void)
{
}
