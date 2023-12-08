#pragma once
#include "AbstractScene.h"
class Porker : public AbstractScene
{
private:
	int a[10];         //取り敢えず作った変数用の配列


	int Cursor[2];        //カーソル用変数


	int Round_Count;   //ラウンド数変数


	int CheckUI[3];    //確認用のUI(コールが0,レイズが1フォールドが2)
	

	int Pot;           //プレイヤーと敵が賭けてるスコア(チップ)の合計


	int Score[2];      //Score[0]がプレイヤー、Score[1]が敵のスコア(チップ)


	int Player_Choice[3]; //プレイヤーの選択 0がコール、1がレイズ、2がフォールド


	int  Enemy_Choice[3];//敵の選択 0がコール、1がレイズ、2がフォールド

	int Wait_TimeFLG;
	int Poker_Second[2];//待機時間計測用(0がプレイヤーの選択後1が敵の選択後

	int P_Rand[2];    //Randでとった画像配列の番号を入れとく箱(プレイヤーカード用)
	int P_CARD_A[2];  //Randでとった数を14で割った余りを入れとく箱(プレイヤーカード用)
	int P_CARD_S[2];  //Randでとった数を14で割った商を入れとく箱(プレイヤーカード用)

	int E_Rand[2];    //Randでとった画像配列の番号を入れとく箱(敵カード用)
	int E_CARD_A[2];  //Randでとった数を14で割った余りを入れとく箱(敵カード用)
	int E_CARD_S[2];  //Randでとった数を14で割った商を入れとく箱(敵カード用)

	int C_Rand[5];    //Randでとった画像配列の番号を入れとく箱(テーブルカード用)
	int C_CARD_A[5];  //Randでとった数を14で割った余りを入れとく箱(テーブルカード用)
	int C_CARD_S[5];  //Randでとった数を14で割った商を入れとく箱(テーブルカード用)
public:

	Porker();

	~Porker();

	//描画以外の更新を実行
	AbstractScene* Update() override;

	//描画に関することを実装
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

