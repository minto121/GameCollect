#include "DxLib.h"
#include "takoyaki.h"
//#include "GameMain.h"
#include "PadInput.h"
#include "GameSelect.h"


Takoyaki::Takoyaki()
{
	Select = 0;
	Cards_img[56];
	cardimg = LoadDivGraph("../images/Takoyaki/PlayingCards.png",56,14,4,128,256,Cards_img);//�J�[�h�摜�ǂݍ���
	CursolImg = LoadGraph("../images/Takoyaki/cursor.png");//�J�[�\���摜�ǂݍ���
	select_X = 100;
	BackCard_Img = LoadGraph("../image/Takoyaki/card_back.png");
}

Takoyaki::~Takoyaki() {

}

AbstractScene* Takoyaki::Update()
{

	/*if (PAD_INPUT::OnPressed(XINPUT_BUTTON_DPAD_LEFT))
	{
		Select--;
		select_X -= 5;
	}

	if (PAD_INPUT::OnPressed(XINPUT_BUTTON_DPAD_RIGHT)) {
		Select++;
		select_X += 5;
	}*/
	//�\���L�[������
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT))
	{
		Select--;
		select_X -= 120;
	}
	//�\���L�[������
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT))
	{
		Select++;
		select_X += 120;
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
		if (select_X == 100) {
			cardFlipped = true; // ����̈ʒu��A�{�^�����������ꍇ�A�J�[�h�𗠕Ԃ�
			ClearDrawScreen(); // ��ʂ��N���A
		}
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
		DrawGraph(70, 50, Cards_img[1], TRUE);
	}
	{
		
		if (cardFlipped) {
			DrawGraph(70, 50, Cards_img[0], TRUE);
		}
		else {
			DrawGraph(70, 50, BackCard_Img, TRUE); // �J�[�h�����Ԃ��Ă��Ȃ��ꍇ�͗��ʂ�`��
		}
		
	}
	DrawGraph(70, 50, Cards_img[0], TRUE);
	DrawGraph(190, 50, Cards_img[2], TRUE);
	DrawGraph(190, 50, Cards_img[3], TRUE);
	DrawGraph(190, 50, Cards_img[4], TRUE);
	DrawGraph(190, 50, Cards_img[5], TRUE);


	//�J�[�\���̕`��
	DrawGraph(select_X, 250, CursolImg, TRUE);


	//DrawGraph(650, select_y, CursorImg, TRUE);
}






