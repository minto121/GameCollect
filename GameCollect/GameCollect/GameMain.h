#pragma once
#include "AbstractScene.h"
#include "DotAndBox.h"


class GameMain :public AbstractScene {
private:
	DotAndBox dotandbox;
public:
	GameMain();
	~GameMain();

	virtual AbstractScene* Update() override;
	virtual void Draw() const override;
};

