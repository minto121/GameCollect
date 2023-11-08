#pragma once
#include "AbstractScene.h"


class Rabbit : public AbstractScene
{
private:
	int BackGroundImg;

	int HoundImg;    //���摜
	int RabbitImg;   //�E�T�M�摜

	int rabbit_X;  //�E�T�MX���W
	int rabbit_Y;  //�E�T�MY���W
	int rabbitSpeed;

	int hound_X;   //��X���W
	int hound_Y;   //��Y���W
	int houndSpeed;

public:
	Rabbit();
	~Rabbit();

	//�`��ȊO�̍X�V�����s
	AbstractScene* Update() override;

	//�`��Ɋւ��邱�Ƃ�����
	void Draw() const override;

};