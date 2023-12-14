#pragma once
#include "AbstractScene.h"
class Porker : public AbstractScene
{
private:
	int Tranpu_Img[56];

	int BackGround[3];

	int a[30];             //取り敢えず作った変数用の配列


	int Cursor[2];         //カーソル用変数


	int Round_Count;       //ラウンド数変数


	int CheckUI[3];        //確認用のUI(コールが0,レイズが1フォールドが2)
	

	int Pot;               //プレイヤーと敵が賭けてるスコア(チップ)の合計


	int Score[2];          //Score[0]がプレイヤー、Score[1]が敵のスコア(チップ)


	int Player_Choice[3];  //プレイヤーの選択 0がコール、1がレイズ、2がフォールド


	int Enemy_Choice[3];   //敵の選択 0がコール、1がレイズ、2がフォールド


	int Wait_TimeFLG[5];   //待機時間発動のフラグ


	int Poker_Second[5];   //待機時間計測用(0がプレイヤーの選択後1が敵の選択後


	int Action_UI;         //行動選択後のUI(1がベット、2がレイズ、3がフォールド、4が敵のコール、5が敵のフォールド)


	int FB_UI;             //FB待機時間用


	int Round_UI;          //ラウンド表示UI


	int Turn;              //ターン


	int ShowDawnUI;        //ショウダウンUI    


	int ShowDawn;          //ショウダウン


	int Result;            //リザルト画面


	int LastGame;          //残りゲーム数


	int P_Rand[2];         //Randでとった画像配列の番号を入れとく箱(プレイヤーカード用)

	int P_CARD_A[2];       //Randでとった数を14で割った余りを入れとく箱(プレイヤーカード用)

	int P_CARD_S[2];       //Randでとった数を14で割った商を入れとく箱(プレイヤーカード用)

	int E_Rand[2];         //Randでとった画像配列の番号を入れとく箱(敵カード用)

	int E_CARD_A[2];       //Randでとった数を14で割った余りを入れとく箱(敵カード用)

	int E_CARD_S[2];       //Randでとった数を14で割った商を入れとく箱(敵カード用)

	int C_Rand[5];         //Randでとった画像配列の番号を入れとく箱(テーブルカード用)

	int C_CARD_A[5];       //Randでとった数を14で割った余りを入れとく箱(テーブルカード用)

	int C_CARD_S[5];       //Randでとった数を14で割った商を入れとく箱(テーブルカード用)

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



	int P_SORT[15];        //カードのソート用

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

	//描画以外の更新を実行
	AbstractScene* Update() override;

	//描画に関することを実装
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

