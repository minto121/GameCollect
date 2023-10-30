#include"DxLib.h"
#include"Hex_GameMain.h"

Hex::Hex() {
	BanImg = LoadGraph("../images/Hex/Hex_11Å~11.png");
	BlueHexImg = LoadGraph("../images/Hex/hexagon-B50.png");
	RedHexImg = LoadGraph("../images/Hex/hexagon-R50.png");
}

AbstractScene* Hex::Update() {
	return this;
}

void Hex::Draw()const {
	DrawGraph(0, 0, BanImg, FALSE);
}
