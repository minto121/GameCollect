#pragma once
#include "AbstractScene.h"

class Hound : public AbstractScene
{
private:
	int BackGroundImg;

	int cursorImg;
	int cursorFlg;

	int HoundImg;    //���摜

	int RabbitImg;   //�E�T�M�摜
	int R_texture;

	int rabbit_X;  //�E�T�MX���W
	int rabbit_Y;  //�E�T�MY���W
	int rabbitFlg;

	int hound_X;   //��X���W
	int hound_Y;   //��Y���W

	int HoundFlg1;  //���t���O
	int HoundFlg2;
	int HoundFlg3;

	int HoundDrawflg1;   //���`��t���O
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

	//�`��ȊO�̍X�V�����s
	AbstractScene* Update() override;

	//�`��Ɋւ��邱�Ƃ�����
	void Draw() const override;

};