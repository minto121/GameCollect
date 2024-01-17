#pragma once
#include "AbstractScene.h"

class Hound : public AbstractScene
{
private:
	int BackGroundImg;

	int cursorImg;
	int cursorFlg;

	int HoundImg;    //猟犬画像

	int RabbitImg;   //ウサギ画像
	int R_texture;

	int rabbit_X;  //ウサギX座標
	int rabbit_Y;  //ウサギY座標
	int rabbitFlg;

	int hound_X;   //猟犬X座標
	int hound_Y;   //猟犬Y座標

	int HoundFlg1;  //猟犬フラグ
	int HoundFlg2;
	int HoundFlg3;

	int HoundDrawflg1;   //猟犬描画フラグ
	int HoundDrawflg2;
	int HoundDrawflg3;
	
	int HoundMoveflg1;   //
	int HoundMoveflg2;
	int HoundMoveflg3;

	struct Bord {
		int x, y;
		int flg;
	};
	int i, j;

	struct Bord bord[5][3] = {
		{0, 1, 2, 3, 4 },
		{5, 6, 7, 8, 9 },
		{10, 11, 12, 13, 14}
	};

public:
	Hound();
	~Hound();

	//描画以外の更新を実行
	AbstractScene* Update() override;

	//描画に関することを実装
	void Draw() const override;

};