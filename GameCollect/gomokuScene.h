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
	int bCount;
	int wCount;
	int gomoku_Banmen[13][13];
	bool gomoku_Phase; // æU:0 ŒãU:1
	int gomoku_Battle; // ‡’†:0	•‚ÌŸ‚¿:1 ”’‚ÌŸ‚¿:2
public:
	gomokuScene();
	~gomokuScene();
	AbstractScene* Update() override;
	void Draw() const override;
};

