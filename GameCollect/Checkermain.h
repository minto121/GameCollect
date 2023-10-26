#pragma once
#include "AbstractScene.h"
#include <DxLib.h>


#define Speace 0
#define Black 1
#define White 2
class Checkermain:
	public AbstractScene
{

private:
	int Boardimg; //�@��
	int PieceB; //�@�
	int PieceW; // �
	int Checkerback; // �w�i
	int size = 100;
	int board[8][8];
		
	/*{
		0, 1, 0, 1, 0, 1, 0, 1,
		1, 0, 1, 0, 1, 0, 1, 0,
		0, 1, 0, 1, 0, 1, 0, 1,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 2, 0, 2, 0, 2, 0, 2,
		2, 0, 2, 0, 2, 0, 2, 0,
		0, 2, 0, 2, 0, 2, 0, 2, };*/
	int selectX;
	int selectY;
	int g_OldKey ;
	int g_NowKey;
	int g_KeyFlg ;

public:
	Checkermain();

	~Checkermain();

	//�`��ȊO�̍X�V�����s
	AbstractScene* Update() override;

	//�`��Ɋւ��邱�Ƃ�����
	void Draw() const override;

	// �u���b�N�z��̏�����
	void InitBlock() const ;
};

