#pragma once
#include "AbstractScene.h"
#include "DotAndBox.h"
#include "DrawLine.h"

class GameMain :public AbstractScene {
private:
	DotAndBox dotandbox;
	Line line;
public:
	GameMain();
	~GameMain();

	virtual AbstractScene* Update() override;
	virtual void Draw() const override;
};

