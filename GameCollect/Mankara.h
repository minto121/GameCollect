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
		int img;
	} ;

	struct STONE gStone[6][8];

	

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
	int Stone_count;
	int StonePocket[2][6]; // �Γ���Ă�|�P�b�g
	int sideAddition;      // �ړ������邽�߂̏���
	int Stonenum;          // �z��̒��̐΂̑���

	int CountUp;

	bool StoneFlg;
	int moveStone; 
	// �|�P�b�g�̐��Ɠ����Ă���΂̐�
	int P1StoneSave[6][4]; 
	// �|�P�b�g�̐��Ɠ����Ă���΂̐�
	int P2StoneSave[6][4]; 

public:
	Mankara();
	AbstractScene* Update();
	void Draw() const;
	// �΂��ړ��������̓�������
	void MoveStone();
};

/*if (P1Turn == 1) {
	if (P1Pocket[0] == TRUE) {
		if (Stone_cnt > 0) {
			StonePocket[1] += Stone_cnt;
			StonePocket[2] += Stone_cnt;
			StonePocket[3] += Stone_cnt;
			StonePocket[4] += Stone_cnt;
				Stone_cnt-=1;
		}
		P2Turn = 1;
		P1Turn = 0;
	}
	else if (P1Pocket[1] == TRUE) {
		movePocket = 1;
		if (Stone_cnt > 0) {
			StonePocket[1 + movePocket] += Stone_cnt;
			StonePocket[2 + movePocket] += Stone_cnt;
			StonePocket[3 + movePocket] += Stone_cnt;
			StonePocket[4 + movePocket] += Stone_cnt;
			Stone_cnt -= 1;
		}
		P2Turn = 1;
		P1Turn = 0;
	}
	else if (P1Pocket[2] == TRUE) {
		movePocket = 2;
		if (Stone_cnt > 0) {
			StonePocket[1 + movePocket] += Stone_cnt;
			StonePocket[2 + movePocket] += Stone_cnt;
			StonePocket[3 + movePocket] += Stone_cnt;
			StonePocket[4 + movePocket] += Stone_cnt;
			P1BigPocket++;
			Stone_cnt -= 2;
		}
		P2Turn = 0;
		P1Turn = 1;

	}
	else if (P1Pocket[3] == TRUE) {
		movePocket = 3;
		if (Stone_cnt > 0) {
			StonePocket[1 + movePocket] += Stone_cnt;
			StonePocket[2 + movePocket] += Stone_cnt;
			P1BigPocket++;
			StonePocket[3 + movePocket] += Stone_cnt;
			Stone_cnt -= 3;
		}
		P2Turn = 1;
		P1Turn = 0;
	}
	else if (P1Pocket[4] == TRUE) {
		movePocket = 4;
		if (Stone_cnt > 0) {
			StonePocket[1 + movePocket] += Stone_cnt;
			StonePocket[2 + movePocket] += Stone_cnt;
			P1BigPocket++;
			StonePocket[3 + movePocket] += Stone_cnt;
			Stone_cnt -= 4;
		}
		P2Turn = 1;
		P1Turn = 0;
	}
	else if (P1Pocket[5] == TRUE) {
		movePocket = 5;
		if (Stone_cnt > 0) {
			StonePocket[1 + movePocket] += Stone_cnt;
			StonePocket[2 + movePocket] += Stone_cnt;
			P1BigPocket++;
			StonePocket[3 + movePocket] += Stone_cnt;
			Stone_cnt -= 5;
		}
		P2Turn = 1;
		P1Turn = 0;
	}
}*/



//// �QP�p�΂̈ړ�
//if (P2Turn == 1) {

   // if (P2Pocket[0] == TRUE) {
   //	 
   //	 if (Stone_cnt > 0) {
   //		 StonePocket[7 + movePocket] += Stone_cnt;
   //		 StonePocket[8 + movePocket] += Stone_cnt;
   //		 StonePocket[9 + movePocket] += Stone_cnt;
   //		 StonePocket[10 + movePocket] += Stone_cnt;
   //		 Stone_cnt -= 1;
   //	 }
   //	 P2Turn = 0;
   //	 P1Turn = 1;
   // }
   // else if (P2Pocket[1] == TRUE) {
   //	 movePocket = 1;
   //	 if (Stone_cnt > 0) {
   //		 StonePocket[7 + movePocket] += Stone_cnt;
   //		 StonePocket[8 + movePocket] += Stone_cnt;
   //		 StonePocket[9 + movePocket] += Stone_cnt;
   //		 StonePocket[10 + movePocket] += Stone_cnt;
   //		 Stone_cnt -= 1;
   //	 }
   //	 P2Turn = 0;
   //	 P1Turn = 1;
   // }
   // else if (P2Pocket[2] == TRUE) {
   //	 movePocket = 2;
   //	 if (Stone_cnt > 0) {
   //		 StonePocket[7 + movePocket] += Stone_cnt;
   //		 StonePocket[8 + movePocket] += Stone_cnt;
   //		 StonePocket[9 + movePocket] += Stone_cnt;
   //		 P2BigPocket++;
   //		 Stone_cnt -= 2;
   //	 }
   //	 P2Turn = 0;
   //	 P1Turn = 1;
   // }
   // else if (P2Pocket[3] == TRUE) {
   //	 movePocket = 3;
   //	 if (Stone_cnt > 0) {
   //		 StonePocket[7 + movePocket] += Stone_cnt;
   //		 StonePocket[8 + movePocket] += Stone_cnt;
   //		 P2BigPocket++;
   //		 StonePocket[0] += Stone_cnt;
   //		 Stone_cnt -= 3;
   //	 }
   //	 P2Turn = 1;
   //	 P1Turn = 0;
   // }
   // else if (P2Pocket[4] == TRUE) {
   //	 movePocket = 4;
   //	 if (Stone_cnt > 0) {
   //		 StonePocket[7 + movePocket] += Stone_cnt;
   //		 P2BigPocket++;
   //		 StonePocket[0] += Stone_cnt;
   //		 StonePocket[1] += Stone_cnt;
   //		 Stone_cnt -= 4;
   //	 }
   //	 P2Turn = 0;
   //	 P1Turn = 1;
   // }
   // else if (P2Pocket[5] == TRUE) {
   //	 movePocket = 5;
   //	 if (Stone_cnt > 0) {
   //		 P2BigPocket++;
   //		 StonePocket[0] += Stone_cnt;
   //		 StonePocket[1] += Stone_cnt;
   //		 StonePocket[2] += Stone_cnt;
   //		 Stone_cnt -= 5;
   //	 }
   //	 P2Turn = 0;
   //	 P1Turn = 1;
   // }

//}