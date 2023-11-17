#pragma once
#include"AbstractScene.h"

class Hex:public AbstractScene {
protected:
	//int BackImg;
	int BackImg;	//�w�i�摜
	int RedHexImg;
	int BlueHexImg;
	int GreenHexImg;
	int BlackHexImg;	
	int HexImg;
	//615
	//335

	int Select_i;
	int Select_j;
	int CheckFlg;
	int CheckCnt;
	int ClearFlg;

	struct Tile {
		int flg;
		int x, y;
	};

	struct Tile gStage[13][13];

public:
	Hex();

	void GameInit();

	void DrawStage() const;	//�X�e�[�W�`��

	void Select();	//�^�C����u���ꏊ�̈ړ�&�ݒu

	void Check_P();

	void Check_E();

	~Hex() {};

	virtual AbstractScene* Update()override;

	virtual void Draw() const override;
};