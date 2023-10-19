#include"DxLib.h"
#include"main.h"
#include"Hanahuda_GameMain.h"
#include"Math.h"

Hanahuda::Hanahuda()
{
	if(Stage = LoadGraph("images/Hanafuda/BG_Dummy.png")){}
}

Hanahuda::~Hanahuda()
{
}

Hanahuda::Update()
{
}

Hanahuda::Draw()
{
	DrawGraph(0, 0, Stage, TRUE);
}