#pragma once
#include"AbstractScene.h"

class Hex:public AbstractScene {
protected:
	//int BackImg;
	int BackImg;
	int RedHexImg;
	int BlueHexImg;
	int BlackHexImg;
	int HexImg;
	int SelectX;	//615
	int SelectY;	//335
	int Select_i;
	int Select_j;

	struct Tile {
		int flg;
		int x, y;
		int w, h;
		int backup;
	};

	struct Tile gStage[13][13];

public:
	Hex();

	void GameInit();

	void DrawStage() const;

	void Select();

	~Hex() {};

	virtual AbstractScene* Update()override;

	virtual void Draw() const override;
};