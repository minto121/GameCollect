#pragma once
#include "AbstractScene.h"
class gomokuScene : public AbstractScene
{
private:
	int TitleImg;
	int wTopImg;
	int bTopImg;
	int cX;
	int cY;
	int g_OldKey;
	int g_NowKey;
	int g_KeyFlg;
	int gomoku_Banmen[13][13];
	bool gomoku_Phase; // ��U:0 ��U:1
	int Battle; // ������:0	���̏���:1 ���̏���:2
public:
	gomokuScene();
	~gomokuScene();
	AbstractScene* Update() override;
	void Draw() const override;
};

