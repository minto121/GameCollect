#pragma once
#include"AbstractScene.h"

class Hex:public AbstractScene {
protected:
	//int BackImg;
	int BanImg;
	int RedHexImg;
	int BlueHexImg;
public:
	Hex();

	virtual ~Hex() {};

	virtual AbstractScene* Update()override;

	virtual void Draw() const override;
};