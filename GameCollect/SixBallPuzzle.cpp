#include "SixBallPuzzle.h"
#include "DxLib.h"
#include <math.h>
#include "PadInput.h"
#include <cstdlib>  //ランダム関数用
#include <ctime>    //srandの初期化に使用


SixBallPuzzle::SixBallPuzzle()
{
	//FPSの計測と表示を行うローカル変数の宣言
	LONGLONG nowTime = GetNowHiPerformanceCount();
	LONGLONG oldTime = nowTime;
	double deltaTime = 0;

	/*********************************画像の読込****************************************************/
	
	//ボールの分割読込
	LoadDivGraph("../images/SixBallPuzzle/ball.png", 5, 5, 1, 64, 64, Ball_img);	//画像の全体サイズ：320px*64px

	//背景画像読込
	Back_Ground = LoadGraph("../images/SixBallPuzzle/square.png");

	oldTime = nowTime;
	nowTime = GetNowHiPerformanceCount();

	//ボール生成とNEXTボールの移動
	CreateBlock();

	// Newボールの座標初期化
	gPosX = NEWBLOCK_X;
	gPosY = NEWBLOCK_Y;

	// ブロックの移動処理
	ControlBoll();

	//自動落下
	nowTime = GetNowCount();

	if (nowTime >= (gStartTime )) {
		if (CheckOverlap(gPosX, gPosY + 1) == 0) {
			gPosY++;
		}
		else {
			//　ブロックの固定
			LockBlock(gPosX, gPosY);

			//　ブロック消去とブロックを下ろす処理
			CheckLines();

			//　新しいブロックの作成
			CreateBlock();
		}

		//ステージの初期化（壁設定とクリア）
		for (int i = 0; i < HEIGHT; i++) {
			for (int j = 0; j < WIDTH; j++) {
				if (j == 0 || j == WIDTH - 1 || i == HEIGHT - 1) {
					gStage[i][j] = 9; //壁
				}
				else {
					gStage[i][j] = 0; //初期化 　確認(GetRand(9))
				}
			}
		}
	}

	// ボールの初期位置と速度を設定
	for (int i = 0; i < MaxBalls; i++)
	{
		Random = GetRand(9);			//ランダムの取得
		ballX[i] = 32 + Random * 64;	// X座標
		ballY[i] = -64 * i;				// ボールのY座標をランダムに設定
		ballSpeed[i] = 2;				// 落下速度
		ballActive[i] = true;			// ボールがアクティブかどうか
	}

	SRand(GetNowCount());

	//乱数生成器を初期化
	//srand(static_cast<unsigned int>(time(0)));
}

SixBallPuzzle::~SixBallPuzzle()
{

}

void SixBallPuzzle::CreateBlock(void)
{
	//ランダムにブロック選択
	int r = GetRand(3);

	//新しいブロックをセット＆次のブロックを生成
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			gNewBlock[i][j] = gNextBlock[i][j];
			gNextBlock[i][j] = gBlockList[r][i][j];
		}
	}

	//　新しいブロックの出現位置をセット
	gPosX = NEWBLOCK_X;		// NewブロックのX座標
	gPosY = NEWBLOCK_Y;		// NewブロックのY座標

	//　ゲームオーバーの判定
	if (CheckOverlap(gPosX, gPosY) != 0) {
		//gGameMode = GAMEOVER;
	}
}

void SixBallPuzzle::ControlBoll(void)
{
	//十字キーを押したらブロックの交換を行う
	// ↓キーを押していたらボール君を下に移動させる
	if (CheckHitKey(KEY_INPUT_DOWN) == 1) BallY += 3;
}

int SixBallPuzzle::CheckOverlap(int x2, int y2)
{
	//接触の確認
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (gNewBlock[i][j] != 0) {
				if (gStage[y2 + i][x2 + j] != 0) {
					return 1;
				}
			}
		}
	}

	return 0;
}

void SixBallPuzzle::TurnBlock(void)
{
	//作業用
	int temp[4][4] = { 0 };

	//ブロック補正
	do {

		//ブロックを回転して一時保存
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				temp[j][3 - i] = gNewBlock[i][j];
			}
		}

		//回転後のデータを転記
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				gNewBlock[i][j] = temp[i][j];
			}
		}
		if (CheckOverlap(gPosX, gPosY) == 1 && gPosX >= 9) gPosX--;
		if (CheckOverlap(gPosX, gPosY) == 1 && gPosX <= 0) gPosX++;

	} while (CheckOverlap(gPosX, gPosY) == 1);
}

void SixBallPuzzle::LockBlock(int x2, int y2)
{
	 //ブロックを固定する
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (gNewBlock[i][j] != 0) {
				gStage[y2 + i][x2 + j] = gNewBlock[i][j];
			}
		}
	}
}

void SixBallPuzzle::CheckLines(void)
{
	int flg;
	int lineCut = 0;

	// ブロックが横一列だった時は flg が 0
	for (int i = 0; i < HEIGHT - 1; i++) {
		flg = 0;
		for (int j = 1; j <= WIDTH - 1; j++) {
			if (gStage[i][j] == 0) {
				flg = 1;
				break;
			}
		}

		// flgが0ならスコア加算
		if (flg == 0) {
			//　まとめて消去するライン数のカウント
			lineCut++;

			//固定済みブロックを下ろす
			for (int k = i; k > 0; k--) {
				for (int j = 1; j <= WIDTH - 1; j++) {
					gStage[k][j] = gStage[k - 1][j];
				}
			}
			//gScore += 1000;
		}
	}
}

//void SixBallPuzzle::ChangeBlock(void)
//{
//	// 作業用
//	int temp[4][4] = { 0 };
//
//	//ストックなしなら実行
//	if (gStokFlg == 0) {
//		gStokFlg = 1;
//		//　新しいブロックをストックに保管
//		for (int i = 0; i < 4; i++) {
//			for (int j = 0; j < 4; j++) {
//				gStokBlock[i][j] = gNewBlock[i][j];
//			}
//		}
//		//　新しいブロックのセット
//		CreateBlock();
//	}
//	else {
//		//　ストックありならストックと交換
//		for (int i = 0; i < 4; i++) {
//			for (int j = 0; j < 4; j++) {
//				temp[i][j] = gNewBlock[i][j];
//				gNewBlock[i][j] = gStokBlock[i][j];
//				gStokBlock[i][j] = temp[i][j];
//			}
//		}
//	}
//}

AbstractScene* SixBallPuzzle::Update()
{
	// ランダムなボールのインデックスを生成
	//randomBallIndex = rand() % 5;  // 0から4の範囲でランダムにボールを選択

	// y座標を自動的に更新して画像を描画
	// 画像の座標を画面内に制限する（画面下端でリセットする）

	// y座標を自動的に更新してボールを描画
	for (int i = 0; i < MaxBalls; i++)
	{
		// 画面外に出たら再利用
		if (ballY[i] > HEIGHT)
		{
			ballY[i] = -64;			// 画面上部から利用
			ballX[i] = WIDTH - 64;  // ボールのX座標をランダムに設定
			ballSpeed[i] = 1;		// 落下速度
			ballActive[i] = true;	// ボールがアクティブかどうか
		}
	}

	// y座標を自動的に更新してボールを描画
	for (int i = 0; i < MaxBalls; i++)
	{
		if (ballActive[i])
		{
			ballY[i] += ballSpeed[i];  // ボールを落下させる

			// 画面下部で積み上げ
			if (ballY[i] > HEIGHT - 64)
			{
				ballY[i] = HEIGHT - 64;  // 画面下部で停止
				ballSpeed[i] = 0;  // 落下速度を停止

				for (int j = 0; j < MaxBalls; j++)
				{
					// 現在のボールが他のボールと重ならないようにする
					if (i != j && ballActive[j] || ballY[j] < ballY[i] + 64 && ballY[j] + 64 > ballY[i])
					{
						ballY[i] = ballY[j];  // 積み上げる位置を調整
						break;
					}
				}
			}
		}
	}

	return this;
}

void SixBallPuzzle::Draw() const
{
	//選択したランダムなボールを描画
	//DrawGraph(100, FallingY, Ball_img[randomBallIndex], TRUE);

	//背景画像の描画
	DrawGraph(10, 10, Back_Ground, FALSE);

	//ボールの分割描画
	for (int i = 0; i < MaxBalls; i++)
	{
		if (ballActive[i])
		{
			DrawGraph(ballX[i], ballY[i], Ball_img[0], TRUE);
		}
	}

	//　ローカル変数
	//int posX, tempScore;

	//ステージの値でブロックを表示
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (gStage[i][j] != 9) {
				DrawGraph(BLOCKSIZE * j, BLOCKSIZE * i, gBlockImg[gStage[i][j]], TRUE);
			}
		}
	}

	//// Newブロックを描画
	//for (int i = 0; i < 4; i++) {
	//	for (int j = 0; j < 4; j++) {
	//		if (gNewBlock[i][j] != 0) {
	//			DrawGraph(BLOCKSIZE * (j + gPosX), BLOCKSIZE * (i + gPosY), gBlockImg[gNewBlock[i][j]], TRUE);
	//		}
	//	}
	//}

	// Nextブロックとストックブロックを描画
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			//DrawGraph(BLOCKSIZE * j + 480, BLOCKSIZE * i + 350, gBlockImg[gNextBlock[i][j]], TRUE);
			DrawGraph(BLOCKSIZE * j + 360, BLOCKSIZE * i + 240, gBlockImg[gStokBlock[i][j]], TRUE);
		}
	}

	//	レベル表示
	//DrawGraph(400, 140, gNumberImg[gLevel], TRUE);
}


