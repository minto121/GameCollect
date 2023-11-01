#include"DxLib.h"
#include"Hanahuda_GameMain.h"
#include"Math.h"

Hanahuda::Hanahuda()
{

}

Hanahuda::~Hanahuda()
{
}

AbstractScene* Hanahuda::Update()
{
	return NULL;
}

void Hanahuda::Draw() const
{
	DrawFormatString(0, 0,GetColor(255, 0, 0), "‰ÔŽD");
}