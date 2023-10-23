#include "Porker.h"
#include "GameSelect.h"
#include"PadInput.h"
#include "DxLib.h"
Porker::Porker()
{
    if ((Back = LoadGraph("../GameCollect/images/TexasHoldem/BG_Dummy.png"))) {}
    if (LoadDivGraph("../GameCollect/images/TexasHoldem/Trannpu.png", 10, 13, 4, 75, 105, Tranpu_Img)) {}
}

Porker::~Porker()
{

}

AbstractScene* Porker::Update()
{
    return this;
}

void Porker::Draw() const
{
    DrawGraph(0, 0, Back, TRUE);
    DrawString(70, 240, "Porker", 0xffffff);
    DrawGraph(400, 450, Tranpu_Img[1], TRUE);
   
}
