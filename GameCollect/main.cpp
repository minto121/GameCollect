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
#define FRAMERATE 60.0 //フレームレート

#define SCREEN_HEIGHT 720	//画面サイズ (縦)
#define SCREEN_WIDTH 1280	//画面サイズ (横)
#define SCORE_UI_SIZE 180	//スコア表示エリアサイズ (横)

#define FRAMERATE 60.0 //繝輔Ξ繝ｼ繝繝ｬ繝ｼ繝・

#define SCREEN_HEIGHT 720	//逕ｻ髱｢繧ｵ繧､繧ｺ (邵ｦ)
#define SCREEN_WIDTH 1280	//逕ｻ髱｢繧ｵ繧､繧ｺ (讓ｪ)
#define SCORE_UI_SIZE 180	//繧ｹ繧ｳ繧｢陦ｨ遉ｺ繧ｨ繝ｪ繧｢繧ｵ繧､繧ｺ (讓ｪ)


/***********************************************
 * 繝励Ο繧ｰ繝ｩ繝縺ｮ髢句ｧ・
 ***********************************************/
int WINAPI WinMain(_In_ HINSTANCE ih, _In_opt_ HINSTANCE ioh, _In_ LPSTR il, _In_ int ii)
{
	SetMainWindowText("GameCollect");

	ChangeWindowMode(TRUE);		// 繧ｦ繧｣繝ｳ繝峨え繝｢繝ｼ繝峨〒襍ｷ蜍・

	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);	//逕ｻ髱｢繧ｵ繧､繧ｺ縺ｮ險ｭ螳・

	if (DxLib_Init() == -1)
	{
		return -1;	// DX繝ｩ繧､繝悶Λ繝ｪ縺ｮ蛻晄悄蛹門・逅・
	}
	SetDrawScreen(DX_SCREEN_BACK);	// 謠冗判蜈育判髱｢繧定｣上↓縺吶ｋ

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
		//繝輔ぃ繧､繝ｫ繧ｪ繝ｼ繝励Φ
		fopen_s(&fp, "ErrLog.txt", "a");
		//繧ｨ繝ｩ繝ｼ繝・・繧ｿ縺ｮ譖ｸ縺崎ｾｼ縺ｿ
		fprintf_s(fp, "%02d・ｽN %02d・ｽ・ｽ %02d・ｽ・ｽ %02d・ｽ・ｽ %02d・ｽ・ｽ %02d・ｽb : %s・ｽ・ｽ・ｽ・ｽ・ｽ・ｽﾜゑｿｽ・ｽ・ｽB\n", data.Year, data.Mon, data.Day, data.Hour, data.Min, data.Sec, err);

		return 0;
	}
	FpsController FPSC(FRAMERATE, 800);

	// 繧ｲ繝ｼ繝繝ｫ繝ｼ繝・
	while ((ProcessMessage() == 0) && (sceneMng->Update() != nullptr)) {

		ClearDrawScreen();		// 逕ｻ髱｢縺ｮ蛻晄悄蛹・
		PAD_INPUT::UpdateKey();
		sceneMng->Draw();
		FPSC.All();
		FPSC.Disp();
		//蠑ｷ蛻ｶ邨ゆｺ・
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_BACK) || CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}
		ScreenFlip();			// 陬冗判髱｢縺ｮ蜀・ｮｹ繧定｡ｨ逕ｻ髱｢縺ｫ蜿肴丐
	}

	DxLib_End;

	return 0;

}