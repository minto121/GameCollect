#include "Connect4.h"
#include "PadInput.h"
#include "GameSelect.h"


#define POINTX 132.5
int Turn = 1;		//手番


Connect4::Connect4()
{
	if ((gStageImg = LoadGraph("images/SixBallPazzle/Board2.png")) == -1);				//ステージ画像読込
	if ((gCursorImg = LoadGraph("images/SixBallPazzle/Arrow.png")) == -1);				//矢印画像読込
	if ((gRedCoinImg = LoadGraph("images/SixBallPazzle/RedCoin.png")) == -1);			//ボールの分割画像読込
	if ((gYellowCoinImg = LoadGraph("images/SixBallPazzle/YellowCoin.png")) == -1);		//ボールの分割画像読込
	if ((gClearImg = LoadGraph("images/SixBallPazzle/Clear.png")) == -1);		//ボールの分割画像読込

}

Connect4::~Connect4()
{

}

AbstractScene* Connect4::Update()
{
	//クリアした後の画面リセット
	if (Clear != 0)
	{
		if (TimeCnt >= 180) {
			return new Connect4();
		}
		else {
			TimeCnt++;
		}

	}
	if (Clear == 0)
	{
		/****** カーソルの移動処理 *******/
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT)) {
			if (++Num > 7) Num = 1;	//右へ
		}

		if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT)) {
			if (--Num < 1) Num = 7;	//左へ
		}
		Cursor = Num * POINTX + 20;	//カーソルのX座標を増やす

		/******** ボタンで赤色か黄色に切り替える *******/
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_B)) {

			clsDx();	//printfDxを上部に固定
			SetLogFontSize(32);	//printfDxの文字サイズを変える

			switch (Turn)		//ターンの切り替え
			{
			case 1:		//黄色のターン
				printfDx("赤色の番だよ \n");
				for (int y = 5; y >= 0; y--) {	//矢印の縦の列に黄色を描画させる
					if (Stage[Num - 1][y] == 0) {	//Numは横の行を見る
						Stage[Num - 1][y] = 1;		//何もないときに１を代入

						for (int i = 0; i < 4; i++) {
							if (bool connect = CheckConnect(Num - 1, y, i) == true) {
								// クリア
								Clear = 1;
							}
						}
						break;
					}
				}
				Turn = 2;	//コインを置いたらターンを２へ変更
				break;
			case 2:		//赤のターン
				printfDx("黄色の番だよ \n");
				for (int y = 5; y >= 0; y--) {	//矢印の縦の列に黄色を描画させる
					if (Stage[Num - 1][y] == 0) {	//Numは横の行を見る
						Stage[Num - 1][y] = 2;			//何もない時に２を代入

						for (int i = 0; i < 4; i++) {
							if (bool connect = CheckConnect(Num - 1, y, i) == true) {
								// クリア
								Clear = 2;
								printfDx("%d", TimeCnt);
							}
						}
						break;
					}
				}
				Turn = 1;	//コインを置いたらターンを１へ変更
				break;
			}
		}
	}

	return this;

}

void Connect4::Draw() const
{
	DrawGraph(0, 0, gStageImg, TRUE);		//ステージ画像を描画
	DrawGraph(Cursor, 0, gCursorImg, TRUE);	//カーソル画像を描画
	DrawFormatString(950, 10, 0xff0000,"パッドの十字キーで\nカーソルを動かして\nBボタンを押して始めてね");	//説明
	
	SetFontSize(24);
	DrawFormatString(0, 100, 0xffff00, "先行:黄色");
	DrawFormatString(0, 200, 0xff0000, "後行:赤色");
	
	//コインの描画
	for (int x = 6; x >= 0; x--) {		//縦の添え字を見る
		for (int y = 5; y >= 0; y--) {		//横の添え字を見る
			if (Stage[x][y] == 1) {		//1なら黄色のコインをカーソルの位置に描画
				DrawGraph((x * POINTX) + POINTX, y * 100 + 65, gYellowCoinImg, TRUE);
			}
			if (Stage[x][y] == 2) {		//２なら赤色のコインをカーソルの位置に描画
				DrawGraph((x * POINTX) + POINTX, y * 100 + 65, gRedCoinImg, TRUE);
			}
		}
	}

	if (Clear == 1) {
		SetFontSize(200);
		DrawBox(200,200,1200,400,0xffffff,TRUE);
		DrawFormatString(200, 200, 0xff00ff, "黄色の勝ち！", Clear);

	}
		
	if (Clear == 2) {
			SetFontSize(200);
			DrawBox(200, 200, 1200, 400, 0xffffff, TRUE);
			DrawFormatString(200, 200, 0xff00ff, "赤色の勝ち！", Clear);

	}
}

/***** 同じ色のコインが4個以上並んでいるかをチェック *****/
bool Connect4::CheckConnect(int x, int y, int type) {

	int min = CheckConnectMin(x, y, type, 0);
	switch (type) {

		// 横
	case 0:
		// 4つ並んでるか確認
		for (int i = 0; i < 4; i++) {
			// 今の座標 から 1番左の座標 + i が今の座標と一緒じゃない場合 false
			if (Stage[(x - min) + i][y] != Stage[x][y]) {
				return false;
			}
		}
		break;

		// 縦
	case 1:
		// 4つ並んでるか確認
		for (int i = 0; i < 4; i++) {
			// 今の座標 から 1番の下の座標 + i が今の座標と一緒じゃない場合 false
			if (Stage[x][(y - min) + i] != Stage[x][y]) {
				return false;
			}
		}
		break;

		// 斜め右下・左上
	case 2:
		// 4つ並んでるか確認
		for (int i = 0; i < 4; i++) {
			// 今の座標 から 1番左上の座標 + i が今の座標と一緒じゃない場合 false
			if (Stage[(x - min) + i][(y - min) + i] != Stage[x][y]) {
				return false;
			}
		}
		break;

		// 斜め右上・左下
	case 3:
		// 4つ並んでるか確認
		for (int i = 0; i < 4; i++) {
			// 今の座標 から 1番左下の座標 + i が今の座標と一緒じゃない場合 false
			if (Stage[(x - min) + i][(y + min) - i] != Stage[x][y]) {
				return false;
			}
		}
		break;

	default:
		break;
	}

	// 4回ループして最後まで行けた場合 true
	return true;
}


// 並んでいるコインの一番左（斜めであれば、左下か左上）を取得
int Connect4::CheckConnectMin(int x, int y, int type, int cnt)	
{
	if (x - 1 >= 0 && x + 1 <= 9) {		// Xが0から7の間なら見る
		if (y - 1 >= 0 && y + 1 <= 6) {		// Yが0から6の間なら見る

			switch (type) {
				//横の確認
			case 0:
				if (Stage[x - 1][y] == Stage[x][y]) {
					cnt++;
					cnt = CheckConnectMin(x - 1, y, type, cnt);
				}
				break;
				//縦の確認
			case 1:
				if (Stage[x][y] == Stage[x][y - 1]) {
					cnt++;
					cnt = CheckConnectMin(x, y - 1, type, cnt);
				}
				break;
				// 斜め左上の確認
			case 2:
				if (Stage[x - 1][y - 1] == Stage[x][y]) {
					cnt++;
					cnt = CheckConnectMin(x - 1, y - 1, type, cnt);
				}
				break;
				// 斜め左下の確認
			case 3:
				if (Stage[x - 1][y + 1] == Stage[x][y]) {
					cnt++;
					cnt = CheckConnectMin(x - 1, y + 1, type, cnt);
				}
				break;
			default:
				break;
			}
		}
	}
	return cnt;		//cntの値を返す
}