#pragma once
#include"AbstractScene.h"

class Hex :public AbstractScene {
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
	int P_CheckCnt;
	int P_CheckFlg;
	int ClearFlg;
	int E_CheckCnt;
	int E_CheckFlg;
	int TurnFlg;
	int TurnSave;

	struct Tile {
		int flg;
		int x, y;
		int cnt;
	};

	struct Tile gStage[13][13];

public:
	Hex();

	void GameInit();

	void DrawStage() const;	//�X�e�[�W�`��

	void Select();	//�^�C����u���ꏊ�̈ړ�&�ݒu

	void Check_P();

	void Check_E();

	void Enemy();
	~Hex() {};

	virtual AbstractScene* Update()override;

	virtual void Draw() const override;
};