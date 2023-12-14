#pragma once
#include "AbstractScene.h"

class SixBollPuzzle:
	public AbstractScene
{

private:
	int Ball_img[4];		//�{�[��
	int Back_Ground_img;	//�w�i�摜
	int FallingX;			//��������u���b�N��X���W�i�Œ�ʒu�j
	int FallingY = 100;		//��������u���b�N��Y���W�i�����ʒu�j

public:
	SixBollPuzzle();

	~SixBollPuzzle();

	//�`��ȊO�̍X�V�����s
	AbstractScene* Update() override;

	//�`��Ɋւ��邱�Ƃ�����
	void Draw() const override;

};

