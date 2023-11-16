#pragma once
#include "AbstractScene.h"
class Mankara :public AbstractScene
{
private:

	

	int Board; // �Q�[���{�[�h�̉摜
	int Background; // �w�i�摜

	int P1Turn;
	int P2Turn;

	struct STONE
	{
		int flg = 1;
		int img[6][8];
	} ;

	struct STONE gStone;

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

	// �΂̉摜
	int StoneImg[6]; 

	int Pocket_cnt;

	int InitialStone;
	int Stone_cnt;
	int movePocket;

	int StonePocket[2][6]; // �Γ���Ă�|�P�b�g
	int sideAddition;      // �ړ������邽�߂̏���
	int Stonenum;          // �z��̒��̐΂̑���

public:
	Mankara();
	AbstractScene* Update();
	void Draw() const;
};

