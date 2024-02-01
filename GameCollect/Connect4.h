#pragma once

/*�N���X���E�w�b�_�[�̃t�@�C������SixBallPuzzle�ɂȂ��Ă���̂͏�����ɂ����̂ł��B
	���ۂɂ�Connect4.h�ł�*/

#include "AbstractScene.h"
#include "DxLib.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

//��ʃT�C�Y (�c)��720
//��ʃT�C�Y (��))��1280

//const int HEIGHT = 12;
//const int WIDTH = 12;
const int BLOCKSIZE = 48;
const int MARGIN = 0;

class Connect4 :public AbstractScene{

private:
	int Stage[7][6] = {};	//�X�e�[�W�̔z��
	unsigned int Cr;

	int Cursor = 0;	//�J�[�\����X�l
	int Num = 1;	//�J�[�\���̈ʒu
	
	int gStageImg;		//�X�e�[�W�摜
	int gCursorImg;		//�J�[�\���摜
	int gRedCoinImg;	//�Ԃ̃R�C��
	int gYellowCoinImg;	//���F�̃R�C��
	int gClearImg;		//�N���A�\��

	int CheckAnswer;
public:
	struct Boll{
	int flg;		//�t���O�i�O�F�\�����Ȃ��@�P�F�\������j
	int x, y;		//���W
	int w, h;		//���A����
	int img;		//�摜�ԍ�
	};
	
	//struct Block gStage[HEIGHT][WIDTH];

	Connect4();

	~Connect4();

	//�`��ȊO�̍X�V�����s
	AbstractScene* Update() override;

	//�`��Ɋւ��邱�Ƃ�����
	void Draw() const override;

	bool CheckConnect(int x, int y, int type);

	int CheckConnectMin(int x, int y, int type, int cnt); // �q�����Ă��邩�̃`�F�b�N
};

