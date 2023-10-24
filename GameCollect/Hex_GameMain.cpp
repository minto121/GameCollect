#include"DxLib.h"
#include"Hex_GameMain.h"

Hex::Hex() {
	BackImg = LoadGraph("../images/Hex/BG_Dummy.png");
}

AbstractScene* Hex::Update() {
	return this;
}

void Hex::Draw()const {
	DrawGraph(0, 0, BackImg, FALSE);
}
