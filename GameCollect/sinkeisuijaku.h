#pragma once
#include "AbstractScene.h"
class sinkeisuijaku :public AbstractScene
{
public:

private:

	virtual AbstractScene* Update()override;
	void Draw()const override;

	int S_timg;
	int S_back;
};

