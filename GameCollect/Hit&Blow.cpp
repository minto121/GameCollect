#include"Hit&Blow.h"
#include"DxLib.h"
#include"PadInput.h"
#include<stdlib.h>
#include<time.h>

HitAndBlow::HitAndBlow() 
{
	// ダミー画像を読込
	/*LoadGraph("../images/HitAndBlow/BG_Dummy.png");*/
	// ヒットした時の画像読込
	HitImg = LoadGraph("../images/HitAndBlow/HitPin.png");
	// ブローした時の画像読込
	BlowImg = LoadGraph("../images/HitAndBlow/BlowPin.png");
	// 色の画像追加(仮表示)
	ColorImg[0] = LoadGraph("../images/HitAndBlow/Blue_Foal.png");
	ColorImg[1] = LoadGraph("../images/HitAndBlow/Red_Foal.png");
	ColorImg[2] = LoadGraph("../images/HitAndBlow/Green_Foal.png");
	ColorImg[3] = LoadGraph("../images/HitAndBlow/Yellow_Foal.png");
	ColorImg[4] = LoadGraph("../images/HitAndBlow/Purple_Foal.png");
	ColorImg[5] = LoadGraph("../images/HitAndBlow/White_Foal.png");

	DecisionFlg = TRUE;

	WarpPosition = 0;
	SidePosition = 0;

	Turns = 0;
}

HitAndBlow::~HitAndBlow()
{
	
}

AbstractScene* HitAndBlow::Update()
{
	RandomDecision(); // 答えの配列をランダムに設定する

		//十字キー↑入力
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP))
		{
			WarpPosition--;
			if (WarpPosition < 0) WarpPosition = 0;  // 位置が0より下なら、0にする
		}

		// 十字キー↓入力
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN))
		{
			WarpPosition++;
			if (WarpPosition > 4) WarpPosition = 4;
		}

		// 十字キー←入力
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT))
		{
			Color[SidePosition--];
			if (SidePosition < 0) SidePosition = 5;
		}

		//十字キー→入力
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT))
		{
			Color[SidePosition++];
			if (SidePosition > 5) SidePosition = 0;
		}

		// デバック用
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
		{
			Turns++;
			if (Turns > 8) {
				Turns = 8;
			}
		}

		// デバック用
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_B))
		{
			Turns--;
			if (Turns < 0) {
				Turns = 0;
			}
		}
		
	/* ここに自分が駒を入れる処理を書く */
	/* 重すぎてタスクの応答がなくなるため、コメントアウト中 */
	//while (Turns < 8)
	//{
	//	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A && WarpPosition == 0))
	//	{
	//		/* ジャッジ処理を書く */
	//		Turns++;
	//	}
	//	else if (PAD_INPUT::OnButton(XINPUT_BUTTON_A && WarpPosition != 0))
	//	{
	//		Reasoning[WarpPosition] = Color[SidePosition];  // 色を場所に配置
	//	}


	//}

		
	return this;
}

void HitAndBlow::Draw() const
{
	for (int i = 0; i < 6; i++) { // 駒を表示
		DrawGraph(350 + i * 100, 600, ColorImg[i], TRUE); // それぞれの色の駒を表示(位置は決定)
	}
	DrawGraph(200, 100, HitImg, TRUE); // それぞれの色の駒を表示
	DrawGraph(300, 100, BlowImg, TRUE); // それぞれの色の駒を表示
	
	DrawTriangle(300 + SidePosition * 100, 575, 350 + SidePosition * 100, 625, 300 + SidePosition * 100, 675, 0xff0000, TRUE); // どこの駒を指しているのか表示
	DrawBox(150 + Turns * 100, 100 + WarpPosition * 75, 200 + Turns * 100, 175 + WarpPosition * 75, 0x00ff00, FALSE); // どこの場所を埋めようとしているか表示

	/* 正解の駒表示 */
	/* 重すぎてタスクの応答がなくなるため、コメントアウト中 */
	//for (int i = 0; i < 4; i++) {
	//	DrawFormatString(400, 400 + i * 20, 0xffffff, "%d", Answer[i]); // デバック用
	//	DrawGraph(1000, 170 + i * 75, ColorImg[Answer[i]], TRUE); // 答えを画像で表示
	//	DrawGraph(100 * Turns, 170 + i * 75, ColorImg[Reasoning[WarpPosition]], TRUE); // 予想を画像で表示
	//}

}

void HitAndBlow::RandomDecision() 
{
	/* 答えの配列をランダムに設定する */
	srand((unsigned int)time(NULL));

	if (DecisionFlg == TRUE) {
		for (int i = 0; i < 4; i++) {
			Answer[i] = rand() % 6;
			if (Answer[i] == Answer[(i + 1) % 4] || Answer[i] == Answer[(i + 2) % 4] || Answer[i] == Answer[(i + 3) % 4]) {
				i--;
			}
		}
		DecisionFlg = FALSE;
	}

}