#include"DxLib.h"
#include"Hanahuda_GameMain.h"
#include"Math.h"

Hanahuda::Hanahuda()
{
	Stage = LoadGraph("images/Hanafuda/BG_Dummy.png");
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
}