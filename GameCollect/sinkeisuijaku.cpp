#include "sinkeisuijaku.h"
#include "DxLib.h"
#include <stdlib.h>
#include <time.h>



AbstractScene* sinkeisuijaku::Update()
{	
	S_timg = LoadGraph("../images/sinkensuijaku/ura.png");
	S_back = LoadGraph("../images/sinkensuijaku/back.png");

	//トランプの画像
	S_TH[0] = LoadGraph("../images/sinkensuijaku/D1.png");
	S_TH[1] = LoadGraph("../images/sinkensuijaku/D2.png");
	S_TH[2] = LoadGraph("../images/sinkensuijaku/D3.png");
	S_TH[3] = LoadGraph("../images/sinkensuijaku/D4.png");
	S_TH[4] = LoadGraph("../images/sinkensuijaku/D5.png");
	S_TH[5] = LoadGraph("../images/sinkensuijaku/D6.png");
	S_TH[6] = LoadGraph("../images/sinkensuijaku/D7.png");
	S_TH[7] = LoadGraph("../images/sinkensuijaku/D8.png");
	S_TH[8] = LoadGraph("../images/sinkensuijaku/D9.png");
	S_TH[9] = LoadGraph("../images/sinkensuijaku/D10.png");

	S_TH[0] = LoadGraph("../images/sinkensuijaku/H1.png");
	S_TH[0] = LoadGraph("../images/sinkensuijaku/H2.png");
	S_TH[0] = LoadGraph("../images/sinkensuijaku/H3.png");
	S_TH[0] = LoadGraph("../images/sinkensuijaku/H4.png");
	S_TH[0] = LoadGraph("../images/sinkensuijaku/H5.png");
	S_TH[0] = LoadGraph("../images/sinkensuijaku/H6.png");
	S_TH[0] = LoadGraph("../images/sinkensuijaku/H7.png");
	S_TH[0] = LoadGraph("../images/sinkensuijaku/H8.png");
	S_TH[0] = LoadGraph("../images/sinkensuijaku/H9.png");
	S_TH[0] = LoadGraph("../images/sinkensuijaku/H10.png");

	// 入力キー取得
	g_OldKey = g_NowKey;
	g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	g_KeyFlg = g_NowKey & ~g_OldKey;

	//カウントを増やす
	count++;

	//メニューカーソル移動処理
	
	//上移動
	if (g_KeyFlg & PAD_INPUT_UP) {
		if (S_ber >= 0 && S_ber <= 4) {
			S_ber = S_ber - 1;
		}
		if (S_ber <0) {
			S_ber = 3;
		}
	}


	//下移動
	if (g_KeyFlg & PAD_INPUT_DOWN) {
		if (S_ber >= 0 && S_ber <= 4) {
			S_ber = S_ber + 1;
		}
		if (S_ber >= 4) {
			S_ber = 0;
		}
	}
	
	//右移動
	if (g_KeyFlg & PAD_INPUT_RIGHT) {
		S2_ber = S2_ber + 1;
		if (S2_ber == 5 || S2_ber == 9 || S2_ber == 14 || S2_ber == 19 || S2_ber == 24) {
			S2_ber = S2_ber - 5;
		}
	}

	//左移動
	if (g_KeyFlg & PAD_INPUT_LEFT) {
			S2_ber = S2_ber - 1;
		if (S2_ber == -1 || S2_ber == 6 || S2_ber ==  11|| S2_ber == 16 || S2_ber == 21) {
			S2_ber = S2_ber + 5;
		}
	}

	//カード選択
	if (g_KeyFlg & PAD_INPUT_1) {
		trumpflg = 1;
	}
	if (trumpflg == 1) trumps[S_ber][S2_ber].flg = 1;
	trumpflg = 0;


	//トランプに値を入れる

	if (count < 2) {
	int x = 1;
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 5; i++) {
			trumps[j][i].syurui = x++;
		}
		}
	}


	//先行後攻決め
	Select();

	// 現在の時間を使って初期化
	srand((unsigned int)time(NULL));


	if (randend != 1) {

		for (int i = 0; i < 20; i++) {
			// 1または2をランダムに生成
			r = (rand() % 4) + 1;
			r2 = (rand() % 5) + 1;


			trumps[0][1].syurui = trumps[0][0].syurui;
			trumps[0][0].syurui = trumps[r][r2].syurui;
			trumps[r][r2].syurui = trumps[0][1].syurui;
		}
	}
	if (count >= 10 ) {
		randend = 1;
	}


	if (trumps[S_ber][S2_ber].flg == 1) {
		DrawGraph(395 + S2_ber * 110, 70 + S_ber * 140, S_TH[0], TRUE);
	}

	////ひっくり返したトランプ画像
	//if (trumps[S_ber][S2_ber].flg == 1) {
	//	int trump_num = trumps[S_ber][S2_ber].syurui;

	//	// カードの "trump_num" に応じて、適切なカード画像を描画
	//	if (trump_num >= 1 && trump_num <= 10) {
	//		DrawGraph(395 + S2_ber * 110, 70 + S_ber * 140, S_TD[trump_num - 1], TRUE);
	//	}
	//	if (trump_num >= 1 && trump_num <= 10) {
	//		DrawGraph(395 + S2_ber * 110, 70 + S_ber * 140, S_TH[trump_num - 1], TRUE);
	//	}
	//	}
	//	switch (trump_num) {
	//	case 1:
	//		DrawGraph(395 + S2_ber * 110, 70 + S_ber * 140, S_TD[0], TRUE);
	//		break;
	//	case 2:
	//		DrawGraph(395 + S2_ber * 110, 70 + S_ber * 140, S_TD[1], TRUE);
	//		break;
	//	case 3:
	//		DrawGraph(395 + S2_ber * 110, 70 + S_ber * 140, S_TD[3], TRUE);
	//		break;
	//	case 4:
	//		DrawGraph(395 + S2_ber * 110, 70 + S_ber * 140, S_D1, TRUE);
	//		break;
	//	case 5:
	//		DrawGraph(395 + S2_ber * 110, 70 + S_ber * 140, S_D1, TRUE);
	//		break;
	//	case 6:
	//		DrawGraph(395 + S2_ber * 110, 70 + S_ber * 140, S_D1, TRUE);
	//		break;
	//	case 7:
	//		DrawGraph(395 + S2_ber * 110, 70 + S_ber * 140, S_D1, TRUE);
	//		break;
	//	case 8:
	//		DrawGraph(395 + S2_ber * 110, 70 + S_ber * 140, S_D1, TRUE);
	//		break;
	//	case 9:
	//		DrawGraph(395 + S2_ber * 110, 70 + S_ber * 140, S_D1, TRUE);
	//		break;
	//	case 10:
	//		DrawGraph(395 + S2_ber * 110, 70 + S_ber * 140, S_D1, TRUE);
	//		break;
	//	case 11:
	//		DrawGraph(395 + S2_ber * 110, 70 + S_ber * 140, S_TH[0], TRUE);
	//		break;
	//	case 12:
	//		DrawGraph(395 + S2_ber * 110, 70 + S_ber * 140, S_TH[1], TRUE);
	//		break;
	//	case 13:
	//		DrawGraph(395 + S2_ber * 110, 70 + S_ber * 140, S_D1, TRUE);
	//		break;
	//	case 14:
	//		DrawGraph(395 + S2_ber * 110, 70 + S_ber * 140, S_D1, TRUE);
	//		break;
	//	case 15:
	//		DrawGraph(395 + S2_ber * 110, 70 + S_ber * 140, S_D1, TRUE);
	//		break;
	//	case 16:
	//		DrawGraph(395 + S2_ber * 110, 70 + S_ber * 140, S_D1, TRUE);
	//		break;
	//	case 17:
	//		DrawGraph(395 + S2_ber * 110, 70 + S_ber * 140, S_D1, TRUE);
	//		break;
	//	case 18:
	//		DrawGraph(395 + S2_ber * 110, 70 + S_ber * 140, S_D1, TRUE);
	//		break;
	//	case 19:
	//		DrawGraph(395 + S2_ber * 110, 70 + S_ber * 140, S_D1, TRUE);
	//		break;
	//	case 20:
	//		DrawGraph(395 + S2_ber * 110, 70 + S_ber * 140, S_D1, TRUE);
	//		break;

	//	}
	//}



	return this;
}

void sinkeisuijaku::Draw() const
{
//test

	DrawFormatString(100, 100, 0xfff00f, "flg %d", trumps[S_ber][S2_ber].flg);

	DrawFormatString(100, 150, 0xfff00f, "%d %d", S_ber,S2_ber);

	DrawFormatString(100, 180, 0xfff00f, "種類%d", trumps[S_ber][S2_ber].syurui);
	DrawFormatString(100, 230, 0xfff00f, "count %d", count);
	
	//test 

	if (first  == 1) {
		DrawFormatString(50, 30, 0xff00ff, "先行です！");
	}
	else {
		DrawFormatString(50, 30, 0xff00ff, "後攻です！");
	}
	
	//DrawGraph(0,0, S_back, FALSE);
	
	for (int j = 1; j < 5; j++) {
		for (int i = 0; i < 5; i++) {
			if (trumps[S_ber][S2_ber].flg == 0) {
				DrawRotaGraph(450 + i * 110, 0 + j * 140, 0.5, 0, S_timg, TRUE);
			}
			else {
				
			}
		}
	}
	DrawBox(395 + S2_ber * 110 , 70 +S_ber * 140 , 495 + S2_ber  * 110, 215 + S_ber * 140, 0x00ffff, TRUE);


	//カーソルの四角
		for (int j = 0; j < 4; j++) {
			for (int i = 0; i < 5; i++) {
				DrawBox(395 + i * 110, 70 + j * 140, 495 + i * 110, 215 + j * 140, 0x00ffff, FALSE);
			}
		}
	}

void sinkeisuijaku::Select()
{
	// 現在の時間を使って初期化
	srand((unsigned int)time(NULL));


	// 1または2をランダムに生成
	first = (rand() % 2) + 1;
	

}

