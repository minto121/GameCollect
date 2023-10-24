#pragma once
#include "AbstractScene.h"

class SixBollPuzzle:
	public AbstractScene
{

private:
	int Boll; //　ボール
	int Back_Ground_img; //　背景画像
	int e;

public:
	SixBollPuzzle();

	~SixBollPuzzle();

	//描画以外の更新を実行
	AbstractScene* Update() override;

	//描画に関することを実装
	void Draw() const override;

};

