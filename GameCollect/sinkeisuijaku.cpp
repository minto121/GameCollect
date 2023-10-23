#include "sinkeisuijaku.h"
#include "DxLib.h"


AbstractScene* sinkeisuijaku::Update()
{
	S_timg = LoadGraph("../images/sinkensuijaku/ura.png");
	S_back = LoadGraph("../images/sinkensuijaku/back.png");
	return this;
}

void sinkeisuijaku::Draw() const
{
	DrawGraph(0,0, S_back, FALSE);
	DrawBox(450,100, 120, 120, 0x00ffff, FALSE);
	for (int j = 1; j < 5; j++) {
		for (int i = 0; i < 5; i++) {
			DrawRotaGraph(450 + i * 100, 0+ j*150, 0.5, 0, S_timg, TRUE);
		}
	}
}

