#pragma once
#include"AbstractScene.h"

class HitAndBlow : public AbstractScene {
private:
	/* 画像読み込み */
	int ColorImg[6]; // 色の駒の画像配列
	int HitBlowImg[2]; // ヒットピンとブローピンの画像表示
	//int HitImg;  // ヒットピンの画像表示
	//int BlowImg; // ブローピンの画像表示
	
	/* 変数 */
	int Color[6]; // 色の駒を入れる配列
	int Answer[4];  // 色と場所を当てる配列
	int Reasoning[4];  // 色と場所を推理する配列
	int SaveReasoning[8][4]; // 色と場所を決定した配列
	int SaveColor; // 確定した色を表示
	int ColorDecision; // 色の場所決定変数
	int DecisionFlg;  // 答え決定フラグ
	int Hit;     // ヒット数を数える変数
	int Blow;    // ブロー数を数える変数
	int WarpPosition;  // 今入れようとしている場所の変数
	int SidePosition;  // 色を選択する場所の変数
	int Change;  // 交換する時に使う変数
	int Turns; // ターン数を数える変数
	int ColorFlg; // 色を入れたか確認するフラグ
	int SaveHit[8];
	int SaveBlow[8];

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

	//// 判定の関数
	void Judgment();
};