#include"Hit&Blow.h"
#include"DxLib.h"
#include"PadInput.h"
#include"GameSelect.h"
#include"Title.h"
#include"FpsController.h"
#include<stdlib.h>
#include<time.h>
#define WAITTIME 180 // 画面遷移する待機時間（固定用）

HitAndBlow::HitAndBlow()
{
	TableBgImg = LoadGraph("../images/HitAndBlow/BackGround02.png");

	BoardImg = LoadGraph("../images/HitAndBlow/HitBlowBoard.png");

	LoadDivGraph("../images/HitAndBlow/ColorBall.png", 6, 6, 1, 64, 64, ColorImg);
	LoadDivGraph("../images/HitAndBlow/HitBlowPin.png", 2, 2, 1, 32, 32, HitBlowImg);

	DecisionFlg = TRUE; // 答えを一回だけ決めるフラグをTRUEにする
	TurnFlg = TRUE;

	WarpPosition = 0;
	SidePosition = 0;

	Turns = 0;

	ArrayInit();

	SaveColor = 0; // セーブカラー初期化

	Hit = 0;  // ヒットの数を初期化
	Blow = 0;  // ブローの数を初期化

	Count = 0; // カウントの初期化

	MoveFlg = -1; // 一旦先攻でも後攻でもない値を入れる

	ChangeColor = -1; // 場所だけ変える変数を初期化

	FirstMoveFlg = -1;

	/* デバック用 */
	Covering = 0;
	CoveringFlg = FALSE;

}

HitAndBlow::~HitAndBlow()
{

}

AbstractScene* HitAndBlow::Update()
{
	RandomDecision(); // 答えの配列をランダムに設定する

	/* ここに自分が駒を入れる処理を書く */
	if (Turns < 8 && SaveHit[Turns - 1] != 4)
	{
		//十字キー↑入力
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP))
		{
			WarpPosition--;
			if (WarpPosition < 0) WarpPosition = 3; // 位置が0未満なら、0にする
		}

		// 十字キー↓入力
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN))
		{
			WarpPosition++;
			if (WarpPosition > 3) WarpPosition = 0; // 位置が3を超えたら、3にする
		}

		// 十字キー←入力
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT))
		{
			Color[SidePosition--];
			if (SidePosition < 0) SidePosition = 5; // 位置が0未満になったら、5にする
		}

		//十字キー→入力
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT))
		{
			Color[SidePosition++];
			if (SidePosition > 5) SidePosition = 0; // 位置が5を超えたら、0に戻す
		}
		
		if (MoveFlg == 0) { // 敵がやる処理		
			ERandomChoice();
			Judgment();

			ResetColor();

			MoveFlg = 1;
		}
		else if (PAD_INPUT::OnButton(XINPUT_BUTTON_X) && Reasoning[0] != -1 && Reasoning[1] != -1 && Reasoning[2] != -1 && Reasoning[3] != -1) // 色が入っている時
		{
			/* ジャッジ処理を書く */
			Judgment();
			ResetColor();
			MoveFlg = 0;
		}
		else if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) // 色を入れる処理
		{
			Reasoning[WarpPosition] = SidePosition;  // 色を場所に配置
			WarpPosition++; // 色を選択するカーソルの位置を一つずらす
			if (WarpPosition > 3) WarpPosition = 0; // 位置が3を超えたら、一番上にする
		}
		else if (PAD_INPUT::OnButton(XINPUT_BUTTON_B)) { // 色を外す処理
			Reasoning[WarpPosition] = -1;
		}
	}
	else {
		/* 何秒か待つ処理を作る */
		if (SaveHit[Turns - 1] == 4) {
			if (Count < WAITTIME) {
				Count++;
			}
			else if(MoveFlg == 0){
				Count = 0; // カウントをリセット
				return new Title();// 遷移場所は一旦置いてるだけ(プレイヤーWin)
			}
			else {
				Count = 0; // カウントをリセット
				return new Title();// 遷移場所は一旦置いてるだけ(プレイヤーLose)
			}
		}
		else {
			if (Count < WAITTIME) {
				Count++;
			}
			else {
				Count = 0; // カウントをリセット
				return new GameSelect();// 遷移場所は一旦置いてるだけ(ドロー)
			}
		}
	}

	return this;
}

void HitAndBlow::Draw() const
{
	DrawGraph(0, 0, TableBgImg, FALSE); // 背景画像表示(透明OFF)

	DrawGraph(0, 0, BoardImg, TRUE); // ボード画像表示

	for (int i = 0; i < 6; i++) { // 駒を表示
		DrawGraph(350 + i * 100, 600, ColorImg[i], TRUE); // それぞれの色の駒を表示(位置は決定)
	}
	if (Turns < 8 && SaveHit[Turns - 1] != 4) {
		DrawBox(350 + SidePosition * 100, 595, 420 + SidePosition * 100, 665, 0xff0000, FALSE); // 色を埋める場所がどこにあるかを見せるボックス
		DrawBox(80 + Turns * 130, 210 + WarpPosition * 80, 160 + Turns * 130, 290 + WarpPosition * 80, 0x00ff00, FALSE); // どこの場所を埋めようとしているか表示
	}
	
	//DrawFormatString(100, 600, 0xffffff, "Turnsは%d", CoveringFlg); // デバック用
	//DrawFormatString(100, 700, 0xffffff, "Coveringは%d", Covering); // デバック用
	/* 予想したカラーを表示する */
	if (Reasoning[WarpPosition % 4] >= 0) {
		DrawGraph(90 + Turns * 130, 220 + WarpPosition * 80, ColorImg[Reasoning[WarpPosition % 4]], TRUE); // 予想を画像で表示
	}

	if (Reasoning[(WarpPosition + 1) % 4] >= 0) {
		DrawGraph(90 + Turns * 130, 220 + (WarpPosition + 1) % 4 * 80, ColorImg[Reasoning[(WarpPosition + 1) % 4]], TRUE); // 予想を画像で表示
	}
	
	if (Reasoning[(WarpPosition + 2) % 4] >= 0) {
		DrawGraph(90 + Turns * 130, 220 + (WarpPosition + 2) % 4 * 80, ColorImg[Reasoning[(WarpPosition + 2) % 4]], TRUE); // 予想を画像で表示
	}
	
	if (Reasoning[(WarpPosition + 3) % 4] >= 0) {
		DrawGraph(90 + Turns * 130, 220 + (WarpPosition + 3) % 4 * 80, ColorImg[Reasoning[(WarpPosition + 3) % 4]], TRUE); // 予想を画像で表示
	}

	
	for (int i = 0; i < 4; i++) {
		if (SaveHit[Turns - 1] == 4 || Turns == 8) { // 8ターン経過か、4ヒットしたら表示
		DrawGraph(1125, 220 + i * 80, ColorImg[Answer[i]], TRUE); // 答えを画像で表示
		}
	}
	
	for (int i = 0; i < Turns; i++) {
		/* 過去に入れた色を表示 */
		DrawGraph(90 + i * 130, 220, ColorImg[SaveReasoning[i][0]], TRUE);
		DrawGraph(90 + i * 130, 220 + 1 * 80, ColorImg[SaveReasoning[i][1]], TRUE);
		DrawGraph(90 + i * 130, 220 + 2 * 80, ColorImg[SaveReasoning[i][2]], TRUE);
		DrawGraph(90 + i * 130, 220 + 3 * 80, ColorImg[SaveReasoning[i][3]], TRUE);

		/* ジャッジ用の描画処理を書く */
		for (int j = 0; j < SaveHit[i]; j++) {
			DrawGraph(80 + (j % 2) * 35 + i * 130, 100 + (j / 2) * 40, HitBlowImg[1], TRUE);
		}
		for (int k = 0; k < SaveBlow[i]; k++) {
			DrawGraph(80 + ((SaveHit[i] + k) % 2) * 35 + i * 130, 100 + ((SaveHit[i] + k) / 2) * 40, HitBlowImg[0], TRUE);
		}
	}
	for (int i = 0; i < 8; i++) {
		SetFontSize(32);
		if (FirstMoveFlg == TRUE) {
			if (i % 2 == 0) {
				DrawFormatString(110 + (i / 2) * 260, 50, 0xff0000, "P"); // プレイヤーの順番を上に表示
			}
			else {
				DrawFormatString(240 + (i / 2) * 260, 50, 0x00ffff, "E"); // エネミーの順番を上に表示
			}
		}
		else if (i % 2 == 0) {
			DrawFormatString(110 + (i / 2) * 260, 50, 0x00ffff, "E"); // エネミーの順番を上に表示
		}
		else {
			DrawFormatString(240 + (i / 2) * 260, 50, 0xff0000, "P"); // プレイヤーの順番を上に表示
		}

	}
}

void HitAndBlow::RandomDecision()
{
	/* 答えの配列をランダムに設定する */
	srand((unsigned int)time(NULL));

	if (DecisionFlg == TRUE) {
		for (int i = 0; i < 4; i++) {
			Answer[i] = GetRand(5);
			if (Answer[i] == Answer[(i + 1) % 4] || Answer[i] == Answer[(i + 2) % 4] || Answer[i] == Answer[(i + 3) % 4]) { // 色が重なったら
				i--; // 選別をやり直す
			}
		}
		DecisionFlg = FALSE;
	}
	/* 先攻・後攻をランダムに決める */
	if (TurnFlg == TRUE) {
		MoveFlg = /*rand() % 2*/0;
		TurnFlg = FALSE;
		FirstMoveFlg = MoveFlg; // 先攻か後攻かを覚えてもらう（描画処理で必要）
	}
	
}

void HitAndBlow::ERandomChoice()
{
	/* 答えの配列をランダムに設定する */
	srand((unsigned int)time(NULL));

	for (int i = 0; i < 4; i++) {
		//if (SaveHit[Turns - 1] + SaveBlow[Turns - 1] == 4 /*|| SaveHit[Turns - 2] + SaveBlow[Turns - 2]*/) {// ヒットとブローの合計の数が４つになったら
		//	ChangeColor = rand() % 4;
		//	Reasoning[i] = SaveReasoning[Turns][ChangeColor]; // 場所だけ変える
		//	if (Reasoning[i] == Reasoning[(i + 1) % 4] || Reasoning[i] == Reasoning[(i + 2) % 4] || Reasoning[i] == Reasoning[(i + 3) % 4]) { // 順番被ってたら
		//		i--; // iの抽選やり直す
		//	}
		//}
		/*else */{
			Reasoning[i] = rand() % 6;
			/* デバック用 */
			//if (CoveringFlg == FALSE) {
			//	Reasoning[0] = 0;
			//	Reasoning[1] = 1;
			//	Reasoning[2] = 2;
			//	Reasoning[3] = 3;
			//}
			//else {
			//	Reasoning[i] = rand() % 6; // 違う奴にする
			//}

			if (Reasoning[i] == Reasoning[(i + 1) % 4] || Reasoning[i] == Reasoning[(i + 2) % 4] || Reasoning[i] == Reasoning[(i + 3) % 4]) { // 色が重なったら
				i--; // 選別をやり直す
			}

			
			if (Turns != 0 && i == 3) {	
				for (Covering = 0; Covering < Turns; Covering++) {
					if (Reasoning[0] == SaveReasoning[Covering][0]
						&& Reasoning[1] == SaveReasoning[Covering][1]
						&& Reasoning[2] == SaveReasoning[Covering][2]
						&& Reasoning[3] == SaveReasoning[Covering][3]) { // 前入れた奴と全く同じだったら
						/* デバック用 */
						CoveringFlg = TRUE; // 被っていたと知らせる

						i = -1; // 0代入すると3つしか交換しないので、インクリメントして0になる-1を代入
						Reasoning[0] = -1;// 中身全部空にする
						Reasoning[1] = -1;// 中身全部空にする
						Reasoning[2] = -1;// 中身全部空にする
						Reasoning[3] = -1;// 中身全部空にする

						break; // 被りがあるか調べたいので、一度被ったらループを抜ける

					}
					/* デバック用 */
					else {
						CoveringFlg = FALSE; // 被っていないと知らせる
					}
					
				}
			}			
			// 1ターン目に当たるのを阻止
			if (Turns / 2 == 0 && Reasoning[0] == Answer[0] && Reasoning[1] == Answer[1] && Reasoning[2] == Answer[2] && Reasoning[3] == Answer[3]) {
				i = -1; // iを最初に戻す(0代入すると3つしか交換しないので、インクリメントして0になる-1を代入)
			}
		}
	}
}

void HitAndBlow::Judgment()
{
	for (int i = 0; i < 4; i++) {
		if (Reasoning[i] == Answer[i]) {
			Hit++; // hitに１を足す
		}
		else if (Reasoning[i] == Answer[(i + 1) % 4] || Reasoning[i] == Answer[(i + 2) % 4] || Reasoning[i] == Answer[(i + 3) % 4]) { // 色だけが当たっているとき、
			/* 色がどこかしら被っていた時の処理 */
			if (Reasoning[i] == Reasoning[(i + 1) % 4] || Reasoning[i] == Reasoning[(i + 2) % 4] || Reasoning[i] == Reasoning[(i + 3) % 4]) {	
				if (Reasoning[i] == Reasoning[(i + 1) % 4] && Reasoning[(i + 1) % 4] != Answer[(i + 1) % 4]) {// 被っている場所の色がヒットしていないか確認	
					if (Reasoning[(i + 1) % 4] != Reasoning[(i + 2) % 4] && Reasoning[(i + 1) % 4] != Reasoning[(i + 3) % 4]) {// 2重に判定していないか確認
						if ((i + 1) / 4 == 0) {// ブローが２重に加算されていなければ、
							Blow++; // blowに１を足す
						}
					}
				}
				// その場所の色がヒットしていなくて、ブローが２重に加算されていなければ、
				if (Reasoning[i] == Reasoning[(i + 2) % 4] && Reasoning[(i + 2) % 4] != Answer[(i + 2) % 4]) {
					if (Reasoning[(i + 2) % 4] != Reasoning[(i + 3) % 4]) { // 2重に判定していないか確認
						if ((i + 2) / 4 == 0) {// ブローが２重に加算されていなければ、
							Blow++; // blowに１を足す
						}
					}
				}
				// その場所の色がヒットしていなくて、ブローが２重に加算されていなければ、
				if (Reasoning[i] == Reasoning[(i + 3) % 4] && Reasoning[(i + 3) % 4] != Answer[(i + 3) % 4] 
					&& Reasoning[(i + 2) % 4] != Answer[(i + 2) % 4] && Reasoning[(i + 1) % 4] != Answer[(i + 1) % 4]) {
					if ((i + 3) / 4 == 0) {// ブローが２重に加算されていなければ、
						Blow++; // blowに１を足す
					}	
				}
			}
			else { // 他の色被っていなければ
				Blow++; // blowに１を足す
			}
		}
	}
	SaveHit[Turns] = Hit; // そのターンのヒットした数を格納
	SaveBlow[Turns] = Blow; // そのターンのブローした数を格納
}

void HitAndBlow::ResetColor() 
{
	/* 色のデータ引き継ぎ */
	SaveReasoning[SaveColor][0] = Reasoning[0];
	SaveReasoning[SaveColor][1] = Reasoning[1];
	SaveReasoning[SaveColor][2] = Reasoning[2];
	SaveReasoning[SaveColor][3] = Reasoning[3];

	SaveColor++; // 描画列1追加
	Turns++; // ターン数1増加

	for (int i = 0; i < 4; i++) {
		/* 色をリセット */
		Reasoning[i] = -1;
	}

	WarpPosition = 0;

	Hit = 0;
	Blow = 0;

}

void HitAndBlow::ArrayInit()
{
	for (int i = 0; i < 4; i++) {
		Reasoning[i] = -1;// 中身全部空にする
		Answer[i] = -1;
	}

	for (int j = 0; j < 8; j++) {
		SaveHit[j] = 0;
		SaveBlow[j] = 0;
		for (int k = 0; k < 4; k++) {
			SaveReasoning[j][k] = 0;
		}
	}

	for (int m = 0; m < 6; m++) {
		Color[m] = 0;
	}
}
