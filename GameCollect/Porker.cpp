#include "Porker.h"
#include"DxLib.h"
#include"PadInput.h"
#include<stdlib.h>
#include"math.h"
#include "GameSelect.h"



Porker::Porker()
{
	if (LoadDivGraph("../GameCollect/images/TexasHoldem/PlayingCards.png", 56, 14, 4, 128, 256, Tranpu_Img, FALSE)) {}

	BackGround[0] = LoadGraph("../GameCollect/images/TexasHoldem/Poker_Back.png");
	BackGround[1] = LoadGraph("../GameCollect/images/TexasHoldem/金背景2.png");
	BackGround[2] = LoadGraph("../GameCollect/images/TexasHoldem/虹背景.png");
	Round_Count = 1;//ラウンド数
	
	ROUND_INIT();//ラウンド初期化
}


Porker::~Porker()
{

}


//ラウンド初期化
void Porker::ROUND_INIT()
{

  //プレイヤーと敵が賭けてるスコア(チップ)の合計
  Pot = 0;         

  //行動選択後のUI(1がベット、2がレイズ、3がフォールド、4が敵のコール、5が敵のフォールド)
  Action_UI = 0;


  //FB待機時間用
  FB_UI = 0;


  //ターン表示UI
  Turn = 1;


  //ラウンド表示UI
  Round_UI = TRUE;
 

  //ショウダウン
  ShowDawn = FALSE;              


  //ショウダウンUI
  ShowDawnUI = FALSE;


  //リザルト画面
  Result = FALSE;


  //残りゲーム数
  LastGame = 4;


  //ゲーム終了
  GameOver = FALSE;


   P_NOPEA_FLG = FALSE;

   P_2PEA_FLG = FALSE;

   P_3CARD_FLG = FALSE;

   P_STRAIGHT_FLG = FALSE;

   P_FLASH_FLG = FALSE;

   P_FULLHOUSE_FLG = FALSE;

   P_4CARD_FLG = FALSE;

   P_SF_FLG = FALSE;

   P_RSF_FLG = FALSE;

   E_NOPEA_FLG = FALSE;

   E_2PEA_FLG = FALSE;

   E_3CARD_FLG = FALSE;

   E_STRAIGHT_FLG = FALSE;

   E_FLASH_FLG = FALSE;

   E_FULLHOUSE_FLG = FALSE;

   E_4CARD_FLG = FALSE;

   E_SF_FLG = FALSE;

   E_RSF_FLG = FALSE;


  //ペアフラグ
  for (int x = 0; x <= 1; x++)
  {
	  P_PEA_FLG[x] = FALSE;
  }



  //もしラウンドが1なら初期所持スコアは1000になる Score[0]がプレイヤー、Score[1]が敵
  if (Round_Count == 1) {             
	  for (int x = 0; x <= 1; x++)
	  {
		  Score[x] = 5000;           
	  }
  }



  // 適当な変数の箱用
  for (int x = 0; x <= 29; x++)
  {
	  a[x] = 0;                    
  }


  //確認用のUI(ベットが0,レイズが1,フォールドが2)
  for (int x = 0; x <= 2; x++)
  {
	  CheckUI[x] = FALSE;
  }


  //確認用のUIのカーソル座標用
  for (int x = 0; x <= 1; x++)
  {
	  Cursor[x] = 0;
  }


  //プレイヤーの選択(0がコール、1がレイズ、2がフォールド)
  for (int x = 0; x <= 2; x++)
  {
	  Player_Choice[x] = FALSE;
  }


  //敵の選択(0がコール、1がフォールド)
  for (int x = 0; x <= 2; x++)
  {
	  Enemy_Choice[x] = FALSE;
  }


  //待機時間用
  for (int x = 0; x <= 4; x++)
  {
	  Poker_Second[x] = FALSE;
  }


  //待機時間発動のフラグ
  for (int x = 0; x <= 4; x++)
  {
	  Wait_TimeFLG[x] = FALSE; 
  }


  //ソート用
  for (int x = 0; x <= 14; x++)
  {
	  P_SORT[x] = 0;
  }

  //ソート用2
  for (int x = 0; x <= 4; x++)
  {
	  P_SORT2[x] = 0;
  }

  //ソート用3
  for (int x = 0; x <= 5; x++)
  {
	  P_SORT3[x] = 0;
  }

  //ソート用4
  for (int x = 0; x <= 14; x++)
  {
	  E_SORT[x] = 0;
  }

  //ハンドUI
  for (int x = 0; x <= 8; x++)
  {
	 Hand[x] = FALSE;
  }

  //すとれーと番号格納用
  for (int x = 0; x <= 14; x++)
  {
	  P_Straight[x] = 0;
  }

  //すとれーと番号格納用enemy
  for (int x = 0; x <= 14; x++)
  {
	  E_Straight[x] = 0;
  }


  for (int x = 0; x <= 1; x++)
  {
	 W_point[x] = 0;
  }

  for (int x = 0; x <= 1; x++)
  {
	  R_Win[x] = 0;
  }

  for (int x = 0; x <= 1; x++)
  {
	  WL[x] = 0;
  }

 
  CARD_SETTING();
}


//最初に払う参加費
void Porker::FIRST_BET()
{

	//ラウンド1開始時に参加費250払う
	if (Round_Count == 1 && a[1] == 0)
	{	
		Wait_TimeFLG[1] = TRUE;
		for (int x = 0; x <= 1; x++)
		{
			
			Score[x] = Score[x] - 250;
			Pot += 250;
			a[1] = 1;
			a[5] = 250;
		}
		
	}

	//ラウンド2開始時に参加費500払う
	if (Round_Count == 2 && a[1] == 0)
	{
		Wait_TimeFLG[1] = TRUE;
		for (int x = 0; x <= 1; x++)
		{
			
			Score[x] = Score[x] - 500;
			Pot += 500;
			a[1] = 1;
			a[5] = 500;
		}
		
	}

	//ラウンド3開始時に参加費750払う
	if (Round_Count == 3 && a[1] == 0)
	{
		Wait_TimeFLG[1] = TRUE;
		for (int x = 0; x <= 1; x++)
		{
			
			Score[x] = Score[x] - 750;
			Pot += 750;
			a[1] = 1;
			a[5] = 750;
		}
	
	}

}


//カード
void Porker::CARD_SETTING()
{
	
	//最初に配られるカード敵味方それぞれ2枚ずつ
	
		P_Rand[0] =  GetRand(55);   //プレイヤーのホールカード1

		P_Rand[1] = GetRand(55);   //プレイヤーのホールカード2

		E_Rand[0] = GetRand(55);   //敵のホールカード1

		E_Rand[1] = GetRand(55);   //敵のホールカード2

	//2ターン目の三枚

		C_Rand[0] = GetRand(55);   //テーブルカード1

		C_Rand[1] = GetRand(55);   //テーブルカード2

		C_Rand[2] = GetRand(55);   //テーブルカード3

	//3ターン目の三枚

		C_Rand[3] = GetRand(55);   //テーブルカード4

	//4ターン目の三枚
	
		C_Rand[4] = GetRand(55);   //テーブルカード4


}


//カードのだぶり防止と計算
void Porker::CARD_SETTING2()
{
	//ダブり無し用



		if (P_Rand[0] == 0 || P_Rand[0] == 14 || P_Rand[0] == 28 || P_Rand[0] == 42) {
			P_Rand[0] = GetRand(55);
		}
		if (P_Rand[1] == 0 || P_Rand[1] == 14 || P_Rand[1] == 28 || P_Rand[1] == 42 || P_Rand[1] == P_Rand[0]) {
			P_Rand[1] = GetRand(55);
		}
		if (E_Rand[0] == 0 || E_Rand[0] == 14 || E_Rand[0] == 28 || E_Rand[0] == 42 || E_Rand[0] == P_Rand[0] ||
			E_Rand[0] == P_Rand[1]) {
			E_Rand[0] = GetRand(55);
		}
		if (E_Rand[1] == 0 || E_Rand[1] == 14 || E_Rand[1] == 28 || E_Rand[1] == 42 || E_Rand[1] == P_Rand[0] ||
			E_Rand[1] == P_Rand[1] || E_Rand[1] == E_Rand[0]) {
			E_Rand[1] = GetRand(55);
		}

		if (C_Rand[0] == 0 || C_Rand[0] == 14 || C_Rand[0] == 28 || C_Rand[0] == 42 || C_Rand[0] == P_Rand[0] ||
			C_Rand[0] == P_Rand[1] || C_Rand[0] == E_Rand[0] || C_Rand[0] == E_Rand[1]) {
			C_Rand[0] = GetRand(55);
		}
		if (C_Rand[1] == 0 || C_Rand[1] == 14 || C_Rand[1] == 28 || C_Rand[1] == 42 || C_Rand[1] == P_Rand[0] ||
			C_Rand[1] == P_Rand[1] || C_Rand[1] == E_Rand[0] || C_Rand[1] == E_Rand[1] || C_Rand[1] == C_Rand[0]) {
			C_Rand[1] = GetRand(55);
		}
		if (C_Rand[2] == 0 || C_Rand[2] == 14 || C_Rand[2] == 28 || C_Rand[2] == 42 || C_Rand[2] == P_Rand[0] ||
			C_Rand[2] == P_Rand[1] || C_Rand[2] == E_Rand[0] || C_Rand[2] == E_Rand[1] || C_Rand[2] == C_Rand[0] ||
			C_Rand[2] == C_Rand[1]) {
			C_Rand[2] = GetRand(55);
		}
		if (C_Rand[3] == 0 || C_Rand[3] == 14 || C_Rand[3] == 28 || C_Rand[3] == 42 || C_Rand[3] == P_Rand[0] ||
			C_Rand[3] == P_Rand[1] || C_Rand[3] == E_Rand[0] || C_Rand[3] == E_Rand[1] || C_Rand[3] == C_Rand[0] ||
			C_Rand[3] == C_Rand[1] || C_Rand[3] == C_Rand[2]) {
			C_Rand[3] = GetRand(55);
		}
		if (C_Rand[4] == 0 || C_Rand[4] == 14 || C_Rand[4] == 28 || C_Rand[4] == 42 || C_Rand[4] == P_Rand[0] ||
			C_Rand[4] == P_Rand[1] || C_Rand[4] == E_Rand[0] || C_Rand[4] == E_Rand[1] || C_Rand[4] == C_Rand[0] ||
			C_Rand[4] == C_Rand[1] || C_Rand[4] == C_Rand[2] || C_Rand[4] == C_Rand[3]) {
			C_Rand[4] = GetRand(55);
		}


}


//カード分析
void Porker::CARD_ANALAYSIS()
{
	//最初にRandでとった数を14で割る


		for (int i = 0; i < 2; i++) {
			P_CARD_A[i] = P_Rand[i] % 14;
			//もし余りが1だった場合エースになるので数字を14にして最強にする
			if (P_CARD_A[i] == 1)
			{
				P_CARD_A[i] = 14;
			}
			P_CARD_S[i] = P_Rand[i] / 14;
		}

		for (int j = 0; j < 2; j++) {
			E_CARD_A[j] = E_Rand[j] % 14;
			//もし余りが1だった場合エースになるので数字を14にして最強にする
			if (E_CARD_A[j] == 1)
			{
				E_CARD_A[j] = 14;
			}
			E_CARD_S[j] = E_Rand[j] / 14;
		}

		for (int c = 0; c < 5; c++) {
			//もし余りが1だった場合エースになるので数字を14にして最強にする
			C_CARD_A[c] = C_Rand[c] % 14;
			if (C_CARD_A[c] == 1)
			{
				C_CARD_A[c] = 14;
			}
			C_CARD_S[c] = C_Rand[c] / 14;
		}

		//プレイヤーのカード2枚でのペア
		if (P_CARD_A[0] == P_CARD_A[1])
		{
			P_PEA_FLG[0] = TRUE;
			Wait_TimeFLG[3] = TRUE;
		}
	

}


//カードのソート用
void Porker::CARD_SORT()
{
	

		P_SORT[0] = C_CARD_A[0];
		P_SORT[1] = C_CARD_A[1];
		P_SORT[2] = C_CARD_A[2];
		P_SORT[3] = C_CARD_A[3];
		P_SORT[4] = C_CARD_A[4];
		P_SORT[5] = P_CARD_A[0];
		P_SORT[6] = P_CARD_A[1];
		int sort;
		for (int a = 0; a <= 5; a++) {
			for (int b = a + 1; b <= 6; b++) {
				if (P_SORT[a] > P_SORT[b]) {
					sort = P_SORT[a];
					P_SORT[a] = P_SORT[b];
					P_SORT[b] = sort;
				}
			}
		}


		E_SORT[0] = C_CARD_A[0];
		E_SORT[1] = C_CARD_A[1];
		E_SORT[2] = C_CARD_A[2];
		E_SORT[3] = C_CARD_A[3];
		E_SORT[4] = C_CARD_A[4];
		E_SORT[5] = E_CARD_A[0];
		E_SORT[6] = E_CARD_A[1];
		int sort2;
		for (int a = 0; a <= 5; a++) {
			for (int b = a + 1; b <= 6; b++) {
				if (E_SORT[a] > E_SORT[b]) {
					sort2 = E_SORT[a];
					E_SORT[a] = E_SORT[b];
					E_SORT[b] = sort2;
				}
			}
		}




		P_SORT[7] = P_Rand[0];
		P_SORT[8] = P_Rand[1];
		P_SORT[9] = C_Rand[0];
		P_SORT[10] = C_Rand[1];
		P_SORT[11] = C_Rand[2];
		P_SORT[12] = C_Rand[3];
		P_SORT[13] = C_Rand[4];

		for (int x = 7; x <= 13; x++) 
		{
			if (P_SORT[x] == 1)
			{
				P_SORT[x] = 14;
			}
			if (P_SORT[x] == 15)
			{
				P_SORT[x] = 28;
			}
			if (P_SORT[x] == 29)
			{
				P_SORT[x] = 42;
			}
			if (P_SORT[x] == 43)
			{
				P_SORT[x] = 56;
			}
		}

		int sort5;
		for (int a = 7; a <= 12; a++) {
			for (int b = a + 1; b <= 13; b++) {
				if (P_SORT[a] > P_SORT[b]) {
					sort5 = P_SORT[a];
					P_SORT[a] = P_SORT[b];
					P_SORT[b] = sort5;
				}
			}
		}

		E_SORT[7] = E_Rand[0];
		E_SORT[8] = E_Rand[1];
		E_SORT[9] = C_Rand[0];
		E_SORT[10] = C_Rand[1];
		E_SORT[11] = C_Rand[2];
		E_SORT[12] = C_Rand[3];
		E_SORT[13] = C_Rand[4];
		int sort6;
		for (int a = 7; a <= 12; a++) {
			for (int b = a + 1; b <= 13; b++) {
				if (E_SORT[a] > E_SORT[b]) {
					sort6 = E_SORT[a];
					E_SORT[a] = E_SORT[b];
					E_SORT[b] = sort6;
				}
			}
		}
	

	if (Turn == 2) {
		P_SORT2[0] = P_CARD_A[0];
		P_SORT2[1] = P_CARD_A[1];
		P_SORT2[2] = C_CARD_A[0];
		P_SORT2[3] = C_CARD_A[1];
		P_SORT2[4] = C_CARD_A[2];

		int sort3;
		for (int a = 0; a <= 3; a++) {
			for (int b = a + 1; b <= 4; b++) {
				if (P_SORT2[a] > P_SORT2[b]) {
					sort3 = P_SORT2[a];
					P_SORT2[a] = P_SORT2[b];
					P_SORT2[b] = sort3;
				}
			}
		}
	}
	
	if (Turn == 3) {
		P_SORT3[0] = P_CARD_A[0];
		P_SORT3[1] = P_CARD_A[1];
		P_SORT3[2] = C_CARD_A[0];
		P_SORT3[3] = C_CARD_A[1];
		P_SORT3[4] = C_CARD_A[2];
		P_SORT3[5] = C_CARD_A[3];

		int sort4;
		for (int a = 0; a <= 4; a++) {
			for (int b = a + 1; b <= 5; b++) {
				if (P_SORT3[a] > P_SORT3[b]) {
					sort4 = P_SORT2[a];
					P_SORT3[a] = P_SORT3[b];
					P_SORT3[b] = sort4;
				}
			}
		}
	}
}




//確認UI
void Porker::UI()
{
	//他のUIが出ておらずYボタンを押したときベット
	if(PAD_INPUT::OnButton(XINPUT_BUTTON_Y) && CheckUI[1] == FALSE && CheckUI[2] == FALSE)
	{
		CheckUI[0] = TRUE;//ベットフラグ

	}


	//他のUIが出ておらずBボタンを押したときレイズ
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_B) && CheckUI[0] == FALSE && CheckUI[2] == FALSE)
	{
		CheckUI[1] = TRUE;
	}


	//他のUIが出ておらずXボタンを押したときフォールド
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_X) && CheckUI[1] == FALSE && CheckUI[0] == FALSE)
	{
		CheckUI[2] = TRUE;
		
	}




	//カーソルの左移動
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT)) {
		Cursor[0] = 1;//左
	}

	//カーソルの右移動
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT)) {
		Cursor[0] = 0;//右
	}

	//Aボタンで決定後
	if (Cursor[0] == 1)
	{
		//Aボタンで決定(ベット)
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_A) && CheckUI[0] == TRUE) {
			Player_Choice[0] = TRUE;//ベットフラグ
			Cursor[0] = 0;
			CheckUI[0] = FALSE;
		}

		//Aボタンで決定(レイズ)
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_A) && CheckUI[1] == TRUE) {
			Player_Choice[1] = TRUE;//レイズフラグ
			Cursor[0] = 0;
			CheckUI[1] = FALSE;
		}

		//Aボタンで決定(フォールド)
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_A) && CheckUI[2] == TRUE) {
			Player_Choice[2] = TRUE;//フォーカードフラグ
			Cursor[0] = 0;
			CheckUI[2] = FALSE;
		}
	}

	//Aボタンで拒否後
	if (Cursor[0] == 0)
	{
		//Aボタンで決定
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_A) && CheckUI[0] == TRUE) {
			CheckUI[0] = FALSE;
		}
		//Aボタンで決定
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_A) && CheckUI[1] == TRUE) {
			CheckUI[1] = FALSE;
		}
		//Aボタンで決定
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_A) && CheckUI[2] == TRUE) {
			CheckUI[2] = FALSE;
		}
	}
}


//プレイヤーの選択(ベット、レイズ、フォールド)
void Porker::PLAYER_CHOICE()
{
	
	//ベットなら
	if (Player_Choice[0] == TRUE)
	{
		//ラウンド1なら100
		if (Round_Count == 1) {
			Score[0] = Score[0] - 100;
			Pot = Pot + 100;
			a[2] = 100;
		}

		//ラウンド2なら200
		if (Round_Count == 2) {
			Score[0] = Score[0] - 200;
			Pot = Pot + 200;
			a[2] = 200;
			
		}

		//ラウンド3なら300
		if (Round_Count == 3) {
			Score[0] = Score[0] - 300;
			Pot = Pot + 300;
			a[2] = 300;
		}
		Wait_TimeFLG[0] = TRUE;
		

	}

	


	//レイズなら
	if (Player_Choice[1] == TRUE)
	{
		//ラウンド1なら200
		if (Round_Count == 1) {
			Score[0] = Score[0] - 200;
			Pot = Pot + 200;
			a[2] = 200;
		}

		//ラウンド2なら300
		if (Round_Count == 2) {
			Score[0] = Score[0] - 300; 
			Pot = Pot + 300;
			a[2] = 300;
		}

		//ラウンド3なら400
		if (Round_Count == 3) {
			Score[0] = Score[0] - 400;
			Pot = Pot + 400;
			a[2] = 400;
		}
		
		Wait_TimeFLG[0] = TRUE;
	
	}

	//フォールドなら敵のスコアにポットのスコアを加算してラウンドを加算
	if (Player_Choice[2] == TRUE)
	{
		Wait_TimeFLG[0] = TRUE;
	}

}


//敵の選択(コール、フォールド)
void Porker::ENEMY_CHOICE()
{
	//ランダムで敵の選択
	if (Poker_Second[0] == 120 && Action_UI != 3)
	{
		a[4] = GetRand(99);

		//90パーセントでコール
		if (a[4] <= 99)
		{
			Enemy_Choice[0] = TRUE;
			Action_UI = 4;
		
		}
		///*10%でフォールド*/
		//else if (a[4] >= 89)
		//{
		//	Enemy_Choice[1] = TRUE;
		//}



		//敵のコール
		if (Enemy_Choice[0] == TRUE) {

			//ラウンド1
			if (Round_Count == 1)
			{
				Score[1] = Score[1] - a[2];
				Pot = Pot + a[2];
			}

			//ラウンド2
			if (Round_Count == 2)
			{
				Score[1] = Score[1] - a[2];
				Pot = Pot + a[2];
			}

			//ラウンド3
			if (Round_Count == 3)
			{
				Score[1] = Score[1] - a[2];
				Pot = Pot + a[2];
			}

			Action_UI = 4; //コール表示
			Enemy_Choice[0] = FALSE;
		}

	}
}


//ラウンド終了の処理
void Porker::ROUND_END()
{

	
	if (Turn == 5 )
	{
		Wait_TimeFLG[2] = TRUE;
		
	}
	

	if(ShowDawn == TRUE && PAD_INPUT::OnButton(XINPUT_BUTTON_A))
	{
		Turn += 1;
	}
	if (ShowDawn == TRUE && PAD_INPUT::OnRelease(XINPUT_BUTTON_A))
	{
		Result = TRUE;
	}
	

	if(Result == TRUE && PAD_INPUT::OnButton(XINPUT_BUTTON_A))
	{
		Round_Count += 1;
		ROUND_INIT();
		
	}



}


//待ち時間関係
void Porker::WAIT_TIME()
{
	
	Poker_Second[4]++;
	if (Poker_Second[4] == 60)
	{
		Poker_Second[4] = 0;
	}
	

	if (Wait_TimeFLG[0] == TRUE)
	{
		Poker_Second[0]++;

		for (int x = 0; x <= 2; x++) {
			if (Poker_Second[0] >= 1 && Poker_Second[0] <= 120 && Player_Choice[x] == TRUE)
			{
				Action_UI = x + 1;
			}
		}

		if (Player_Choice[2] == TRUE && Poker_Second[0] >= 121)
		{
			Action_UI = 0;

			Poker_Second[0] = 0;

			Player_Choice[2] = FALSE;

			Result = TRUE;
			Score[1] += Pot;
			Pot = 0;

			Wait_TimeFLG[0] = FALSE;
		}


		for (int x = 0; x <= 1; x++) {
			if (Poker_Second[0] >= 121 && Enemy_Choice[x] == TRUE)
			{
				for (int x = 0; x <= 2; x++)
				{
					Player_Choice[x] = FALSE;
				}
				Action_UI = 4 + x;
			}
		}
		

		if (Poker_Second[0] == 240 && Action_UI != 5)
		{
			Action_UI = 0;
			for (int x = 0; x <= 2; x++)
			{
				Player_Choice[x] = FALSE;
			}
			Enemy_Choice[0] = FALSE;
			Poker_Second[0] = 0;
			Turn = Turn + 1;//ターン表示UI+1
			LastGame -= 1;  //残りゲーム数-1
			Wait_TimeFLG[0] = FALSE;
		}

		//敵がフォールド
		if (Poker_Second[0] == 240 && Action_UI == 5)
		{
			Action_UI = 0;

			Result = TRUE;
			Score[0] += Pot;
			Pot = 0;

			Wait_TimeFLG[0] = FALSE;
		}
	}

	//FB表示時間
	if (Wait_TimeFLG[1] == TRUE)
	{
		Poker_Second[1]++;

		if (Poker_Second[1] >= 1 && Poker_Second[1] <= 120)
		{
			FB_UI = 1;
		}

		if (Poker_Second[1] >= 121)
		{
			FB_UI = 2;
		}

		if (Poker_Second[1] == 240)
		{
			FB_UI = 0;

			Poker_Second[1] = 0;

			Wait_TimeFLG[1] = FALSE;
		}
	}
	
	//ショウダウン表示時間
	if (Wait_TimeFLG[2] == TRUE)
	{
		Poker_Second[2]++;
		ShowDawnUI = TRUE;

		if (Poker_Second[2] == 120)
		{
			ShowDawnUI = FALSE;
			ShowDawn = TRUE;
			Wait_TimeFLG[2] = FALSE;
			Poker_Second[2] = 0;
			Turn += 1;
		}
	}


	if (Wait_TimeFLG[3] == TRUE)
	{
		Poker_Second[3]++;
		if (Poker_Second[3] == 60) 
		{
			Poker_Second[3] = 0;
		}
	}
}


//ラウンド表示UI
void Porker::ROUND_UI()
{
	for (int x = 0; x <= 2; x++)
	{
		if (Round_UI == TRUE && Round_Count == x + 1 && PAD_INPUT::OnButton(XINPUT_BUTTON_A))
		{
			
			Round_UI = FALSE;
			Wait_TimeFLG[3] = FALSE;
		}
	}
}


//
void Porker::HAND()
{
	if (a[7] >= 0 && a[7] <= 9) {

		int x = 0;
		int y = 0;
		int z = 0;
		int v = 0;
		if (a[7] == 0) {
			//RSF
			for (x = 7; x <= 10; x++)
			{
				z = 1;
				P_Straight[0] = 0;
				for (y = x + 1; y <= 13; y++)
				{
					if (P_SORT[x] + z == P_SORT[y])
					{
						P_Straight[0] += 1;
						z += 1;

					}
				}
			}
			if (P_Straight[0] >= 4 && P_Straight[1] == 14 || P_Straight[1] == 28 || P_Straight[1] == 42 || P_Straight[1] == 56)
			{
				P_RSF_FLG = TRUE;
				
			}
			a[7] = 1;
		}



		




		//SF
		if (a[7] == 1&&P_RSF_FLG == FALSE)
		{


			for (x = 7; x <= 10; x++)
			{
				z = 1;
				P_Straight[2] = 0;
				for (y = x + 1; y <= 13; y++)
				{
					if (P_SORT[x] + z == P_SORT[y])
					{
						PP[0] = P_SORT[y];
						P_Straight[2] += 1;
						z += 1;
						if (P_Straight[2] >= 4)
						{
							P_SF_FLG = TRUE;
							
						}
					}
				}
			}
			a[7] = 2;
		}
		//4card
		if (a[7] == 2 && P_SF_FLG == FALSE && P_RSF_FLG == FALSE) {

			for (x = 0; x <= 3; x++)
			{
				for (y = x + 1; y <= 4; y++) {

					if (P_SORT[x] == P_SORT[y])
					{

						for (z = y + 1; z <= 5; z++) {

							if (P_SORT[y] == P_SORT[z])
							{

								for (v = z + 1; v <= 6; v++) {

									if (P_SORT[z] == P_SORT[v])
									{
										PP[0] = P_SORT[v];
										P_4CARD_FLG = TRUE;
										
									}
								}
							}
						}
					}

				}
			}
			a[7] = 3;
		}
		//fullhouse
		if (a[7] == 3 && P_4CARD_FLG == FALSE && P_SF_FLG == FALSE && P_RSF_FLG == FALSE)
		{
			for (x = 0; x <= 3; x++)
			{
				for (y = x + 1; y <= 4; y++) {

					if (P_SORT[x] == P_SORT[y])
					{

						for (z = y + 1; z <= 5; z++) {

							if (P_SORT[y] == P_SORT[z])
							{
								PP[0] = P_SORT[z];
								a[9] += 1;						
							}
							else if (P_SORT[y] != P_SORT[z])
							{
								PP[1] = P_SORT[y];
								a[8] += 1;
							}
						}
					}

				}
			}
			if (a[9] >= 1 && a[8] >= 1)
			{
				PP[0] = PP[0] + PP[1];
				P_FULLHOUSE_FLG = TRUE;
				
			}
			a[7] = 4;
		}
		//flash
		if (a[7] == 4 && P_FULLHOUSE_FLG == FALSE && P_4CARD_FLG == FALSE && P_SF_FLG == FALSE && P_RSF_FLG == FALSE)
		{
			if (P_CARD_A[0] < P_CARD_A[1])
			{
				PP[0] = P_CARD_A[1];
			}

			else if (P_CARD_A[0] > P_CARD_A[1])
			{
				PP[0] = P_CARD_A[0];
			}

			else if (P_CARD_A[0] == P_CARD_A[1])
			{
				PP[0] = P_CARD_A[0];
			}

			if (P_CARD_S[0] == P_CARD_S[1])
			{
				a[10] += 1;
				a[11] += 1;
			}
			for (x = 0; x <= 4; x++)
			{
				if (P_CARD_S[0] == C_CARD_S[x])
				{
					a[10] += 1;
				}
				if (P_CARD_S[1] == C_CARD_S[x])
				{
					a[11] += 1;
				}
			}
			if (a[10] >= 4 || a[11] >= 4)
			{
				P_FLASH_FLG = TRUE;
				
			}
			a[7] = 5;

		}
		//straight
		if (a[7] == 5 && P_FLASH_FLG == FALSE && P_FULLHOUSE_FLG == FALSE && P_4CARD_FLG == FALSE && P_SF_FLG == FALSE && P_RSF_FLG == FALSE)
		{

			for (x = 0; x <= 3; x++)
			{
				z = 1;
				P_Straight[3] = 0;
				for (y = x + 1; y <= 6; y++)
				{
					if (P_SORT[x] + z == P_SORT[y])
					{
						PP[0] = P_SORT[y];
						P_Straight[3] += 1;
						z += 1;
						if (P_Straight[3] >= 4)
						{
							P_STRAIGHT_FLG = TRUE;
							
						}
					}
				}
			}

			a[7] = 6;

		}
		//3card
		if (a[7] == 6 && P_STRAIGHT_FLG == FALSE && P_FLASH_FLG == FALSE && P_FULLHOUSE_FLG == FALSE && P_4CARD_FLG == FALSE && P_SF_FLG == FALSE && P_RSF_FLG == FALSE)
		{

			for (x = 0; x <= 3; x++)
			{
				for (y = x + 1; y <= 4; y++) {

					if (P_SORT[x] == P_SORT[y])
					{

						for (z = y + 1; z <= 5; z++) {

							if (P_SORT[y] == P_SORT[z])
							{
								PP[0] = P_SORT[z];
								P_3CARD_FLG = TRUE;
								
							}
						}
					}

				}
			}
			a[7] = 7;
		}
		//pea 2pea
		if (a[7] == 7 && P_3CARD_FLG == FALSE && P_STRAIGHT_FLG == FALSE && P_FLASH_FLG == FALSE && P_FULLHOUSE_FLG == FALSE && P_4CARD_FLG == FALSE && P_SF_FLG == FALSE && P_RSF_FLG == FALSE) {

			for (x = 0; x <= 5; x++)
			{
				for (y = x + 1; y <= 6; y++) {

					if (P_SORT[x] == P_SORT[y])
					{
						PP[0] = P_SORT[y];
						a[6] += 1;
						break;
					}

				}
			}

			if (a[6] == 1)
			{
				P_PEA_FLG[1] = TRUE;

			}
			else if (a[6] >= 2)
			{
				P_2PEA_FLG = TRUE;
				P_PEA_FLG[0] = FALSE;
			}
			a[7] = 8;
		}

		if (a[7] == 8 && P_PEA_FLG[0] == FALSE && P_PEA_FLG[1] == FALSE && P_2PEA_FLG == FALSE && P_3CARD_FLG == FALSE && P_STRAIGHT_FLG == FALSE && P_FLASH_FLG == FALSE && P_FULLHOUSE_FLG == FALSE && P_4CARD_FLG == FALSE && P_SF_FLG == FALSE && P_RSF_FLG == FALSE)
		{
			P_NOPEA_FLG = TRUE;
			if (P_CARD_A[0] < P_CARD_A[1])
			{
				PP[0] = P_CARD_A[1];
			}

			else if (P_CARD_A[0] > P_CARD_A[1])
			{
				PP[0] = P_CARD_A[0];
			}

			else if (P_CARD_A[0] == P_CARD_A[1])
			{
				PP[0] = P_CARD_A[0];
			}
			a[7] = 9;
		}

		a[7] = 10;


	}


		//enemy
		if (a[7] >= 10&& a[7] <=19 ) {

			int x = 0;
			int y = 0;
			int z = 0;
			int v = 0;

			if (a[7] == 10) {
				//RSF
				for (x = 7; x <= 10; x++)
				{
					z = 1;
					E_Straight[0] = 0;
					for (y = x + 1; y <= 13; y++)
					{
						if (E_SORT[x] + z == E_SORT[y])
						{
							E_Straight[0] += 1;
							z += 1;

						}
					}
				}

				if (E_Straight[0] >= 4 && E_Straight[1] == 14 || E_Straight[1] == 28 || E_Straight[1] == 42 || E_Straight[1] == 56)
				{
					E_RSF_FLG = TRUE;
				}
				a[7] = 11;
			}



			//SF
			if (a[7] == 11&&E_RSF_FLG == FALSE)
			{


				for (x = 7; x <= 10; x++)
				{
					z = 1;
					E_Straight[2] = 0;
					for (y = x + 1; y <= 13; y++)
					{
						if (E_SORT[x] + z == E_SORT[y])
						{
							EP[0] = E_SORT[y];
							E_Straight[2] += 1;
							z += 1;
							if (E_Straight[2] >= 4)
							{
								E_SF_FLG = TRUE;
								
							}
						}
					}
				}
				a[7] = 12;
			}
			//4card
			if (a[7] == 12 && E_SF_FLG == FALSE && E_RSF_FLG == FALSE) {

				for (x = 0; x <= 3; x++)
				{
					for (y = x + 1; y <= 4; y++) {

						if (E_SORT[x] == E_SORT[y])
						{

							for (z = y + 1; z <= 5; z++) {

								if (E_SORT[y] == E_SORT[z])
								{

									for (v = z + 1; v <= 6; v++) {

										if (E_SORT[z] == E_SORT[v])
										{
											EP[0] = E_SORT[y];
											E_4CARD_FLG = TRUE;
											
										}
									}
								}
							}
						}

					}
				}
				a[7] = 13;
			}
			//fullhouse
			if (a[7] == 13 && E_4CARD_FLG == FALSE && E_SF_FLG == FALSE && E_RSF_FLG == FALSE)
			{
				for (x = 0; x <= 3; x++)
				{
					for (y = x + 1; y <= 4; y++) {

						if (E_SORT[x] == E_SORT[y])
						{

							for (z = y + 1; z <= 5; z++) {

								if (E_SORT[y] == E_SORT[z])
								{
									EP[0] = E_SORT[y];
									a[13] += 1;	
								}
								else if (E_SORT[y] != E_SORT[z])
								{
									EP[1] = E_SORT[y];
									a[14] += 1;
								}
							}
						}

					}
				}
				if (a[13] >= 1 && a[14] >= 1)
				{
					E_FULLHOUSE_FLG = TRUE;
					
				}
				a[7] = 14;
			}
			//flash
			if (a[7] == 14 && E_FULLHOUSE_FLG == FALSE && E_4CARD_FLG == FALSE && E_SF_FLG == FALSE && E_RSF_FLG == FALSE)
			{
				if (E_CARD_A[0] < E_CARD_A[1])
				{
					EP[0] = E_CARD_A[1];
				}

				else if (E_CARD_A[0] > E_CARD_A[1])
				{
					EP[0] = E_CARD_A[0];
				}

				else if (E_CARD_A[0] == E_CARD_A[1])
				{
					EP[0] = E_CARD_A[0];
				}

				if (E_CARD_S[0] == E_CARD_S[1])
				{
					a[15] += 1;
					a[16] += 1;
				}
				for (x = 0; x <= 4; x++)
				{
					if (E_CARD_S[0] == C_CARD_S[x])
					{
						a[15] += 1;
					}
					if (E_CARD_S[1] == C_CARD_S[x])
					{
						a[16] += 1;
					}
				}
				if (a[15] >= 4 || a[16] >= 4)
				{
					E_FLASH_FLG = TRUE;
					
				}
				a[7] = 15;
			}
			//straight
			if (a[7] == 15 && E_FLASH_FLG == FALSE && E_FULLHOUSE_FLG == FALSE && E_4CARD_FLG == FALSE && E_SF_FLG == FALSE && E_RSF_FLG == FALSE)
			{

				for (x = 0; x <= 3; x++)
				{
					z = 1;
					E_Straight[3] = 0;
					for (y = x + 1; y <= 6; y++)
					{
						if (E_SORT[x] + z == E_SORT[y])
						{
							PP[0] = E_SORT[y];
							E_Straight[3] += 1;
							z += 1;
							if (E_Straight[3] >= 4)
							{
								E_STRAIGHT_FLG = TRUE;
								
							}
						}
					}
				}

				a[7] = 16;
				
			}
			//3card
			if (a[7] == 16&&E_STRAIGHT_FLG == FALSE && E_FLASH_FLG == FALSE && E_FULLHOUSE_FLG == FALSE && E_4CARD_FLG == FALSE && E_SF_FLG == FALSE && E_RSF_FLG == FALSE)
			{

				for (x = 0; x <= 3; x++)
				{
					for (y = x + 1; y <= 4; y++) {

						if (E_SORT[x] == E_SORT[y])
						{

							for (z = y + 1; z <= 5; z++) {

								if (E_SORT[y] == E_SORT[z])
								{
									PP[0] = E_SORT[z];
									E_3CARD_FLG = TRUE;
									
								}
							}
						}

					}
				}
				a[7] = 17;
			}
			//pea 2pea
			if (a[7] == 17 && E_3CARD_FLG == FALSE && E_STRAIGHT_FLG == FALSE && E_FLASH_FLG == FALSE && E_FULLHOUSE_FLG == FALSE && E_4CARD_FLG == FALSE && E_SF_FLG == FALSE && E_RSF_FLG == FALSE) {

				for (x = 0; x <= 5; x++)
				{
					for (y = x + 1; y <= 6; y++) {

						if (E_SORT[x] == E_SORT[y])
						{
							a[17] += 1;
							break;
						}

					}
				}

				if (a[17] == 1)
				{
					E_PEA_FLG[1] = TRUE;
					EP[0] = E_SORT[y];

				}
				else if (a[17] >= 2)
				{
					E_2PEA_FLG = TRUE;
					E_PEA_FLG[1] = FALSE;
					EP[0] = E_SORT[y];
				}
				a[7] = 18;
			}

			if (a[7] == 18 && E_PEA_FLG[0] == FALSE && E_PEA_FLG[1] == FALSE && E_2PEA_FLG == FALSE && E_3CARD_FLG == FALSE && E_STRAIGHT_FLG == FALSE && E_FLASH_FLG == FALSE && E_FULLHOUSE_FLG == FALSE && E_4CARD_FLG == FALSE && E_SF_FLG == FALSE && E_RSF_FLG == FALSE)
			{
				E_NOPEA_FLG = TRUE;
				if (E_CARD_A[0] < E_CARD_A[1])
				{
					EP[0] = E_CARD_A[1];
				}

				else if (E_CARD_A[0] > E_CARD_A[1])
				{
					EP[0] = E_CARD_A[0];
				}

				else if (E_CARD_A[0] == E_CARD_A[1])
				{
					EP[0] = E_CARD_A[0];
				}
				a[7] = 19;
			}

			

			a[7] = 20;

		}

	
}


//
void Porker::GAMEOVER()
{
	if (Round_Count == 4)
	{
		if (Score[0] > Score[1]) 
		{
			WL[0] = 1;
				GameOver = TRUE;
		}
		
		if (Score[0] < Score[1])
		{
			WL[0] = 2;
			GameOver = TRUE;
		}

		

	}
	
}


//
void Porker::WINANDLOSE()
{
	if (Turn >= 4&&a[7] == 20)
	{
		if (P_PEA_FLG[0] == TRUE || P_PEA_FLG[1] == TRUE)
		{
			W_point[0] = 1;
		}

		if (P_2PEA_FLG == TRUE )
		{
			W_point[0] = 2;
		}

		if (P_3CARD_FLG == TRUE)
		{
			W_point[0] = 3;
		}

		if (P_STRAIGHT_FLG == TRUE)
		{
			W_point[0] = 4;
		}

		if (P_FLASH_FLG == TRUE)
		{
			W_point[0] = 5;
		}

		if (P_FULLHOUSE_FLG == TRUE)
		{
			W_point[0] = 6;
		}

		if (P_4CARD_FLG == TRUE)
		{
			W_point[0] = 7;
		}

		if (P_SF_FLG == TRUE)
		{
			W_point[0] = 8;
		}

		if (P_RSF_FLG == TRUE)
		{
			W_point[0] = 9;
		}

		if (E_PEA_FLG[0] == TRUE || E_PEA_FLG[1] == TRUE)
		{
			W_point[1] = 1;
		}

		if (E_2PEA_FLG == TRUE)
		{
			W_point[1] = 2;
		}

		if (E_3CARD_FLG == TRUE)
		{
			W_point[1] = 3;
		}

		if (E_STRAIGHT_FLG == TRUE)
		{
			W_point[1] = 4;
		}

		if (E_FLASH_FLG == TRUE)
		{
			W_point[1] = 5;
		}

		if (E_FULLHOUSE_FLG == TRUE)
		{
			W_point[1] = 6;
		}

		if (E_4CARD_FLG == TRUE)
		{
			W_point[1] = 7;
		}

		if (E_SF_FLG == TRUE)
		{
			W_point[1] = 8;
		}

		if (E_RSF_FLG == TRUE)
		{
			W_point[1] = 9;
		}

		if (W_point[0] > W_point[1])
		{
			R_Win[0] = TRUE;
		}
		if (W_point[0] < W_point[1])
		{
			R_Win[1] = TRUE;
		}
		if (W_point[0] == W_point[1])
		{
			if (PP[0] > EP[0])
			{
				R_Win[0] = TRUE;
			}
			else if (PP[0] < EP[0])
			{
				R_Win[1] = TRUE;
			}
			else if (PP[0] == EP[0] &&a[28] == 0)
			{
				a[27]=GetRand(1);
				a[28] = 1;
				if (a[27] == 0)
				{
					R_Win[1] = TRUE;
				}

				else if (a[27] == 1) 
				{
					R_Win[0] = TRUE;
				}
			}
		}

		if (R_Win[0] == TRUE && Result == TRUE)
		{
			Score[0] = Pot + Score[0];
			Pot = 0;

		}
		if (R_Win[1] == TRUE && Result == TRUE)
		{
			Score[1] = Pot + Score[1];
			Pot = 0;
		}
	}


}


//アップデート
AbstractScene* Porker::Update()
{
	if (GameOver == TRUE && PAD_INPUT::OnButton(XINPUT_BUTTON_A))
	{
		return new GameSelect();
	}


	CARD_SETTING2();
	CARD_ANALAYSIS();
	CARD_SORT();
	HAND();
	ROUND_UI();
	WAIT_TIME();
	WINANDLOSE();
	GAMEOVER();
	if (Round_UI == FALSE) {

		FIRST_BET();
		
		ENEMY_CHOICE();
		ROUND_END();
		

		if (Wait_TimeFLG[0] == FALSE && Wait_TimeFLG[1] == FALSE && Wait_TimeFLG[2] == FALSE)
		{

			

			if (Turn < 5 && Result == FALSE && GameOver == FALSE)
			{
				PLAYER_CHOICE();
				UI();
			}

			
		}
	}
	return this;
}


//描画
void Porker::Draw() const
{

	DrawGraph(0, 0, BackGround[0], FALSE);

	


	//DrawString(1150, 20, "SCORE", 0x000000);
	SetFontSize(50);
	DrawFormatString(50, 80, 0xffffff, "%d", Round_Count);  //ラウンド数
	DrawFormatString(30, 329, 0xffffff, "%d", LastGame);  //ラウンド数
	/*DrawFormatString(10, 85, 0xffffff, "%d", Turn);   */       //ターン数
	DrawFormatString(1140, 580, /*0x000000,*/0xffffff, "%d", Score[0]); //プレイヤーのスコア
	DrawFormatString(1140, 110, /*0x000000,*/0xffffff, "%d", Score[1]);  //敵のスコア
	DrawFormatString(1140, 350, /*0x000000,*/0xffffff, "%d", Pot);          //賭けてるスコアの合計



	if (Turn >= 4 && P_RSF_FLG == TRUE)
	{
		SetFontSize(40);
		if (Poker_Second[4] >= 0 && Poker_Second[4] <= 20) {
			DrawString(905, 560, "ROYAL", 0x0055ff, TRUE);
		}
		if (Poker_Second[4] >= 20 && Poker_Second[4] <= 40) {
			DrawString(870, 610, "STRAIGHT", 0xffff1a, TRUE);
		}
		if (Poker_Second[4] >= 40 && Poker_Second[4] <= 60) {
			DrawString(905, 660, "FLUSH", 0xff0000, TRUE);
		}
	}




	if (Turn >= 4 && P_SF_FLG == TRUE)
	{
		SetFontSize(40);
		if (Poker_Second[4] >= 30) {
			DrawString(870, 580, "STRAIGHT", 0xffff1a, TRUE);
			DrawString(905, 630, "FLUSH", 0xffff1a, TRUE);
			DrawString(910, 530, "", 0xffff1a, TRUE);
			DrawString(950, 530, "", 0xffff1a, TRUE);
		}
	}

	if (Turn >= 4 && P_4CARD_FLG == TRUE)
	{
		SetFontSize(40);
		if (Poker_Second[4] >= 30) {
			DrawString(910, 550, "FOUR", 0xffff1a, TRUE);
			DrawString(910, 600, "OF A", 0xffff1a, TRUE);
			DrawString(915, 650, "KIND", 0xffff1a, TRUE);
			DrawString(910, 530, "", 0xffff1a, TRUE);
			DrawString(950, 530, "", 0xffff1a, TRUE);
		}
	}


	if (Turn >= 4 && P_FULLHOUSE_FLG == TRUE)
	{
		SetFontSize(40);
		if (Poker_Second[4] >= 30) {
			DrawString(920, 570, "FULL", 0xff0000, TRUE);
			DrawString(910, 640, "HOUSE", 0xff0000, TRUE);
		}
	}

	if (Turn >= 4 && P_FLASH_FLG == TRUE)
	{
		SetFontSize(40);
		DrawString(890, 600, "FLUSH", 0x00ff2b, TRUE);
	}
	
	if (Turn >= 4 && P_STRAIGHT_FLG == TRUE)
	{
		SetFontSize(40);
		DrawString(870, 600, "STRAIGHT", 0xffff00, TRUE);
	}

	if (Turn >= 4 && P_3CARD_FLG == TRUE)
	{
		SetFontSize(40);
		DrawString(900, 550, "THREE", 0x0055ff, TRUE);
		DrawString(930, 600, "OF", 0x0055ff, TRUE);
		DrawString(915, 650, "KIND", 0x0055ff, TRUE);
	}
	if (Turn >= 4 && P_2PEA_FLG == TRUE)
	{
		SetFontSize(40);
		DrawString(870, 600, "TWO PAIR", 0xffffff, TRUE);
	}
	if (Turn >= 4 && P_PEA_FLG[0] == TRUE || Turn >= 4 && P_PEA_FLG[1] == TRUE&& P_2PEA_FLG == FALSE)
	{
		SetFontSize(40);
		DrawString(870, 600, "ONE PAIR", 0xffffff, TRUE);
	}
	if (Turn >= 4 &&P_NOPEA_FLG == TRUE)
	{
		SetFontSize(40);
		DrawString(880, 600, "NO PAIR", 0xffffff, TRUE);
	}


	if (ShowDawn == FALSE)
	{
		SetFontSize(40);
		DrawString(900, 100, "? ? ?", 0xffffff, TRUE);
	}

	if (ShowDawn == TRUE && E_RSF_FLG == TRUE)
	{
		SetFontSize(40);
		if (Poker_Second[4] >= 0 && Poker_Second[4] <= 20) {
			DrawString(905, 80, "ROYAL", 0x0055ff, TRUE);
		}
		if (Poker_Second[4] >= 20 && Poker_Second[4] <= 40) {
			DrawString(870, 100, "STRAIGHT", 0xffff1a, TRUE);
		}
		if (Poker_Second[4] >= 40 && Poker_Second[4] <= 60) {
			DrawString(905, 120, "FLUSH", 0xff0000, TRUE);
		}
	}
	
		if (ShowDawn == TRUE && E_SF_FLG == TRUE)
		{
			SetFontSize(40);
			if (Poker_Second[4] >= 30) {
				DrawString(870, 100, "STRAIGHT", 0xffff1a, TRUE);
				DrawString(905, 120, "FLUSH", 0xffff1a, TRUE);
				DrawString(910, 530, "", 0xffff1a, TRUE);
				DrawString(950, 530, "", 0xffff1a, TRUE);
			}
		}

		if (ShowDawn == TRUE && E_4CARD_FLG == TRUE)
		{
			SetFontSize(40);
			if (Poker_Second[4] >= 30) {
				DrawString(910, 80, "FOUR", 0xffff1a, TRUE);
				DrawString(910, 100, "OF A", 0xffff1a, TRUE);
				DrawString(915, 120, "KIND", 0xffff1a, TRUE);
				DrawString(910, 530, "", 0xffff1a, TRUE);
				DrawString(950, 530, "", 0xffff1a, TRUE);
			}
		}


		if (ShowDawn == TRUE && E_FULLHOUSE_FLG == TRUE)
		{
			SetFontSize(40);
			if (Poker_Second[4] >= 30) {
				DrawString(920, 100, "FULL", 0xff0000, TRUE);
				DrawString(910, 120, "HOUSE", 0xff0000, TRUE);
			}
		}

		if (ShowDawn == TRUE && E_FLASH_FLG == TRUE)
		{
			SetFontSize(40);
			DrawString(890, 100, "FLUSH", 0x00ff2b, TRUE);
		}

		if (ShowDawn == TRUE && E_STRAIGHT_FLG == TRUE)
		{
			SetFontSize(40);
			DrawString(870, 100, "STRAIGHT", 0xffff00, TRUE);
		}

		if (ShowDawn == TRUE && E_3CARD_FLG == TRUE)
		{
			SetFontSize(40);
			DrawString(900, 80, "THREE", 0x0055ff, TRUE);
			DrawString(930, 100, "OF", 0x0055ff, TRUE);
			DrawString(915, 120, "KIND", 0x0055ff, TRUE);
		}
		if (ShowDawn == TRUE && E_2PEA_FLG == TRUE)
		{
			SetFontSize(40);
			DrawString(870, 100, "TWO PAIR", 0xffffff, TRUE);
		}
		if (ShowDawn == TRUE && E_PEA_FLG[0] == TRUE && E_2PEA_FLG == FALSE || ShowDawn == TRUE && E_PEA_FLG[1] == TRUE && E_2PEA_FLG == FALSE)
		{
			SetFontSize(40);
			DrawString(870, 100, "ONE PAIR", 0xffffff, TRUE);
		}
		if (ShowDawn == TRUE && E_NOPEA_FLG == TRUE)
		{
			SetFontSize(40);
			DrawString(880, 100, "NO PAIR", 0xffffff, TRUE);
		}
	

	                           //カード//
	SetFontSize(30);
	DrawGraph(460, 495, Tranpu_Img[P_Rand[0]], TRUE); //プレイヤーのカード1
	DrawGraph(635, 495, Tranpu_Img[P_Rand[1]], TRUE); //プレイヤーのカード2

	//ショウダウンしたら現れる
	if (ShowDawn == TRUE)
	{
		DrawGraph(460, -10, Tranpu_Img[E_Rand[0]], TRUE);   //敵のカード1
		DrawGraph(635, -10, Tranpu_Img[E_Rand[1]], TRUE);   //敵のカード2

	}

	//ショウダウンしたら消える
	if (ShowDawn == FALSE) 
	{
		DrawGraph(460, -10, Tranpu_Img[0], TRUE);           //敵の裏カード1
		DrawGraph(635, -10, Tranpu_Img[0], TRUE);           //敵の裏カード2
	}
	

	if (Turn >=2)
	{
		DrawGraph(150, 225, Tranpu_Img[C_Rand[0]], TRUE);   //テーブルカード1
		DrawGraph(350, 225, Tranpu_Img[C_Rand[1]], TRUE);   //テーブルカード2
		DrawGraph(550, 225, Tranpu_Img[C_Rand[2]], TRUE);   //テーブルカード3	

		
		

	}
	if (Turn >= 3)
	{
		DrawGraph(750, 225, Tranpu_Img[C_Rand[3]], TRUE);   //テーブルカード4
	}
	if (Turn >= 4)
	{
		DrawGraph(950, 225, Tranpu_Img[C_Rand[4]], TRUE);   //テーブルカード3
	}


	                       //リザルト画面//

	if (Result == TRUE)
	{
		DrawBox(0, 0, 1280, 720, 0xffffff, TRUE);
		SetFontSize(40);
		DrawString(580, 60, "RESULT", 0x000000, TRUE);
		

		if (R_Win[0] == TRUE)
		{
			//ROUND WIN
				SetFontSize(36);
				DrawString(580, 200, "YOU WIN", 0x000000, TRUE);
				DrawFormatString(100, 400, 0xff0000, "PLAYER'S SCORE: %d", Score[0], TRUE);
				DrawFormatString(780, 400, 0x6445ff, "ENEMY'S SCORE: %d", Score[1], TRUE);
				if (Round_Count !=3) {
					DrawString(450, 550, "[X]BUTTON-NEXT ROUND", 0x000000, TRUE);
				}
				else if (Round_Count == 3) {
					DrawString(450, 550, "[X]BUTTON-GAME OVER", 0x000000, TRUE);
				}
			
		}
		if (R_Win[1] == TRUE)
		{
			//ROUND LOSE
			SetFontSize(36);
			DrawString(580, 200, "YOU LOSE", 0x000000, TRUE);
			DrawFormatString(100, 400, 0x6445ff, "PLAYER'S SCORE: %d", Score[0], TRUE);
			DrawFormatString(780, 400, 0xff0000, "ENEMY'S SCORE: %d", Score[1], TRUE);
			if (Round_Count != 3) {
				DrawString(450, 550, "[X]BUTTON-NEXT ROUND", 0x000000, TRUE);
			}
			else if (Round_Count == 3) {
				DrawString(450, 550, "[X]BUTTON-GAME OVER", 0x000000, TRUE);
			}
		}
	}


	if (GameOver == TRUE)
	{
		
		if (WL[0] == 1) {
			DrawBox(0, 0, 1280, 720, 0xffffff, TRUE);
			SetFontSize(40);
			DrawString(580, 200, "YOUWIN", 0x000000, TRUE);
			SetFontSize(30);
			DrawString(480, 650, "A_BUTTON-Game Select", 0xffffff, TRUE);
		}

		if (WL[0] == 2) {
			DrawBox(0, 0, 1280, 720, 0x000000, TRUE);
			SetFontSize(40);
			DrawString(570, 200, "YOULOSE", 0xffffff, TRUE);
			SetFontSize(30);
			DrawString(480, 650, "A_BUTTON-Game Select", 0xffffff, TRUE);
		}
	}



	                        //      UI     //

	//ショウダウンUI
	if (ShowDawnUI == TRUE)
	{
		DrawBox(250, 250, 980, 500, 0xffffff, TRUE);
		DrawBox(250, 250, 980, 500, 0x000000, FALSE);
		SetFontSize(50);
		DrawString(520, 300, "SHOW DAWN", 0x000000, TRUE);
	}


	//Round1表示UI
	if (Round_UI == TRUE && Round_Count == 1)
	{
		DrawBox(0, 0, 1280, 720, 0x000000, TRUE);
		//11pea
		if (P_PEA_FLG[0] == TRUE && P_CARD_A[0] == 11)
		{
			if (Poker_Second[3] >= 30) {
				SetFontSize(40);
				DrawString(580, 100, "ROUND1", 0x0055ff, TRUE);
				SetFontSize(30);
				DrawString(485, 650, "Press the A button", 0x0055ff, TRUE);
			}
		}
	
		//12pea
		else if (P_PEA_FLG[0] == TRUE && P_CARD_A[0] == 12)
		{
			if (Poker_Second[3] >= 30) {
				SetFontSize(40);
				DrawString(580, 100, "ROUND1", 0xffff00, TRUE);
				SetFontSize(30);
				DrawString(485, 650, "Press the A button", 0xffff00, TRUE);
			}
		}

		//13pea
		else if (P_PEA_FLG[0] == TRUE && P_CARD_A[0] == 13)
		{
			
			if (Poker_Second[3] >= 30) {
				SetFontSize(40);
				DrawString(580, 100, "ROUND1", 0x00ff2b, TRUE);
				SetFontSize(30);
				DrawString(485, 650, "Press the A button", 0x00ff2b, TRUE);
			}
			
				SetFontSize(60);
				DrawString(530, 320, "CHANCE!", 0x00ff2b, TRUE);
			
			
		}

		//14pea
		else if (P_PEA_FLG[0] == TRUE && P_CARD_A[0] == 14)
		{
	
			if (Poker_Second[3] >= 30) {
				SetFontSize(40);
				DrawString(580, 100, "ROUND1", 0xff0000, TRUE);
				SetFontSize(30);
				DrawString(485, 650, "Press the A button", 0xff0000, TRUE);
			}

			
				SetFontSize(70);
				DrawString(450, 350, "SUPER HOT!!", 0xff0000, TRUE);
		
		}

		//nomal pea
		else if (P_PEA_FLG[0] == TRUE && P_CARD_A[0] <= 10) {
			if (Poker_Second[3] >= 30) {
				SetFontSize(40);
				DrawString(580, 100, "ROUND1", 0xffffff, TRUE);
				SetFontSize(30);
				DrawString(485, 650, "Press the A button", 0xffffff, TRUE);
			}
		}

		//no pea
		else if (P_PEA_FLG[0] == FALSE) {
			SetFontSize(40);
			DrawString(580, 100, "ROUND1", 0xffffff, TRUE);
			SetFontSize(30);
			DrawString(485, 650, "Press the A button", 0xffffff, TRUE);
		}

		//RSF
		if (P_RSF_FLG == TRUE)
		{
			DrawGraph(0, 0, BackGround[2], FALSE);
			SetFontSize(40);
			DrawString(580, 100, "ROUND1", 0x000000, TRUE);
			SetFontSize(30);
			DrawString(485, 650, "Press the A button", 0x000000, TRUE);
		}
	}
	//Round2表示UI
	if (Round_UI == TRUE && Round_Count == 2)
	{
		DrawBox(0, 0, 1280, 720, 0x000000, TRUE);
		//11pea
		if (P_PEA_FLG[0] == TRUE && P_CARD_A[0] == 11)
		{
			if (Poker_Second[3] >= 30) {
				SetFontSize(40);
				DrawString(580, 100, "ROUND2", 0x0055ff, TRUE);
				SetFontSize(30);
				DrawString(485, 650, "Press the A button", 0x0055ff, TRUE);
			}
		}

		//12pea
		else if (P_PEA_FLG[0] == TRUE && P_CARD_A[0] == 12)
		{
			if (Poker_Second[3] >= 30) {
				SetFontSize(40);
				DrawString(580, 100, "ROUND2", 0xffff00, TRUE);
				SetFontSize(30);
				DrawString(485, 650, "Press the A button", 0xffff00, TRUE);
			}
		}

		//13pea
		else if (P_PEA_FLG[0] == TRUE && P_CARD_A[0] == 13)
		{

			if (Poker_Second[3] >= 30) {
				SetFontSize(40);
				DrawString(580, 100, "ROUND1", 0x00ff2b, TRUE);
				SetFontSize(30);
				DrawString(485, 650, "Press the A button", 0x00ff2b, TRUE);
			}
			
				SetFontSize(60);
				DrawString(530, 320, "CHANCE!", 0x00ff2b, TRUE);
			

		}

		//14pea
		else if (P_PEA_FLG[0] == TRUE && P_CARD_A[0] == 14)
		{

			if (Poker_Second[3] >= 30) {
				SetFontSize(40);
				DrawString(580, 100, "ROUND2", 0xff0000, TRUE);
				SetFontSize(30);
				DrawString(485, 650, "Press the A button", 0xff0000, TRUE);
			}

			
				SetFontSize(70);
				DrawString(450, 350, "SUPER HOT!!", 0xff0000, TRUE);
			
		}

		//nomal pea
		else if (P_PEA_FLG[0] == TRUE && P_CARD_A[0] <= 10) {
			if (Poker_Second[3] >= 30) {
				SetFontSize(40);
				DrawString(580, 100, "ROUND2", 0xffffff, TRUE);
				SetFontSize(30);
				DrawString(485, 650, "Press the A button", 0xffffff, TRUE);
			}
		}

		//no pea
		else if (P_PEA_FLG[0] == FALSE) {
			SetFontSize(40);
			DrawString(580, 100, "ROUND2", 0xffffff, TRUE);
			SetFontSize(30);
			DrawString(485, 650, "Press the A button", 0xffffff, TRUE);
		}
	}
	//Round3表示UI
	if (Round_UI == TRUE && Round_Count == 3)
	{
		DrawBox(0, 0, 1280, 720, 0x000000, TRUE);
		//11pea
		if (P_PEA_FLG[0] == TRUE && P_CARD_A[0] == 11)
		{
			if (Poker_Second[3] >= 30) {
				SetFontSize(40);
				DrawString(580, 100, "ROUND3", 0x0055ff, TRUE);
				SetFontSize(30);
				DrawString(485, 650, "Press the A button", 0x0055ff, TRUE);
			}
		}

		//12pea
		else if (P_PEA_FLG[0] == TRUE && P_CARD_A[0] == 12)
		{
			if (Poker_Second[3] >= 30) {
				SetFontSize(40);
				DrawString(580, 100, "ROUND3", 0xffff00, TRUE);
				SetFontSize(30);
				DrawString(485, 650, "Press the A button", 0xffff00, TRUE);
			}
		}

		//13pea
		else if (P_PEA_FLG[0] == TRUE && P_CARD_A[0] == 13)
		{

			if (Poker_Second[3] >= 30) {
				SetFontSize(40);
				DrawString(580, 100, "ROUND3", 0x00ff2b, TRUE);
				SetFontSize(30);
				DrawString(485, 650, "Press the A button", 0x00ff2b, TRUE);
			}
			
				SetFontSize(60);
				DrawString(530, 320, "CHANCE!", 0x00ff2b, TRUE);
			

		}

		//14pea
		else if (P_PEA_FLG[0] == TRUE && P_CARD_A[0] == 14)
		{

			if (Poker_Second[3] >= 30) {
				SetFontSize(40);
				DrawString(580, 100, "ROUND3", 0xff0000, TRUE);
				SetFontSize(30);
				DrawString(485, 650, "Press the A button", 0xff0000, TRUE);
			}

		
				SetFontSize(70);
				DrawString(450, 350, "SUPER HOT!!", 0xff0000, TRUE);
			
		}

		//nomal pea
		else if (P_PEA_FLG[0] == TRUE && P_CARD_A[0] <= 10) {
			if (Poker_Second[3] >= 30) {
				SetFontSize(40);
				DrawString(580, 100, "ROUND3", 0xffffff, TRUE);
				SetFontSize(30);
				DrawString(485, 650, "Press the A button", 0xffffff, TRUE);
			}
		}

		//no pea
		else if (P_PEA_FLG[0] == FALSE) {
			SetFontSize(40);
			DrawString(580, 100, "ROUND3", 0xffffff, TRUE);
			SetFontSize(30);
			DrawString(485, 650, "Press the A button", 0xffffff, TRUE);
		}
	}


	//FB表示UI
	if (FB_UI == 1)
	{
		DrawBox(300, 200, 980, 500, 0x00d5ff, TRUE);
		DrawBox(300, 200, 980, 500, 0x000000, FALSE);
		SetFontSize(30);
		DrawString(510, 230, "PLAYER'S BLIND BET", 0x000000, TRUE);
		DrawFormatString(580, 340, 0x000000,"COST:%d",a[5]);
		DrawFormatString(350, 450, 0x000000, "SCORE:%d", Score[0] + a[5]);
		DrawString(620, 450, "→", 0x000000, TRUE);
		DrawFormatString(800, 450, 0x000000, "SCORE:%d", Score[0]);
	}
	if (FB_UI == 2)
	{
		DrawBox(300, 200, 980, 500, 0xff00aa, TRUE);
		DrawBox(300, 200, 980, 500, 0x000000, FALSE);
		SetFontSize(30);
		DrawString(515, 230, "ENEMY'S BLIND BET", 0x000000, TRUE);
		DrawFormatString(580, 340, 0x000000, "COST:%d", a[5]);
		DrawFormatString(350, 450, 0x000000, "SCORE:%d", Score[1] + a[5]);
		DrawString(620, 450, "→", 0x000000, TRUE);
		DrawFormatString(800, 450, 0x000000, "SCORE:%d", Score[1]);
	}


	//ベット確認UI
	if (CheckUI[0] == TRUE) 
	{
		DrawBox(0, 0, 1280, 720, 0x000000, TRUE);
		SetFontSize(40);
		DrawString(470, 150, "ベットしますか？", 0xffffff, TRUE);
		DrawString(250, 450, "YES", 0xffffff, TRUE);
		DrawString(1000, 450, "NO", 0xffffff, TRUE);
		SetFontSize(30);
		DrawString(420, 650, "十字キーで選択,Aボタンで決定", 0xffffff, TRUE);
		

		//左入力
		if (Cursor[0] == 1) 
		{
			DrawTriangle(180, 420, 210, 470, 180, 520, GetColor(255, 0, 0), TRUE);

		}
		//右入力
		if (Cursor[0] == 0)
		{
			DrawTriangle(930, 420, 960, 470, 930, 520, GetColor(255, 0, 0), TRUE);

		}
		
	}
	
	//レイズ確認UI
	if (CheckUI[1] == TRUE)
	{
		DrawBox(0, 0, 1280, 720, 0x000000, TRUE);
		SetFontSize(40);
		DrawString(470, 150, "レイズしますか？", 0xffffff, TRUE);
		DrawString(250, 450, "YES", 0xffffff, TRUE);
		DrawString(1000, 450, "NO", 0xffffff, TRUE);
		SetFontSize(30);
		DrawString(420, 650, "十字キーで選択,Aボタンで決定", 0xffffff, TRUE);
		//左入力
		if (Cursor[0] == 1)
		{
			DrawTriangle(180, 420, 210, 470, 180, 520, GetColor(255, 0, 0), TRUE);
		}
		//右入力
		if (Cursor[0] == 0)
		{
			DrawTriangle(930, 420, 960, 470, 930, 520, GetColor(255, 0, 0), TRUE);
		}
	}

	//フォールド確認UI
	if (CheckUI[2] == TRUE)
	{
		DrawBox(0, 0, 1280, 720, 0x000000, TRUE);
		SetFontSize(40);
		DrawString(460, 150, "フォールドしますか？", 0xffffff, TRUE);
		DrawString(250, 450, "YES", 0xffffff, TRUE);
		DrawString(1000, 450, "NO", 0xffffff, TRUE);
		SetFontSize(30);
		DrawString(420, 650, "十字キーで選択,Aボタンで決定", 0xffffff, TRUE);
		//左入力
		if (Cursor[0] == 1)
		{
			DrawTriangle(180, 420, 210, 470, 180, 520, GetColor(255, 0, 0), TRUE);
		}
		//右入力
		if (Cursor[0] == 0)
		{
			DrawTriangle(930, 420, 960, 470, 930, 520, GetColor(255, 0, 0), TRUE);
		}
	}

	//ベット表示UI
	if (Action_UI == 1)
	{
		DrawBox(300, 200, 980, 500, 0x00d5ff, TRUE);
		DrawBox(300, 200, 980, 500, 0x000000, FALSE);
		SetFontSize(30);
		DrawString(600, 200, "Player", 0x000000, TRUE);
		DrawString(620, 300, "BET", 0x000000, TRUE);
		DrawFormatString(350, 400, 0x000000, "SCORE:%d", Score[0] + a[2]);
		DrawString(620, 400, "→", 0x000000, TRUE);
		DrawFormatString(800, 400, 0x000000, "SCORE:%d", Score[0]);
	}

	//レイズ表示UI
	if (Action_UI == 2)
	{

		DrawBox(300, 200, 980, 500, 0x00d5ff, TRUE);
		DrawBox(300, 200, 980, 500, 0x000000, FALSE);
		SetFontSize(30);
		DrawString(600, 200, "Player", 0x000000, TRUE);
		DrawString(610, 300, "RAISE", 0x000000, TRUE);
		DrawFormatString(350, 400, 0x000000, "SCORE:%d", Score[0] + a[2]);
		DrawString(620, 400, "→", 0x000000, TRUE);
		DrawFormatString(800, 400, 0x000000, "SCORE:%d", Score[0]);
	}

	//フォールド表示UI
	if (Action_UI == 3)
	{
		DrawBox(300, 200, 980, 500, 0x00d5ff, TRUE);
		DrawBox(300, 200, 980, 500, 0x000000, FALSE);
		SetFontSize(30);
		DrawString(600, 200, "Player", 0x000000, TRUE);
		DrawString(610, 300, "FOLD", 0x000000, TRUE);
		DrawFormatString(350, 400, 0x000000, "SCORE:%d", Score[0] + a[2]);
		DrawString(620, 400, "→", 0x000000, TRUE);
		DrawFormatString(800, 400, 0x000000, "SCORE:%d", Score[0]);
	}

	//敵コール表示UI
	if (Action_UI == 4)
	{
		DrawBox(300, 200, 980, 500, 0xff00aa, TRUE);
		DrawBox(300, 200, 980, 500, 0x000000, FALSE);
		SetFontSize(30);
		DrawString(600, 200, "ENEMY", 0x000000, TRUE);
		DrawString(605, 300, "CALL", 0x000000, TRUE);
		DrawFormatString(350, 400, 0x000000, "SCORE:%d", Score[1] + a[2]);
		DrawString(620, 400, "→", 0x000000, TRUE);
		DrawFormatString(800, 400, 0x000000, "SCORE:%d", Score[1]);
	}

	//敵フォールド表示UI
	if (Action_UI == 5)
	{
		DrawBox(300, 200, 980, 500, 0xff00aa, TRUE);
		DrawBox(300, 200, 980, 500, 0x000000, FALSE);
		SetFontSize(30);
		DrawString(600, 200, "ENEMY", 0x000000, TRUE);
		DrawString(605, 300, "FOLD", 0x000000, TRUE);
		DrawFormatString(350, 400, 0x000000, "SCORE:%d", Score[1] + a[2]);
		DrawString(620, 400, "→", 0x000000, TRUE);
		DrawFormatString(800, 400, 0x000000, "SCORE:%d", Score[1]);
	}


}


