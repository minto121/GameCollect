#pragma once
#include"AbstractScene.h"
#define GAME_FUDA 8 //��i�����̎�D�A����̎�D�A�u���D���ꂼ��̍ŏ��̖����@�W�j
//#define KAS 24  //�J�X�@�S���łQ�S��
//#define TAN 10  //�^���@�S���łP�O��
//#define TANE 9  //�^�l�@�S���łX��
//#define HIKARI  //���D�@�S���łT��

class Hanafuda : public AbstractScene
{
private:
	//�����D�\���́i�����D�̌��A�D�̎�ނ��Ƃ̍��W�j
	typedef struct P_MOTIFUDA {
		int kas_count = 0; //��p�J�E���g
		typedef struct Kas {
			int x;
			int y;
			int Img;
			bool display = FALSE; //�\��
		}Kas;
		struct Kas kas[24];//���D�z��@�J�X�@�Q�S
		int tan_count = 0; //��p�J�E���g
			typedef struct Tan{
			int x;
			int y;
			int Img;
			bool display = FALSE; //�\��
		}Tan; 
			struct Tan tan[10];//���D�z��@�^���@�P�O
		int tane_count = 0;  //��p�J�E���g
		typedef struct Tane {
			int x;
			int y;
			int Img;
			bool display = FALSE; //�\��
		}Tane;
		struct Tane tane[9];//���D�z��@�^�l�@�X
		int hikari_count = 0; 
		typedef struct Hikari {
			int x;
			int y;
			int Img;
			bool display = FALSE; //�\��
		}Hikari;//���D�z��@���D�@�T
		struct Hikari hikari[5];
	}P_MOTIFUDA;
	struct P_MOTIFUDA P_Motifuda;
	//���D�\���́i���D���̑����A�ő�W���j�̏��������D�ɑ��
	typedef struct TORIFUDA { //0����D���炾�������̎��D�A
		int Img;              //1�͎R�D����o�����Ƃ��̎��D������肷��ɂP����R���g��
		int month;			  //2����͑����̎��Ɏg�����肸�炵�Ŏg��
		int FudaX;
		int FudaY;
		bool Hikari = FALSE;
		bool Tane = FALSE;
		bool Tan = FALSE;
		bool Kas = FALSE;
		bool display = FALSE;
	}TORIFUDA;
	struct TORIFUDA torifuda[8];
	int toricount = 0; //���D�J�E���g�@�P����邲�Ƃɑ��₷�@�ő�W
	//��D�����ɏo���D�̍\���́i�I��������D���̑����A��̎D�Ƃ͌��Ŕ��肷��A�Q�[���Ƃ��Ċ�������܂ł͈ړ���̉��Ɉړ�����j
	typedef struct JUDGEFUDA {
		int Img;
		int month;
		int judgeX;
		int judgeY;
		bool Hikari = FALSE;
		bool Tane = FALSE;
		bool Tan = FALSE;
		bool Kas = FALSE;
	    bool Judge = FALSE;
	}JUDGEFUDA;
	struct JUDGEFUDA Judgefuda;
	//�D�̍\����
	typedef  struct FUDA{
		int Img; //�D�摜
		int month;//��
		bool Hikari = FALSE;
		bool Tane = FALSE;
		bool Tan = FALSE;
		bool Kas = FALSE;
 	}FUDA;
	 struct FUDA Fuda[48];
	//�v���C���[�̍\����
	typedef struct PLAYER {
		int Img; //�D�摜
		int month;  //��Ԃ̌�����p
		int FudaX;
		int FudaY;
		bool Hikari = FALSE;
		bool Tane = FALSE;
		bool Tan = FALSE;
		bool Kas = FALSE;
		bool display = FALSE;
		bool in = FALSE;
	}PLAYER;
	struct PLAYER Player[8];
	int P_count = 0; //��D�̐�
	int GameScore = 0;  //�Q�[�����̃X�R�A�i�����������Ȃǂň����j
	int TotalScore = 0; //�ŏI�I�ȏ��s�����߂�X�R�A
	//�G�̍\����
	typedef struct ENEMY {
			int Img; //�D�摜
			int month;  //��Ԃ̌�����p
			int FudaX;
			int FudaY;
			bool Hikari = FALSE;
			bool Tane = FALSE;
			bool Tan = FALSE;
			bool Kas = FALSE;
			bool display = FALSE;
			bool in = FALSE;
	}ENEMY;
	struct ENEMY Enemy[8];
	int E_GameScore = 0; //�Q�[�����̃X�R�A(�����������Ȃǂň���)
	int E_TotalScore = 0; //�ŏI�I�ȏ��s�����߂�X�R�A
	int E_count= 0; //��D�̐�
	//�u���D�i��j�̍\���́i�ő�P�Q���u����A�j
	typedef struct FIELD {
		int Img; //�D�摜
		int month = 0; //���D�̌����� 
		int FudaX = 0;
		int FudaY = 0;
		bool Hikari = FALSE;
		bool Tane = FALSE;
		bool Tan = FALSE;
		bool Kas = FALSE;
		bool diplay = FALSE;
		bool in = FALSE;
	}FIELD;
	struct FIELD Field[12];
	int F_count = 0;//�u���D�̖����i��̎D�̑������Ɏg���J�E���g�p�j
	typedef struct YAMAFUDA {
		int Img;
		int month;
		int X;
		int Y;
		bool draw = FALSE;
		int judge = 0;
		bool Hikari = FALSE;
		bool Tane = FALSE;
		bool Tan = FALSE;
		bool Kas = FALSE;
	}YAMAFUDA;
	struct YAMAFUDA yamafuda;

	int FudaImg[48]; //�D�摜
	int UraImg; //�D���摜
	int U_Img;
	int Stage;  //�w�i�摜
	int MouseX, MouseY;  //�}�E�X���W
	int i;
	int j; //�����p�t���O
	int n;
	int count;
	int judgeflg = 0;
	int  Playerflg;  //���ԗp �e�t���O�i�P�F���ԁ@�O�F�҂��j
	int Partnerflg;	//���ԗp �q�t���O�i�P�F���ԁ@�O�F�҂��j
	int P_judge;  //�v���C���[�p ������
	int E_judge;  //AI�p ������
	int Judgeflg;
	int Startflg;  //�Q�[���X�^�[�g�t���O
	int OyaGimeflg; //�e���߃t���O()
	int shuffleflg;  //�D�z�z�p�t���O
	int Fudaflg;
	int Phase;
	int Monthflg;
	int r;
	int now_select;
	int select;
	int input_margin;
	//int a; //�D�z�z���p�ϐ�
	int tick;
	int Gameflg;
	int P_shuffleflg;
	int E_shuffleflg;
	int CursorX; //�莝���D�J�[�\�����W�iX���j
	int CursorY; //�莝���D�J�[�\�����W�iY���j
	int CenterX;
	int CenterY;
	int Trash = 0;
	int P_fudaImg;
	int E_fudaImg;
	int yama[48];
	int s = 0;
	int x = 0;
	int stick_x;
	bool P_turn = FALSE;
	bool E_turn = FALSE; //�^�[������
	bool P_draw = FALSE;
	bool E_draw = FALSE; //�R�D�����������
	bool Moveflg = FALSE;
	bool Cursor = FALSE;
	bool MoveCursor = FALSE;
public:
	Hanafuda();
	~Hanafuda();
	virtual AbstractScene* Update()override;
	void Draw()const;
	void shuffleFuda(); //�D�z�z
	void OyaGime();// �e����
	void Oyaban();
	void Koban();
	//void Month();
	void location();
	/*void Init();*/
	void Tefudalocation();
	void Hiku();
	void Move();
	void Init(); //������
	/*void FudaMove();*/
	//void Kas();
	//void Tan();
	//void Tane();
	//int Akatan();
	//int Aotan();
	//int Inosikatyou();
	//int Hanami();
	//int Tukimi();
	//int Sankou();
	//int Sikou();
	//int Amesikou();
	//int Gokou();
	//int Koikoi();
	//int Syobu();
};