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
	
	for (int j = 1; j < 5; j++) {
		for (int i = 0; i < 5; i++) {
			DrawRotaGraph(450 + i * 110, 0+ j*160, 0.5, 0, S_timg, TRUE);
		}
	}
	DrawBox(395, 90, 495, 235, 0x00ffff, FALSE);

	for (int j = 0; j < 5; j++) {
		for (int i = 0; i < 5; i++) {
			DrawBox(395 + i * 110, 90 + j * 160, 495 + i * 110, 235 + j * 160, 0x00ffff, FALSE);
		}
	}
}

