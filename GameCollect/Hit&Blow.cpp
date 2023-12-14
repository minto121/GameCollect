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
	/* 画像読み込み */
	TableBgImg = LoadGraph("images/HitAndBlow/BackGround02.png");

	BoardImg = LoadGraph("images/HitAndBlow/HitBlowBoard.png");

	LoadDivGraph("images/HitAndBlow/ColorBall.png", 6, 6, 1, 64, 64, ColorImg);
	LoadDivGraph("images/HitAndBlow/HitBlowPin.png", 2, 2, 1, 32, 32, HitBlowImg);

	/* BGM・SE読み込み */
	PutPinSE = LoadSoundMem("../sound/SE/PutPin.wav");
	HitPinSE = LoadSoundMem("../sound/SE/HitPin.wav");
	BlowPinSE = LoadSoundMem("../sound/SE/BlowPin.wav");

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

	DescriptionFlg = TRUE;
	OperationFlg = TRUE;

	WinLoseDrawFlg = -1;
}

HitAndBlow::~HitAndBlow()
{
	/* メモリ容量軽くするため、音楽ファイル消しておく */
	DeleteSoundMem(PutPinSE);
	DeleteSoundMem(HitPinSE);
	DeleteSoundMem(BlowPinSE);
}

AbstractScene* HitAndBlow::Update()
{
	RandomDecision(); // 答えの配列をランダムに設定する

	FontSize = GetFontSize();

	if (DescriptionFlg == TRUE) { // 説明画面にいる間
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
			//if (Count < 60) { // 1秒立ってなかったら、
			//	Count++; // 1フレーム足す
			//}
			//else { // ボタンを押して、1秒たったら
			//	Count = 0; // カウントをリセットして、
			//	DescriptionFlg = FALSE; // 説明画面を閉じる
			//}
			DescriptionFlg = FALSE; // 説明画面を閉じる
			OperationFlg = TRUE; // 操作説明画面に入る
		}
		/* ここに自分が駒を入れる処理を書く */
	}
	else if (OperationFlg == TRUE) {
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
			OperationFlg = FALSE; // 操作説明画面を閉じる
		}
		else if (PAD_INPUT::OnButton(XINPUT_BUTTON_B)) {
			OperationFlg = FALSE; // 操作説明画面を閉じる
			DescriptionFlg = TRUE; // 説明画面に戻る
		}
	}else if (DescriptionFlg == FALSE && OperationFlg == FALSE && WinLoseDrawFlg == -1 && Turns < 8 && SaveHit[Turns - 1] != 4) {
	
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
			ERandomChoice(); // 適当に色を入れて

			Judgment(); // ジャッジ処理呼ぶ

			/* 音を鳴らす処理 */
			PlaySoundSE();

			/* プレイヤーターンに行く前に色をリセット */
			ResetColor();
			MoveFlg = 1; // 自分のターンに移動
		}
		else if (PAD_INPUT::OnButton(XINPUT_BUTTON_X) && Reasoning[0] != -1 && Reasoning[1] != -1 && Reasoning[2] != -1 && Reasoning[3] != -1) // 色が入っている時
		{
			Judgment(); // ジャッジ処理を呼ぶ

			/* 音を鳴らす処理 */
			PlaySoundSE();

			/* エネミーターンに行く前に色をリセット */
			ResetColor();
			MoveFlg = 0; // 敵のターンに移動
		}
		else if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) // 色を入れる処理
		{
			Reasoning[WarpPosition] = SidePosition;  // 色を場所に配置
			WarpPosition++; // 色を選択するカーソルの位置を一つずらす
			PlaySoundMem(PutPinSE, DX_PLAYTYPE_NORMAL, TRUE);
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
			else if (MoveFlg == 0) {
				Count = 0; // カウントをリセット
				WinLoseDrawFlg = 1; // 勝敗フラグを勝利状態にする
			}
			else {
				Count = 0; // カウントをリセット
				WinLoseDrawFlg = 2; // 勝敗フラグを負け状態にする
			}
		}
		else {
			if (Count < WAITTIME) {
				Count++;
			}
			else {
				Count = 0; // カウントをリセット
				WinLoseDrawFlg = 0; // 勝敗フラグを引き分け状態にする
			}
		}
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_A) && WinLoseDrawFlg != -1) {
			SetFontSize(FontSize); // フォントサイズを元に戻す
			return new GameSelect();// ゲームセレクト画面に遷移
		}
	}



	
	return this;
}

void HitAndBlow::Draw() const
{
	DrawGraph(0, 0, TableBgImg, FALSE); // 背景画像表示(透明OFF)

	if (DescriptionFlg == TRUE) { // ゲームの遊び方・勝敗について
		SetFontSize(40);
		DrawFormatString(500, 0, 0xffffff, "＜ゲームの遊び方＞");
		DrawFormatString(500, 480, 0xffffff, "＜ゲームの勝敗＞");

		SetFontSize(30);
		/* ゲームの遊び方 */
		DrawFormatString(0, 50, 0xffffff, "○６色の色（赤、青、緑、黄、紫、白）からランダムに選ばれる");
		DrawFormatString(0, 80, 0xffffff, "４色の色と位置を当てるゲーム!");
		DrawFormatString(0, 110, 0xffffff, "○プレイヤーおよび対戦相手は、４色の色と位置を予想する。");
		DrawFormatString(0, 140, 0xff0000, "○ヒントとして、色と位置が当たっている「ヒット」と、");
		DrawFormatString(0, 170, 0xff0000, "色だけ当たっている「バイト」が何個あるか、");
		DrawFormatString(0, 200, 0xff0000, "それぞれ教えてもらえる。ただし、");
		DrawFormatString(0, 230, 0xff0000, "どこがヒットしていて、どの色がバイトしているかまでは教えてもらえない。");
		DrawFormatString(0, 260, 0x00ff00, "例）設定された色が紫・白・赤・黄だとして、");
		DrawFormatString(0, 290, 0x00ff00, "プレイヤーが青・赤・緑・黄と予想した場合、");
		DrawFormatString(0, 320, 0x00ff00, "プレイヤーのヒントとして、1ヒット1ブロー");
		DrawFormatString(0, 350, 0x00ff00, "（黄は色と位置が合ってるので1ヒット、赤は色だけ合ってるので1ブロー）");
		DrawFormatString(0, 380, 0x00ff00, "という情報が与えられる。");
		DrawFormatString(0, 410, 0xffffff, "○これを繰り返して、先に4ヒット");
		DrawFormatString(0, 440, 0xffffff, "（つまり、4つの色と位置が全て当たっている状態）すれば勝ちとなる。");

		/* ゲームの勝敗 */
		DrawFormatString(0, 520, 0xffffff, "○ランダムに決まっている色と場所を全て当てた（4ヒットした）方の勝利！");
		DrawFormatString(0, 550, 0xffffff, "○自分と対戦相手が合計8ターン以内に色と場所を全て当てられなかった場合は、");
		DrawFormatString(0, 580, 0xffffff, "引き分けとなる。");

		/* 遷移を教える文章*/
		SetFontSize(60);
		DrawFormatString(300, 620, 0xffffff, "Aボタンで操作方法画面へ");
	}
	else if (OperationFlg == TRUE) {
		SetFontSize(40);
		DrawFormatString(500, 0, 0xffffff, "＜操作方法＞");
		DrawFormatString(500, 240, 0xffffff, "＜ルール＞");


		SetFontSize(30);
		DrawFormatString(0, 50, 0xffffff, "○十字キーの←、→で色を選択するカーソルが動く。");
		DrawFormatString(0, 80, 0xffffff, "○十字キーの↑、↓で色を置く場所のカーソルが動く。");
		DrawFormatString(0, 110, 0xffffff, "○Aボタンで色を置くことが出来る。");
		DrawFormatString(0, 140, 0xffffff, "○Bボタンで置いていた色を取ることが出来る。");
		DrawFormatString(0, 170, 0xffffff, "○4つ全て置いた状態で、Xボタンを押すと、");
		DrawFormatString(0, 200, 0xffffff, "置いている色が確定する。");
		/* ヒットピンの画像と説明 */
		DrawFormatString(0, 280, 0xffffff, "○");
		DrawGraph(30, 280, HitBlowImg[1], TRUE);
		DrawFormatString(70, 280, 0xffffff, "ヒットピン：色と場所があっている");
		/* ブローピンの画像と説明 */
		DrawFormatString(0, 310, 0xffffff, "○");
		DrawGraph(30, 310, HitBlowImg[0], TRUE);
		DrawFormatString(70, 310, 0xffffff, "ブローピン：色のみがあっている");
		DrawFormatString(0, 340, 0xffffff, "○先攻・後攻はランダムで決められる。");
		DrawFormatString(0, 370, 0xffffff, "○プレイヤーのターンの場所は、");
		DrawFormatString(480, 370, 0xff0000, "P");
		DrawFormatString(0, 400, 0xffffff, "○相手のターンの場所は、");
		DrawFormatString(390, 400, 0x00ffff, "E");
		DrawFormatString(420, 400, 0xffffff, "と上に表示される。");

		SetFontSize(60);
		DrawFormatString(300, 560, 0xffffff, "Aボタンでゲームスタート");
		DrawFormatString(300, 620, 0xffffff, "Bボタンでゲームの遊び方画面へ");


	}
	else if (WinLoseDrawFlg == 0 || WinLoseDrawFlg == 1 || WinLoseDrawFlg == 2) {
		switch (WinLoseDrawFlg) {
		case 0:
			SetFontSize(60);
			DrawFormatString(300, 360, 0x00ff00, "引き分けです。");
			DrawFormatString(300, 500, 0xffffff, "Aボタンでゲームせレクト画面へ");
			break;
		case 1:
			SetFontSize(60);
			DrawFormatString(300, 360, 0xff0000, "あなたの勝ちです！！");
			DrawFormatString(300, 500, 0xffffff, "Aボタンでゲームせレクト画面へ");
			break;
		case 2:
			SetFontSize(60);
			DrawFormatString(300, 360, 0x0000ff, "あなたの負けです・・・");
			DrawFormatString(300, 500, 0xffffff, "Aボタンでゲームせレクト画面へ");
			break;
		}
	}
	else { // ゲームメイン画像処理
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
		MoveFlg = GetRand(1);
		TurnFlg = FALSE;
		FirstMoveFlg = MoveFlg; // 先攻か後攻かを覚えてもらう（描画処理で必要）
	}
	
}

void HitAndBlow::ERandomChoice()
{
	/* 答えの配列をランダムに設定する */
	srand((unsigned int)time(NULL));

	for (int i = 0; i < 4; i++) {
		if (SaveHit[Turns - 1] + SaveBlow[Turns - 1] == 4) {// 前のターンでヒットとブローの合計の数が４つになったら
			Reasoning[i] = SaveReasoning[Turns - 1][GetRand(3)]; // 場所だけ変える
			if (Reasoning[i] == Reasoning[(i + 1) % 4] || Reasoning[i] == Reasoning[(i + 2) % 4] || Reasoning[i] == Reasoning[(i + 3) % 4]) { // 順番被ってたら
				i--; // iの抽選やり直す
			}
			/* 全く同じ色、順番になってないか確かめる処理 */
			if (Turns != 0 && i == 3) {
				CheckCovered();
				if (CoveringFlg == TRUE) { // もし、被っていたら
					i = -1; // 0代入すると3つしか交換しないので、インクリメントして0になる-1を代入
				}
			}
		}
		else if (SaveHit[Turns - 2] + SaveBlow[Turns - 2]) {// 前の自分のターンでヒットとブローの合計の数が４つになったら
			Reasoning[i] = SaveReasoning[Turns - 2][GetRand(3)]; // 場所だけ変える
			if (Reasoning[i] == Reasoning[(i + 1) % 4] || Reasoning[i] == Reasoning[(i + 2) % 4] || Reasoning[i] == Reasoning[(i + 3) % 4]) { // 順番被ってたら
				i--; // iの抽選やり直す
			}
			/* 全く同じ色、順番になってないか確かめる処理 */
			if (Turns != 0 && i == 3) {
				CheckCovered(); // 被りないか確認
				if (CoveringFlg == TRUE) {
					i = -1; // 0代入すると3つしか交換しないので、インクリメントして0になる-1を代入
				}
			}
		}
		else {
			Reasoning[i] = rand() % 6;

			if (Reasoning[i] == Reasoning[(i + 1) % 4] || Reasoning[i] == Reasoning[(i + 2) % 4] || Reasoning[i] == Reasoning[(i + 3) % 4]) { // 色が重なったら
				i--; // 選別をやり直す
			}

			/* 全く同じ色、順番になってないか確かめる処理 */
			if (Turns != 0 && i == 3) {	
				CheckCovered(); // 被りないか確認
				if (CoveringFlg == TRUE) {
					i = -1; // 0代入すると3つしか交換しないので、インクリメントして0になる-1を代入
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

void HitAndBlow::CheckCovered()
{
	for (Covering = 0; Covering < Turns; Covering++) {
		if (Reasoning[0] == SaveReasoning[Covering][0]
			&& Reasoning[1] == SaveReasoning[Covering][1]
			&& Reasoning[2] == SaveReasoning[Covering][2]
			&& Reasoning[3] == SaveReasoning[Covering][3]) { // 前入れた奴と全く同じだったら
			
			CoveringFlg = TRUE; // 被っていたと知らせる

			Reasoning[0] = -1;// 中身全部空にする
			Reasoning[1] = -1;// 中身全部空にする
			Reasoning[2] = -1;// 中身全部空にする
			Reasoning[3] = -1;// 中身全部空にする

			break; // 被りがあるか調べたいので、一度被ったらループを抜ける

		}
		else {
			CoveringFlg = FALSE; // 被っていないと知らせる
		}

	}
}

void HitAndBlow::PlaySoundSE() 
{
	/* 音を鳴らす処理 */
	for (int i = 0; i < SaveHit[Turns]; i++) {
		if (CheckSoundMem(HitPinSE) == 0) { // 再生させていなかったら
			if (CheckSoundMem(BlowPinSE) == 0) {
				PlaySoundMem(HitPinSE, DX_PLAYTYPE_BACK, TRUE); // 再生する
				Count = 0; // カウント時間をリセット
			}
			else {
				i--;
			}
		}
		else {
			Count++;
			i--;
		}
		Count = 0;// カウント時間をリセット
	}
	Count = 0; // カウント時間をリセット
	for (int i = 0; i < SaveBlow[Turns] + 1; i++) {
		if (CheckSoundMem(BlowPinSE) == 0) { // 再生させていなかったら
			if (CheckSoundMem(HitPinSE) == 0) {
				PlaySoundMem(BlowPinSE, DX_PLAYTYPE_BACK, TRUE); // 再生する
				Count = 0; // カウント時間をリセット
			}
			else {
				i--;
			}	
		}
		else {
			Count++;
			i--;
		}
	}
	StopSoundMem(BlowPinSE);
	Count = 0;// カウント時間をリセット
}
