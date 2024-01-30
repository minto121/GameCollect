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

		switch (Turn)
		{
		case 1:
			printfDx("黄色だよ \n");
			for (int y = 5; y >= 0; y--) {	//矢印の縦の列に黄色を描画させる
				if (Stage[Num - 1][y] == 0) {	//Numは横の行を見てる
					Stage[Num - 1][y] = 1;
					//printfDx("%d", y);
					Check(y);
					CheckWidth(y,x,cnt,col);
					break;
				}
			}
			Turn = 2;
			break;
		case 2:
			printfDx("赤色だよ \n");
				for (int y = 5; y >= 0; y--) {	//矢印の縦の列に黄色を描画させる
					if (Stage[Num - 1][y] == 0) {	//Numは横の行を見てる
						//printfDx("%d \n");
						Stage[Num - 1][y] = 2;
						Check(y);
						CheckWidth(y,x,cnt,col);
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

void Connect4::Check(int y)
{
	int Height = y;	//yの添え字を引っ張って来る
	
	//縦のチェック
	if ((Stage[Num - 1][Height] == Stage[Num - 1][Height + 1]) &&
		(Stage[Num - 1][Height] == Stage[Num - 1][Height + 2]) &&
		(Stage[Num - 1][Height] == Stage[Num - 1][Height + 3]))
	{
		printfDx("クリア!! \n");
	}

}

void Connect4::CheckWidth(int y,int x,int cnt,int col)
{
	int Width = Num - 1;
	int c;
	/*int col;
	int cnt = 0;*/

	//横のチェック
	//if (Stage[7][6] == 0)return 0;

	if (cnt >= 4) {

		Stage[Num][Width];
		col = Stage[Num][Width];
		c = Stage[Num][Width];
		(cnt)++;

		if (Stage[Num][Width + 1] == c)Check( Width - 1);

		printf("000");

	}
}


	
