#pragma once
#include "AbstractScene.h"
class sinkensuijaku_ResultScene : public AbstractScene
{
public:
	virtual AbstractScene* Update()override;
	void Draw()const override;
};

