#pragma once
#include "AbstractScene.h"

class RabbitAndHounds : public AbstractScene
{
private:
	int BackGroundImg;

	int Player;

	int now_menu; //現在選択してるメニュー
	int font_handle;  //フォント
	int input_margin;  //操作時間間隔

public:

	RabbitAndHounds();

	~RabbitAndHounds();

	//描画以外の更新を実行
	AbstractScene* Update() override;

	//描画に関することを実装
	void Draw() const override;

};

