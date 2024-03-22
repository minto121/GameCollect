#pragma once
#include "AbstractScene.h"


class Rabbit : public AbstractScene
{
private:
	int BackGroundImg;
	int cursorImg;
	int HoundImg;    //���摜

	int rabbitimg;
	
	struct Bord{
		int x, y;
		int flg;
	};
	struct Bord bord[5][3] = 
	{
		{1,2,3,4,5},
		{6,7,8,9,10},
		{11,12,13,14,15}
	};
	

	int RabbitImg[2];   //�E�T�M�摜
	int R_texture;

	int rabbit_X;  //�E�T�MX���W
	int rabbit_Y;  //�E�T�MY���W
	int rabbitFlg;

	int hound_X;   //��X���W
	int hound_Y;   //��Y���W
	int houndSpeed;

	int Ax;
	int Ay;
	int Aposition;

	int Img;

public:
	Rabbit();
	~Rabbit();

	void DrawBord() const;

	//�`��ȊO�̍X�V�����s
	AbstractScene* Update() override;

	//�`��Ɋւ��邱�Ƃ�����
	void Draw() const override;

};