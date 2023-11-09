#include "SixBallPuzzle.h"
#include "DxLib.h"
#include "PadInput.h"
#include <cstdlib>  //�����_���֐��p
#include <ctime>    //srand�̏������Ɏg�p


SixBallPuzzle::SixBallPuzzle()
{
	//�w�i�摜�Ǎ�
	Back_Ground_img = LoadGraph("../images/SixBallPuzzle/BackGroundBall_1.png");
	
	//�{�[���̕����Ǎ�
	LoadDivGraph("../images/SixBallPuzzle/ball.png", 5, 5, 1, 64, 64, Ball_img);	//�摜�̑S�̃T�C�Y�F320px*64px

	// �{�[���̏����ʒu�Ƒ��x��ݒ�
	for (int i = 0; i < MaxBalls; i++)
	{
		ballX[i] = 100;  // X���W
		ballY[i] = i + 80;  // ����Y���W��80�s�N�Z�������炷
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
	if (FallingY < 600)
	{
		FallingY += 2;  //�{�[���̗������x
	}

	// y���W�������I�ɍX�V���ă{�[����`��
	for (int i = 0; i < MaxBalls; i++)
	{
		if (ballActive[i])
		{
			ballY[i] += ballSpeed[i];  // �{�[���𗎉�������

			// ��ʊO�ɏo����ė��p
			if (ballY[i] > ScreenHeight)
			{
				ballY[i] = -64;  // ��ʏ㕔����ė��p
				ballX[i] = rand() % (ScreenWidth - 64);  // �{�[����X���W�������_���ɐݒ�
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
	//DrawGraph(0, 0, Back_Ground_img, FALSE);

	//�{�[���̕����`��
	DrawGraph(100, FallingY, Ball_img[1],FALSE);

	//�{�[���̕����`��
	for (int i = 0; i < MaxBalls; i++) 
	{
		if (ballActive[i]) 
		{
			DrawGraph(ballX[i], ballY[i], Ball_img[i], TRUE);
		}
	}
}
