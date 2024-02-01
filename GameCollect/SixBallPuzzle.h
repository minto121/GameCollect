//#pragma once
//#include "AbstractScene.h"
//#include <math.h>
//#include <stdio.h>
//#include <stdlib.h>
//
//const int MaxBalls = 1;
//const int HEIGHT = 720;
//const int WIDTH = 1280;
//
//
//class SixBallPuzzle:public AbstractScene{
//
//private:
//	/*�萔�̐錾*/
//	const int BLOCKSIZE = 24;	// �u���b�N�摜�̃T�C�Y
//	const int NEWBLOCK_X = 4;	// New�u���b�NX���W
//	const int NEWBLOCK_Y = 0;	// New�u���b�NY���W
//
//	/*�摜�p�ϐ�*/
//	int Ball_img[4];		//�{�[��
//	int Back_Ground;		//�w�i�摜
//
//	//int FallingX = 360;			//��������u���b�N��X���W�i�Œ�ʒu�j
//	//int FallingY = 100;			//��������u���b�N��Y���W�i�����ʒu�j
//	//int randomBallIndex;
//	
//	int g01dKey;			// �O��̓��̓L�[
//	int gNowKey;			// ����̓��̓L�[
//	int gKeyFlg;			// ���̓L�[���
//
//	int Random = 0;						//�����̎擾
//	int gStage[HEIGHT][WIDTH];						//�X�e�[�W�z��
//	int gBlockImg[10];								//�u���b�N�摜
//	int gLevel;										//	���x���A�b�v�ϐ�
//	int gSpeed[6] = { 1000,800,600,500,300,150 };	//	�����X�s�[�h�z��
//
//	int BallY;
//
//	float ballX[MaxBalls];     // X���W�̔z��
//	float ballY[MaxBalls];     // Y���W�̔z��
//	float ballSpeed[MaxBalls]; // �������x�̔z��
//	bool ballActive[MaxBalls]; // �{�[�����A�N�e�B�u���ǂ����̔z��
//	
//	int gNewBlock[4][4] = { 0 };				//�V�����u���b�N�p
//	int gNextBlock[4][4] = { 0 };				//���̃u���b�N�p
//	int gStokBlock[4][4] = { 0 };				//�X�g�b�N�u���b�N�p
//	int gStokFlg = 0;							//�X�g�b�N�t���O
//
//	int gBlockList[3][5][3] = {
//	{ {0,0,0},{0,1,1},{0,1,1},{0,0,0} },
//	{ {0,0,0},{0,0,0},{2,2,2},{0,0,0} },
//	{ {0,0,0},{3,0,0},{3,3,3},{0,0,0} },
//	};
//
//	int gPosX = NEWBLOCK_X;	//�@New�u���b�N��X���W
//	int gPosY = NEWBLOCK_Y;	//�@New�u���b�N��Y���W
//
//	int gStartTime;			//�@���Ԍv���̊J�n����
//
//public:
//	void CreateBlock(void);				//�u���b�N������NEXT�u���b�N�̈ړ�
//	void ControlBoll(void);			// �u���b�N�̍��W����
//	int CheckOverlap(int x2, int y2);	//�@�u���b�N�̈ړ��\�`�F�b�N����
//	void TurnBlock(void);				// �u���b�N�̉�]����
//	void LockBlock(int x2, int y2);		// ���n�����u���b�N���Œ�ς݃u���b�N�ɉ�����
//	void CheckLines(void);				//�@�u���b�N�������̎��̏���
//	void ChangeBlock(void);				//�@�u���b�N�̌����i�X�g�b�N�����j
//
//
//	SixBallPuzzle();
//
//	~SixBallPuzzle();
//
//	//�`��ȊO�̍X�V�����s
//	AbstractScene* Update() override;
//
//	//�`��Ɋւ��邱�Ƃ�����
//	void Draw() const override;
//
//};
//
