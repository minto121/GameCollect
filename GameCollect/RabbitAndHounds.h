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

	int rabbit_X;  //ウサギX座標
	int rabbit_Y;  //ウサギY座標
	int rabbitSpeed;

	int hound_X;   //猟犬X座標
	int hound_Y;   //猟犬Y座標
	int houndSpeed;


	

public:
	RabbitAndHounds();

	~RabbitAndHounds();

	//描画以外の更新を実行
	AbstractScene* Update() override;

	//描画に関することを実装
	void Draw() const override;

	void RabbitPiece();
	void HoundIPiece();

};

