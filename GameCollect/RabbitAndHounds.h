#pragma once
#include "AbstractScene.h"

class RabbitAndHounds : public AbstractScene
{
private:
	int BackGroundImg;

	int Player;

	int now_menu; //���ݑI�����Ă郁�j���[
	int font_handle;  //�t�H���g
	int input_margin;  //���쎞�ԊԊu

public:

	RabbitAndHounds();

	~RabbitAndHounds();

	//�`��ȊO�̍X�V�����s
	AbstractScene* Update() override;

	//�`��Ɋւ��邱�Ƃ�����
	void Draw() const override;

};

