#pragma once
#include"AbstractScene.h"
#define NUM_FUDA 4  //�D�̎�ށ@�S
#define MONTH 12  //���̎�ށ@�P�Q
#define FUDA 8    //��ɏo�Ă���D


class Hanafuda:
	public AbstractScene
{
private:
	//�J�[�h�̍\����
	// struct FUDA{
	//	long fuda[48];  //�D
	//	int Month;  //��
	//	int draw_num[NUM_FUDA * MONTH];
 //	};
	// struct FUDA Fuda;
	////�v���C���[�̍\����
	//struct PLAYER {
	//	int hand[8];  //��D�̃J�[�h�z��
	//	int num_hand; //��D�̃J�[�h�̖���
	//}Player;
	//struct PLAYER player;
	//struct ENEMY {
	//	int hand[8];
	//	int num_hand;
	//};
	//struct ENEMY Enemy;
	//static FUDA Fuda[NUM_FUDA];  //�J�[�h�̔z��
	int  FudaImg[48]; //�D�摜48��
	int F_Img;
	int E_fudaImg;
	int E_fuda[7];
	int P_fudaImg;
	int P_fuda[7];
	int UraImg;  //�D���摜
	int U_Img;
	int Stage;        //�w�i�摜
	int MouseX, MouseY;  //�}�E�X���W
	int i;
	int j; //�����p�t���O
	int z;
	int b;
	int  Playerflg;  //���ԗp �e�t���O�i�P�F���ԁ@�O�F�҂��j
	int Partnerflg;	//���ԗp �q�t���O�i�P�F���ԁ@�O�F�҂��j
	int P_judge;  //�v���C���[�p ������
	int E_judge;  //AI�p ������
	int Judgeflg;
	int Startflg;  //�Q�[���X�^�[�g�t���O
	int OyaGimeflg; //�e���߃t���O()
	float P_FudaX, P_FudaY;//�D���W
	float E_FudaX, E_FudaY;
	int shuffleflg;  //�D�z�z�p�t���O
	int Fudaflg;
	int Phase;
	int Monthflg;
	//int a; //�D�z�z���p�ϐ�
	long P_numhand[8];
	int E_numhand[8];
	int tick;
	int Gameflg;
	int Pnum_hand; //��D�����J�E���g
	long P_hand[8];//��D�z��
	int HandImg_1;
	int n;
	int Field[8];
	int Fieldflg;
	int P_shuffleflg;
	int E_shuffleflg;
public:
	Hanafuda();
	~Hanafuda();
	virtual AbstractScene* Update()override;
	void Draw()const;
	void shuffleFuda(); //�D�z�z
	void OyaGime() ; // �e����
	void Month();
	void Oya();
	void Ko();
	int Kas();
	int Tan();
	int Tane();
	int Akatan();
	int Aotan();
	int Inosikatyou();
	int Hanami();
	int Tukimi();
	int Sankou();
	int Sikou();
	int Amesikou();
	int Gokou();
	int Koikoi();
	int Syobu();
};