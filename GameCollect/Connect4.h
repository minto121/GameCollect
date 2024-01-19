#pragma once

#include "AbstractScene.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

class Connect4 :public AbstractScene{

private:
	int Board[5][6] = {};
	unsigned int Cr;

public:
	Connect4();

	~Connect4();

	//�`��ȊO�̍X�V�����s
	AbstractScene* Update() override;

	//�`��Ɋւ��邱�Ƃ�����
	void Draw() const override;
};

