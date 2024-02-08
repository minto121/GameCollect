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

	int RabbitFlg;		 //�E�T�M�t���O
	int RabbitDrawflg;   //�E�T�M�`��t���O
	int RabbitMoveflg;   //�E�T�M�ړ��t���O
	int RabbitTurnflg;	 //�E�T�M�^�[���t���O

	int HoundFlg1;		//���t���O
	int HoundFlg2;
	int HoundFlg3;

	int HoundDrawflg1;   //���`��t���O
	int HoundDrawflg2;
	int HoundDrawflg3;
	
	int HoundMoveflg1;   //���ړ��t���O
	int HoundMoveflg2;
	int HoundMoveflg3;

	int HoundTurnflg;	//���^�[���t���O

	int RabbitWinflg;
	int HoundWinflg;

	struct Bord {
		int x, y;
		int flg;
	};
	int i;
	int j, k, l;

	struct Bord bord[5][3] = {
		{0, 1, 2, 3, 4 },
		{5, 6, 7, 8, 9 },
		{10,11,12,13,14}
	};

	bool a, b;

public:
	Hound();
	~Hound();

	void GameJudge();

	//�`��ȊO�̍X�V�����s
	AbstractScene* Update() override;

	//�`��Ɋւ��邱�Ƃ�����
	void Draw() const override;

};