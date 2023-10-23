#include"Hit&Blow.h"
#include"DxLib.h"
#include<stdlib.h>
#include<time.h>

HitAndBlow::HitAndBlow() 
{
	// ダミー画像を読込
	/*LoadGraph("../images/HitAndBlow/BG_Dummy.png");*/
	// ヒットした時の画像読込
	HitImg = LoadGraph("../images/HitAndBlow/ヒットピン.png");
	// ブローした時の画像読込
	BlowImg = LoadGraph("../images/HitAndBlow/ブローピン.png");
	// 色の画像追加(仮表示)
	ColorImg[0] = LoadGraph("../images/HitAndBlow/青色の駒.png");
	ColorImg[1] = LoadGraph("../images/HitAndBlow/赤色の駒.png");
	ColorImg[2] = LoadGraph("../images/HitAndBlow/緑色の駒.png");
	ColorImg[3] = LoadGraph("../images/HitAndBlow/黄色の駒.png");
	ColorImg[4] = LoadGraph("../images/HitAndBlow/紫色の駒.png");
	ColorImg[5] = LoadGraph("../images/HitAndBlow/白色の駒.png");
}

HitAndBlow::~HitAndBlow()
{
	
}

AbstractScene* HitAndBlow::Update()
{
	/* 答えの配列をランダムに設定する */
	srand((unsigned int)time(NULL));

	for (int i = 0; i < 4; i++) {
		Answer[i] = rand() % 6;
		if (Answer[i] == Answer[(i + 1) % 4] || Answer[i] == Answer[(i + 2) % 4] || Answer[i] == Answer[(i + 3) % 4]) {
			i--;
		}
	}
	return this;
}

void HitAndBlow::Draw() const
{
	for (int i = 0; i < 6; i++) { // 駒を表示
		DrawGraph(350 + i * 100, 600, ColorImg[i], TRUE); // それぞれの色の駒を表示(位置は決定)
	}
	DrawGraph(200, 200, HitImg, TRUE); // それぞれの色の駒を表示
	DrawGraph(200, 250, BlowImg, TRUE); // それぞれの色の駒を表示

	for (int i = 0; i < 4; i++) {
		DrawFormatString(400, 400 + i * 20, 0xffffff, "%d", Answer[i]);
	}
	
}