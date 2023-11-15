#pragma once
#include "AbstractScene.h"
class gomokuScene : public AbstractScene
{
private:
	int TitleImg;
	int wTopImg;
	int bTopImg;
	int gomoku_BackImg;
	int cX;
	int cY;
	int gomoku_AI_MoveX;
	int gomoku_AI_MoveY;
	int enemyX;
	int enemyY;
	int g_OldKey;
	int g_NowKey;
	int g_KeyFlg;
	int bCount;
	int wCount;
	int gomoku_Banmen[13][13];
	bool gomoku_Phase; // æU:0 ŒãU:1
	int gomoku_Battle; // ‡’†:0	•‚ÌŸ‚¿:1 ”’‚ÌŸ‚¿:2
	int gomoku_AImove_Point;
	int gomoku_AI_think;
	int Key_Count = 0;
public:
	gomokuScene();
	~gomokuScene();
	AbstractScene* Update() override;
	void Draw() const override;
};

