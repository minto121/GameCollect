#pragma once
#include "AbstractScene.h"

const int MaxBalls = 50;

class SixBallPuzzle:
	public AbstractScene
{

private:
	int ScreenHeight = 720;
	int ScreenWidth = 1280;

	/*�摜�p�ϐ�*/
	int Ball_img[4];		//�{�[��
	int Back_Ground;		//�w�i�摜

	//int FallingX = 360;			//��������u���b�N��X���W�i�Œ�ʒu�j
	//int FallingY = 100;		//��������u���b�N��Y���W�i�����ʒu�j
	//int randomBallIndex;
	
	float ballX[MaxBalls];     // X���W�̔z��
	float ballY[MaxBalls];     // Y���W�̔z��
	float ballSpeed[MaxBalls]; // �������x�̔z��
	bool ballActive[MaxBalls];  // �{�[�����A�N�e�B�u���ǂ����̔z��
	

public:
	SixBallPuzzle();

	~SixBallPuzzle();

	//�`��ȊO�̍X�V�����s
	AbstractScene* Update() override;

	//�`��Ɋւ��邱�Ƃ�����
	void Draw() const override;

};

