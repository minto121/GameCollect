#pragma once
#include "AbstractScene.h"
class Porker : public AbstractScene
{
private:
	int Tranpu_Img[52];
	int Back;
public:
	Porker();

	~Porker();

	//�`��ȊO�̍X�V�����s
	AbstractScene* Update() override;

	//�`��Ɋւ��邱�Ƃ�����
	void Draw() const override;
};

