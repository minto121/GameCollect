#include "DxLib.h"
#include "takoyaki.h"
//#include "GameMain.h"
#include "PadInput.h"
#include "GameSelect.h"


Takoyaki::Takoyaki()
{
	Select = 0;
	Cards_img[56];

	// �J�[�h�摜�̏�����
	for (int i = 0; i < 56; ++i) {
		Cards_img[i] = -1;  // �f�t�H���g�l�ŏ�����
	}

	// �J�[�h�摜�̏�����
	cardimg = LoadDivGraph("images/Takoyaki/PlayingCards.png", 56, 14, 4, 128, 256, Cards_img);  // �J�[�h�摜�ǂݍ���
	CursolImg = LoadGraph("images/Takoyaki/cursor.png");										//�J�[�\���摜�ǂݍ���
	select_X = 100;
	BackCard_Img = Cards_img[0];

	AButtonPressed = false;
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

	//�J�[�\���@��
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT))
	{
		Select--;
		select_X -= 120;
	}
	//�J�[�\���E
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT))
	{
		Select++;
		select_X += 120;
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
		if (select_X == select_X) {
			AButtonPressed = true; // A�{�^���������ꂽ���Ƃ��L�^
			if (select_X >= 70 && select_X < 1180) { // �J�[�h���`�悳��Ă���͈͓����m�F
				if (Select >= 0 && Select < 10) {
					if (!cardFlipped[0][Select]) {
						handCard[0][Select] = GetRand(8) + 1; // 1?9�̃����_���Ȓl���Z�b�g
						cardFlipped[0][Select] = true; // �J�[�h�𗠕Ԃ�
					}
				}
			}
		}
	}
	else {
		AButtonPressed = false; // A�{�^����������Ă��Ȃ����Ƃ��L�^
	}

	//��D�̕`��
	Draw();
	ScreenFlip();
	return this;
}

void Takoyaki::Draw()const
{
	ClearDrawScreen();

	// �J�[�h�摜�`��
	for (int i = 0; i < 10; ++i) {
		int cardIndex = handCard[0][i];
		if (cardIndex >= 0 && cardIndex < 56) {
			DrawGraph(70 + i * 120, 50, cardFlipped[0][i] ? Cards_img[cardIndex] : BackCard_Img, TRUE);
		}
		else {
			// �J�[�h�������ȏꍇ�A�o�b�N�J�[�h��`��
			DrawGraph(70 + i * 120, 50, BackCard_Img, TRUE);
		}
	}

	// 2P���̎�D�̃J�[�h�摜�`��
	for (int i = 0; i < 10; ++i) {
		int cardIndex = handCard[1][i];
		if (cardIndex >= 0 && cardIndex < 56) {
			DrawGraph(70 + i * 120, 300, cardFlipped[1][i] ? Cards_img[cardIndex] : BackCard_Img, TRUE);
		}
		else {
			DrawGraph(70 + i * 120, 300, BackCard_Img, TRUE); // �J�[�h�������ȏꍇ�A�o�b�N�J�[�h��`��
		}
	}
	//�J�[�\���̕`��
	DrawGraph(select_X, 250, CursolImg, TRUE);
	ScreenFlip();

	
}