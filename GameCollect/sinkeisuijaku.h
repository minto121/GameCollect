#pragma once
#include "AbstractScene.h"
class sinkeisuijaku :public AbstractScene
{
public:

private:

	virtual AbstractScene* Update()override;
	void Draw()const override;

	void Select();

	int first;

	int S_timg;
	int S_back;

	int g_KeyFlg;
	int S_ber = 0;
	int S2_ber = 0;
	int g_MenuY = 0;
	int g_OldKey;
	int g_NowKey;
};

