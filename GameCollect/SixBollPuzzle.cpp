#include "SixBollPuzzle.h"
#include "DxLib.h"
#include "PadInput.h"

SixBollPuzzle::SixBollPuzzle()
{
	//�w�i�摜�Ǎ�
	Back_Ground_img = LoadGraph("../images/SixBallPuzzle/BackGround01.png");
	
	//Ball_img = LoadGraph("../images/SixBallPuzzle/ball.png");

	//�{�[���̕����Ǎ�
	LoadDivGraph("../images/SixBallPuzzle/ball.png", 5, 5, 1, 64, 64, Ball_img);	//�摜�̑S�̃T�C�Y�F320px*64px

}

SixBollPuzzle::~SixBollPuzzle()
{

}

AbstractScene* SixBollPuzzle::Update()
{
	//���������摜�������_���œǂލ���
	/*for (int i = 0; i < 3; i++) {
		Ball_img[i] = LoadGraph(imagePaths[i]);
	}*/

	// y���W�������I�ɍX�V���ĉ摜��`��
	// �摜�̍��W����ʓ��ɐ�������i��ʉ��[�Ń��Z�b�g����j
	if (FallingY < 600)
	{
		FallingY += 2;  //�{�[���̗������x
	}

	return this;
}

void SixBollPuzzle::Draw() const{

	//�w�i�摜�̕`��
	DrawGraph(0, 0, Back_Ground_img, FALSE);

	//�{�[���̕����`��
	DrawGraph(100, FallingY, Ball_img[1], TRUE);
	DrawGraph(136, FallingY, Ball_img[2], TRUE);
	DrawGraph(118, FallingY - 36, Ball_img[3], TRUE);
}
