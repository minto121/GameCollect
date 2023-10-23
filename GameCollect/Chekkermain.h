#pragma once
#include "AbstractScene.h"
class Chekkermain:
	public AbstractScene
{

private:
	int Boardimg; //　盤
	int Pieceimg; //　駒

public:
	Chekkermain();

	~Chekkermain();

	//描画以外の更新を実行
	AbstractScene* Update() override;

	//描画に関することを実装
	void Draw() const override;

};

