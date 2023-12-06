#pragma once
#include "AbstractScene.h"
#include <DxLib.h>
class Mankara :public AbstractScene
{
private:
	int Board; // �Q�[���{�[�h�̉摜
	int Background; // �w�i�摜

	//int P1PocketImg;
	//int P2PocketImg;

	int P1Turn;
	int P2Turn;

	struct STONE
	{
		int img;
	} ;
	// �F�ƌ�
	struct STONE gStone[6][16];

	struct STONE2
	{
		int img;
	} ;
	// �΂̐F�ƌ�
	struct STONE2 gStone2[6][16];


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

	/*int BigPocket[6][40];
	int BigPocket2[6][40];*/

	// �΂̉摜
	int StoneImg[6]; 

	int Pocket_cnt;

	int InitialStone;
	int Stone_cnt;
	int movePocket;
	int Stone_count;
	int StonePocket[2][6]; // �Γ���Ă�|�P�b�g
	int sideAddition;      // �ړ������邽�߂̏���
	int Stonenum;          // �z��̒��̐΂̑���

	int CountUp;

	bool StoneFlg;
	int moveStone; 
	int moveStone2;
	// �|�P�b�g�̐��Ɠ����Ă���΂̐�
	int P1StoneSave[6][4]; 
	// �|�P�b�g�̐��Ɠ����Ă���΂̐�
	int P2StoneSave[6][4]; 

	int JustGoal; //�҂�����S�[���p 

public:
	Mankara();
	AbstractScene* Update();
	void Draw() const;
	// �΂��ړ��������̓�������
	void MoveStone();
};