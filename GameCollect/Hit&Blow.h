#pragma once
#include"AbstractScene.h"

class HitAndBlow : public AbstractScene {
private:
	int ColorImg[6]; // 色の駒の画像配列
	int Color[6]; // 色の駒を入れる配列
	int Answer[4];  // 色と場所を当てる配列
	int Reasoning[4];  // 色と場所を推理する配列 
	int Hit;     // ヒット数を数える変数
	int Blow;    // ブロー数を数える変数
	int HitImg;  // ヒットピンの画像表示
	int BlowImg; // ブローピンの画像表示

public:
	// インクリメント
	HitAndBlow();
	// デクリメント
	~HitAndBlow();
	// 描画以外をアップデート
	AbstractScene* Update();
	// 描画をアップデート
	void Draw() const override;
};