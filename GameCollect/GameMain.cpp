#include "GameMain.h"
#include "DxLib.h"
#include "PadInput.h"
#include "AbstractScene.h"
#include "Title.h"



GameMain::GameMain() {
   

}

GameMain::~GameMain() {

}

AbstractScene* GameMain::Update() {

    if (dotandbox.Result() != 0 && dotandbox.OnButtonClicked() != 0)
    {
        return new Title;     //‘JˆÚ‚³‚¹‚½‚¢æ
    }
    
    dotandbox.Update();

    return this;
}

void GameMain::Draw() const {
    
    dotandbox.Draw();

}