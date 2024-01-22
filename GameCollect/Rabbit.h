#pragma once
#include "AbstractScene.h"


class Rabbit : public AbstractScene
{
private:
	int BackGroundImg;

	int cursorImg;
	int cursorFlg;

	int HoundImg;    //猟犬画像
	int RabbitImg;    //ウサギ画像
	int rabbitimg;

	int RabbitFlg;		//ウサギフラグ
	int RabbitDrawflg;   //ウサギ描画フラグ
	int RabbitMoveflg;   //ウサギ移動フラグ
	
	struct Bord{
		
		int x, y;
		int flg;
	};
	int i, j;

	struct Bord bord[5][3] = {
		{0, 1, 2, 3, 4 },
		{5, 6, 7, 8, 9 },
	  {10, 11, 12, 13, 14}
	};
	
	//int RabbitImg[1];   //ウサギ画像
	int R_texture;

public:
	Rabbit();
	~Rabbit();

	//void DrawBord() const;

	//描画以外の更新を実行
	AbstractScene* Update() override;

	//描画に関することを実装
	void Draw() const override;

};