#pragma once
#include "AbstractScene.h"

const int MaxBalls = 10;

class SixBallPuzzle:
	public AbstractScene
{

private:
	int Ball_img[4];		//�{�[��
	int Back_Ground_img;	//�w�i�摜
	int FallingX;			//��������u���b�N��X���W�i�Œ�ʒu�j
	int FallingY = 100;		//��������u���b�N��Y���W�i�����ʒu�j
	int randomBallIndex;
	
	float ballX[MaxBalls];     // X���W�̔z��
	float ballY[MaxBalls];     // Y���W�̔z��
	float ballSpeed[MaxBalls]; // �������x�̔z��
	bool ballActive[MaxBalls];  // �{�[�����A�N�e�B�u���ǂ����̔z��
	int ScreenHeight;
	int ScreenWidth;

public:
	SixBallPuzzle();

	~SixBallPuzzle();

	//�`��ȊO�̍X�V�����s
	AbstractScene* Update() override;

	//�`��Ɋւ��邱�Ƃ�����
	void Draw() const override;

};

