#pragma once
#include "AbstractScene.h"
class Checkermain:
	public AbstractScene
{

private:
	int Boardimg; //�@��
	int PieceB; //�@�
	int PiceW; // �
	int Checkerback; // �w�i

public:
	Checkermain();

	~Checkermain();

	//�`��ȊO�̍X�V�����s
	AbstractScene* Update() override;

	//�`��Ɋւ��邱�Ƃ�����
	void Draw() const override;

};

