#include "sinkeisuijaku.h"
#include "DxLib.h"
#include <stdlib.h>
#include <time.h>

sinkeisuijaku::sinkeisuijaku()
{
    testflg = 0;
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


    if (isPlayerTurn == 1) {

        if (testcount == 0) {
            for (int j = 0; j < 4; j++) {
                for (int i = 0; i < 5; i++) {
                    test1 = trumps[j][i].syurui;
                }
            }
        }
        //カーソルの値を格納


        if (count >= 10) {
            // カード選択
            if (g_KeyFlg & PAD_INPUT_1) {
                trumpflg = 1;
                rCount++;
                peacount++;
            }
            if (trumpflg == 1 && rCount <= 2) {
                trumps[S_ber][S2_ber].flg = 1;
                //test

                trumps[S_ber][S2_ber].syunflg = trumps[S_ber][S2_ber].syurui;

            }






            // カードを選択したときの種類を2回まで記録
            if (peacount == 1) {
                test1 = trumps[S_ber][S2_ber].syurui;
                testcount += 1;
            }
            if (testcount = 0) {
                test3 = test1;
            }
            if (testcount = 2) {
                test2 = test3;
            }

            else if (peacount == 2) {
                if (test1 != trumps[S_ber][S2_ber].syurui) {
                    test2 = trumps[S_ber][S2_ber].syurui;
                }
            }
        }
        trumpflg = 0;
        if (peacount >= 3) {
            peacount = 0;
        }




        // プレイヤーのターン
        // ここにプレイヤーのターンの処理を実装します。
        // キー入力などを利用してプレイヤーの操作を受け付ける処理が考えられます。
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
                if (trumpflg == 0 ) {
                    // カードを選択したときの種類を1回目に記録
                    test1 = trumps[S_ber][S2_ber].syurui;
                    testcount++;
                }
                else if (rCount < 2 ) {
                    // 2回目のカード選択時に揃っているか判定
                    test2 = trumps[S_ber][S2_ber].syurui;
                    rCount++;

                    // カードを裏返す
                    for (int j = 0; j < 4; j++) {
                        for (int i = 0; i < 5; i++) {
                            trumps[j][i].flg = 0;

                        }
                    }

                    // カードが裏の状態であれば、表にする
                    if (trumpflg == 1 ) {
                        trumps[S_ber][S2_ber].flg = 1;
                        trumpflg = 1;
                    }

                   

                    // カード選択時に rCount が2より大きい場合でも連続して裏返せないようにリセット
                    rCount = 0;
                }
            }


            if (count >= 10) {
                randend = 1;
            }

            //トランプの選択3回目で裏面に戻す

            if (rCount >= 2) {
               pTime = pTime += 1;
                if (pTime % 50 == 0) {

                    for (int j = 0; j < 4; j++) {
                        for (int i = 0; i < 5; i++) {
                            trumps[j][i].flg = 0;
                            trumps[j][i].syunflg = 21;
                            pTime = 0;
                        }
                    }
                    test1 = 21;
                    test2 = 21;
                    rCount = 0;
                    peacount = 0;

                    // プレイヤーの手番が終了したら、isPlayerTurn フラグを false に設定し、コンピューターのターンへ移行します。
                    isPlayerTurn = 0;
                    isComputerTurn = 1;
                }
            }





            // 揃ったカードの確認とメッセージ表示
            for (int j = 0; j < 4; j++) {
                for (int i = 0; i < 5; i++) {
                    if (trumps[j][i].flg == 1 && trumps[j][i].syunflg != 0) {
                        for (int k = 0; k < 4; k++) {
                            for (int l = 0; l < 5; l++) {
                                if (trumps[j][i].syunflg + 10 == trumps[k][l].syunflg || trumps[j][i].syunflg - 10 == trumps[k][l].syunflg) {
                                    trumps[j][i].visible = 1;
                                    pea = 1;
                                }
                            }
                        }
                    }
                }
            }

            pea = 0;




            // カードを選択したときの種類を2回まで記録
            if (testcount == 1) {
                test1 = trumps[S_ber][S2_ber].syurui;
                testcount++;
            }
            else if (testcount == 3) {
                test2 = trumps[S_ber][S2_ber].syurui;
                testcount = 0;
       
            }
        }

    }

  

    if (isComputerTurn == 1) {
        // コンピューターのターン
        ComputerTurn();

        // コンピューターの手番が終了したら、カードの揃い具合を確認する処理を実行します。
        CheckMatched();
    }





    return this;
}

void sinkeisuijaku::Draw() const
{
    SetFontSize(50);
    DrawFormatString(20, 100, 0x00ffff, "残り時間 %d", 5 - pTime / 10);


  
    if (pea == 1) {
        DrawFormatString(100, 120, 0x00ffff, "そろった ");
    }



     // トランプの表示
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 5; i++) {
            
            if (trumps[j][i].visible == 0) {
            if (trumps[j][i].flg == 0) {
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
            //プレイヤーがカードを揃えたら
            if (trumps[j][i].visible == 1) {
                DrawGraph(340 + i * 120, 0 + j * 150, S_T[42], TRUE);
            }

            //コンピューターがカードを揃えたら
            if (trumps[j][i].visible == 2) {
                DrawGraph(340 + i * 120, 0 + j * 150, S_T[39], TRUE);

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

void sinkeisuijaku::ComputerTurn()
{
 

    //カウント
    cTime++;


    if (rebirth == 0) {

        int randRow, randCol, randRow2, randCol2;

        // ランダムな座標を生成
        do {
             randRow = rand() % 4;
              randCol = rand() % 5;
        } while (trumps[randRow][randCol].visible == 1);

            do {
                randRow2 = rand() % 4;
                randCol2 = rand() % 5;
            } while (randRow2 == randRow && randCol2 == randCol || trumps[randRow2][randCol2].visible == 1);  // 2枚目が1枚目と異なる座標になるように



                // 選択した2枚のカードをめくる
            trumps[randRow][randCol].flg = 1;
            trumps[randRow2][randCol2].flg = 1;
            rebirth = rebirth + 1;

            if (trumps[randRow][randCol].syurui + 10 == trumps[randRow2][randCol2].syurui || trumps[randRow][randCol].syurui == trumps[randRow2][randCol2].syurui - 10) {
                trumps[randRow][randCol].visible = 2;
                trumps[randRow2][randCol2].visible = 2;
           }

        }
    
            //とりあえずカードを裏面に戻す

            if (cTime % 50 == 0) {

                for (int j = 0; j < 4; j++) {
                    for (int i = 0; i < 5; i++) {
                        trumps[j][i].flg = 0;
                        trumps[j][i].syunflg = 21;
                    }
                }
                // コンピューターの手番が終了したら、isComputerTurn フラグを false に設定し、プレイヤーのターンへ移行します。
                isComputerTurn = 0;
                isPlayerTurn = 1;
                rebirth = 0;
    }

}

void sinkeisuijaku::CheckMatched()
{
    // ここにカードの揃い具合を確認する処理を実装します。
     // プレイヤーとコンピューターの両方に対して適切な処理を行います。

     // カードが揃った場合、揃ったフラグを設定するなどの処理が考えられます。
}
s