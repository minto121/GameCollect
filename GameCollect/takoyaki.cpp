#include "DxLib.h"
#include "takoyaki.h"
//#include "GameMain.h"
#include "PadInput.h"
#include "GameSelect.h"


Takoyaki::Takoyaki()
{
	Select=0;
	Cards_img[56];
	cardimg = LoadDivGraph("../images/Takoyaki/PlayingCards.png",56,14,4,128,256,Cards_img);	//�J�[�h�摜�ǂݍ���
	CursolImg = LoadGraph("../images/Takoyaki/cursor.png");										//�J�[�\���摜�ǂݍ���
	select_X = 100;
	BackCard_Img = LoadGraph("../image/Takoyaki/card_back.png");
	

	//��D�̏�����
	for (int i = 0; i < 10; ++i) {
		handCard[0][i] = 0;
		handCard[1][i] = 0;
		cardFlipped[0][i] = false;
		cardFlipped[1][i] = false;
	}

	//�ŏ��Ɏ�D��`��
	Draw();
	ScreenFlip();
}

Takoyaki::~Takoyaki() {

}

AbstractScene* Takoyaki::Update()
{
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
			cardFlipped[0][Select] = !cardFlipped[0][Select]; // �J�[�h�𗠕Ԃ�
		}
	}

	//��D�̕`��
	Draw();
	ScreenFlip();
	return this;
}

void Takoyaki::Draw()const
{
	ClearDrawScreen();


	// ��̎�D��`��
	for (int i = 0; i < 10; ++i) {
		DrawGraph(70 + i * 120, 50, cardFlipped[0][i] ? Cards_img[handCard[0][i]] : BackCard_Img, TRUE);
	}

	// ���̎�D��`��
	for (int i = 0; i < 10; ++i) {
		DrawGraph(70 + i * 120, 300, Cards_img[handCard[1][i]], TRUE);
	}

	////�J�[�h�摜�`��
	//if (cardFlipped) {
	//	DrawGraph(70, 50, Cards_img[1], TRUE);
	//}
	//{
	//	
	//	if (cardFlipped) {
	//		DrawGraph(70, 50, Cards_img[0], TRUE);
	//	}
	//	else {
	//		DrawGraph(70, 50, BackCard_Img, TRUE); // �J�[�h�����Ԃ��Ă��Ȃ��ꍇ�͗��ʂ�`��
	//	}
	//	
	//}
	//DrawGraph(70, 50, Cards_img[0], TRUE);
	//DrawGraph(190, 50, Cards_img[2], TRUE);
	//DrawGraph(190, 50, Cards_img[3], TRUE);
	//DrawGraph(190, 50, Cards_img[4], TRUE);
	//DrawGraph(190, 50, Cards_img[5], TRUE);


	//�J�[�\���̕`��
	DrawGraph(select_X, 250, CursolImg, TRUE);
	ScreenFlip();

	//DrawGraph(650, select_y, CursorImg, TRUE);
}






