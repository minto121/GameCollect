#pragma once
#pragma once
#include "AbstractScene.h"

class RabbitAndHounds : public AbstractScene
{

private:
	int Boardimg; //　盤
	int Pieceimg; //　駒
	int back;

	

public:
	RabbitAndHounds();

	~RabbitAndHounds();

	//描画以外の更新を実行
	AbstractScene* Update() override;

	//描画に関することを実装
	void Draw() const override;

};

