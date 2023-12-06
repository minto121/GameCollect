#include "DxLib.h"
#include "takoyaki.h"
//#include "GameMain.h"
#include "PadInput.h"
#include "GameSelect.h"


Takoyaki::Takoyaki()
{
	Select = 0;
	Cards_img[42];
	cardimg = LoadGraph("../images/Takoyaki/PlayingCardsfake.png");//�J�[�h�摜�ǂݍ���
	CursolImg = LoadGraph("../images/Takoyaki/cursor.png");//�J�[�\���摜�ǂݍ���
	select_X = 0;
	BackCard_Img = LoadGraph("../image/Takoyaki/card_back.png");
}

Takoyaki::~Takoyaki() {

}

AbstractScene* Takoyaki::Update()
{

	if (PAD_INPUT::OnPressed(XINPUT_BUTTON_DPAD_LEFT))
	{
		Select--;
		select_X -= 5;
	}

	if (PAD_INPUT::OnPressed(XINPUT_BUTTON_DPAD_RIGHT)) {
		Select++;
		select_X += 5;
	}
	if (PAD_INPUT::OnPressed(XINPUT_BUTTON_A)) {
		cardFlipped = !cardFlipped;
	}
	return this;
}

void Takoyaki::Draw()const
{

	//�^�C�g���̕`��
	//DrawGraph(0, 0, TitleImg, FALSE);
	DrawString(350, 50, "main", 0xffffff, TRUE);

	//�J�[�h�摜�`��
	if (cardFlipped) {
		DrawGraph(70, 50, BackCard_Img, TRUE);
	}
	DrawGraph(70, 50, cardimg, TRUE);
	DrawGraph(190, 50, cardimg, TRUE);

	//�J�[�\���̕`��
	DrawGraph(select_X, 350, CursolImg, TRUE);


	//DrawGraph(650, select_y, CursorImg, TRUE);
}






