#include "sinkeisuijaku.h"
#include "DxLib.h"
#include <stdlib.h>
#include <time.h>

sinkeisuijaku::sinkeisuijaku()
{
}

AbstractScene* sinkeisuijaku::Update()
{
    // トランプの画像を分割読み込み
    LoadDivGraph("images/Concentration/PlayingCards.png", 56, 14, 4, 128, 256, S_T);

    // キー入力処理
    // 入力キー取得
    g_OldKey = g_NowKey;
    g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
    g_KeyFlg = g_NowKey & ~g_OldKey;

    // ゲームロジック
    count++;

    // メニューカーソル移動処理
    // 上移動
    if (g_KeyFlg & PAD_INPUT_UP) {
        if (S_ber >= 0 && S_ber <= 4) {
            S_ber = S_ber - 1;
        }
        if (S_ber < 0) {
            S_ber = 3;
        }
    }

    // 下移動
    if (g_KeyFlg & PAD_INPUT_DOWN) {
        if (S_ber >= 0 && S_ber <= 4) {
            S_ber = S_ber + 1;
        }
        if (S_ber >= 4) {
            S_ber = 0;
        }
    }

    // 右移動
    if (g_KeyFlg & PAD_INPUT_RIGHT) {
        S2_ber = S2_ber + 1;
        if (S2_ber == 5 || S2_ber == 9 || S2_ber == 14 || S2_ber == 19 || S2_ber == 24) {
            S2_ber = S2_ber - 5;
        }
    }

    // 左移動
    if (g_KeyFlg & PAD_INPUT_LEFT) {
        S2_ber = S2_ber - 1;
        if (S2_ber == -1 || S2_ber == 6 || S2_ber == 11 || S2_ber == 16 || S2_ber == 21) {
            S2_ber = S2_ber + 5;
        }
    }

    if (count >= 10) {
        // カード選択
        if (g_KeyFlg & PAD_INPUT_1) {
            trumpflg = 1;
            rCount++;
        }
        if (trumpflg == 1) {
            trumps[S_ber][S2_ber].flg = 1;
        }
      
    }
    trumpflg = 0;

    // トランプに値を入れる
    if (count < 2) {
        int x = 1;
        for (int j = 0; j < 4; j++) {
            for (int i = 0; i < 5; i++) {
                trumps[j][i].syurui = x++;
            }
        }
    }

    // 先行後攻決め
    srand((unsigned int)time(NULL)); // 現在の時間を使って初期化
    first = (rand() % 2) + 1; // 1または2をランダムに生成
    srand((unsigned int)time(NULL));

    if (randend != 1) {
        for (int i = 0; i < 19; i++) {
            r = (rand() % 3) + 1;
            r2 = (rand() % 4) + 1;
            trumps[4][6].syurui = trumps[0][0].syurui;
            trumps[0][0].syurui = trumps[r][r2].syurui;
            trumps[r][r2].syurui = trumps[4][6].syurui;
        }
    }
    if (count >= 10) {
        randend = 1;
    }

    //トランプの選択3回目で裏面に戻す

    if (rCount % 3 == 0) {
        for (int j = 0; j < 4; j++) {
            for (int i = 0; i < 5; i++) {
                    trumps[j][i].flg = 0;
            }
        }
    }

  

    return this;
}

void sinkeisuijaku::Draw() const
{
    //00と01でそろったの文字でたからあとは数字が揃ったら似したい
    if (trumps[0][1].flg == 1 && trumps[0][2].flg == 1) {
        DrawFormatString(100, 100, 0x0000ff, "そろったぜ！");
    }


  DrawFormatString(100, 260, 0xfff00f, "flg %d", trumps[0][1].flg);

    /*DrawFormatString(100, 260, 0xfff00f, "rCount %d", rCount);
    DrawFormatString(100, 280, 0xfff00f, "r2Count %d", r2Count);*/

    // トランプの表示
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 5; i++) {
            if (trumps[j][i].flg == 0 ) {
                // カードが選択されていない場合、カードの裏を表示
                DrawRotaGraph(400 + i * 120, 130 + j * 150, 1, 0, S_T[0], TRUE);
            }
            else {
                if (trumps[j][i].syurui <= 10) {
                    // カードが選択されている場合、カードの表を表示
                    DrawGraph(340 + i * 120, 0 + j * 150, S_T[trumps[j][i].syurui], TRUE);
                }
                if (trumps[j][i].syurui > 10) {
                    DrawGraph(340 + i * 120, 0 + j * 150, S_T[trumps[j][i].syurui + 18], TRUE);
                }
            }
        }
    }

    // 選択中のトランプにハイライトを表示
    DrawBox(355 + S2_ber * 120, 55 + S_ber * 150, 450 + S2_ber * 120, 200 + S_ber * 150, 0xff0000, FALSE);

    // その他の情報表示
    DrawFormatString(100, 180, 0xfff00f, "種類%d", trumps[S_ber][S2_ber].syurui);

    // ターン情報表示
    if (first == 1) {
        DrawFormatString(50, 30, 0xff00ff, "先行です！");
    }
    else {
        DrawFormatString(50, 30, 0xff00ff, "後攻です！");
    }
}