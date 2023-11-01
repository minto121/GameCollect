#include "DxLib.h"
#include "takoyaki.h"
//#include "GameMain.h"
#include "PadInput.h"
#include "GameSelect.h"


Takoyaki::Takoyaki()
{
	Select = 0;
	 Cards_img[42];
	cardimg1=LoadGraph("../images/Takoyaki/PlayingCardsfake.png");//カード画像読み込み
	CursolImg=LoadGraph("../images/Takoyaki/cursor.png");//カーソル画像読み込み
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

void Takoyaki::Draw()const
{
	
	//タイトルの描画
	//DrawGraph(0, 0, TitleImg, FALSE);
	DrawString(350, 50, "main", 0xffffff, TRUE);

	//カード画像描画
	DrawGraph(70, 50,cardimg1,TRUE);
	DrawGraph(190, 50, cardimg1, TRUE);

	//カーソルの描画
	DrawGraph(select_X,50 , CursolImg, TRUE);
   
	
    //DrawGraph(650, select_y, CursorImg, TRUE);
}