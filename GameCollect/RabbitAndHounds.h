#pragma once
#include "AbstractScene.h"

class RabbitAndHounds : public AbstractScene
{
private:
	int BackGroundImg;
	int Board; //�@��
	int Piece; //�@��

	int Player;

	int HoundImg;    //���摜
	int RabbitImg;   //�E�T�M�摜

	int hound_X;   //��X���W
	int hound_Y;   //��Y���W
	int houndSpeed;


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

	void RabbitPiece();
	void HoundIPiece();

};

