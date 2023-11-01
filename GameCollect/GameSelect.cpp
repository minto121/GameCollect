#include "GameSelect.h"
#include "Title.h"
#include"PadInput.h"
#include "DxLib.h"
#include"RabbitAndHounds.h"

GameSelect::GameSelect()
{
	Select = 0;
	Once = TRUE;

}

GameSelect::~GameSelect()
{
}

AbstractScene* GameSelect::Update()
{
	//�\���L�[������
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP))
	{
		Select--;
		if (Select < 0)Select = 3;
	}
	//�\���L�[������
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN))
	{
		Select++;
		if (Select > 3)Select = 0;
	}

	//L�X�e�B�b�N�����
	if (PAD_INPUT::GetLStick().ThumbY > 10000 && Once == TRUE)
	{
		Select--;
		if (Select < 0)Select = 3;
		Once = FALSE;
	}

	//L�X�e�B�b�N������
	if (PAD_INPUT::GetLStick().ThumbY < -10000 && Once == TRUE)
	{
		Select++;
		if (Select > 3)Select = 0;
		Once = FALSE;
	}

	//L�X�e�B�b�N�����ɖ߂��ꂽ��Once�����Z�b�g
	if (Once == FALSE && PAD_INPUT::GetLStick().ThumbY < 10000 && PAD_INPUT::GetLStick().ThumbY > -10000)
	{
		Once = TRUE;
	}

	

	return this;
}

void GameSelect::Draw() const
{
	DrawString(70, 240, "Select", 0xffffff);
}
