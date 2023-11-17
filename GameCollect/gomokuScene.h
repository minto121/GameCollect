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
	int g_OldKey;
	int g_NowKey;
	int g_KeyFlg;
	int bCount;
	int wCount;
	bool gomoku_TurnSetFlg;
	bool gomoku_Turn;
	bool gomoku_PlayerTurn;
	int gomoku_Pfs; // �v���C���[�̊�� ������:1 ������:2
	bool gomoku_AITurn;
	int gomoku_Efs; // �G�l�~�[(AI)�̊�� ������:1 ������:2
	int gomoku_Banmen[13][13];
	bool gomoku_Phase; // ��U:0 ��U:1
	int gomoku_Battle; // ������:0	���̏���:1 ���̏���:2
	int gomoku_AI_MoveX;
	int gomoku_AI_MoveY;
	bool gomoku_AI_FirstSetFlg;
	int gomoku_AImove_Point;
	int gomoku_AI_think;
	int Key_Count = 0;
public:
	gomokuScene();
	~gomokuScene();
	AbstractScene* Update() override;
	void Draw() const override;
	/*void gomoku_Player_Turn();
	void gomoku_AI_Turn();*/
};

