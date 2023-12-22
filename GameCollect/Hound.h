#pragma once
#include "AbstractScene.h"

class Hound : public AbstractScene
{
private:
	int BackGroundImg;

	int cursorImg;
	int cursorFlg;

	int HoundImg;    //Â¢æ

	int RabbitImg;   //ETMæ
	int R_texture;

	int rabbit_X;  //ETMXÀW
	int rabbit_Y;  //ETMYÀW
	int rabbitFlg;

	int hound_X;   //Â¢XÀW
	int hound_Y;   //Â¢YÀW
	int HoundFlg1;
	int HoundFlg2;
	int HoundFlg3;

	int HoundMoveflg1;
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

	//`æÈOÌXVðÀs
	AbstractScene* Update() override;

	//`æÉÖ·é±ÆðÀ
	void Draw() const override;

};