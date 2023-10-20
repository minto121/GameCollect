#include"Hit&Blow.h"
#include"DxLib.h"

HitAndBlow::HitAndBlow() 
{
	// ダミー画像を読込
	LoadGraph("../images/HitAndBlow/BG_Dummy.png");
	// ヒットした時の画像読込
	LoadGraph("../images/HitAndBlow/ヒットピン.png");
	// ブローした時の画像読込
	LoadGraph("../images/HitAndBlow/ブローピン.png");
}

HitAndBlow::~HitAndBlow()
{

}

AbstractScene* HitAndBlow::Update()
{

}

void HitAndBlow::Draw() const
{

}