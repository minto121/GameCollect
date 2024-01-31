#include "Connect4.h"
#include"PadInput.h"

#define POINTX 132.5
int Turn = 1;		//手番

Connect4::Connect4()
{
	if ((gStageImg = LoadGraph("images/SixBallPazzle/Board2.png")) == -1);				//ステージ画像読込
	if ((gCursorImg = LoadGraph("images/SixBallPazzle/Arrow.png")) == -1);				//矢印画像読込
	if ((gRedCoinImg = LoadGraph("images/SixBallPazzle/RedCoin.png")) == -1);			//ボールの分割画像読込
	if ((gYellowCoinImg = LoadGraph("images/SixBallPazzle/YellowCoin.png")) == -1);		//ボールの分割画像読込
}

Connect4::~Connect4()
{

}

AbstractScene* Connect4::Update()
{
	/****** カーソルの移動処理 *******/
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT)) {
		if (++Num > 7) Num = 1;	//右へ
	}

	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT)) {
		if (--Num < 1) Num = 7;	//左へ
	}

	Cursor = Num  * POINTX + 20;	//カーソルのX座標を増やす

	/******** ボタンで赤色か黄色に切り替える *******/
	
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_B)) {
		clsDx();
		SetLogFontSize(32);
		switch (Turn)
		{
		case 1:
			printfDx("黄色だよ \n");
			for (int y = 5; y >= 0; y--) {	//矢印の縦の列に黄色を描画させる
				if (Stage[Num - 1][y] == 0) {	//Numは横の行を見てる
					Stage[Num - 1][y] = 1;

					for (int i = 0; i < 4; i++) {
						if (bool connect = CheckConnect(Num - 1, y, i) == true) {
							// クリア
							printfDx("クリア！\n");
						}
					}
					break;
				}
			}
			Turn = 2;
			break;
		case 2:
			printfDx("赤色だよ \n");
				for (int y = 5; y >= 0; y--) {	//矢印の縦の列に黄色を描画させる
					if (Stage[Num - 1][y] == 0) {	//Numは横の行を見てる;
						Stage[Num - 1][y] = 2;

						for (int i = 0; i < 4; i++) {
							if (bool connect = CheckConnect(Num - 1, y, i) == true) {
								// クリア
								printfDx("クリア！\n");
							}
						}
						break;
					}
				}
				Turn = 1;
				break;
		}
	}
	return this;
}

void Connect4::Draw() const
{
	DrawGraph(0, 0, gStageImg, TRUE);		//ステージ画像
	DrawGraph(Cursor, 0, gCursorImg, TRUE);	//カーソル画像
	DrawFormatString(0, 100, 0xf0f0f0, "%d", Cursor);	//カーソルの値
	
	//ボールの描画
	for (int x = 6; x >= 0; x--) {
		for (int y = 5; y >= 0; y--) {
			if (Stage[x][y] == 1) {
				DrawGraph((x * POINTX) + POINTX, y * 100 + 65, gYellowCoinImg, TRUE);
			}
			if (Stage[x][y] == 2) {
				DrawGraph((x * POINTX) + POINTX, y * 100 + 65, gRedCoinImg, TRUE);
			}
		}
	}
}

bool Connect4::CheckConnect(int x, int y, int type) {
	int min = CheckConnectMin(x, y, type, 0);
	switch (type) {

		// 横
	case 0:
		// 4つ並んでるか確認
		for (int i = 0; i < 4; i++) {
			// 今の座標 - 一番左の座標 + i が今の座標と一緒じゃない場合false
			if (Stage[(x - min) + i][y] != Stage[x][y]) {
				return false;
			}
		}
		break;

		// 縦
	case 1:
		// 4つ並んでるか確認
		for (int i = 0; i < 4; i++) {
			if (Stage[x][(y - min) + i] != Stage[x][y]) {
				return false;
			}
		}
		break;

		// 斜め右下・左上
	case 2:
		// 4つ並んでるか確認
		for (int i = 0; i < 4; i++) {
			if (Stage[(x - min) + i][(y - min) + i] != Stage[x][y]) {
				return false;
			}
		}
		break;

		// 斜め右上・左下
	case 3:
		// 4つ並んでるか確認
		for (int i = 0; i < 4; i++) {
			if (Stage[(x - min) + i][(y + min) - i] != Stage[x][y]) {
				return false;
			}
		}
		break;

	default:
		break;
	}

	// 4回ループして最後まで行けた場合true
	return true;
}


// 一番左を取得
int Connect4::CheckConnectMin(int x, int y, int type, int cnt)
{
	// 0から7の間なら見る
	if (x - 1 >= 0 && x + 1 <= 7) {
		if (y - 1 >= 0 && y + 1 <= 6) {

			switch (type) {
				//横を確認
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
				// 斜め右下・左上
			case 2:
				if (Stage[x - 1][y - 1] == Stage[x][y]) {
					cnt++;
					cnt = CheckConnectMin(x - 1, y - 1, type, cnt);
				}
				break;
				// 斜め右上・左下
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
	return cnt;
}