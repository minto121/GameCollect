#include "DxLib.h"
#include "Title.h"

#include "PadInput.h"

#include "LastCard.h"

//�^�C�g�����j���[
enum class TITLE_MENU
{
	GAME_START = 0,
	GAME_RANKING,
	GAME_HELP,
	GAME_END
};

Title::Title()
{

	//�t�H���g�̒ǉ�
	MenuFont = CreateFontToHandle("HG�n�p�p�߯�ߑ�", 64, 8, DX_FONTTYPE_ANTIALIASING);

	////�^�C�g���摜�̓ǂݍ���
	//if ((TitleImg = LoadGraph("Resource/Images/mori.png")) == -1)
	//{
	//	throw "Resource/Images/mori.png";
	//}
	//// �J�[�\���摜�̓ǂݍ���
	//if ((CursorImg = LoadGraph("Resource/Images/Apple_Red.png")) == -1)
	//{
	//	throw "Resource/Images/apple.png";
	//}
	////BGM�̓ǂݍ���
	//if ((TitleBGM = LoadSoundMem("Resource/sounds/BGM/yonhonnorecorder.wav")) == -1)
	//{
	//	throw "Resource/sounds/BGM/yonhonnorecorder.wav";
	//}
	////BGM�̉��ʕύX
	//ChangeVolumeSoundMem(140, TitleBGM);

	////SE�̓ǂݍ���
	//if ((MenuSE = LoadSoundMem("Resource/sounds/SE/select01.wav")) == -1) //�I��SE
	//{
	//	throw "Resource/sounds/SE/select01.wav";
	//}
	////SE�̉��ʕύX
	//ChangeVolumeSoundMem(110, MenuSE);

	////BGM�̍Đ�
	//if (CheckSoundMem(TitleBGM) == 0)
	//{
	//	PlaySoundMem(TitleBGM, DX_PLAYTYPE_LOOP);
	//}
}

Title::~Title()
{
	
}

AbstractScene* Title::Update()
{

	/*if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))*/
	if(CheckHitKey(KEY_INPUT_P))
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
		return new LastCard();
	}

	


	return this;
}

void Title::Draw()const
{
	//�^�C�g���̕`��
	DrawGraph(0, 0, TitleImg, FALSE);
	DrawStringToHandle(150, 100, "�Q�[����S", 0xffffff, MenuFont);

	//���j���[�̕`��
	DrawStringToHandle(70, 240, "�����[��", 0xffffff, MenuFont);
	DrawStringToHandle(70, 320, "��񂫂�", 0xffffff, MenuFont);
	DrawStringToHandle(70, 400, "�ւ��", 0xffffff, MenuFont);
	DrawStringToHandle(70, 480, "�����", 0xffffff, MenuFont);

	//�J�[�\���̕`��
	int select_y = 230 + Select * 80;
	DrawGraph(650, select_y, CursorImg, TRUE);
}