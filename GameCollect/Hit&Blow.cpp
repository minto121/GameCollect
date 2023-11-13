#include"Hit&Blow.h"
#include"DxLib.h"
#include"PadInput.h"
#include"GameSelect.h"
#include"Title.h"
#include"FpsController.h"
#include<stdlib.h>
#include<time.h>

HitAndBlow::HitAndBlow()
{
	TableBgImg = LoadGraph("../images/HitAndBlow/BackGround02.png");

	BoardImg = LoadGraph("../images/HitAndBlow/HitBlowBoard.png");

	LoadDivGraph("../images/HitAndBlow/ColorBall.png", 6, 6, 1, 64, 64, ColorImg);
	LoadDivGraph("../images/HitAndBlow/HitBlowPin.png", 2, 2, 1, 32, 32, HitBlowImg);

	DecisionFlg = TRUE;
	EChoiceFlg = TRUE;

	WarpPosition = 0;
	SidePosition = 0;

	Turns = 0;

	ColorFlg = FALSE;

	for (int i = 0; i < 4; i++) {
		Reasoning[i] = -1;// エラー消す用のコンストラクト
	}

	SaveColor = 0; // セーブカラー初期化

	Hit = 0;  // ヒットの数を初期化
	Blow = 0;  // ブローの数を初期化

	count = 0; // カウントの初期化
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
		if ((Turns % 2) == 0) { // 敵がやる処理
			ERandomChoice();
			Judgment();

			if (SaveHit[Turns - 1] == 4) {
				/* 何秒か待つ処理を作る */
				while (count < 1200) {
					count++;
				}
				count = 0; // カウントをリセット
				//return new GameSelect();// 遷移場所は一旦置いてるだけ
			}

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


		}else
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_X) && Reasoning[0] != -1 && Reasoning[1] != -1 && Reasoning[2] != -1 && Reasoning[3] != -1) // 色が入っている時
		{
			/* ジャッジ処理を書く */
			Judgment();

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
		else if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
		{
			ColorDecision = WarpPosition; // 入れたい縦の位置を保存
			Reasoning[ColorDecision] = SidePosition;  // 色を場所に配置
			WarpPosition++;
			if (WarpPosition > 3) WarpPosition = 0; // 位置が3を超えたら、3にする
		}
		else if (PAD_INPUT::OnButton(XINPUT_BUTTON_B)) {
			ColorDecision = WarpPosition;
			Reasoning[ColorDecision] = -1;
		}
	}
	else {
		/* 何秒か待つ処理を作る */
		if (SaveHit[Turns - 1] == 4) {
			/* 何秒か待つ処理を作る */
			while (count < 1200) {
				count++;
			}
			count = 0; // カウントをリセット
			//return new GameSelect(); // 遷移場所は一旦置いてるだけ
		}else
		while (count < 1200) {
			count++;
		}
		count = 0; // カウントをリセット
		//return new Title();// 遷移場所は一旦置いてるだけ
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
	DrawTriangle(300 + SidePosition * 100, 575, 350 + SidePosition * 100, 625, 300 + SidePosition * 100, 675, 0xff0000, TRUE); // どこの駒を指しているのか表示
	DrawBox(80 + Turns * 130, 210 + WarpPosition * 80, 160 + Turns * 130, 290 + WarpPosition * 80, 0x00ff00, FALSE); // どこの場所を埋めようとしているか表示

	//DrawFormatString(100, 600, 0xffffff, "Turnsは%d", Hit); // デバック用

	/* 正解の駒表示 */
	if (DecisionFlg == FALSE && SaveHit[Turns - 1] == 4 || Turns == 8) { // 正解が決まっていて、8ターン経過か、4ヒットしたら表示
		for (int i = 0; i < 4; i++) {
			DrawGraph(1100, 220 + i * 80, ColorImg[Answer[i]], TRUE); // 答えを画像で表示
		}
	}
	//DrawFormatString(100, 700, 0xffffff, "Turnsは%d", Reasoning[WarpPosition]); // デバック用
	/* 予想したカラーを表示する */
	if (ColorFlg == TRUE || Reasoning[WarpPosition % 4] >= 0) {
		DrawGraph(92 + Turns * 130, 222 + WarpPosition * 80, ColorImg[Reasoning[WarpPosition % 4]], TRUE); // 予想を画像で表示
	}
	else {
		/*DeleteGraph(ColorImg[Reasoning[WarpPosition % 4]]);*/
	}

	if (ColorFlg == TRUE || Reasoning[(WarpPosition + 1) % 4] >= 0) {
		DrawGraph(92 + Turns * 130, 222 + (WarpPosition + 1) % 4 * 80, ColorImg[Reasoning[(WarpPosition + 1) % 4]], TRUE); // 予想を画像で表示
	}
	else {
		/*DeleteGraph(ColorImg[Reasoning[(WarpPosition + 1) % 4]]);*/
	}

	if (ColorFlg == TRUE || Reasoning[(WarpPosition + 2) % 4] >= 0) {
		DrawGraph(92 + Turns * 130, 222 + (WarpPosition + 2) % 4 * 80, ColorImg[Reasoning[(WarpPosition + 2) % 4]], TRUE); // 予想を画像で表示
	}
	else {
		/*DeleteGraph(ColorImg[Reasoning[(WarpPosition + 2) % 4]]);*/
	}

	if (ColorFlg == TRUE || Reasoning[(WarpPosition + 3) % 4] >= 0) {
		DrawGraph(92 + Turns * 130, 222 + (WarpPosition + 3) % 4 * 80, ColorImg[Reasoning[(WarpPosition + 3) % 4]], TRUE); // 予想を画像で表示
	}
	else {
		/*DeleteGraph(ColorImg[Reasoning[(WarpPosition + 3) % 4]]);*/
	}
	/* 過去に入れた色を表示 */
	for (int i = 0; i < Turns; i++) {
		if (SaveReasoning[i][0] >= 0) {
			DrawGraph(92 + i * 130, 222, ColorImg[SaveReasoning[i][0]], TRUE);
		}
		if (SaveReasoning[i][1] >= 0) {
			DrawGraph(92 + i * 130, 222 + 1 * 80, ColorImg[SaveReasoning[i][1]], TRUE);
		}
		if (SaveReasoning[i][2] >= 0) {
			DrawGraph(92 + i * 130, 222 + 2 * 80, ColorImg[SaveReasoning[i][2]], TRUE);
		}
		if (SaveReasoning[i][3] >= 0) {
			DrawGraph(92 + i * 130, 222 + 3 * 80, ColorImg[SaveReasoning[i][3]], TRUE);
		}
		/* ジャッジ用の描画処理を書く */
		for (int j = 0; j < SaveHit[i]; j++) {
			DrawGraph(80 + (j % 2) * 35 + i * 130, 100 + (j / 2) * 40, HitBlowImg[1], TRUE);
		}
		for (int k = 0; k < SaveBlow[i]; k++) {
			DrawGraph(80 + ((SaveHit[i] + k) % 2) * 35 + i * 130, 100 + ((SaveHit[i] + k) / 2) * 40, HitBlowImg[0], TRUE);
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

void HitAndBlow::ERandomChoice()
{
	/* 答えの配列をランダムに設定する */
	srand((unsigned int)time(NULL));

	EChoiceFlg = TRUE;

	if (EChoiceFlg == TRUE) {
		for (int i = 0; i < 4; i++) {
			/*for (int j = 0; j < Turns; j++) {*/
				if (SaveHit[Turns-1] + SaveBlow[Turns-1] == 4) {// ヒットとブローの合計の数が４つになったら
					ChangeColor = rand() % 4;
					Reasoning[i] = SaveReasoning[Turns][ChangeColor];
					if (Reasoning[i] == Reasoning[(i + 1) % 4] || Reasoning[i] == Reasoning[(i + 2) % 4] || Reasoning[i] == Reasoning[(i + 3) % 4]) { // 順番被ってたら
						i--; // iの抽選やり直す
					}
				}else
					Reasoning[i] = rand() % 6;
				if (Reasoning[i] == Reasoning[(i + 1) % 4] || Reasoning[i] == Reasoning[(i + 2) % 4] || Reasoning[i] == Reasoning[(i + 3) % 4]) { // 色が重なったら
					i--; // 選別をやり直す
				}
				// 1ターン目に当たるのを阻止
				if (Turns / 2 == 0 && Reasoning[0] == Answer[0] && Reasoning[1] == Answer[1] && Reasoning[2] == Answer[2] && Reasoning[3] == Answer[3]) {
					i = 0;
				}
			/*}*/
			
		}
		EChoiceFlg = FALSE;
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

