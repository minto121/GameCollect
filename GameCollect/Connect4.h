#pragma once

#include "AbstractScene.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

class Connect4 :public AbstractScene{

private:

public:
	Connect4();

	~Connect4();

	//�`��ȊO�̍X�V�����s
	AbstractScene* Update() override;

	//�`��Ɋւ��邱�Ƃ�����
	void Draw() const override;
};

