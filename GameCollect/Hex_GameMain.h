#pragma once
#include"AbstractScene.h"

class Hex:public AbstractScene {
protected:
	//int BackImg;
	int BackImg;	//背景画像
	int RedHexImg;
	int BlueHexImg;
	int GreenHexImg;
	int BlackHexImg;	
	int HexImg;
	//615
	//335

	int Select_i;
	int Select_j;
	int CheckFlg;
	int CheckCnt;
	int ClearFlg;

	struct Tile {
		int flg;
		int x, y;
	};

	struct Tile gStage[13][13];

public:
	Hex();

	void GameInit();

	void DrawStage() const;	//ステージ描画

	void Select();	//タイルを置く場所の移動&設置

	void Check_P();

	void Check_E();

	~Hex() {};

	virtual AbstractScene* Update()override;

	virtual void Draw() const override;
};