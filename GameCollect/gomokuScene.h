#pragma once
#include "AbstractScene.h"
#include "gomoku_TitleScene.h"
class gomokuScene : public AbstractScene
{
private:
	int TitleImg;
	int wTopImg;
	int bTopImg;
	int gomoku_BackImg;
	int gomoku_HelpImg1;
	int gomoku_HelpImg2;
	int cX;
	int cY;
	int g_OldKey;
	int g_NowKey;
	int g_KeyFlg;
	int bCount;
	int wCount;
	bool gomoku_TurnSetFlg;
	int gomoku_Turn;
	int gomoku_PlayerTurn;
	int gomoku_Pfs; // プレイヤーの基石 黒い石:1 白い石:2
	int gomoku_AITurn;
	int gomoku_Efs; // エネミー(AI)の基石 黒い石:1 白い石:2
	int gomoku_Banmen[13][13];
	int gomoku_Phase; // 先攻:0 後攻:1
	int gomoku_Battle; // 試合中:0	黒の勝ち:1 白の勝ち:2
	int gomoku_AI_MoveX;
	int gomoku_AI_MoveY;
	int gomoku_AImove_Point;
	int gomoku_AI_think;
	int Key_Count = 0;
	int gomoku_Player_WaitTime;
	int gomoku_AI_WaitTime;
	int gomoku_Result_WaitTime;
	int gomoku_elapsedturn; // 経過ターンをカウントする変数
	int gomoku_Cursordisplaytime; // カーソルに動きを持たせる
	int gomoku_BGM1;
	int gomoku_SoundStart;
	bool gomoku_HelpDisplayflg;
	int gomokuHelp_Number;
	int gomoku_HelpWaitTime;
	int gomoku_ScrollWaitTime;
	int gomoku_ScrollSE;
public:
	gomokuScene();
	~gomokuScene();
	AbstractScene* Update() override;
	void Draw() const override;
	/*void gomoku_Player_Turn();
	void gomoku_AI_Turn();*/
};

