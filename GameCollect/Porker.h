#pragma once
#include "AbstractScene.h"
class Porker : public AbstractScene
{
private:
	int Tranpu_Img[56];

	int BackGround[3];

	int a[30];             //��芸����������ϐ��p�̔z��


	int Cursor[2];         //�J�[�\���p�ϐ�


	int Round_Count;       //���E���h���ϐ�


	int CheckUI[3];        //�m�F�p��UI(�R�[����0,���C�Y��1�t�H�[���h��2)
	

	int Pot;               //�v���C���[�ƓG���q���Ă�X�R�A(�`�b�v)�̍��v


	int Score[2];          //Score[0]���v���C���[�AScore[1]���G�̃X�R�A(�`�b�v)


	int Player_Choice[3];  //�v���C���[�̑I�� 0���R�[���A1�����C�Y�A2���t�H�[���h


	int Enemy_Choice[3];   //�G�̑I�� 0���R�[���A1�����C�Y�A2���t�H�[���h


	int Wait_TimeFLG[5];   //�ҋ@���Ԕ����̃t���O


	int Poker_Second[5];   //�ҋ@���Ԍv���p(0���v���C���[�̑I����1���G�̑I����


	int Action_UI;         //�s���I�����UI(1���x�b�g�A2�����C�Y�A3���t�H�[���h�A4���G�̃R�[���A5���G�̃t�H�[���h)


	int FB_UI;             //FB�ҋ@���ԗp


	int Round_UI;          //���E���h�\��UI


	int Turn;              //�^�[��


	int ShowDawnUI;        //�V���E�_�E��UI    


	int ShowDawn;          //�V���E�_�E��


	int Result;            //���U���g���


	int LastGame;          //�c��Q�[����


	int P_Rand[2];         //Rand�łƂ����摜�z��̔ԍ������Ƃ���(�v���C���[�J�[�h�p)

	int P_CARD_A[2];       //Rand�łƂ�������14�Ŋ������]������Ƃ���(�v���C���[�J�[�h�p)

	int P_CARD_S[2];       //Rand�łƂ�������14�Ŋ������������Ƃ���(�v���C���[�J�[�h�p)

	int E_Rand[2];         //Rand�łƂ����摜�z��̔ԍ������Ƃ���(�G�J�[�h�p)

	int E_CARD_A[2];       //Rand�łƂ�������14�Ŋ������]������Ƃ���(�G�J�[�h�p)

	int E_CARD_S[2];       //Rand�łƂ�������14�Ŋ������������Ƃ���(�G�J�[�h�p)

	int C_Rand[5];         //Rand�łƂ����摜�z��̔ԍ������Ƃ���(�e�[�u���J�[�h�p)

	int C_CARD_A[5];       //Rand�łƂ�������14�Ŋ������]������Ƃ���(�e�[�u���J�[�h�p)

	int C_CARD_S[5];       //Rand�łƂ�������14�Ŋ������������Ƃ���(�e�[�u���J�[�h�p)

	int P_NOPEA_FLG;

	int P_PEA_FLG[2];

	int P_2PEA_FLG;

	int P_3CARD_FLG;

	int P_STRAIGHT_FLG;

	int P_FLASH_FLG;

	int P_FULLHOUSE_FLG;

	int P_4CARD_FLG;

	int P_SF_FLG;

	int P_RSF_FLG;

	int E_NOPEA_FLG;

	int E_PEA_FLG[2];

	int E_2PEA_FLG;

	int E_3CARD_FLG;

	int E_STRAIGHT_FLG;

	int E_FLASH_FLG;

	int E_FULLHOUSE_FLG;

	int E_4CARD_FLG;

	int E_SF_FLG;

	int E_RSF_FLG;



	int P_SORT[15];        //�J�[�h�̃\�[�g�p

	int P_SORT2[5];

	int P_SORT3[6];

	int P_Straight[15];

	int E_Straight[15];

	int E_SORT[15];
	
	int Hand[9];

	int GameOver;
public:

	Porker();

	~Porker();

	//�`��ȊO�̍X�V�����s
	AbstractScene* Update() override;

	//�`��Ɋւ��邱�Ƃ�����
	void Draw() const override;


	void ROUND_INIT();
	void ROUND_END();
	void FIRST_BET();
	void UI();
	void PLAYER_CHOICE();
	void ENEMY_CHOICE();
	void CARD_SETTING();
	void CARD_SETTING2();
	void CARD_ANALAYSIS();
;	void CARD_SORT();
	void WAIT_TIME();
	void ROUND_UI();
	void HAND();
	void GAMEOVER();

	//void ();
};

