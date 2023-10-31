#include "DxLib.h"
#include "takoyaki.h"
//#include "GameMain.h"
#include "PadInput.h"
#include "GameSelect.h"


Card::Card()
{
	 Cards_img[42];
	cardimg1=LoadGraph("../images/Takoyaki/PlayingCardsfake.png");
	CursolImg=LoadGraph("../images/Takoyaki/cursor.png");
	select_X = 0;
}

Card::~Card()
{

}

AbstractScene*Card::Update()
{

	select_X = PAD_INPUT::OnPressed(XINPUT_BUTTON_PAD_LEFT) * 52;
}

void Card::Draw()const
{
	
	//タイトルの描画
	//DrawGraph(0, 0, TitleImg, FALSE);
	DrawString(350, 50, "main", 0xffffff, TRUE);

	DrawGraph(70, 50,cardimg1,TRUE);
	DrawGraph(190, 50, cardimg1, TRUE);

	//カーソルの描画
	int select_x;
	DrawGraph(75, 190, CursolImg, TRUE);
   
	
    //DrawGraph(650, select_y, CursorImg, TRUE);
}