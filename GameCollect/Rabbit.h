#pragma once
#include "AbstractScene.h"


class Rabbit : public AbstractScene
{
private:
	int BackGroundImg;

	int HoundImg;    //Â¢æ
	
	struct Bord{
		int flg;
	};
	struct Bord bord[5][3];
	

	int RabbitImg[2];   //ETMæ
	int R_texture;

	int rabbit_X;  //ETMXÀW
	int rabbit_Y;  //ETMYÀW
	int rabbitFlg;

	int hound_X;   //Â¢XÀW
	int hound_Y;   //Â¢YÀW
	int houndSpeed;

	int Ax;
	int Ay;
	int Aposition;

	int Img;

public:
	Rabbit();
	~Rabbit();

	//`æÈOÌXVðÀs
	AbstractScene* Update() override;

	//`æÉÖ·é±ÆðÀ
	void Draw() const override;

};