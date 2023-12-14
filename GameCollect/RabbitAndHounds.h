#pragma once
#include "AbstractScene.h"

class RabbitAndHounds : public AbstractScene
{
private:
	int BackGroundImg;
	int Board; //　盤
	int Piece; //　駒

	int Player;

	int HoundImg;    //猟犬画像
	int RabbitImg;   //ウサギ画像

	int hound_X;   //猟犬X座標
	int hound_Y;   //猟犬Y座標
	int houndSpeed;


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

	void RabbitPiece();
	void HoundIPiece();

};

