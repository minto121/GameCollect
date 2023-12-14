#pragma once
#include "AbstractScene.h"
#include "gomoku_TitleScene.h"
class gomokuScene : public AbstractScene
{
private:
	int TitleImg; // 背景画像
	int wTopImg; // 白石の画像
	int bTopImg; // 黒石の画像
	int gomoku_BackImg; // 盤面画像
	int gomoku_HelpImg1; // ヘルプ画面1
	int gomoku_HelpImg2; // ヘルプ画面2
	int cX; // 盤面x座標
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
	int gomoku_SE1; // ヘルプ画面表示時に出す音
	int gomoku_SE2; // ヘルプ画面を閉じるときに出す音
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

