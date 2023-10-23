#include"DxLib.h"
#include"Hanahuda_GameMain.h"
#include"Math.h"

Hanahuda::Hanahuda()
{
	MouseX = 0;
	MouseY = 0;
	Stage = LoadGraph("images/Hanafuda/BG_Dummy.png");
	if(LoadDivGraph("images/Hanafuda/HanafudaCard.png", 48,8,6,128,256,HudaImg)){}
}

Hanahuda::~Hanahuda()
{
}

AbstractScene* Hanahuda::Update()
{
	GetMousePoint(&MouseX, &MouseY);

	return this;
}

void Hanahuda::Draw()const
{
	/*DrawGraph(0, 0, Stage, TRUE);*/
	DrawGraph(100, 100,HudaImg[0], TRUE);
	DrawLine(100, 140, 100, 320, GetColor(255, 0, 0), TRUE);
	DrawFormatString(0, 20, GetColor(255, 255, 255), " マウス座標：X座標 %d Y座標 %d", MouseX, MouseY);

}