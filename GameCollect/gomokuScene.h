#pragma once
#include "AbstractScene.h"
class gomokuScene : public AbstractScene
{
private:
	int TitleImg;
	int wTopImg;
	int bTopImg;
	int cX;
	int cY;
public:
	gomokuScene();
	~gomokuScene();
	AbstractScene* Update() override;
	void Draw() const override;
};

