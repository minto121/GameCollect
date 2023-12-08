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
#define FRAMERATE 60.0 //t[[g

#define SCREEN_HEIGHT 720	//æÊTCY (c)
#define SCREEN_WIDTH 1280	//æÊTCY (¡)
#define SCORE_UI_SIZE 180	//XRA\¦GATCY (¡)

#define FRAMERATE 60.0 //ãã¬ã¼ã ã¬ã¼ãE

#define SCREEN_HEIGHT 720	//ç»é¢ãµã¤ãº (ç¸¦)
#define SCREEN_WIDTH 1280	//ç»é¢ãµã¤ãº (æ¨ª)
#define SCORE_UI_SIZE 180	//ã¹ã³ã¢è¡¨ç¤ºã¨ãªã¢ãµã¤ãº (æ¨ª)


/***********************************************
 * ãã­ã°ã©ã ã®éå§E
 ***********************************************/
int WINAPI WinMain(_In_ HINSTANCE ih, _In_opt_ HINSTANCE ioh, _In_ LPSTR il, _In_ int ii)
{
	SetMainWindowText("GameCollect");

	ChangeWindowMode(TRUE);		// ã¦ã£ã³ãã¦ã¢ã¼ãã§èµ·åE

	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);	//ç»é¢ãµã¤ãºã®è¨­å®E

	if (DxLib_Init() == -1)
	{
		return -1;	// DXã©ã¤ãã©ãªã®åæååEçE
	}
	SetDrawScreen(DX_SCREEN_BACK);	// æç»åç»é¢ãè£ã«ãã

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
		//ãã¡ã¤ã«ãªã¼ãã³
		fopen_s(&fp, "ErrLog.txt", "a");
		//ã¨ã©ã¼ãEEã¿ã®æ¸ãè¾¼ã¿
		fprintf_s(fp, "%02dE½N %02dE½E½ %02dE½E½ %02dE½E½ %02dE½E½ %02dE½b : %sE½E½E½E½E½E½Üï¿½E½E½B\n", data.Year, data.Mon, data.Day, data.Hour, data.Min, data.Sec, err);

		return 0;
	}
	FpsController FPSC(FRAMERATE, 800);

	// ã²ã¼ã ã«ã¼ãE
	while ((ProcessMessage() == 0) && (sceneMng->Update() != nullptr)) {

		ClearDrawScreen();		// ç»é¢ã®åæåE
		PAD_INPUT::UpdateKey();
		sceneMng->Draw();
		FPSC.All();
		FPSC.Disp();
		//å¼·å¶çµäºE
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_BACK) || CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}
		ScreenFlip();			// è£ç»é¢ã®åE®¹ãè¡¨ç»é¢ã«åæ 
	}

	DxLib_End;

	return 0;

}