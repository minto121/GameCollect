#pragma once
#include"AbstractScene.h"

class HitAndBlow : public AbstractScene {
private:
	/* 画像読み込み */
	int ColorImg[6]; // 色の駒の画像配列
	int HitBlowImg[2]; // ヒットピンとブローピンの画像入れる配列
	int TableBgImg; // 背景画面の画像入れる変数
	int BoardImg; // ボード画像入れる変数

	/* SE */
	int PutPinSE; // ピンを置くSE
	int HitPinSE; // ヒットピンのSE

	/* 配列 */
	int Color[6]; // 色の駒を入れる配列
	int Answer[4];  // 色と場所を当てる配列
	int Reasoning[4];  // 色と場所を推理する配列
	int SaveReasoning[8][4]; // 色と場所を決定した配列
	int SaveHit[8]; // そのターンのヒットした数を格納
	int SaveBlow[8];// そのターンのブローした数を格納
	/* 変数 */
	int SaveColor; // 確定した色を表示
	int DecisionFlg;  // 答え決定フラグ
	int Hit;     // ヒット数を数える変数
	int Blow;    // ブロー数を数える変数
	int WarpPosition;  // 今入れようとしている場所の変数
	int SidePosition;  // 色を選択する場所の変数
	int Turns; // ターン数を数える変数
	int ChangeColor; // 色が全部分かった時、順番だけを入れ替えるための変数
	int MoveFlg; // 先攻後攻決めるフラグ
	int FirstMoveFlg; // 最初が先攻か後攻かを暗記する変数
	bool TurnFlg; // ターン数を決めるフラグ
	int WaitTimeFlg; // 待ち時間を作るための変数
	int Count; // 画面遷移の時間管理する変数
	int CoveringFlg; // 色と場所が被っているか確認するフラグ
	int Covering; // 色と場所被ってないか確認する時に必要な変数

public:
	// インクリメント
	HitAndBlow();
	// デクリメント
	~HitAndBlow();
	// 描画以外をアップデート
	AbstractScene* Update();
	// 描画をアップデート
	void Draw() const override;

	// ランダムに正解の色と場所、順番を決める関数
	void RandomDecision();

	// 判定の関数
	void Judgment();

	// 敵の予想をする関数
	void ERandomChoice();

	// 色をリセットする関数
	void ResetColor();

	// 配列の初期化関数
	void ArrayInit();

	// 今までのターンと被りないか確認する関数
	void CheckCovered();

};