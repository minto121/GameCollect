#pragma once
#include "AbstractScene.h"


class Rabbit : public AbstractScene
{
private:
	int BackGroundImg;

	int cursorImg;
	int cursorFlg;

	int HoundImg;    //���摜
	int RabbitImg;    //�E�T�M�摜
	int rabbitimg;

	int RabbitFlg;		//�E�T�M�t���O
	int RabbitDrawflg;   //�E�T�M�`��t���O
	int RabbitMoveflg;   //�E�T�M�ړ��t���O
	
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
	
	//int RabbitImg[1];   //�E�T�M�摜
	int R_texture;

public:
	Rabbit();
	~Rabbit();

	//void DrawBord() const;

	//�`��ȊO�̍X�V�����s
	AbstractScene* Update() override;

	//�`��Ɋւ��邱�Ƃ�����
	void Draw() const override;

};