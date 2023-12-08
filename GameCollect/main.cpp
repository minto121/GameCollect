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
#include"Mankara.h"
#define FRAMERATE 60.0 //�t���[�����[�g

#define SCREEN_HEIGHT 720	//��ʃT�C�Y (�c)
#define SCREEN_WIDTH 1280	//��ʃT�C�Y (��)
#define SCORE_UI_SIZE 180	//�X�R�A�\���G���A�T�C�Y (��)

#define FRAMERATE 60.0 //フレームレーチE

#define SCREEN_HEIGHT 720	//画面サイズ (縦)
#define SCREEN_WIDTH 1280	//画面サイズ (横)
#define SCORE_UI_SIZE 180	//スコア表示エリアサイズ (横)


/***********************************************
 * プログラムの開姁E
 ***********************************************/
int WINAPI WinMain(_In_ HINSTANCE ih, _In_opt_ HINSTANCE ioh, _In_ LPSTR il, _In_ int ii)
{
	SetMainWindowText("GameCollect");

	ChangeWindowMode(TRUE);		// ウィンドウモードで起勁E

	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);	//画面サイズの設宁E

	if (DxLib_Init() == -1)
	{
		return -1;	// DXライブラリの初期化�E琁E
	}
	SetDrawScreen(DX_SCREEN_BACK);	// 描画先画面を裏にする

	SceneManager* sceneMng;

	try
	{
		sceneMng = new SceneManager((AbstractScene*)new /*RabbitAndHounds());*/GameSelect());
;
	}
	catch (const char* err)
	{
		FILE* fp = NULL;

		DATEDATA data;

		GetDateTime(&data);
		//ファイルオープン
		fopen_s(&fp, "ErrLog.txt", "a");
		//エラーチE�Eタの書き込み
		fprintf_s(fp, "%02d�E�N %02d�E��E� %02d�E��E� %02d�E��E� %02d�E��E� %02d�E�b : %s�E��E��E��E��E��E�܂��E��E�B\n", data.Year, data.Mon, data.Day, data.Hour, data.Min, data.Sec, err);

		return 0;
	}
	FpsController FPSC(FRAMERATE, 800);

	// ゲームルーチE
	while ((ProcessMessage() == 0) && (sceneMng->Update() != nullptr)) {

		ClearDrawScreen();		// 画面の初期匁E
		PAD_INPUT::UpdateKey();
		sceneMng->Draw();
		FPSC.All();
		FPSC.Disp();
		//強制終亁E
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_BACK) || CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}
		ScreenFlip();			// 裏画面の冁E��を表画面に反映
	}

	DxLib_End;

	return 0;

}