#pragma once
#include "AbstractScene.h"
class Porker : public AbstractScene
{
private:
	
	int a;
	int wt;
	int ps1;
	int es1;
	int Bs;
	int BTN_flg;
	int P_FPS;
	int P_TEKI;
	int WP;
	int WP2;
	int WP3;
	int WP4;
	int WP_FLG[5];
	int YP[4];
	int YP2[4];
	int YE[4];

	int Winflg;
	int Loseflg;
	int Drawflg;
	int E_Fouldflg;
	int E_CAllflg;
	int E_Raiseflg;
	int P_Call_H_flg;
	int P_Raise_H_flg;
	int P_Fould_H_flg;
	int E_Fould_H_flg;
	int G_Over_H_flg;
	int WTflg[3];
	
	int WTRelese[3];
	
	int BTN_RELESE_FLG[6];
	
	int P_F_flg;
	int RC_H_flg;
	int CARD_URA_H_flg;

	int Tranpu_Img[56];
	int Back;
	int P_rand[2];
	
	int E_rand[2];
	
	int C_rand[5];
	
	int C_flg[3];

	int P_CARD_S[2];//�v���C���[�J�[�h�̏��i�[�p
	int P_CARD_A[2];//�v���C���[�J�[�h�̗]��i�[�p

	int E_CARD_S[2];//�G�J�[�h�̏��i�[�p
	int E_CARD_A[2];//�G�J�[�h�̗]��i�[�p

	int C_CARD_S[5];//��ɏo�Ă���J�[�h1~5�̏��i�[�p
	int C_CARD_A[5];//��ɏo�Ă���J�[�h1~5�̗]��i�[�p
	
	
	int P_PEA_FLG[4];//�v���C���[��1�y�A�̃t���O
	int P_2PEA_FLG;//�v���C���[��2�y�A�̃t���O
	int P_THREE_FLG;//�v���C���[�̃X���[�J�[�h�̃t���O
	int P_FH_FLG;

public:
	Porker();

	~Porker();

	//�`��ȊO�̍X�V�����s
	AbstractScene* Update() override;

	//�`��Ɋւ��邱�Ƃ�����
	void Draw() const override;


	
	void ROUND_INIT();//���E���h������

	void PLAYER_CALL();//�v���C���[�̃R�[���p�֐�

	void PLAYER_RAISE();//�v���C���[�̃��C�Y�p�֐�

	void ENEMIE_CHOISE();//�G�̑I��p�֐�

	void CARD_ANALYSIS();//�J�[�h�̐����ƃ}�[�N�𒲂ׂ�p�̊֐�

	void P_CARD_YAKU();//������̂��߂̊֐�

	void P_CARD_YAKU3CARD();

	void P_CARD_FULLHOUSE();

};

