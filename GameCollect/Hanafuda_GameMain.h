#pragma once
#include"AbstractScene.h"
#include <windows.h>
#define GAME_FUDA 8 //場（自分の手札、相手の手札、置き札それぞれの最初の枚数　８）
//#define KAS 24  //カス　全部で２４枚
//#define TAN 10  //タン　全部で１０枚
//#define TANE 9  //タネ　全部で９枚
//#define HIKARI  //光札　全部で５枚

class Hanafuda : public AbstractScene
{
private:
	//持ち札構造体（持ち札の月、札の種類ごとの座標）
	typedef struct P_MOTIFUDA {
		int kas_count = 0; //役用カウント
		typedef struct Kas {
			int x;
			int y;
			int Img;
			bool display = FALSE; //表示
		}Kas;
		struct Kas kas[24];//取り札配列　カス　２４
		int tan_count = 0; //役用カウント
			typedef struct Tan{
			int x;
			int y;
			int Img;
			bool display = FALSE; //表示
		}Tan; 
			struct Tan tan[10];//取り札配列　タン　１０
		int tane_count = 0;  //役用カウント
		typedef struct Tane {
			int x;
			int y;
			int Img;
			bool display = FALSE; //表示
		}Tane;
		struct Tane tane[9];//取り札配列　タネ　９
		int hikari_count = 0; 
		typedef struct Hikari {
			int x;
			int y;
			int Img;
			bool display = FALSE; //表示
		}Hikari;//取り札配列　光札　５
		struct Hikari hikari[5];
		bool TaneYaku = FALSE;
		bool TanYaku = FALSE;
		bool KasYaku = FALSE;
	}P_MOTIFUDA;
	struct P_MOTIFUDA P_Motifuda;

	//敵の持ち札
	typedef struct E_MOTIFUDA {
		int kas_count = 0; //役用カウント
		typedef struct Kas {
			int x;
			int y;
			int Img;
			bool display = FALSE; //表示
		}Kas;
		struct Kas kas[24];//取り札配列　カス　２４
		int tan_count = 0; //役用カウント
		typedef struct Tan {
			int x;
			int y;
			int Img;
			bool display = FALSE; //表示
		}Tan;
		struct Tan tan[10];//取り札配列　タン　１０
		int tane_count = 0;  //役用カウント
		typedef struct Tane {
			int x;
			int y;
			int Img;
			bool display = FALSE; //表示
		}Tane;
		struct Tane tane[9];//取り札配列　タネ　９
		int hikari_count = 0;
		typedef struct Hikari {
			int x;
			int y;
			int Img;
			bool display = FALSE; //表示
		}Hikari;//取り札配列　光札　５
		struct Hikari hikari[5];
		bool TaneYaku = FALSE;
		bool TanYaku = FALSE;
		bool KasYaku = FALSE;
	}E_MOTIFUDA;
	struct E_MOTIFUDA E_Motifuda;

	//取り札構造体（取り札情報の代入先、最大８枚）の情報を持ち札に代入
	typedef struct TORIFUDA { //0が手札からだした時の取り札、
		int Img;              //1は山札から出したときの取り札か総取りするに１から３を使う
		int month;			  //2からは総取りの時に使ったりずらしで使う
		int FudaX;
		int FudaY;
		bool Hikari = FALSE;
		bool Tane = FALSE;
		bool Tan = FALSE;
		bool Kas = FALSE;
		bool display = FALSE;
	}TORIFUDA;
	struct TORIFUDA torifuda[8];
	int toricount = 0; //取り札カウント　１枚取るごとに増やす　最大８
	//手札から場に出す札の構造体（選択した手札情報の代入先、場の札とは月で判定する、ゲームとして完成するまでは移動場の横に移動する）
	typedef struct JUDGEFUDA {
		int Img;
		int month = 0;
		int X;
		int Y;
		bool display = FALSE;
		bool Hikari = FALSE;
		bool Tane = FALSE;
		bool Tan = FALSE;
		bool Kas = FALSE;
	}JUDGEFUDA;
	struct JUDGEFUDA Judgefuda;
	//札の構造体
	typedef  struct FUDA{
		int Img; //札画像
		int month;//月
		bool Hikari = FALSE;
		bool Tane = FALSE;
		bool Tan = FALSE;
		bool Kas = FALSE;
 	}FUDA;
	 struct FUDA Fuda[48];
	//プレイヤーの構造体
	typedef struct PLAYER {
		int Img; //札画像
		int month;  //手番の月判定用
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
	int P_count = 0; //手札の数
	int P_Score = 0;  //ゲーム中のスコア（こいこい時などで扱う）
	int P_TotalScore = 0;//最終的な勝敗を決めるスコア
	//敵の構造体
	typedef struct ENEMY {
			int Img; //札画像
			int month;  //手番の月判定用
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
	int E_Score = 0; //ゲーム中のスコア(こいこい時などで扱う)
	int E_TotalScore = 0; //最終的な勝敗を決めるスコア
	int E_count= 0; //手札の数
	//置き札（場）の構造体（最大１２枚置ける、）
	typedef struct FIELD {
		int Img; //札画像
		int month = 0; //取り札の月判定 
		int FudaX = 0;
		int FudaY = 0;
		bool Hikari = FALSE;
		bool Tane = FALSE;
		bool Tan = FALSE;
		bool Kas = FALSE;
		bool display = FALSE;
		bool in = FALSE;
	}FIELD;
	struct FIELD Field[12];
	int F_count = 0;//置き札の枚数（場の札の増減時に使うカウント用）

	typedef struct YAMAFUDA {
		int Img;
		int month;
		int X;
		int Y;
		int judge = 0;
		bool Hikari = FALSE;
		bool Tane = FALSE;
		bool Tan = FALSE;
		bool Kas = FALSE;
		bool display = FALSE;
	}YAMAFUDA;
	struct YAMAFUDA yamafuda;

	typedef struct OyaGime {
		int P_Img;
		int P_month;
		int E_Img;
		int E_month;
	}OyaGime;
	struct OyaGime oyagime;
	int FudaImg[48]; //札画像
	int UraImg; //札裏画像
	int U_Img;
	int Stage;  //背景画像
	int MouseX, MouseY;  //マウス座標
	int i;
	int j; //乱数用フラグ
	int n;
	int count;
	int judgeflg = 0;
	int  Playerflg;  //順番用 親フラグ（１：順番　０：待ち）
	int Partnerflg;	//順番用 子フラグ（１：順番　０：待ち）
	int P_judge;  //プレイヤー用 月判定
	int E_judge;  //AI用 月判定
	int Judgeflg;
	int Startflg;  //ゲームスタートフラグ
	int OyaGimeflg; //親決めフラグ()
	int shuffleflg;  //札配布用フラグ
	int Fudaflg;
	int Phase;
	int Monthflg;
	int r;
	int now_select;
	int select;
	int input_margin;
	//int a; //札配布時用変数
	int tick;
	int Gameflg;
	int P_shuffleflg;
	int E_shuffleflg;
	int P_CursorX; //手持ち札カーソル座標（X軸）
	int P_CursorY; //手持ち札カーソル座標（Y軸）
	int E_CursorX;
	int E_CursorY;
	int P_CenterX;
	int P_CenterY;
	int E_CenterX;
	int E_CenterY;
	int Trash = 0;
	int P_fudaImg;
	int E_fudaImg;
	int yama[48];
	int s = 0;
	int x = 0;
	int stick_x;
	int Sute = 0;
	int FieldCount = 0;
	int MoveJudge = 0;
	int K_Judge = 0;
	int Y_month;
	bool P_Win = FALSE;
	bool E_Win = FALSE;
	bool P_turn = FALSE;
	bool E_turn = FALSE; //ターン判定
	bool P_draw = FALSE;
	bool E_draw = FALSE; //山札から引く判定
	bool Moveflg = FALSE;
	bool P_Cursor = FALSE;
	bool E_Cursor = FALSE;
	bool P_MoveCursor = FALSE;
	bool E_MoveCursor = FALSE;
public:
	Hanafuda();
	~Hanafuda();
	virtual AbstractScene* Update()override;
	void Draw()const;
	void shuffleFuda(); //札配布
	void OyaGime();// 親決め
	void P_ban();
	void E_ban();
	void location();
	void Init();
	void Tefudalocation();
	void Hiku();
	void Move();
	void Sutefuda();
	void Judge();
	void Koikoi();
	//void Agari();
	//役
	void Tane();
	void Tan();
	void Kas();
	//void Akatan();
	//void Aotan();
	//void Inosikatyou();
	//int Hanami();
	//int Tukimi();
	//int Sankou();
	//int Sikou();
	//int Amesikou();
	//int Gokou();
	//int Koikoi();
	//int Syobu();
};