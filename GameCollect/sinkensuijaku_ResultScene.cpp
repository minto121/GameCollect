#include "sinkensuijaku_ResultScene.h"
#include <DxLib.h>
AbstractScene* sinkensuijaku_ResultScene::Update()
{
	return nullptr;
}

void sinkensuijaku_ResultScene::Draw() const
{
	SetFontSize(100);
	DrawFormatString(300, 200, 0xffffff,"aaaaaaaaaaaaaaaaaa");
}
