#pragma once
#include "AbstractScene.h"

class SixBollPuzzle:
	public AbstractScene
{

private:
	int Ball_img; //�@�{�[��
	int Back_Ground_img; //�@�w�i�摜
	int e;

public:
	SixBollPuzzle();

	~SixBollPuzzle();

	//�`��ȊO�̍X�V�����s
	AbstractScene* Update() override;

	//�`��Ɋւ��邱�Ƃ�����
	void Draw() const override;

};

