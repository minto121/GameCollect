#pragma once
#include"AbstractScene.h"

class Hex:public AbstractScene {
protected:
	//int BackImg;
	int BanImg;
	int RedHexImg;
	int BlueHexImg;
	int SelectX;
	int SelectY;

	struct Tile {
		int flg;
		int x, y;
		int w, h;
		int backup;
	};

	struct Tile gStage[12][12];

public:
	Hex();

	void GameInit();

	void DrawStage() const;

	void Select();

	~Hex() {};

	virtual AbstractScene* Update()override;

	virtual void Draw() const override;
};