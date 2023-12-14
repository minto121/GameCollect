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
	int cX; // カーソルx座標
	int cY; // カーソル盤面y座標
	int g_OldKey;
	int g_NowKey;
	int g_KeyFlg;
	int bCount; // 黒石の数
	int wCount; // 白石の数
	bool gomoku_TurnSetFlg; // 先手後手を決めるフラグ
	int gomoku_Turn; // 現在のターン
	int gomoku_PlayerTurn; // プレイヤーターン
	int gomoku_Pfs; // プレイヤーの基石 黒い石:1 白い石:2
	int gomoku_AITurn; // AIのターン
	int gomoku_Efs; // エネミー(AI)の基石 黒い石:1 白い石:2
	int gomoku_Banmen[13][13]; // 盤面[x][y]
	int gomoku_Phase; // 先攻:0 後攻:1
	int gomoku_Battle; // 試合中:0	黒の勝ち:1 白の勝ち:2
	int gomoku_AI_MoveX; // AIx座標
	int gomoku_AI_MoveY; // AIy座標
	int gomoku_AImove_Point; // AIの評価値
	int gomoku_AI_think; // 行動が終わったかどうか確認する変数(0:行動中 1:行動済み)
	int Key_Count = 0; // 入力が行われたか
	int gomoku_Player_WaitTime; // プレイヤーのクールタイム
	int gomoku_AI_WaitTime; // // AIのクールタイム
	int gomoku_Result_WaitTime; // リザルトのクールタイム
	int gomoku_elapsedturn; // 経過ターンをカウントする変数
	int gomoku_Cursordisplaytime; // カーソルに動きを持たせる
	int gomoku_BGM1; // プレイ中のBGM
	int gomoku_SE1; // ヘルプ画面表示時に出す音
	int gomoku_SE2; // ヘルプ画面を閉じるときに出す音
	int gomoku_SoundStart; // BGMが流れているかどうか(0:再生されていない 1:再生中)
	bool gomoku_HelpDisplayflg; // ヘルプ画面が開かれているかどうかのフラグ(0:ゲーム画面 1:ヘルプ画面)
	int gomokuHelp_Number; // 現在のヘルプ画面のページ番号
	int gomoku_HelpWaitTime; // ヘルプ画面のクールタイム
	int gomoku_ScrollWaitTime; // ヘルプ画面のページをめくった時に発生するクールタイム
	int gomoku_ScrollSE; // スクロール時のSE
public:
	gomokuScene();
	~gomokuScene();
	AbstractScene* Update() override;
	void Draw() const override;
	/*void gomoku_Player_Turn();
	void gomoku_AI_Turn();*/
};

