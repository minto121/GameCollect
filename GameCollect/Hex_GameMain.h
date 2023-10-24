#pragma once
#include"AbstractScene.h"

class Hex:public AbstractScene {
protected:
	int BackImg;
	//int BanImg;

public:
	Hex();

	virtual ~Hex() {};

	virtual AbstractScene* Update()override;

	virtual void Draw() const override;
};