#include "Porker.h"
#include"DxLib.h"
#include"PadInput.h"
#include<stdlib.h>
#include"math.h"


Porker::Porker()
{
	
	Round_Count = 1;//ラウンド数
	
	ROUND_INIT();//ラウンド初期化
}


Porker::~Porker()
{

}


//ラウンド初期化
void Porker::ROUND_INIT()
{

  //賭けてるスコアの合計　
  Pot = 0;         


  Wait_TimeFLG = FALSE;


   //もしラウンドが1なら初期所持スコアは1000になる Score[0]がプレイヤー、Score[1]が敵
  if (Round_Count == 1) {             
	  for (int x = 0; x <= 1; x++)
	  {
		  Score[x] = 2500;           
	  }
  }


  // 適当な変数の箱用
  for (int x = 0; x <= 9; x++)
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


  //敵の選択(0がコール、1がレイズ、2がフォールド)
  for (int x = 0; x <= 2; x++)
  {
	  Enemy_Choice[x] = FALSE;
  }


  //待機時間用
  for (int x = 0; x <= 1; x++)
  {
	  Poker_Second[x] = FALSE;
  }

}


//最初に払う参加費
void Porker::FIRST_BET()
{
	//ラウンド1
	if (Round_Count == 1 && a[1] == 0)
	{
		for (int x = 0; x <= 1; x++)
		{
			Score[x] = Score[x] - 100;
			Pot += 100;

		}
		a[1] = 1;
	}

	//ラウンド2
	if (Round_Count == 2 && a[1] == 1)
	{
		for (int x = 0; x <= 1; x++)
		{
			Score[x] = Score[x] - 100;
			Pot += 200;
		}
		a[1] = 2;
	}

	//ラウンド3
	if (Round_Count == 3 && a[1] == 2)
	{
		for (int x = 0; x <= 1; x++)
		{
			Score[x] = Score[x] - 500;
			Pot += 400;
		}
		a[1] = 3;
	}

}


//ラウンド事の処理
void Porker::ROUND()
{
	//1ラウンド目




}


//カード
void Porker::CARD_SETTING()
{
	//最初に配られるカード敵味方それぞれ2枚ずつ
	if (a[0] == 0) {
		P_Rand[0] = GetRand(55);   //プレイヤーのホールカード1

		P_Rand[1] = GetRand(55);   //プレイヤーのホールカード2

		E_Rand[0] = GetRand(55);   //敵のホールカード1

		E_Rand[1] = GetRand(55);   //敵のホールカード2

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
		a[0] = 1;
	}

	//最初にRandでとった数を14で割る
	if (a[0] == 1) 
	{
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
	}



	C_Rand[0] = GetRand(55);   //コミュニティカード1

	C_Rand[1] = GetRand(55);   //コミュニティカード2

	C_Rand[2] = GetRand(55);   //コミュニティカード3

	C_Rand[3] = GetRand(55);   //コミュニティカード4

	C_Rand[4] = GetRand(55);  //コミュニティカード5   

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
			Player_Choice[1] = TRUE;//ベットフラグ
			Cursor[0] = 0;
			CheckUI[1] = FALSE;
		}

		//Aボタンで決定(フォールド)
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_A) && CheckUI[2] == TRUE) {
			Player_Choice[2] = TRUE;//ベットフラグ
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
		//ラウンド1なら
		if (Round_Count == 1) {
			Score[0] = Score[0] - 100;
			Pot = Pot + 100;
		}

		//ラウンド2なら
		if (Round_Count == 2) {
			Score[0] = Score[0] - 200;
			Pot = Pot + 200;
		}

		//ラウンド3なら
		if (Round_Count == 3) {
			Score[0] = Score[0] - 300;
			Pot = Pot + 300;
		}

		Player_Choice[0] = FALSE;
		Wait_TimeFLG = TRUE;
	}

	//レイズなら
	if (Player_Choice[1] == TRUE)
	{
		//ラウンド1なら
		if (Round_Count == 1) {
			Score[0] = Score[0] - 200;
			Pot = Pot + 200;
		}

		//ラウンド2なら
		if (Round_Count == 2) {
			Score[0] = Score[0] - 300;
			Pot = Pot + 300;
		}

		//ラウンド3なら
		if (Round_Count == 3) {
			Score[0] = Score[0] - 400;
			Pot = Pot + 400;
		}

		Player_Choice[1] = FALSE;
		Wait_TimeFLG = TRUE;
	}

	//フォールドなら
	if (Player_Choice[2] == TRUE)
	{
		Score[1] = Score[1] + Pot;
		Pot = 0;
		Player_Choice[2] = FALSE;
		ROUND_INIT();
		Round_Count = Round_Count + 1;
	}

}


//敵の選択
void Porker::ENEMY_CHOICE()
{


}


//待ち時間
void Porker::WAIT_TIME()
{
	//プレイヤーの決定後
	if (Wait_TimeFLG == TRUE)
	{

		Poker_Second[0]++;

		if (Poker_Second[0] > 60)
		{
			
			

		}
		if (Poker_Second[0] == 120)
		{
			Wait_TimeFLG = FALSE;
		}
	}

}

//アップデート
AbstractScene* Porker::Update()
{

	CARD_SETTING();
	FIRST_BET();
	UI();
	PLAYER_CHOICE();
	return this;
}


//描画
void Porker::Draw() const
{
	DrawFormatString(10, 15, 0xffffff, "ROUND:%d", Round_Count); //ラウンド数
	DrawFormatString(1120, 600, 0xffffff, "PLAYER:%d", Score[0]);//プレイヤーのスコア
	DrawFormatString(1120, 100, 0xffffff, "ENEMY:%d", Score[1]); //敵のスコア
	DrawFormatString(1150, 350, 0xffffff, "POT:%d",Pot); //賭けてるスコアの合計

	DrawFormatString(400, 600, 0xffffff, "P_CARD1:%d", P_Rand[0]); //プレイヤーのカード1
	DrawFormatString(600, 600, 0xffffff, "P_CARD2:%d", P_Rand[1]); //プレイヤーのカード2
	DrawFormatString(400, 0, 0xffffff, "E_CARD1:%d", E_Rand[0]); //敵のカード1
	DrawFormatString(600, 0, 0xffffff, "E_CARD2:%d", E_Rand[1]); //敵のカード2
	
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

}


