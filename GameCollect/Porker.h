#pragma once
#include "AbstractScene.h"
class Porker : public AbstractScene
{
private:
	int a[10];         //��芸����������ϐ��p�̔z��


	int Cursor[2];        //�J�[�\���p�ϐ�


	int Round_Count;   //���E���h���ϐ�


	int CheckUI[3];    //�m�F�p��UI(�R�[����0,���C�Y��1�t�H�[���h��2)
	

	int Pot;           //�v���C���[�ƓG���q���Ă�X�R�A(�`�b�v)�̍��v


	int Score[2];      //Score[0]���v���C���[�AScore[1]���G�̃X�R�A(�`�b�v)


	int Player_Choice[3]; //�v���C���[�̑I�� 0���R�[���A1�����C�Y�A2���t�H�[���h


	int  Enemy_Choice[3];//�G�̑I�� 0���R�[���A1�����C�Y�A2���t�H�[���h

	int Wait_TimeFLG;
	int Poker_Second[2];//�ҋ@���Ԍv���p(0���v���C���[�̑I����1���G�̑I����

	int P_Rand[2];    //Rand�łƂ����摜�z��̔ԍ������Ƃ���(�v���C���[�J�[�h�p)
	int P_CARD_A[2];  //Rand�łƂ�������14�Ŋ������]������Ƃ���(�v���C���[�J�[�h�p)
	int P_CARD_S[2];  //Rand�łƂ�������14�Ŋ������������Ƃ���(�v���C���[�J�[�h�p)

	int E_Rand[2];    //Rand�łƂ����摜�z��̔ԍ������Ƃ���(�G�J�[�h�p)
	int E_CARD_A[2];  //Rand�łƂ�������14�Ŋ������]������Ƃ���(�G�J�[�h�p)
	int E_CARD_S[2];  //Rand�łƂ�������14�Ŋ������������Ƃ���(�G�J�[�h�p)

	int C_Rand[5];    //Rand�łƂ����摜�z��̔ԍ������Ƃ���(�e�[�u���J�[�h�p)
	int C_CARD_A[5];  //Rand�łƂ�������14�Ŋ������]������Ƃ���(�e�[�u���J�[�h�p)
	int C_CARD_S[5];  //Rand�łƂ�������14�Ŋ������������Ƃ���(�e�[�u���J�[�h�p)
public:

	Porker();

	~Porker();

	//�`��ȊO�̍X�V�����s
	AbstractScene* Update() override;

	//�`��Ɋւ��邱�Ƃ�����
	void Draw() const override;


	void ROUND_INIT();
	void ROUND();
	void FIRST_BET();
	void UI();
	void PLAYER_CHOICE();
	void ENEMY_CHOICE();
	void CARD_SETTING();
	void WAIT_TIME();
	//void ();
};

