#include"Hit&Blow.h"
#include"DxLib.h"
#include"PadInput.h"
#include<stdlib.h>
#include<time.h>

HitAndBlow::HitAndBlow() 
{
	// ヒットした時の画像読込
	HitImg = LoadGraph("../images/HitAndBlow/HitPin.png");
	// ブローした時の画像読込
	BlowImg = LoadGraph("../images/HitAndBlow/BlowPin.png");

	LoadDivGraph("../images/HitAndBlow/ColorBall.png", 6, 6, 1, 64, 64, ColorImg);
	
	DecisionFlg = TRUE;

	WarpPosition = 0;
	SidePosition = 0;

	Turns = 0;

	ColorFlg = FALSE;

	for (int i = 0; i++; i < 4) {
		Reasoning[i] = 0;
	}
	Reasoning[0] = -1; // エラー消す用のコンストラクト
	Reasoning[1] = -1; // エラー消す用のコンストラクト
	Reasoning[2] = -1; // エラー消す用のコンストラクト
	Reasoning[3] = -1; // エラー消す用のコンストラクト

	SaveColor = 0; // セーブカラー初期化
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
		if (WarpPosition > 3) WarpPosition = 3;
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
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_RIGHT_SHOULDER))
	{
		Turns++;
		if (Turns > 7) {
			Turns = 7;
		}
	}

	// デバック用
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_LEFT_SHOULDER))
	{
		Turns--;
		if (Turns < 0) {
			Turns = 0;
		}
	}
	
	
	/* ここに自分が駒を入れる処理を書く */
	if (Turns < 8)
	{
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_X) && Reasoning[0] != -1 && Reasoning[1] != -1 && Reasoning[2] != -1 && Reasoning[3] != -1) // 色が入っている時
		{
			/* ジャッジ処理を書く */
			
			//SaveColor = Turns; // 前のターンの色と順番をセーブする
			 /* 色のデータ引き継ぎ */ 
			SaveReasoning[SaveColor][0] = Reasoning[0];
			SaveReasoning[SaveColor][1] = Reasoning[1];
			SaveReasoning[SaveColor][2] = Reasoning[2];
			SaveReasoning[SaveColor][3] = Reasoning[3];

			SaveColor++; // 描画列1追加
			Turns++; // ターン数1増加
			
			Reasoning[0] = -1; // 色をリセット
			Reasoning[1] = -1; // 色をリセット
			Reasoning[2] = -1; // 色をリセット
			Reasoning[3] = -1; // 色をリセット

		}
		else if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
		{
			ColorDecision = WarpPosition; // 入れたい縦の位置を保存
			Reasoning[ColorDecision] = SidePosition;  // 色を場所に配置
			ColorFlg = TRUE; // 色を入れたか確認するフラグを真とする
		}
		/* この処理は要らないかもしれないので、あとで消す */
		//else if (Reasoning[WarpPosition] != SidePosition) {
		//	ColorFlg = FALSE;
		//}

	}
	else {
		/* 答えを出す処理追加 */
	}
		
	return this;
}

void HitAndBlow::Draw() const
{
	for (int i = 0; i < 7; i++) { // 駒を表示
		DrawGraph(350 + i * 100, 600, ColorImg[i], TRUE); // それぞれの色の駒を表示(位置は決定)
	}
	DrawGraph(200, 100, HitImg, TRUE); // HitPinを表示
	DrawGraph(300, 100, BlowImg, TRUE); //BlowPinを表示
	
	DrawTriangle(300 + SidePosition * 100, 575, 350 + SidePosition * 100, 625, 300 + SidePosition * 100, 675, 0xff0000, TRUE); // どこの駒を指しているのか表示
	DrawBox(200 + Turns * 70, 100 + WarpPosition * 100, 280 + Turns * 70, 180 + WarpPosition * 100, 0x00ff00, FALSE); // どこの場所を埋めようとしているか表示

	DrawFormatString(100, 600, 0xffffff, "Turnsは%d", Turns); // デバック用
	
	/* 正解の駒表示 */
	/* 重すぎてタスクの応答がなくなるため、コメントアウト中 */
	if (DecisionFlg == FALSE) {
		for (int i = 0; i < 4; i++) {
			//DrawFormatString(400, 400 + i * 20, 0xffffff, "%d", Answer[i]); // デバック用
			DrawGraph(1100, 170 + i * 75, ColorImg[Answer[i]], TRUE); // 答えを画像で表示
		}
		//DrawFormatString(100, 700, 0xffffff, "Turnsは%d", Reasoning[WarpPosition]); // デバック用
		/* 予想したカラーを表示する */
		if (ColorFlg == TRUE || Reasoning[WarpPosition % 4] >= 0) {
			DrawGraph(215 + Turns * 70, 115 + WarpPosition * 100, ColorImg[Reasoning[WarpPosition % 4]], TRUE); // 予想を画像で表示
		}
		if (ColorFlg == TRUE || Reasoning[(WarpPosition + 1) % 4] >= 0) {
			DrawGraph(215 + Turns * 70, 115 + (WarpPosition + 1) % 4 * 100, ColorImg[Reasoning[(WarpPosition + 1) % 4]], TRUE); // 予想を画像で表示
		}
		if (ColorFlg == TRUE || Reasoning[(WarpPosition + 2) % 4] >= 0) {
			DrawGraph(215 + Turns * 70, 115 + (WarpPosition + 2) % 4 * 100, ColorImg[Reasoning[(WarpPosition + 2) % 4]], TRUE); // 予想を画像で表示
		}
		if (ColorFlg == TRUE || Reasoning[(WarpPosition + 3) % 4] >= 0) {
			DrawGraph(215 + Turns * 70, 115 + (WarpPosition + 3) % 4 * 100, ColorImg[Reasoning[(WarpPosition + 3) % 4]], TRUE); // 予想を画像で表示
		}
		/* 過去に入れた色を表示 */
		for (int i = 0; i < Turns; i++) {
			for (int j = 0; j < 4; j++) {
				if (SaveReasoning[i][0] >= 0) {
					DrawGraph(215 + i * 70, 115, ColorImg[SaveReasoning[i][0]], TRUE); // 予想を画像で表示
				}
				if (SaveReasoning[i][1] >= 0) {
					DrawGraph(215 + i * 70, 115 + 1 * 100, ColorImg[SaveReasoning[i][1]], TRUE); // 予想を画像で表示
				}
				if (SaveReasoning[i][2] >= 0) {
					DrawGraph(215 + i * 70, 115 + 2 * 100, ColorImg[SaveReasoning[i][2]], TRUE); // 予想を画像で表示
				}
				if (SaveReasoning[i][3] >= 0) {
					DrawGraph(215 + i * 70, 115 + 3 * 100, ColorImg[SaveReasoning[i][3]], TRUE); // 予想を画像で表示
				}
			}
		}
	}
}

void HitAndBlow::RandomDecision() 
{
	/* 答えの配列をランダムに設定する */
	srand((unsigned int)time(NULL));

	if (DecisionFlg == TRUE) {
		for (int i = 0; i < 4; i++) {
			Answer[i] = rand() % 6;
			if (Answer[i] == Answer[(i + 1) % 4] || Answer[i] == Answer[(i + 2) % 4] || Answer[i] == Answer[(i + 3) % 4]) { // 色が重なったら
				i--; // 選別をやり直す
			}
		}
		DecisionFlg = FALSE;
	}

}