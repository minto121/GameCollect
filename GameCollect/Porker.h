#pragma once
#include "AbstractScene.h"
class Porker : public AbstractScene
{
private:
	int Tranpu_Img[52];
	int Back;
public:
	Porker();

	~Porker();

	//描画以外の更新を実行
	AbstractScene* Update() override;

	//描画に関することを実装
	void Draw() const override;
};

