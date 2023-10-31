#pragma once
#pragma once
#include "AbstractScene.h"

class RabbitAndHounds : public AbstractScene
{

private:
	int BackGroundImg;
	int Board; //　盤
	int Piece; //　駒

	int HoundImg;    //猟犬画像
	int RabbitImg;   //ウサギ画像
	

public:
	RabbitAndHounds();

	~RabbitAndHounds();

	//描画以外の更新を実行
	AbstractScene* Update() override;

	//描画に関することを実装
	void Draw() const override;

};

