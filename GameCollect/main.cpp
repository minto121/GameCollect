#include"DxLib.h"
#include"SceneManager.h"
#include"PadInput.h"
#include "Title.h"
#include "FpsController.h"
//#include"Hanafuda_GameMain.h"
#include "takoyaki.h"
//#include"Hanafuda_GameMain.h"
//#include "Checkermain.h"
#include "SixBallPuzzle.h"
#include "RabbitAndHounds.h"
#include "GameSelect.h"
#include"Reversi.h"
#include"Title.h"
#include"Hex_GameMain.h"

#define FRAMERATE 60.0 //フレームレート

#define SCREEN_HEIGHT 720	//画面サイズ (縦)
#define SCREEN_WIDTH 1280	//画面サイズ (横)
#define SCORE_UI_SIZE 180	//スコア表示エリアサイズ (横)


/***********************************************
 * プログラムの開始
 ***********************************************/
int WINAPI WinMain(_In_ HINSTANCE ih, _In_opt_ HINSTANCE ioh, _In_ LPSTR il, _In_ int ii)
{
	SetMainWindowText("GameCollect");

	ChangeWindowMode(TRUE);		// ウィンドウモードで起動

	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);	//画面サイズの設定

	if (DxLib_Init() == -1)
	{
		return -1;	// DXライブラリの初期化処理
	}
	SetDrawScreen(DX_SCREEN_BACK);	// 描画先画面を裏にする

	SceneManager* sceneMng;

	try
	{
		sceneMng = new SceneManager((AbstractScene*)new /*RabbitAndHounds());*/GameSelect());

	}
	catch (const char* err)
	{
		FILE* fp = NULL;

		DATEDATA data;

		GetDateTime(&data);
		//ファイルオープン
		fopen_s(&fp, "ErrLog.txt", "a");
		//エラーデータの書き込み
		fprintf_s(fp, "%02d年 %02d月 %02d日 %02d時 %02d分 %02d秒 : %sがありません。\n", data.Year, data.Mon, data.Day, data.Hour, data.Min, data.Sec, err);

		return 0;
	}
	FpsController FPSC(FRAMERATE, 800);

	// ゲームループ
	while ((ProcessMessage() == 0) && (sceneMng->Update() != nullptr)) {

		ClearDrawScreen();		// 画面の初期化
		PAD_INPUT::UpdateKey();
		sceneMng->Draw();
		FPSC.All();
		FPSC.Disp();
		//強制終了
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_BACK) || CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}
		ScreenFlip();			// 裏画面の内容を表画面に反映
	}

	DxLib_End;

	return 0;

}