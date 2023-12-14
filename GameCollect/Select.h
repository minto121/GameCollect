#pragma once
#include"AbstractScene.h"

class GameSelect :
	public AbstractScene
{
private:

public:
	GameSelect();
	~GameSelect();
	AbstractScene* Update() override;
	void Draw() const override;
};