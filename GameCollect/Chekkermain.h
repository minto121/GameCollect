#pragma once
#include "AbstractScene.h"
class Chekkermain:
	public AbstractScene
{

private:
	int Boardimg; //�@��
	int Pieceimg; //�@��

public:
	Chekkermain();

	~Chekkermain();

	//�`��ȊO�̍X�V�����s
	AbstractScene* Update() override;

	//�`��Ɋւ��邱�Ƃ�����
	void Draw() const override;

};

