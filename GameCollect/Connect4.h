#pragma once

#include "AbstractScene.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

class Connect4 :public AbstractScene{

private:
	int Board[5][6] = {};
	unsigned int Cr;

public:
	Connect4();

	~Connect4();

	//描画以外の更新を実行
	AbstractScene* Update() override;

	//描画に関することを実装
	void Draw() const override;
};

