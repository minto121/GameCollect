#pragma once
#include "AbstractScene.h"
#include <DxLib.h>
class Mankara :public AbstractScene
{
private:
	int Board; // �Q�[���{�[�h�̉摜
	int Background; // �w�i�摜

	int PocketEnter;// 0�F���I���@�P�F�I�������@�Q�F����̃^�[��
	int MyTurn; // �����̃^�[�����ǂ���
	struct STONE
	{
		int img;
	} ;
	// �΂̐��ƃ|�P�b�g
	struct STONE gStone[16][6];

	struct STONE2
	{
		int img;
	} ;
	// �΂̐��ƃ|�P�b�g
	struct STONE2 gStone2[16][6];

	struct GOAL
	{
		int img;
	} ;
	// �΂̐F�ƌ�
	struct GOAL gGoal[30][2];

	// ���s�p�t���O
	int ResultFlg1;
	int ResultFlg2;
	// ���s���o��
	int ResultDraw1;
	int ResultDraw2;
	// �^�[���؂�ւ��p�t���O
	int InputFlg;

	// 1P���I�����Ă���|�P�b�g
	int PlayerPocket;
	// 2P���I�����Ă���|�P�b�g
	int PartnerPocket;

	// 1P�p�|�P�b�g
	int P1Pocket[6];

	// 2P�p�|�P�b�g
	int P2Pocket[6];
	
	//1P�̃S�[��
	int P1BigPocket; 
	//2P�̃S�[��
	int P2BigPocket;

	//�Q�[�����̓����΂̑���
	int FullStone;

	// �΂̉摜
	int StoneImg[6]; 

	int Pocket_cnt;

	// ������
	int InitialStone;
	int Stone_count;
	int StonePocket[12]; // �Γ���Ă�|�P�b�g
	
	// �|�P�b�g�̐��Ɗi�[����Ă���΂̐�
	int P1StoneSave[6]; 
	// �|�P�b�g�̐��Ɠ����Ă���΂̐�
	int P2StoneSave[6]; 


	int tmp;
	int tmp2;

public:
	Mankara();
	AbstractScene* Update();
	void Draw() const;
	// �΂��ړ��������̓�������
	void MoveStone();
};