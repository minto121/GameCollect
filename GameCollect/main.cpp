#include"DxLib.h"
#include"SceneManager.h"
#include"PadInput.h"
#include "Title.h"
#include "FpsController.h"
//#include"Hanafuda_GameMain.h"
#include "takoyaki.h"
//#include"Hanafuda_GameMain.h"
//#include "Checkermain.h"
#include "Connect4.h"
#include "RabbitAndHounds.h"
#include "GameSelect.h"
#include"Reversi.h"
#include"Title.h"
#include"Hex_GameMain.h"
#include "GameMain.h"
#include"Hex_GameMain.h"
#include"Connect4.h"

#define FRAMERATE 60.0 //�t���[�����[�g

#define SCREEN_HEIGHT 720	//��ʃT�C�Y (�c)
#define SCREEN_WIDTH 1280	//��ʃT�C�Y (��)
#define SCORE_UI_SIZE 180	//�X�R�A�\���G���A�T�C�Y (��)


/***********************************************
 * �v���O�����̊J�n
 ***********************************************/
int WINAPI WinMain(_In_ HINSTANCE ih, _In_opt_ HINSTANCE ioh, _In_ LPSTR il, _In_ int ii)
{
	SetMainWindowText("GameCollect");

	ChangeWindowMode(TRUE);		// �E�B���h�E���[�h�ŋN��

	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);	//��ʃT�C�Y�̐ݒ�

	if (DxLib_Init() == -1)
	{
		return -1;	// DX���C�u�����̏���������
	}
	SetDrawScreen(DX_SCREEN_BACK);	// �`����ʂ𗠂ɂ���

	SceneManager* sceneMng;

	try
	{
		sceneMng = new SceneManager((AbstractScene*)new /*RabbitAndHounds());*/GameMain());

	}
	catch (const char* err)
	{
		FILE* fp = NULL;

		DATEDATA data;

		GetDateTime(&data);
		//�t�@�C���I�[�v��
		fopen_s(&fp, "ErrLog.txt", "a");
		//�G���[�f�[�^�̏�������
		fprintf_s(fp, "%02d�N %02d�� %02d�� %02d�� %02d�� %02d�b : %s������܂���B\n", data.Year, data.Mon, data.Day, data.Hour, data.Min, data.Sec, err);

		return 0;
	}
	FpsController FPSC(FRAMERATE, 800);

	// �Q�[�����[�v
	while ((ProcessMessage() == 0) && (sceneMng->Update() != nullptr)) {

		ClearDrawScreen();		// ��ʂ̏�����
		PAD_INPUT::UpdateKey();
		sceneMng->Draw();
		FPSC.All();
		FPSC.Disp();
		//�����I��
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_BACK) || CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}
		ScreenFlip();			// ����ʂ̓��e��\��ʂɔ��f
	}

	DxLib_End();

	return 0;

}