#include "sinkeisuijaku.h"
#include "DxLib.h"
#include <stdlib.h>
#include <time.h>



AbstractScene* sinkeisuijaku::Update()
{
	S_timg = LoadGraph("../images/sinkensuijaku/ura.png");
	S_back = LoadGraph("../images/sinkensuijaku/back.png");

	//トランプの画像
	S_D1 = LoadGraph("../images/sinkensuijaku/D1.png");
	S_D2 = LoadGraph("../images/sinkensuijaku/D2.png");
	S_D3 = LoadGraph("../images/sinkensuijaku/D3.png");
	S_D4 = LoadGraph("../images/sinkensuijaku/D4.png");
	S_D5 = LoadGraph("../images/sinkensuijaku/D5.png");
	S_D6 = LoadGraph("../images/sinkensuijaku/D6.png");
	S_D7 = LoadGraph("../images/sinkensuijaku/D7.png");
	S_D8 = LoadGraph("../images/sinkensuijaku/D8.png");
	S_D9 = LoadGraph("../images/sinkensuijaku/D9.png");
	S_D10 = LoadGraph("../images/sinkensuijaku/D10.png");
	
	S_H1 = LoadGraph("../images/sinkensuijaku/H1.png");
	S_H2 = LoadGraph("../images/sinkensuijaku/H2.png");
	S_H3 = LoadGraph("../images/sinkensuijaku/H3.png");
	S_H4 = LoadGraph("../images/sinkensuijaku/H4.png");
	S_H5 = LoadGraph("../images/sinkensuijaku/H5.png");
	S_H6 = LoadGraph("../images/sinkensuijaku/H6.png");
	S_H7 = LoadGraph("../images/sinkensuijaku/H7.png");
	S_H8 = LoadGraph("../images/sinkensuijaku/H8.png");
	S_H9 = LoadGraph("../images/sinkensuijaku/H9.png");
	S_H10 = LoadGraph("../images/sinkensuijaku/H10.png");


	// 入力キー取得
	g_OldKey = g_NowKey;
	g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	g_KeyFlg = g_NowKey & ~g_OldKey;



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

	return this;
}

void sinkeisuijaku::Draw() const
{
//test

		DrawFormatString(200, 200, 0x0000ff, "%d", trumps[S_ber][S2_ber].flg);

	DrawFormatString(100, 100, 0xfff00f, "%d", trumps[S_ber][S2_ber].flg);
	DrawFormatString(100, 150, 0xfff00f, "%d %d", S_ber,S2_ber);


	if (first  == 1) {
		DrawFormatString(50, 30, 0xff00ff, "先行です！");
	}
	else {
		DrawFormatString(50, 30, 0xff00ff, "後攻です！");
	}
	
	//DrawGraph(0,0, S_back, FALSE);
	
	for (int j = 1; j < 5; j++) {
		for (int i = 0; i < 5; i++) {
			DrawRotaGraph(450 + i * 110, 0+ j*140, 0.5, 0, S_timg, TRUE);
		}
	}
	DrawBox(395 + S2_ber * 110 , 70 +S_ber * 140 , 495 + S2_ber  * 110, 215 + S_ber * 140, 0x00ffff, TRUE);


	//test
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

