#include "DxLib.h"
#include "takoyaki.h"
//#include "GameMain.h"
#include "PadInput.h"
#include "GameSelect.h"


Card::Card()
{

	
}

Card::~Card()
{

}

AbstractScene*Card::Update()
{

	/*if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))*/
	if (CheckHitKey(KEY_INPUT_P))
	{
		//switch (static_cast<TITLE_MENU>(Select))
		//{
		//	//�Q�[����ʂ�
		//case TITLE_MENU::GAME_START:
		//	return new GameSelect();
		//	break;
		//default:
		//	break;
		//}
		return new GameSelect();
	}
	return this;
}

void Card::Draw()const
{
	//�^�C�g���̕`��
	//DrawGraph(0, 0, TitleImg, FALSE);
	DrawString(350, 50, "main", 0xffffff, TRUE);
	//�J�[�\���̕`��
	//int select_y = 230 + Select * 80;
	//DrawGraph(650, select_y, CursorImg, TRUE);
}