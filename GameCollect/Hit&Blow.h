#pragma once
#include"AbstractScene.h"

class HitAndBlow : public AbstractScene {
private:
	/* 画像読み込み */
	int ColorImg[6]; // 色の駒の画像配列
	int HitImg;  // ヒットピンの画像表示
	int BlowImg; // ブローピンの画像表示

	/* 変数 */
	int Color[6]; // 色の駒を入れる配列
	int Answer[4];  // 色と場所を当てる配列
	int Reasoning[4];  // 色と場所を推理する配列 
	int DecisionFlg;  // 答え決定フラグ
	int Hit;     // ヒット数を数える変数
	int Blow;    // ブロー数を数える変数
	int WarpPosition;  // 今入れようとしている場所の変数
	int SidePosition;  // 色を選択する場所の変数
	int Change;  // 交換する時に使う変数
	int Turns;
	

public:
	// インクリメント
	HitAndBlow();
	// デクリメント
	~HitAndBlow();
	// 描画以外をアップデート
	AbstractScene* Update();
	// 描画をアップデート
	void Draw() const override;

	// ランダムに正解の色と場所決める関数
	void RandomDecision();
};