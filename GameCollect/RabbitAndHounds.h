#pragma once
#pragma once
#include "AbstractScene.h"

class RabbitAndHounds : public AbstractScene
{

private:
	int BackGroundImg;
	int Board; //@Õ
	int Piece; //@î

	int HoundImg;    //Â¢æ
	int RabbitImg;   //ETMæ

	int rabbit_X;  //ETMXÀW
	int rabbit_Y;  //ETMYÀW
	int rabbitSpeed;

	int hound_X;   //Â¢XÀW
	int hound_Y;   //Â¢YÀW
	int houndSpeed;
	

public:
	RabbitAndHounds();

	~RabbitAndHounds();

	//`æÈOÌXVðÀs
	AbstractScene* Update() override;

	//`æÉÖ·é±ÆðÀ
	void Draw() const override;

	void RabbitPiece();
	void HoundIPiece();

};

