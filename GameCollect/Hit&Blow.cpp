#include"Hit&Blow.h"
#include"DxLib.h"

HitAndBlow::HitAndBlow() 
{
	// ダミー画像を読込
	LoadGraph("../images/HitAndBlow/BG_Dummy.png");
	// ヒットした時の画像読込
	HitImg=LoadGraph("../images/HitAndBlow/ヒットピン1.png");
	// ブローした時の画像読込
	BlowImg=LoadGraph("../images/HitAndBlow/ブローピン.png");
	// 色の画像追加(仮表示)
	Color[0] = LoadGraph("../images/HitAndBlow/青色の駒1.png");
	Color[1] = LoadGraph("../images/HitAndBlow/赤色の駒1.png");
	Color[2] = LoadGraph("../images/HitAndBlow/緑色の駒1.png");
	Color[3] = LoadGraph("../images/HitAndBlow/黄色の駒1.png");
	Color[4] = LoadGraph("../images/HitAndBlow/紫色の駒1.png");
	Color[5] = LoadGraph("../images/HitAndBlow/白色の駒.png");
}

HitAndBlow::~HitAndBlow()
{
	
}

AbstractScene* HitAndBlow::Update()
{
	return this;
}

void HitAndBlow::Draw() const
{
	for (int i = 0; i < 6; i++) {
		DrawGraph(200 + i * 75, 200, Color[i], TRUE); // それぞれの色の駒を表示
	}
}