#pragma once
#include "AbstractScene.h"

class DotAndBox :public AbstractScene {
private:

public:
	DotAndBox();
	~DotAndBox();
	virtual AbstractScene* Update() override;
	void Draw() const override;
};
