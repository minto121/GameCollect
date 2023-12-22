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
	int i, j;

	struct Bord bord[5][3] = {
		{0, 1, 2, 3, 4 },
		{5, 6, 7, 8, 9 },
	  {10, 11, 12, 13, 14}
	};
	
	int PlayerFlg;

	int RabbitImg[1];   //�E�T�M�摜
	int R_texture;

	int rabbit_X;  //�E�T�MX���W
	int rabbit_Y;  //�E�T�MY���W
	int RabbitFlg;

	int hound_X;   //��X���W
	int hound_Y;   //��Y���W
	int houndSpeed;

public:
	Rabbit();
	~Rabbit();

	//void DrawBord() const;

	//�`��ȊO�̍X�V�����s
	AbstractScene* Update() override;

	//�`��Ɋւ��邱�Ƃ�����
	void Draw() const override;

};