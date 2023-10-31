#pragma once
#pragma once
#include "AbstractScene.h"

class RabbitAndHounds : public AbstractScene
{

private:
	int BackGroundImg;
	int Board; //�@��
	int Piece; //�@��

	int HoundImg;    //���摜
	int RabbitImg;   //�E�T�M�摜
	

public:
	RabbitAndHounds();

	~RabbitAndHounds();

	//�`��ȊO�̍X�V�����s
	AbstractScene* Update() override;

	//�`��Ɋւ��邱�Ƃ�����
	void Draw() const override;

};

