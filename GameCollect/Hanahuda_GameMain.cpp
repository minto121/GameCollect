#include"DxLib.h"
#include"Hanahuda_GameMain.h"
#include"Math.h"

Hanahuda::Hanahuda()
{
	Stage = LoadGraph("images/Hanafuda/BG_Dummy.png");
	if(LoadDivGraph("images/Hanafuda/HanafudaCard.png", 48,8,6,128,128,HudaImg)){}
}

Hanahuda::~Hanahuda()
{
}

AbstractScene* Hanahuda::Update()
{
	return this;
}

void Hanahuda::Draw()const
{
	DrawGraph(0, 0, Stage, TRUE);
	DrawGraph(100, 100,  HudaImg[12], TRUE);
}