#pragma once
#include"AbstractScene.h"
#define NUM_FUDA 4  //�D�̎�ށ@�S
#define MONTH 12  //���̎�ށ@�P�Q
//#define ALL_FUDA[NUM_FUDA * MONTH] //�D����

class Hanafuda:
	public AbstractScene
{
private:
	//�J�[�h�̍\����
	 struct FUDA{
		int fuda[48];  //�D
		int Month;  //��
		int draw_num[NUM_FUDA * MONTH];
 	};
	 struct FUDA Fuda;
	//�v���C���[�̍\����
	struct PLAYER {
		FUDA hand[NUM_FUDA];  //��D�̃J�[�h�z��
		int num_hand; //��D�̃J�[�h�̖���
	}Player;
	struct PLAYER player;
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
	int  Playerflg;  //���ԗp �e�t���O�i�P�F���ԁ@�O�F�҂��j
	int Partnerflg;	//���ԗp �q�t���O�i�P�F���ԁ@�O�F�҂��j
	int P_judge;  //�v���C���[�p ������
	int E_judge;  //AI�p ������
	int Judgeflg;
	int Startflg;  //�Q�[���X�^�[�g�t���O
	int OyaGimeflg; //�e���߃t���O()
	float FudaX, FudaY;  //�D���W
	int shuffleflg;  //�D�z�z�p�t���O
	int Fudaflg;
	int Phase;
	int Monthflg;
public:
	Hanafuda();
	~Hanafuda();
	virtual AbstractScene* Update()override;
	void Draw()const;
	void shuffleFuda(); //�D�z�z
	void OyaGime() ; // �e����

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
	void Month() { //������
		//�v���C���[������
		switch (i) {
		case 0:
		case 1:
		case 2:
		case 3:
			P_judge = 1;
			break;
		case 4:
		case 5:
		case 6:
		case 7:
			P_judge = 2;
			break;
		case 8:
		case 9:
		case 10:
		case 11:
			P_judge = 3;
			break;
		case 12:
		case 13:
		case 14:
		case 15:
			P_judge = 4;
			break;
		case 16:
		case 17:
		case 18:
		case 19:
			P_judge = 5;
			break;
		case 20:
		case 21:
		case 22:
		case 23:
			P_judge = 6;
			break;
		case 24:
		case 25:
		case 26:
		case 27:
			P_judge = 7;
			break;
		case 28:
		case 29:
		case 30:
		case 31:
			P_judge = 8;
			break;
		case 32:
		case 33:
		case 34:
		case 35:
			P_judge = 9;
			break;
		case 36:
		case 37:
		case 38:
		case 39:
			P_judge = 10;
			break;
		case 40:
		case 41:
		case 42:
		case 43:
			P_judge = 11;
			break;
		case 44:
		case 45:
		case 46:
		case 47:
			P_judge = 12;
			break;
		}
		//AI�p������
		switch (j) {
		case 0:
		case 1:
		case 2:
		case 3:
			E_judge = 1;
			break;
		case 4:
		case 5:
		case 6:
		case 7:
			E_judge = 2;
			break;
		case 8:
		case 9:
		case 10:
		case 11:
			E_judge = 3;
			break;
		case 12:
		case 13:
		case 14:
		case 15:
			E_judge = 4;
			break;
		case 16:
		case 17:
		case 18:
		case 19:
			E_judge = 5;
			break;
		case 20:
		case 21:
		case 22:
		case 23:
			E_judge = 6;
			break;
		case 24:
		case 25:
		case 26:
		case 27:
			E_judge = 7;
			break;
		case 28:
		case 29:
		case 30:
		case 31:
			E_judge = 8;
			break;
		case 32:
		case 33:
		case 34:
		case 35:
			E_judge = 9;
			break;
		case 36:
		case 37:
		case 38:
		case 39:
			E_judge = 10;
			break;
		case 40:
		case 41:
		case 42:
		case 43:
			E_judge = 11;
			break;
		case 44:
		case 45:
		case 46:
		case 47:
			E_judge = 12;
			break;
		}
	};  
};