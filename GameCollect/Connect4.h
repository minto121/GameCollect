#pragma once

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
	int Board[6][7];
	unsigned int Cr;

	int Cursor = 0;		//�J�[�\��
	int CursorX = 0;			//�J�[�\���̏����ʒu

	int Num = 0;	//�J�[�\���̈ʒu
	int gKeyFlg;	//���݂̃L�[
	int gOldKey;
	int gNowKey;
	int Key_Count;
	int cX;

	int gStageImg;	//�X�e�[�W�摜
	int gCursorImg;	//�J�[�\���摜

public:

	int flg;		//�t���O�i�O�F�\�����Ȃ��@�P�F�\������j
	int x, y;		//���W
	int w, h;		//���A����
	int img;		//�摜�ԍ�
	int backup;		//�摜�o�b�N�A�b�v

	//struct Block gStage[HEIGHT][WIDTH];

	Connect4();

	~Connect4();

	//�`��ȊO�̍X�V�����s
	AbstractScene* Update() override;

	//�`��Ɋւ��邱�Ƃ�����
	void Draw() const override;
};

