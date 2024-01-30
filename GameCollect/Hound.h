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
	//int R_texture;

	int rabbitFlg;

	int RabbitFlg;		 //ウサギフラグ
	int RabbitDrawflg;   //ウサギ描画フラグ
	int RabbitMoveflg;   //ウサギ移動フラグ
	int RabbitTurnflg;	 //ウサギターンフラグ

	int HoundFlg1;		//猟犬フラグ
	int HoundFlg2;
	int HoundFlg3;
	int HoundFlg[3];

	int HoundDrawflg1;   //猟犬描画フラグ
	int HoundDrawflg2;
	int HoundDrawflg3;
	
	int HoundMoveflg1;   //猟犬移動フラグ
	int HoundMoveflg2;
	int HoundMoveflg3;

	int HoundTurnflg;	//猟犬ターンフラグ

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

	void GameJudge();

	//描画以外の更新を実行
	AbstractScene* Update() override;

	//描画に関することを実装
	void Draw() const override;

};