#include "sinkeisuijaku.h"
#include "DxLib.h"
#include <stdlib.h>
#include <time.h>



AbstractScene* sinkeisuijaku::Update()
{
	S_timg = LoadGraph("../images/sinkensuijaku/ura.png");
	S_back = LoadGraph("../images/sinkensuijaku/back.png");



	



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
	// 現在の時間を使ってシードを初期化
	srand((unsigned int)time(NULL));


	// 1または2をランダムに生成
	first = (rand() % 2) + 1;
	

}

