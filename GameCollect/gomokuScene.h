#pragma once
#include "AbstractScene.h"
class gomokuScene : public AbstractScene
{
private:
	int TitleImg;
public:
	gomokuScene();
	~gomokuScene();
	AbstractScene* Update() override;
	void Draw() const override;
};

