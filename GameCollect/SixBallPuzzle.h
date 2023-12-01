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
	
	int gNewBlock[4][4] = { 0 };		//�V�����u���b�N�p
	int gNextBlock[4][4] = { 0 };		//���̃u���b�N�p
	int gStokBlock[4][4] = { 0 };		//	�X�g�b�N�u���b�N�p
	int gStokFlg = 0;					//	�X�g�b�N�t���O

	int gBlockList[7][4][4] = {
	{ {0,0,0,0},{0,1,1,0},{0,1,1,0},{0,0,0,0} },
	{ {0,0,0,0},{0,0,0,0},{2,2,2,2},{0,0,0,0} },
	{ {0,0,0,0},{3,0,0,0},{3,3,3,0},{0,0,0,0} },
	{ {0,0,0,0},{0,0,0,4},{0,4,4,4},{0,0,0,0} },
	{ {0,0,0,0},{0,5,5,0},{0,0,5,5},{0,0,0,0} },
	{ {0,0,0,0},{0,6,6,0},{6,6,0,0},{0,0,0,0} },
	{ {0,0,0,0},{0,7,0,0},{7,7,7,0},{0,0,0,0} },
	};

public:
	void StageInit(void); // �X�e�[�W�̏�����
	void DrawStage(void); // �X�e�[�W�`��
	void CreateBlock(void); //�u���b�N������NEXT�u���b�N�̈ړ�
	void ControlBlock(void); // �u���b�N�̍��W����
	int CheckOverlap(int x2, int y2);	//�@�u���b�N�̈ړ��\�`�F�b�N����
	void TurnBlock(void);	//�u���b�N�̉�]����
	void LockBlock(int x2, int y2);	//���n�����u���b�N���Œ�ς݃u���b�N�ɉ�����
	void CheckLines(void);		//�@�u���b�N�������̎��̏���
	void ChangeBlock(void);		//�@�u���b�N�̌����i�X�g�b�N�����j

	SixBallPuzzle();

	~SixBallPuzzle();

	//�`��ȊO�̍X�V�����s
	AbstractScene* Update() override;

	//�`��Ɋւ��邱�Ƃ�����
	void Draw() const override;

};

