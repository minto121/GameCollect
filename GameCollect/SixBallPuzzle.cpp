#include "SixBallPuzzle.h"
#include "DxLib.h"
#include "PadInput.h"
#include <cstdlib>  // �����_���֐��p
#include <ctime>    // srand�̏������Ɏg�p


SixBallPuzzle::SixBallPuzzle()
{
	//�w�i�摜�Ǎ�
	Back_Ground_img = LoadGraph("../images/SixBallPuzzle/BackGroundBall_1.png");
	
	//�{�[���̕����Ǎ�
	LoadDivGraph("../images/SixBallPuzzle/ball.png", 5, 5, 1, 64, 64, Ball_img);	//�摜�̑S�̃T�C�Y�F320px*64px

	// �����������������
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

	return this;
}

void SixBallPuzzle::Draw() const{

	// �I�����������_���ȃ{�[����`��
	//DrawGraph(100, FallingY, Ball_img[randomBallIndex], TRUE);

	//�w�i�摜�̕`��
	//DrawGraph(0, 0, Back_Ground_img, FALSE);

	//�{�[���̕����`��
	DrawGraph(100, FallingY, Ball_img[1], TRUE);
}
