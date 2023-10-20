#pragma once
#include"AbstractScene.h"

class HitAndBlow : public AbstractScene {
private:
	int Color[6]; // 色の駒を入れる配列
	int Hit;     // ヒット数を数える変数
	int Blow;    // ブロー数を数える変数 

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