#include "Porker.h"
#include "GameSelect.h"
#include"PadInput.h"
#include "DxLib.h"
#include "Title.h"

Porker::Porker()
{
    if ((Back = LoadGraph("../GameCollect/images/TexasHoldem/BG_Dummy.png"))) {}
    if (LoadDivGraph("../GameCollect/images/TexasHoldem/PlayingCards.png", 56, 14, 4, 128, 256, Tranpu_Img,FALSE)) {}
    a = 0;
    wt = 0;
    ps1 = 1000;
    es1 = 1000;
    Bs = 0;
    P_FPS = 0;
    P_TEKI = 0;
   

    BTN_flg = FALSE;
    Winflg = FALSE;
    Loseflg = FALSE;
    Drawflg = FALSE;
    E_Fouldflg = FALSE;
    P_Call_H_flg = FALSE;
    P_Raise_H_flg = FALSE;
    P_Fould_H_flg = FALSE;
    WTflg1 = FALSE;
    WTflg2 = FALSE;
    WTflg3 = FALSE;
    WTRelese1 = FALSE;
    WTRelese2 = FALSE;
    WTRelese3 = FALSE;
    BTN_RELESE_FLG1 = FALSE;
    BTN_RELESE_FLG2 = FALSE;
    BTN_RELESE_FLG3 = FALSE;
    BTN_RELESE_FLG4 = FALSE;
    BTN_RELESE_FLG5 = FALSE;
    BTN_RELESE_FLG6 = FALSE;
    P_Call_H_flg = FALSE;
    P_Raise_H_flg = FALSE;
    RC_H_flg = FALSE;
    G_Over_H_flg = FALSE;
    ROUND_INIT();
}

Porker::~Porker()
{

}

//ラウンド初期化
void Porker::ROUND_INIT() 
{
    if (Winflg == FALSE && Loseflg == FALSE && Drawflg == FALSE) {
        P_rand1 = GetRand(51);   //プレイヤーのホールカード1
        P_rand2 = GetRand(51);   //プレイヤーのホールカード2

        E_rand1 = GetRand(51);   //敵のホールカード1
        E_rand2 = GetRand(51);   //敵のホールカード2

        C_rand1 = GetRand(51);   //コミュニティカード1
        C_rand2 = GetRand(51);   //コミュニティカード2
        C_rand3 = GetRand(51);   //コミュニティカード3
        C_rand4 = GetRand(51);   //コミュニティカード4
        C_rand5 = GetRand(51);   //コミュニティカード5

        C_flg1 = FALSE;          //コールかレイズした時の判断用1
        C_flg2 = FALSE;          //コールかレイズした時の判断用2
        C_flg3 = FALSE;          //コールかレイズした時の判断用3
        
        E_Fouldflg = FALSE;      //敵がフォールドしたかどうかの判断用
        E_CAllflg = FALSE;       //敵がコールしたかどうかの判断用
        E_Raiseflg = FALSE;      //敵がレイズしたかどうかの判断用

        Winflg = FALSE;
        Loseflg = FALSE;
        Drawflg = FALSE;
        WTflg1 = FALSE;
        WTflg2 = FALSE;
        WTflg3 = FALSE;
        WTRelese1 = FALSE;
        WTRelese2 = FALSE;
        WTRelese3 = FALSE;
        BTN_RELESE_FLG1 = FALSE;
        BTN_RELESE_FLG2 = FALSE;
        BTN_RELESE_FLG3 = FALSE;
        BTN_RELESE_FLG4 = FALSE;
        BTN_RELESE_FLG5 = FALSE;
        BTN_RELESE_FLG6 = FALSE;
        BTN_flg = FALSE;
        RC_H_flg = FALSE;
        P_Fould_H_flg = FALSE;
        E_Fould_H_flg = FALSE;
        G_Over_H_flg = FALSE;
        CARD_URA_H_flg = TRUE;
    }
}





//プレイヤーのコール
void Porker::P_CALL()
{
    if (Winflg == FALSE && Loseflg == FALSE && Drawflg == FALSE) {
        Bs = Bs + 50;
        ps1 = ps1 - 50;
    }
}




//プレイヤーのレイズ
void Porker::PLAYER_RAISE()
{
    if (Winflg == FALSE && Loseflg == FALSE && Drawflg == FALSE) {
        Bs = Bs + 100;
        ps1 = ps1 - 100;
        P_Raise_H_flg = TRUE;
    }
}






//敵のコールとレイズ
void Porker::ENEMIE_CHOISE()
{
    if (Winflg == FALSE && Loseflg == FALSE && Drawflg == FALSE) {
        P_TEKI = GetRand(100);

        if (P_TEKI < 40) {
            Bs = Bs + 50;
            es1 = es1 - 50;
            E_CAllflg = TRUE;
        }
        else if (40 <= P_TEKI && P_TEKI <= 100) {

            Bs = Bs + 100;
            es1 = es1 - 100;
            E_Raiseflg = TRUE;
        }
       /* else if (70 < P_TEKI <= 100) {
            E_Fouldflg = TRUE;
        }*/
    }
   
}


//カード判断
void Porker::CARD_HANDAN()
{
    P_CARD1_A = P_rand1 % 14;
    P_CARD1_S = P_rand1 / 14;
    P_CARD2_A = P_rand2 % 14;
    P_CARD2_S = P_rand2 / 14;


}


AbstractScene* Porker::Update()
{
    if (PAD_INPUT::OnButton(XINPUT_BUTTON_LEFT_SHOULDER) && PAD_INPUT::OnButton(XINPUT_BUTTON_RIGHT_SHOULDER)) {
        return new Title;
    }

    //               カードのかぶり防止               //

    //ホールカード1がかぶった時やり直し用(プレイヤー)
    if (P_rand2 == P_rand1) {
        P_rand2 = GetRand(54);
    }
   
    //ホールカード1がかぶった時やり直し用(敵)
    if (E_rand1 == P_rand1 || E_rand1 == P_rand2) {
        E_rand1 = GetRand(54);
    }
    //ホールカード2がかぶった時やり直し用(敵)
    if (E_rand2 == P_rand1 || E_rand2 == P_rand2|| E_rand2 == E_rand1) {
        E_rand2 = GetRand(54);
    }
    
    //コミュニティカードがかぶった時やり直し用(1回目)
    if (C_rand1 == P_rand1 || C_rand1 == P_rand2 || C_rand1 == E_rand1 || C_rand1 == E_rand2) {
        C_rand1 = GetRand(54);
    }

    //コミュニティカードがかぶった時やり直し用(2回目)
    if (C_rand2== P_rand1 || C_rand2 == P_rand2 || C_rand2 == E_rand1 || C_rand2 == E_rand2 || C_rand2 == C_rand1) {
        C_rand2 = GetRand(54);
    }

    //コミュニティカードがかぶった時やり直し用(3回目)
    if (C_rand3 == P_rand1 || C_rand3 == P_rand2 || C_rand3 == E_rand1 || C_rand3 == E_rand2 || C_rand3 == C_rand1 || C_rand3==C_rand2) {
        C_rand3 = GetRand(54);
    }

    //コミュニティカードがかぶった時やり直し用(4回目)
    if (C_rand4 == P_rand1 || C_rand4 == P_rand2 || C_rand4 == E_rand1 || C_rand4 == E_rand2 || C_rand4 == C_rand1 || C_rand4 == C_rand2||C_rand4 == C_rand3) {
        C_rand4 = GetRand(54);
    }

    //コミュニティカードがかぶった時やり直し用(5回目)
    if (C_rand5 == P_rand1 || C_rand5 == P_rand2 || C_rand5 == E_rand1 || C_rand5 == E_rand2 || C_rand5 == C_rand1 || C_rand5 == C_rand2 || C_rand5 == C_rand3||C_rand5==C_rand4) {
        C_rand5 = GetRand(54);
    }



    //           カード配列調整用            //
    //カードの配列番号がいらんやつだったらやり直し

    if (P_rand1 == 0 || P_rand1 == 14 || P_rand1 == 28 || P_rand1 == 42) {
        P_rand1 = GetRand(54);
    }

    if (P_rand2 == 0 || P_rand2 == 14 || P_rand2 == 28 || P_rand2 == 42) {
        P_rand1 = GetRand(54);
    }

    if (E_rand1 == 0 || E_rand1 == 14 || E_rand1 == 28 || E_rand1 == 42) {
        E_rand1 = GetRand(54);
    }

    if (E_rand2 == 0 || E_rand2 == 14 || E_rand2 == 28 || E_rand2 == 42) {
        E_rand2 = GetRand(54);
    }

    if (E_rand2 == 0 || E_rand2 == 14 || E_rand2 == 28 || E_rand2 == 42) {
        E_rand2 = GetRand(54);
    }

    if (C_rand1 == 0 || C_rand1 == 14 || C_rand1 == 28 || C_rand1 == 42) {
        C_rand1 = GetRand(54);
    }

    if (C_rand2 == 0 || C_rand2 == 14 || C_rand2 == 28 || C_rand2 == 42) {
        C_rand2 = GetRand(54);
    }

    if (C_rand3 == 0 || C_rand3 == 14 || C_rand3 == 28 || C_rand3 == 42) {
        C_rand3 = GetRand(54);
    }

    if (C_rand4 == 0 || C_rand4 == 14 || C_rand4 == 28 || C_rand4 == 42) {
        C_rand4 = GetRand(54);
    }

    if (C_rand5 == 0 || C_rand5 == 14 || C_rand5 == 28 || C_rand5 == 42) {
        C_rand5 = GetRand(54);
    }






    //待ち時間
    if (WTflg1 == TRUE) {
        P_FPS++;
        if (P_FPS > 60) {
            WTRelese1 = TRUE;
            P_FPS = 0;
            WTflg1 = FALSE;
            P_Call_H_flg = FALSE;
            P_Raise_H_flg = FALSE;
            BTN_RELESE_FLG5 = FALSE;
            //ラウンドチェンジ用
            if (RC_H_flg == TRUE || P_Fould_H_flg == TRUE) {
            
                ROUND_INIT();
            }
            if (G_Over_H_flg == TRUE) {
                G_Over_H_flg = FALSE;
            }
           
        }
    }
    if (WTflg2 == TRUE) {
        P_FPS++;
        if (P_FPS > 60) {
            WTRelese2 = TRUE;
            P_FPS = 0;
            WTflg2 = FALSE;
            P_Call_H_flg = FALSE;
            P_Raise_H_flg = FALSE;
        }
    }
    if (WTflg3 == TRUE) {
        P_FPS++;
        if (P_FPS > 60) {
            WTRelese3 = TRUE;
            P_FPS = 0;
            WTflg3 = FALSE;
            P_Call_H_flg = FALSE;
            P_Raise_H_flg = FALSE;
            CARD_URA_H_flg = FALSE;
        }
    }

    //待ち時間終了後の処理
    if (WTRelese1 == TRUE) {
        C_flg1 = TRUE;
        ENEMIE_CHOISE();
        WTRelese1 = FALSE;
        BTN_flg = FALSE;
    }
    if (WTRelese2 == TRUE) {
        C_flg2 = TRUE;
        ENEMIE_CHOISE();
        WTRelese2 = FALSE;
        BTN_flg = FALSE;
    }
    if (WTRelese3 == TRUE) {
        C_flg3 = TRUE;
        ENEMIE_CHOISE();
        WTRelese3 = FALSE;
        BTN_flg = FALSE;
    }



    //           コール処理              //

    //コール1(今はY押す)
    if (PAD_INPUT::OnButton(XINPUT_BUTTON_Y) && C_flg1 == FALSE && Winflg == FALSE && Loseflg == FALSE && Drawflg == FALSE && P_Call_H_flg == FALSE) {
        P_CALL();
        BTN_flg = TRUE;
        BTN_RELESE_FLG1 = TRUE;
    }
    else if (PAD_INPUT::OnRelease(XINPUT_BUTTON_Y) && BTN_RELESE_FLG1 == TRUE) {
        P_Call_H_flg = TRUE;
        WTflg1 = TRUE;
        BTN_flg = FALSE;
        BTN_RELESE_FLG1 = FALSE;
    }

    //コール2(今はY押す)
    if (PAD_INPUT::OnButton(XINPUT_BUTTON_Y) && C_flg1 ==TRUE && C_flg2 == FALSE && BTN_flg == FALSE && Winflg == FALSE && Loseflg == FALSE && Drawflg == FALSE && P_Call_H_flg == FALSE) {
        P_CALL();
        BTN_flg = TRUE;
        BTN_RELESE_FLG2 = TRUE;
    }
    else if (PAD_INPUT::OnRelease(XINPUT_BUTTON_Y)&&BTN_RELESE_FLG2 == TRUE) {
        P_Call_H_flg = TRUE;
        WTflg2 = TRUE;
        BTN_flg = FALSE;
        BTN_RELESE_FLG2 = FALSE;
    }

    //コール3(今はY押す)
    if (PAD_INPUT::OnButton(XINPUT_BUTTON_Y) && C_flg2 == TRUE && C_flg3 == FALSE && BTN_flg == FALSE && Winflg == FALSE && Loseflg == FALSE && Drawflg == FALSE && P_Call_H_flg == FALSE 
        && P_Call_H_flg == FALSE) {
        P_CALL();
        BTN_flg = TRUE;
        BTN_RELESE_FLG3 = TRUE;
    }
    else if (PAD_INPUT::OnRelease(XINPUT_BUTTON_Y)&&BTN_RELESE_FLG3 == TRUE && P_Call_H_flg == FALSE) {
        P_Call_H_flg = TRUE;
        WTflg3 = TRUE;
        BTN_flg = FALSE;
        BTN_RELESE_FLG3 = FALSE;
       
    }




    //               レイズ               //

    //レイズ1(今はB押す)
    if (PAD_INPUT::OnButton(XINPUT_BUTTON_B) && C_flg1 == FALSE && Winflg == FALSE && Loseflg == FALSE && Drawflg == FALSE) {
        PLAYER_RAISE();
        BTN_flg = TRUE;
        BTN_RELESE_FLG1 = TRUE;
    }
    else if (PAD_INPUT::OnRelease(XINPUT_BUTTON_B) && BTN_RELESE_FLG1 == TRUE) {
        WTflg1 = TRUE;
        BTN_flg = FALSE;
        BTN_RELESE_FLG1 = FALSE;
    }
    
    //レイズ2(今はB押す)
    if (PAD_INPUT::OnButton(XINPUT_BUTTON_B) && C_flg1 == TRUE && C_flg2 == FALSE && BTN_flg == FALSE && Winflg == FALSE && Loseflg == FALSE && Drawflg == FALSE) {
        PLAYER_RAISE();
        BTN_flg = TRUE;
        BTN_RELESE_FLG2 = TRUE;
    }
    else if (PAD_INPUT::OnRelease(XINPUT_BUTTON_B) && BTN_RELESE_FLG2 == TRUE) {
        WTflg2 = TRUE;
        BTN_flg = FALSE;
        BTN_RELESE_FLG2 = FALSE;
    }

    //レイズ3(今はB押す)
    if (PAD_INPUT::OnButton(XINPUT_BUTTON_B) && C_flg2 == TRUE && C_flg3 == FALSE && BTN_flg == FALSE && Winflg == FALSE && Loseflg == FALSE && Drawflg == FALSE) {
        PLAYER_RAISE();
        BTN_flg = TRUE;
        BTN_RELESE_FLG3 = TRUE;
    }
    else if (PAD_INPUT::OnRelease(XINPUT_BUTTON_B) && BTN_RELESE_FLG3 == TRUE) {
        WTflg3 = TRUE;
        BTN_flg = FALSE;
        BTN_RELESE_FLG3 = FALSE;
    }







    //         ラウンドを変える(3回目でタイトル)          //

    //ラウンドチェンジ
    if (PAD_INPUT::OnButton(XINPUT_BUTTON_X) && C_flg3 == TRUE && a <= 3) {
        BTN_RELESE_FLG4 = TRUE;
    }
    else if (PAD_INPUT::OnRelease(XINPUT_BUTTON_X) && C_flg3 == TRUE && a <= 3 && BTN_RELESE_FLG4 == TRUE) {
        a++;
        RC_H_flg = TRUE;
        WTflg1 = TRUE;
        BTN_RELESE_FLG4 = FALSE;
    }


    //フォールド用
     if (PAD_INPUT::OnRelease(XINPUT_BUTTON_X) && C_flg3 == FALSE && a <= 3 && BTN_RELESE_FLG5 == FALSE) {
         BTN_RELESE_FLG5 = TRUE;
        a++;
        P_Fould_H_flg = TRUE;
        WTflg1 = TRUE;
        
     }

     //フォールド後スコア
     if (P_Fould_H_flg == TRUE){
         es1 = Bs + es1;
         Bs = 0;
     }

     //ゲーム終了用
    if (PAD_INPUT::OnRelease(XINPUT_BUTTON_X)  && a >= 3)
    {
        P_Fould_H_flg = FALSE;
         G_Over_H_flg = TRUE;
         WTflg1 = TRUE;
    }


    //リザルト画面表示用フラグ
    if (a >= 3 && G_Over_H_flg == FALSE) {

        if (ps1 > es1 && P_Fould_H_flg == FALSE) {
            Winflg = TRUE;
        }
        else if (ps1<es1 && P_Fould_H_flg == FALSE) {
            Loseflg = TRUE;
        }
        else if (ps1 == es1 && P_Fould_H_flg == FALSE) {
            Drawflg = TRUE;
        }

      

    }


    //リザルト画面からのの遷移
    if (PAD_INPUT::OnButton(XINPUT_BUTTON_A) && a >= 3) {
        return new Title;
    }
    if (PAD_INPUT::OnButton(XINPUT_BUTTON_B) && a >= 3) {
        Winflg = FALSE;
        Loseflg = FALSE;
        Drawflg = FALSE;
        ROUND_INIT();
        a = 0;
        es1 = 1000;
        Bs = 0;
        ps1 = 1000;
    }
    return this;
}










void Porker::Draw() const
{

    //                   カードの表示               //
    if (Drawflg == FALSE && Winflg == FALSE && Loseflg == FALSE) {
        DrawFormatString(400, 600, 0xffffff, "prand1: %d", P_rand1, TRUE); //プレイヤーのホールカード1
        DrawFormatString(600, 600, 0xffffff, "prand2: %d", P_rand2, TRUE); //プレイヤーのホールカード2
        DrawGraph(400, 500, Tranpu_Img[P_rand1], TRUE);
        DrawGraph(600, 500, Tranpu_Img[P_rand2], TRUE);

        DrawFormatString(400, 50, 0xffffff, "erand1: %d", E_rand1, TRUE); //敵のホールカード1
        DrawFormatString(600, 50, 0xffffff, "erand2: %d", E_rand2, TRUE); //敵のホールカード2
        //敵カード裏
        if (CARD_URA_H_flg == FALSE) {
            DrawGraph(400, 0, Tranpu_Img[E_rand1], TRUE);
            DrawGraph(600, 0, Tranpu_Img[E_rand2], TRUE);
        }
        //敵カード表
        if (CARD_URA_H_flg == TRUE) {
            DrawGraph(400, 0, Tranpu_Img[0], TRUE);
            DrawGraph(600, 0, Tranpu_Img[0], TRUE);
        }



        //1回目コールした時コミュニティカードを三枚出す
        if (C_flg1 == TRUE) {
            DrawFormatString(100, 300, 0xffffff, "crand1: %d", C_rand1, TRUE); //コミュニティカード1
            DrawFormatString(300, 300, 0xffffff, "crand2: %d", C_rand2, TRUE); //コミュニティカード2
            DrawFormatString(500, 300, 0xffffff, "crand3: %d", C_rand3, TRUE); //コミュニティカード3
            DrawGraph(100, 250, Tranpu_Img[C_rand1], TRUE);
            DrawGraph(300, 250, Tranpu_Img[C_rand2], TRUE);
            DrawGraph(500, 250, Tranpu_Img[C_rand3], TRUE);
        }

        //2回目コールした時コミュニティカードを1枚出す
        if (C_flg2 == TRUE) {
            DrawFormatString(700, 300, 0xffffff, "crand4: %d", C_rand4, TRUE); //コミュニティカード4
            DrawGraph(700, 250, Tranpu_Img[C_rand4], TRUE);

        }

        //3回目コールした時コミュニティカードを1枚出す
        if (C_flg3 == TRUE) {
            DrawFormatString(900, 300, 0xffffff, "crand5: %d", C_rand5, TRUE); //コミュニティカード4
            DrawGraph(900, 250, Tranpu_Img[C_rand5], TRUE);
        }



        //               キー表示              //

        if (C_flg3 == FALSE) {
            DrawString(100, 600, "[Y]BUTTONでコール", 0xffffff, TRUE);
        }

        if (C_flg3 == FALSE) {
            DrawString(100, 640, "[B]BUTTONでレイズ", 0xffffff, TRUE);
        }

        if (C_flg3 == FALSE) {
            DrawString(100, 680, "[X]BUTTONでフォールド", 0xffffff, TRUE);
        }

        if (C_flg3 == TRUE) {
            DrawString(100, 650, "[X]BUTTONでROUND終了", 0xffffff, TRUE);
        }



        //             ROUND 表示               //

        //ROUND1
        if (a == 0) {
            DrawString(50, 50, "ROUND 1", 0xffffff, TRUE);
        }

        //ROUND2
        if (a == 1) {
            DrawString(50, 50, "ROUND 2", 0xffffff, TRUE);
        }

        //ROUND3
        if (a == 2) {
            DrawString(50, 50, "ROUND 3", 0xffffff, TRUE);
        }



    }


    //           チップ表示                //

    //場に出ているチップ(スコア)
    if (Winflg == FALSE && Loseflg == FALSE && Drawflg == FALSE) {
        DrawFormatString(1100, 300, 0xffffff, "チップ: %d", Bs, TRUE);
        DrawFormatString(1000, 600, 0xffffff, "チップ(自分): %d", ps1, TRUE);
        DrawFormatString(50, 100, 0xffffff, "チップ(敵): %d", es1, TRUE);
    }



    //            リザルト画面             //
    
    //勝った時のリザルト画面
    if (Winflg == TRUE && Loseflg == FALSE && Drawflg == FALSE) {
        DrawBox(0, 0, 1000, 780, 0x000000, TRUE);
        DrawString(600, 100, "You Win", 0xffffff, TRUE);
        DrawString(500, 620, "[A]BUTTONでタイトルへ", 0xffffff, TRUE);
        DrawString(500, 650, "[B]BUTTONでリトライ", 0xffffff, TRUE);
        DrawFormatString(1000, 300, 0xffe000, "チップ(自分): %d", ps1, TRUE);
        DrawFormatString(50, 300, 0xffffff, "チップ(敵): %d", es1, TRUE);
    }

    //負けた時のリザルト画面
    if (Loseflg == TRUE && Winflg == FALSE && Drawflg == FALSE) {
        DrawBox(0, 0, 1000, 780, 0x000000, TRUE);
        DrawString(600, 100, "You Lose", 0xffffff, TRUE);
        DrawString(500, 620, "[A]BUTTONでタイトルへ", 0xffffff, TRUE);
        DrawString(500, 650, "[B]BUTTONでリトライ", 0xffffff, TRUE);
        DrawFormatString(1000, 300, 0xffffff, "チップ(自分): %d", ps1, TRUE);
        DrawFormatString(50, 300, 0xffe000, "チップ(敵): %d", es1, TRUE);
    }

    //引き分け時のリザルト画面
    if (Drawflg == TRUE&& Winflg == FALSE && Loseflg == FALSE) {
        DrawBox(0, 0, 1000, 780, 0x000000, TRUE);
        DrawString(600, 100, "DRAW", 0xffffff, TRUE);
        DrawString(500, 620, "[A]BUTTONでタイトルへ", 0xffffff, TRUE);
        DrawString(500, 650, "[B]BUTTONでリトライ", 0xffffff, TRUE);
    }


    //コール表示      
    if (P_Call_H_flg == TRUE) {
        DrawBox(520, 320, 635, 360, 0xFFFF00, TRUE);
        SetFontSize(36);
        DrawString(520, 320, "コール", 0x000000, TRUE);
    }


    //レイズ表示      
    if (P_Raise_H_flg == TRUE) {
        DrawBox(520, 320, 635, 360, 0xFFA500, TRUE);
        SetFontSize(36);
        DrawString(520, 320, "レイズ", 0x000000, TRUE);
    }

    //ROUND CHANGE表示
    if (RC_H_flg == TRUE && Drawflg == FALSE && Winflg == FALSE && Loseflg == FALSE&&G_Over_H_flg == FALSE) {
        DrawBox(460, 320, 700, 360, 0xFFDAB9, TRUE);
        SetFontSize(36);
        DrawString(470, 320, "NEXTラウンド",0x000000 , TRUE);
    }


    //FOULD表示
    if (P_Fould_H_flg == TRUE && Drawflg == FALSE && Winflg == FALSE && Loseflg == FALSE) {
        DrawBox(470, 320, 700, 360, 0x800000, TRUE);
        SetFontSize(36);
        DrawString(485, 320, "フォールド", 0x000000, TRUE);
    }


    //ゲーム終了表示
    if (G_Over_H_flg == TRUE && Drawflg == FALSE && Winflg == FALSE && Loseflg == FALSE) {
        DrawBox(470, 320, 700, 360, 0x4169e1, TRUE);
        SetFontSize(36);
        DrawString(495, 320, "ゲーム終了", 0x000000, TRUE);
    }


    //             システム表示            //
  /*  DrawFormatString(1100, 400, 0xffffff, "WTR2:%d", WTRelese2, TRUE);
    DrawFormatString(1100, 450, 0xffffff, "WTR3:%d", WTRelese3, TRUE);
    DrawFormatString(1100, 550, 0xffffff, "FPS:%d", P_FPS, TRUE);
    DrawFormatString(1100, 500, 0xffffff, "WTR:%d", WTRelese1, TRUE);
    DrawFormatString(500, 500, 0xffffff, "E_F_FLG: %d", E_Fouldflg, TRUE);
    DrawFormatString(500, 470, 0xffffff, "E_C_FLG: %d", E_CAllflg, TRUE);
    DrawFormatString(500, 440, 0xffffff, "E_R_FLG: %d", E_Raiseflg, TRUE);
    DrawFormatString(1100, 650, 0xffffff, "敵乱数: %d", P_TEKI, TRUE);
    DrawFormatString(1100, 670, 0xffffff, "B: %d", b, TRUE);*/

   /* DrawGraph(0, 0, Back, TRUE);*/
   
    /*DrawGraph(100, 300, Tranpu_Img[C_rand1], TRUE);
    DrawGraph(300, 300, Tranpu_Img[C_rand2], TRUE);
    DrawGraph(500, 300, Tranpu_Img[C_rand3], TRUE);
    DrawGraph(700, 300, Tranpu_Img[C_rand4], TRUE);
    DrawGraph(900, 300, Tranpu_Img[C_rand5], TRUE);*/
}
