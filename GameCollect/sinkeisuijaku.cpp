#include "sinkeisuijaku.h"
#include "DxLib.h"
#include <stdlib.h>
#include <time.h>
sinkeisuijaku::sinkeisuijaku()
{
    Select = LoadSoundMem("sound/SE/shuffle2.wav");
  

    testflg = 0;

    //先行後攻決め
    srand((unsigned int)time(NULL)); // 現在の時間を使って初期化q
    first = (rand() % 2) + 1; // 1または2をランダムに生成
    //srand((unsigned int)time(NULL));
    first = 0;
    // 初手のプレイヤーとコンピューターの設定
    if (first == 1) {
        isPlayerTurn = 1;
    }
    else {
        isComputerTurn = 1;
    }
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



    //何枚かめくったカードの数字を覚えさせて、一枚目にそのカードと同じ数字を引いたら2枚目にめくらせる

    if (M == 0) {
        for (int j = 0; j < 4; j++) {
            for (int i = 0; i < 5; i++) {
                if (trumps[j][i].flg == 1) {
                    MemoryCount[0] = trumps[j][i].syurui;
                }
            }
        }
    }        

          if (M == 1) {
              for (int j = 0; j < 4; j++) {
                  for (int i = 0; i < 5; i++) {
                      if (trumps[j][i].flg == 1) {
                          MemoryCount[M] = trumps[j][i].syurui;
                      }
                  }
              }
          }



          if (M == 2) {
              for (int j = 0; j < 4; j++) {
                  for (int i = 0; i < 5; i++) {
                      if (trumps[j][i].flg == 1) {
                          MemoryCount[M] = trumps[j][i].syurui;
                      }
                  }
              }
          }
  


          if (M == 3) {
              for (int j = 0; j < 4; j++) {
                  for (int i = 0; i < 5; i++) {
                      if (trumps[j][i].flg == 1) {
                          MemoryCount[M] = trumps[j][i].syurui;
                      }
                  }
              }
          }



          if (M == 4) {
              for (int j = 0; j < 4; j++) {
                  for (int i = 0; i < 5; i++) {
                      if (trumps[j][i].flg == 1) {
                          MemoryCount[M] = trumps[j][i].syurui;
                      }
                  }
              }
          }



    // トランプに値を入れる
    if (count < 2) {
        int x = 1;
        for (int j = 0; j < 4; j++) {
            for (int i = 0; i < 5; i++) {
                trumps[j][i].syurui = x++;

            }
        }
    }



    if (randend != 1) {
        for (int i = 0; i < 19; i++) {
            r = (rand() % 3) + 1;
            r2 = (rand() % 4) + 1;
            trumps[4][6].syurui = trumps[0][0].syurui;
            trumps[0][0].syurui = trumps[r][r2].syurui;
            trumps[r][r2].syurui = trumps[4][6].syurui;
        }
    }


    //カードすべてが揃ったら画面遷移
    if (Cpeacount + peacount == 20) {
        Resultflg = 1;
        }


    // プレイヤーのターン
    if (isPlayerTurn == 1) {

        if (testcount == 0) {
            for (int j = 0; j < 4; j++) {
                for (int i = 0; i < 5; i++) {
                    select1 = trumps[j][i].syurui;
                }
            }
        }

        // カードを選択したときの種類を2回まで記録
        if (selectcount == 1) {
            select1 = trumps[S_ber][S2_ber].syurui;
            testcount += 1;
        }
        if (testcount == 0) {
            select3 = select1;
        }
        if (testcount == 2) {
            select2 = select3;
        }

        else if (selectcount == 2) {
            if (select1 != trumps[S_ber][S2_ber].syurui) {
                select2 = trumps[S_ber][S2_ber].syurui;
            }
        }

        trumpflg = 0;
        if (selectcount >= 3) {
            selectcount = 0;
        }


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
            if (g_KeyFlg & PAD_INPUT_1 && rCount < 2 && (trumps[S_ber][S2_ber].syurui != lastSelect ) && trumps[S_ber][S2_ber].visible != 1 && trumps[S_ber][S2_ber].visible != 2) {

                M++;
                if (M > 4) {
                    M = 0;
                }
                if (trumpflg == 0) {

                    //選択音
                    PlaySoundMem(Select, DX_PLAYTYPE_BACK);


                    trumps[S_ber][S2_ber].flg = 1;

                    trumpflg = 1;
                    rCount++;
                    selectcount++;

                    // カードがまだ選択されていないか確認
                    // カードを選択したときの種類を1回目に記録
                    select1 = trumps[S_ber][S2_ber].syurui;
                    testcount++;

                    // 最後に選択されたカードの位置を更新
                    lastSelect = trumps[S_ber][S2_ber].syurui;

                }
                else if (rCount < 2) {
                    // 2回目のカード選択時に揃っているか判定
                    select2 = trumps[S_ber][S2_ber].syurui;
                    rCount++;



                    // カードを裏返す
                    for (int j = 0; j < 4; j++) {
                        for (int i = 0; i < 5; i++) {
                            trumps[j][i].flg = 0;
                        }
                    }


                    // カードが裏の状態であれば、表にする
                    if (trumpflg == 1) {
                        trumps[S_ber][S2_ber].flg = 1;
                        trumpflg = 1;
                    }

                    // カード選択時に rCount が2より大きい場合でも連続して裏返せないようにリセット
                    rCount = 0;
                }
            }


            if (count >= 10) {

                if (trumpflg == 1 && rCount <= 2) {

                    //test

                    trumps[S_ber][S2_ber].flg2 = trumps[S_ber][S2_ber].syurui;

                }


                randend = 1;
            }

            //トランプの選択3回目で裏面に戻す

            if (rCount >= 2) {
                pTime = pTime += 1;
                if (pTime % 50 == 0) {

                    for (int j = 0; j < 4; j++) {
                        for (int i = 0; i < 5; i++) {
                            trumps[j][i].flg = 0;
                            trumps[j][i].flg2 = 100;
                            pTime = 0;
                        }
                    }
                    select1 = 0;
                    select2 = 0;
                    rCount = 0;
                    selectcount = 0;

                    // プレイヤーの手番が終了したら、isPlayerTurn フラグを false に設定し、コンピューターのターンへ移行します。
                    isPlayerTurn = 0;
                    isComputerTurn = 1;
                    int i, j = 0;

                }
            }





            // 揃ったカードの確認とメッセージ表示
            for (int j = 0; j < 4; j++) {
                for (int i = 0; i < 5; i++) {
                    if (trumps[j][i].flg == 1) {
                        for (int k = 0; k < 4; k++) {
                            for (int l = 0; l < 5; l++) {
                                if (trumps[j][i].flg2 + 10 == trumps[k][l].flg2 || trumps[j][i].flg2 - 10 == trumps[k][l].flg2) {
                                    trumps[j][i].visible = 1;
                                    pea = 1;
                                    selectcount = selectcount + 1;
                                  //  PlaySoundMem(Select, DX_PLAYTYPE_NORMAL);

                                }
                            }
                        }
                    }
                }
            }

            //プレイヤーの揃えた枚数をカウント
            for (int j = 0; j < 4; j++) {
                for (int i = 0; i < 5; i++) {
                    if (trumps[j][i].flg == 1) {
                        if (trumps[j][i].visible == 1)
                            peacount = peacount + 1;
                    }
                }
            }

            // カードを選択したときの種類を2回まで記録
            if (selectcount == 1) {
                select1 = trumps[S_ber][S2_ber].syurui;
                testcount++;
            }
            else if (selectcount == 2) {
                select2 = trumps[S_ber][S2_ber].syurui;
                testcount = 0;
            }

        }
    }
    

    




    if (isComputerTurn == 1) {
        // コンピューターのターン
        ComputerTurn();
        lastSelect = -1;
        pea = 0;
    }

    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 5; i++) {
            if (trumps[j][i].visible == 1) {
                trumps[j][i].flg = 0;
            }
        }
    }

    return this;
}

void sinkeisuijaku::Draw() const
{
    if (Resultflg == 0) {

        SetFontSize(50);
        DrawFormatString(20, 100, 0x00ffff, "残り時間 %d", 5 - pTime / 10);

        DrawFormatString(100, 230, 0x00ffff, "pea%d ", peacount);
        DrawFormatString(100, 270, 0x00ffff, "pea%d ", Cpeacount);


        DrawFormatString(100, 400, 0x00ffff, "M%d ", MemoryCount[0]);
        DrawFormatString(100, 440, 0x00ffff, "M%d ", MemoryCount[1]);
        DrawFormatString(100, 480, 0x00ffff, "M%d ", MemoryCount[2]);
        DrawFormatString(100, 520, 0x00ffff, "M%d ", MemoryCount[3]);
        DrawFormatString(100, 560, 0x00ffff, "M%d ", MemoryCount[4]);









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

    if (Resultflg == 1) {


    //引き分け
    if (peacount == Cpeacount) {
        SetFontSize(100);
        DrawFormatString(600, 300, 0xffffff, "Draw");
    }

    if (peacount != Cpeacount) {
            SetFontSize(50);
            DrawFormatString(300, 300, 0xffffff, "PLAYER");
            DrawFormatString(850, 300, 0xffffff, "COMPUTER");

            DrawFormatString(300, 350, 0xffffff, "%d枚", peacount);
            DrawFormatString(850, 350, 0xffffff, "%d枚", Cpeacount);

        }

        //playerが勝った場合
        if (peacount > Cpeacount) {
            DrawFormatString(300, 400, 0xffffff, "Winner！");
            DrawFormatString(850, 400, 0xffffff, "Lose...");
        }

        if (peacount < Cpeacount) {

            //computerが勝った場合
            DrawFormatString(300, 400, 0xffffff, "Lose..");
            DrawFormatString(850, 400, 0xffffff, "Winner！");
        }

      
    }

}

void sinkeisuijaku::ComputerTurn()
{
    if (count >= 10) {
        //カウント
        cTime++;


        if (rebirth == 0) {

            int randRow, randCol, randRow2, randCol2;

            // ランダムな座標を生成
            do {
                randRow = rand() % 4;
                randCol = rand() % 5;
            } while (trumps[randRow][randCol].visible == 1 || trumps[randRow][randCol].visible == 2);

            do {
                randRow2 = rand() % 4;
                randCol2 = rand() % 5;
            } while (randRow2 == randRow && randCol2 == randCol || trumps[randRow2][randCol2].visible == 1 || trumps[randRow][randCol].visible == 2 || trumps[randRow][randCol].visible == 1 || trumps[randRow2][randCol2].visible == 1 || trumps[randRow2][randCol2].visible == 2);  // 2枚目が1枚目と異なる座標になるように



             // 選択した2枚のカードをめくる

            trumps[randRow][randCol].flg = 1;
            trumps[randRow2][randCol2].flg = 1;
            rebirth = rebirth + 1;


            if (trumps[randRow][randCol].syurui + 10 == trumps[randRow2][randCol2].syurui || trumps[randRow][randCol].syurui - 10 == trumps[randRow2][randCol2].syurui) {

                trumps[randRow][randCol].visible = 2;
                trumps[randRow2][randCol2].visible = 2;
                selectcount = selectcount + 1;

            }

        }

        //プレイヤーの揃えた枚数をカウント
        for (int j = 0; j < 4; j++) {
            for (int i = 0; i < 5; i++) {
                if (trumps[j][i].flg == 1) {
                    if (trumps[j][i].visible == 2)
                        Cpeacount++;
                }
            }
        }

        for (int j = 0; j < 4; j++) {
            for (int i = 0; i < 5; i++) {
                if (trumps[j][i].visible == 2) {
                    trumps[j][i].flg = 0;
                }
            }
        }


        //とりあえずカードを裏面に戻す

        if (cTime % 50 == 0) {
            for (int j = 0; j < 4; j++) {
                for (int i = 0; i < 5; i++) {
                    trumps[j][i].flg = 0;
                    trumps[j][i].flg2 = 100;
                }
            }
            // コンピューターの手番が終了したら、isComputerTurn フラグを false に設定し、プレイヤーのターンへ移行します。
            isComputerTurn = 0;
            isPlayerTurn = 1;
            rebirth = 0;
        }
    }
}
void sinkeisuijaku::Memory()
{
  
}



