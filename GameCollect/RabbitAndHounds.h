#pragma once
#pragma once
#include "AbstractScene.h"

class RabbitAndHounds : public AbstractScene
{

private:
	int Boardimg; //�@��
	int Pieceimg; //�@��
	int back;

	

public:
	RabbitAndHounds();

	~RabbitAndHounds();

	//�`��ȊO�̍X�V�����s
	AbstractScene* Update() override;

	//�`��Ɋւ��邱�Ƃ�����
	void Draw() const override;

};

