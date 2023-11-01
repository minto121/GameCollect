#include "DxLib.h"
#include "takoyaki.h"
//#include "GameMain.h"
#include "PadInput.h"
#include "GameSelect.h"

std::vector<int> cardHandles(52); // カードのハンドルを格納する配列


Takoyaki::Takoyaki()
{
	Select = 0;
	// カードの読み込み
	LoadDivGraph("../images/Takoyaki/PlayingCards.png", 52, 13, 4, 90, 70, cardHandles.data());
	CursolImg = LoadGraph("../images/Takoyaki/cursor.png");//カーソル画像読み込み
	select_X = 0;
}

Takoyaki::~Takoyaki() {

}

AbstractScene* Takoyaki::Update()
{

	if(PAD_INPUT::OnPressed(XINPUT_BUTTON_DPAD_LEFT))
    {
		Select--;
		select_X -= 5;
    }

	if (PAD_INPUT::OnPressed(XINPUT_BUTTON_DPAD_RIGHT)) {
		Select++;
		select_X += 5;
	}
	if (PAD_INPUT::OnPressed(XINPUT_BUTTON_A)) {
		
	}
	return this;
}

void Takoyaki::Draw() const
{
	//タイトルの描画
	//DrawGraph(0, 0, TitleImg, FALSE);
	DrawString(350, 50, "main", 0xffffff, TRUE);

	//カード画像描画
	DrawGraph(70, 50, cardHandles[0], TRUE);
	DrawGraph(190, 50, cardHandles[1], TRUE);

	//カーソルの描画
	DrawGraph(select_X, 50, CursolImg, TRUE);

	//DrawGraph(650, select_y, CursorImg, TRUE);
}






