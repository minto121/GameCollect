#include "sinkeisuijaku.h"
#include "DxLib.h"

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
	
	return this;
}

void sinkeisuijaku::Draw() const
{
//test
	if (first % 2 == 0) {
		DrawFormatString(50, 30, 0xff00ff, "先行です！");
	}
	else {
		DrawFormatString(50, 30, 0xff00ff, "後攻です！");
	}
	
	DrawFormatString(50, 50,0xff00ff,"%d",S_ber);
	DrawFormatString(50, 70, 0xff00ff, "%d", S2_ber);
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
	//DrawBox(395 + i * 110, 90 + j * 160, 495 + i * 110, 235 + j * 160, 0x00ffff, TRUE);
	

}

void sinkeisuijaku::Select()
{
	first = GetRand(201);

}
