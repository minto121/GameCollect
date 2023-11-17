#include "Porker.h"
#include "GameSelect.h"
#include"PadInput.h"
#include "DxLib.h"
#include "Title.h"

Porker::Porker()
{
  /*  if ((Back = LoadGraph("../GameCollect/images/TexasHoldem/BG_Dummy.png"))) {}*/
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
    WTflg[2] = FALSE;
    
    WTRelese[2] = FALSE;
   
    BTN_RELESE_FLG[5] = FALSE;
   

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
       

        C_flg[0] = FALSE;          //コールかレイズした時の判断用1
        C_flg[1] = FALSE;          //コールかレイズした時の判断用2
        C_flg[2] = FALSE;          //コールかレイズした時の判断用3
        
        E_Fouldflg = FALSE;      //敵がフォールドしたかどうかの判断用
        E_CAllflg = FALSE;       //敵がコールしたかどうかの判断用
        E_Raiseflg = FALSE;      //敵がレイズしたかどうかの判断用

        Winflg = FALSE;
        Loseflg = FALSE;
        Drawflg = FALSE;
        WTflg[0] = FALSE;
        WTflg[1] = FALSE;
        WTflg[2] = FALSE;
        WT2flg[0] = FALSE;
        WT2flg[1] = FALSE;
        WT2flg[2] = FALSE;
        WTRelese[0] = FALSE;
        WTRelese[1] = FALSE;
        WTRelese[2] = FALSE;
        BTN_RELESE_FLG[0] = FALSE;
        BTN_RELESE_FLG[1] = FALSE;
        BTN_RELESE_FLG[2] = FALSE;
        BTN_RELESE_FLG[3] = FALSE;
        BTN_RELESE_FLG[4] = FALSE;
        BTN_RELESE_FLG[5] = FALSE;
        BTN_flg = FALSE;
        RC_H_flg = FALSE;
        P_Fould_H_flg = FALSE;
        E_Fould_H_flg = FALSE;
        G_Over_H_flg = FALSE;
        CARD_URA_H_flg = TRUE;
      
        P_2PEA_FLG = FALSE;
        P_3CARD_FLG = FALSE;
        P_FH_FLG = FALSE;
        P_4CARD_FLG = FALSE;
        P_5CARD_FLG = FALSE;

        WP_FLG[0] = FALSE;
        WP_FLG[1] = FALSE;
        WP_FLG[2] = FALSE;



        P_PEA_FLG[0] = FALSE;
        P_PEA_FLG[1] = FALSE;
        P_PEA_FLG[2] = FALSE;
        P_PEA_FLG[3] = FALSE;

        YP[0] = 0;
        YP[1] = 0;
        YP[2] = 0;
        YP[3] = 0;
        YP[4] = 0;
        YP[5] = 0;
        YP[6] = 0;
        YP[7] = 0;
        YP[8] = 0;
        YP[9] = 0;
        YP[10] = 0;
        YP[11] = 0;
        YP[12] = 0;
        YP[13] = 0;
        YP[14] = 0;
        YP[15] = 0;

        YP2[0] = 0;
        YP2[1] = 0;
        YP2[2] = 0;
        YP2[3] = 0;
        YP2[4] = 0;
        YP2[5] = 0;
        YP2[6] = 0;
        YP2[7] = 0;
        YP2[8] = 0;
        YP2[9] = 0;
        YP2[10] = 0;
        YP2[11] = 0;
        YP2[12] = 0;
        YP2[13] = 0;
        YP2[14] = 0;
        YP2[15] = 0;

        YE[0] = 0;
        YE[1] = 0;
        YE[2] = 0;
        YE[3] = 0;

        CARD_SETTING();
        CARD_ANALYSIS();
        P_CARD_PEA();
        P_CARD_3_CARD();
        P_YAKU();
    }
}

//カード呼び出し
void Porker::CARD_SETTING()
{
    P_rand[0] = GetRand(55);   //プレイヤーのホールカード1
        

    P_rand[1] = GetRand(55);   //プレイヤーのホールカード2
       

        E_rand[0] = GetRand(55);   //敵のホールカード1
      

        E_rand[1] = GetRand(55);   //敵のホールカード2
      

        C_rand[0] =  GetRand(55);   //コミュニティカード1
       

        C_rand[1] = GetRand(55);   //コミュニティカード2
       

        C_rand[2] = GetRand(55);   //コミュニティカード3
      

        C_rand[3] = GetRand(55);   //コミュニティカード4
       

        C_rand[4] = GetRand(55);  //コミュニティカード5
       
        if (P_rand[0] == 0 || P_rand[0] == 14 || P_rand[0] == 28 || P_rand[0] == 42) {
            P_rand[0] = GetRand(55);
        }

        if (P_rand[1] == 0 || P_rand[1] == 14 || P_rand[1] == 28 || P_rand[1] == 42 || P_rand[1] == P_rand[0]) {
            P_rand[1] = GetRand(55);
        }

        if (E_rand[0] == 0 || E_rand[0] == 14 || E_rand[0] == 28 || E_rand[0] == 42 || E_rand[0] == P_rand[0] ||
            E_rand[0] == P_rand[1]) {
            E_rand[0] = GetRand(55);
        }

        if (E_rand[1] == 0 || E_rand[1] == 14 || E_rand[1] == 28 || E_rand[1] == 42 || E_rand[1] == P_rand[0] ||
            E_rand[1] == P_rand[1] || E_rand[1] == E_rand[0]) {
            E_rand[1] = GetRand(55);
        }

        if (C_rand[0] == 0 || C_rand[0] == 14 || C_rand[0] == 28 || C_rand[0] == 42 || C_rand[0] == P_rand[0] ||
            C_rand[0] == P_rand[1] || C_rand[0] == E_rand[0] || C_rand[0] == E_rand[1]) {
            C_rand[0] = GetRand(55);
        }

        if (C_rand[1] == 0 || C_rand[1] == 14 || C_rand[1] == 28 || C_rand[1] == 42 || C_rand[1] == P_rand[0] ||
            C_rand[1] == P_rand[1] || C_rand[1] == E_rand[0] || C_rand[1] == E_rand[1] || C_rand[1] == C_rand[0]) {
            C_rand[1] = GetRand(55);
        }

        if (C_rand[2] == 0 || C_rand[2] == 14 || C_rand[2] == 28 || C_rand[2] == 42 || C_rand[2] == P_rand[0] ||
            C_rand[2] == P_rand[1] || C_rand[2] == E_rand[0] || C_rand[2] == E_rand[1] || C_rand[2] == C_rand[0] ||
            C_rand[2] == C_rand[1]) {
            C_rand[2] = GetRand(55);
        }

        if (C_rand[3] == 0 || C_rand[3] == 14 || C_rand[3] == 28 || C_rand[3] == 42 || C_rand[3] == P_rand[0] ||
            C_rand[3] == P_rand[1] || C_rand[3] == E_rand[0] || C_rand[3] == E_rand[1] || C_rand[3] == C_rand[0] ||
            C_rand[3] == C_rand[1] || C_rand[3] == C_rand[2]) {
            C_rand[3] = GetRand(55);
        }

        if (C_rand[4] == 0 || C_rand[4] == 14 || C_rand[4] == 28 || C_rand[4] == 42 || C_rand[4] == P_rand[0] ||
            C_rand[4] == P_rand[1] || C_rand[4] == E_rand[0] || C_rand[4] == E_rand[1] || C_rand[4] == C_rand[0] ||
            C_rand[4] == C_rand[1] || C_rand[4] == C_rand[2] || C_rand[4] == C_rand[3]) {
            C_rand[4] = GetRand(55);
        }
        if (WT2flg[0] == FALSE) {
            WT2flg[0] = TRUE;
        }
    
}


//プレイヤーのコール
void Porker::PLAYER_CALL()
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


//カード分析
void Porker::CARD_ANALYSIS()
{
    if (WT2flg[0] == TRUE) {
        for (int i = 0; i < 2; i++) {
            P_CARD_A[i] = P_rand[i] % 14;
            P_CARD_S[i] = P_rand[i] / 14;
        }

        for (int j = 0; j < 2; j++) {
            E_CARD_A[j] = E_rand[j] % 14;
            E_CARD_S[j] = E_rand[j] / 14;
        }
        for (int c = 0; c < 5; c++) {
            C_CARD_A[c] = C_rand[c] % 14;
            C_CARD_S[c] = C_rand[c] / 14;
        }
    }
}


//1ペア2ペア判断用
void Porker::P_CARD_PEA()
{
    if (WP_FLG[0] == FALSE) {

       
        if (P_CARD_A[0] == P_CARD_A[1]) {
            YP2[0] = YP2[0] + 1;
        }
        for (YP[0] = 0; YP[0] <= 4; YP[0]++) {
            if (P_CARD_A[0] == C_CARD_A[YP[0]]) {
                YP2[1] = YP2[1] + 1;
            }
            if (P_CARD_A[1] == C_CARD_A[YP[0]]) {
                YP2[2] = YP2[2] + 1;
            }
        }

        for (YP[1] = 0; YP[1] <= 3; YP[1]++) {
            for(YP[2] = YP[1]+1; YP[2] <= 4; YP[2]++)
            if (C_CARD_A[YP[1]] == C_CARD_A[YP[2]]) {
                YP2[3] = YP2[3] + 1;
            }
           
        }
        
    
        if (YP[0] == 5) {
            WP_FLG[0] = TRUE;
        }
    }
}


//3カードフルハウス用
void Porker::P_CARD_3_CARD()
{
    if (WP_FLG[1] == FALSE) {


        
        for (YP[2] = 0; YP[2] <= 3; YP[2]++) {
          
            for (YP[3] = YP[2] + 1; YP[3] <= 4; YP[3]++) {

                if (C_CARD_A[YP[2]] == C_CARD_A[YP[3]]) {

                    for (YP[4] = YP[3] + 1; YP[4] <= 4; YP[4]++) {

                        if (C_CARD_A[YP[3]] == C_CARD_A[YP[4]]) {

                            YP2[4] = YP2[4] + 1;
                            break;

                        }
                    }

                }

            }

        }


        for (YP[5] = 0; YP[5] <= 1;YP[5]++) {
            for (YP[6] = 0; YP[6] <= 4; YP[6]++) {
                if (P_CARD_A[YP[5]] == C_CARD_A[YP[6]]) {
                    for (YP[7] = YP[6] + 1; YP[7] <= 4; YP[7]++) {
                        if (P_CARD_A[YP[5]] == C_CARD_A[YP[7]]||P_CARD_A[0] == P_CARD_A[1]) {

                           
                   
                            YP2[4] = YP2[4] + 1;
                            break;
                        }
                    }
                }
            }
        }
        


        if (YP[2] == 4&&YP[5] == 2) {
            WP_FLG[1] = TRUE;
        }
    }
}

void Porker::P_CARD_FLASH()
{
}


//役のフラグ
void Porker::P_YAKU()
{
    if (YP2[0] + YP2[1] + YP2[2] + YP2[3] == 1) {
        P_PEA_FLG[0] = TRUE;
    }
    if (YP2[0] + YP2[1] + YP2[2] + YP2[3] >= 2) {
        P_2PEA_FLG = TRUE;
    }
    if (YP2[4] >= 1) {
        P_3CARD_FLG = TRUE;
        P_2PEA_FLG = FALSE;
    }
    if (YP2[0] + YP2[1] + YP2[2] + YP2[3] + YP2[4] >= 5&&YP2[3]>0) {
        P_FH_FLG = TRUE;
        P_3CARD_FLG = FALSE;
        P_2PEA_FLG = FALSE;
    }
    
}

//アップデート
AbstractScene* Porker::Update()
{
    if (PAD_INPUT::OnButton(XINPUT_BUTTON_LEFT_SHOULDER) && PAD_INPUT::OnButton(XINPUT_BUTTON_RIGHT_SHOULDER)) {
        return new Title;
    }

    
    
   

    //待ち時間
    if (WTflg[0] == TRUE) {
        P_FPS++;
        if (P_FPS > 60) {
            WTRelese[0] = TRUE;
            P_FPS = 0;
            WTflg[0] = FALSE;
            P_Call_H_flg = FALSE;
            P_Raise_H_flg = FALSE;
            BTN_RELESE_FLG[4] = FALSE;
            //ラウンドチェンジ用
            if (RC_H_flg == TRUE || P_Fould_H_flg == TRUE) {

                ROUND_INIT();
            }
            if (G_Over_H_flg == TRUE) {
                G_Over_H_flg = FALSE;
            }

        }
    }
    if (WTflg[1] == TRUE) {
        P_FPS++;
        if (P_FPS > 60) {
            WTRelese[1] = TRUE;
            P_FPS = 0;
            WTflg[1] = FALSE;
            P_Call_H_flg = FALSE;
            P_Raise_H_flg = FALSE;
        }
    }
    if (WTflg[2] == TRUE) {
        P_FPS++;
        if (P_FPS > 60) {
            WTRelese[2] = TRUE;
            P_FPS = 0;
            WTflg[2] = FALSE;
            P_Call_H_flg = FALSE;
            P_Raise_H_flg = FALSE;
            CARD_URA_H_flg = FALSE;
        }
    }

    //待ち時間終了後の処理
    if (WTRelese[0] == TRUE) {
        C_flg[0] = TRUE;
        ENEMIE_CHOISE();
        WTRelese[0] = FALSE;
        BTN_flg = FALSE;
    }
    if (WTRelese[1] == TRUE) {
        C_flg[1] = TRUE;
        ENEMIE_CHOISE();
        WTRelese[1] = FALSE;
        BTN_flg = FALSE;
    }
    if (WTRelese[2] == TRUE) {
        C_flg[2] = TRUE;
        ENEMIE_CHOISE();
        WTRelese[2] = FALSE;
        BTN_flg = FALSE;
    }



    //           コール処理              //

    //コール1(今はY押す)
    if (PAD_INPUT::OnButton(XINPUT_BUTTON_Y) && C_flg[0] == FALSE && Winflg == FALSE && Loseflg == FALSE && Drawflg == FALSE && P_Call_H_flg == FALSE) {
        PLAYER_CALL();
        BTN_flg = TRUE;
        BTN_RELESE_FLG[0] = TRUE;
    }
    else if (PAD_INPUT::OnRelease(XINPUT_BUTTON_Y) && BTN_RELESE_FLG[0] == TRUE) {
        P_Call_H_flg = TRUE;
        WTflg[0] = TRUE;
        BTN_flg = FALSE;
        BTN_RELESE_FLG[0] = FALSE;
    }

    //コール2(今はY押す)
    if (PAD_INPUT::OnButton(XINPUT_BUTTON_Y) && C_flg[0] == TRUE && C_flg[1] == FALSE && BTN_flg == FALSE && Winflg == FALSE && Loseflg == FALSE && Drawflg == FALSE && P_Call_H_flg == FALSE) {
        PLAYER_CALL();
        BTN_flg = TRUE;
        BTN_RELESE_FLG[1] = TRUE;
    }
    else if (PAD_INPUT::OnRelease(XINPUT_BUTTON_Y) && BTN_RELESE_FLG[1] == TRUE) {
        P_Call_H_flg = TRUE;
        WTflg[1] = TRUE;
        BTN_flg = FALSE;
        BTN_RELESE_FLG[1] = FALSE;
    }

    //コール3(今はY押す)
    if (PAD_INPUT::OnButton(XINPUT_BUTTON_Y) && C_flg[1] == TRUE && C_flg[2] == FALSE && BTN_flg == FALSE && Winflg == FALSE && Loseflg == FALSE && Drawflg == FALSE && P_Call_H_flg == FALSE) {
        PLAYER_CALL();
        BTN_flg = TRUE;
        BTN_RELESE_FLG[2] = TRUE;
    }
    else if (PAD_INPUT::OnRelease(XINPUT_BUTTON_Y) && BTN_RELESE_FLG[2] == TRUE && P_Call_H_flg == FALSE) {
        P_Call_H_flg = TRUE;
        WTflg[2] = TRUE;
        BTN_flg = FALSE;
        BTN_RELESE_FLG[2] = FALSE;

    }




    //               レイズ               //

    //レイズ1(今はB押す)
    if (PAD_INPUT::OnButton(XINPUT_BUTTON_B) && C_flg[0] == FALSE && Winflg == FALSE && Loseflg == FALSE && Drawflg == FALSE) {
        PLAYER_RAISE();
        BTN_flg = TRUE;
        BTN_RELESE_FLG[0] = TRUE;
    }
    else if (PAD_INPUT::OnRelease(XINPUT_BUTTON_B) && BTN_RELESE_FLG[0] == TRUE) {
        WTflg[0] = TRUE;
        BTN_flg = FALSE;
        BTN_RELESE_FLG[0] = FALSE;
    }

    //レイズ2(今はB押す)
    if (PAD_INPUT::OnButton(XINPUT_BUTTON_B) && C_flg[0] == TRUE && C_flg[1] == FALSE && BTN_flg == FALSE && Winflg == FALSE && Loseflg == FALSE && Drawflg == FALSE) {
        PLAYER_RAISE();
        BTN_flg = TRUE;
        BTN_RELESE_FLG[1] = TRUE;
    }
    else if (PAD_INPUT::OnRelease(XINPUT_BUTTON_B) && BTN_RELESE_FLG[1] == TRUE) {
        WTflg[1] = TRUE;
        BTN_flg = FALSE;
        BTN_RELESE_FLG[1] = FALSE;
    }

    //レイズ3(今はB押す)
    if (PAD_INPUT::OnButton(XINPUT_BUTTON_B) && C_flg[1] == TRUE && C_flg[2] == FALSE && BTN_flg == FALSE && Winflg == FALSE && Loseflg == FALSE && Drawflg == FALSE) {
        PLAYER_RAISE();
        BTN_flg = TRUE;
        BTN_RELESE_FLG[2] = TRUE;
    }
    else if (PAD_INPUT::OnRelease(XINPUT_BUTTON_B) && BTN_RELESE_FLG[2] == TRUE) {
        WTflg[2] = TRUE;
        BTN_flg = FALSE;
        BTN_RELESE_FLG[2] = FALSE;
    }







    //         ラウンドを変える(3回目でタイトル)          //

    //ラウンドチェンジ
    if (PAD_INPUT::OnButton(XINPUT_BUTTON_X) && C_flg[2] == TRUE && a <= 3&& Winflg == FALSE && Loseflg == FALSE && Drawflg == FALSE) {
        BTN_RELESE_FLG[3] = TRUE;
    }
    else if (PAD_INPUT::OnRelease(XINPUT_BUTTON_X) && C_flg[2] == TRUE && a <= 3 && BTN_RELESE_FLG[3] == TRUE&&Winflg == FALSE && Loseflg == FALSE && Drawflg == FALSE) {
        a++;
        RC_H_flg = TRUE;
        WTflg[0] = TRUE;
        BTN_RELESE_FLG[3] = FALSE;
    }


    //フォールド用
    if (PAD_INPUT::OnRelease(XINPUT_BUTTON_X) && C_flg[2] == FALSE && a <= 3 && BTN_RELESE_FLG[4] == FALSE && Winflg == FALSE && Loseflg == FALSE && Drawflg == FALSE) {
        BTN_RELESE_FLG[4] = TRUE;
        a++;
        P_Fould_H_flg = TRUE;
        WTflg[0] = TRUE;

    }

    //フォールド後スコア
    if (P_Fould_H_flg == TRUE) {
        es1 = Bs + es1;
        Bs = 0;
    }

    //ゲーム終了用
    if (PAD_INPUT::OnRelease(XINPUT_BUTTON_X) && a >= 3)
    {
        P_Fould_H_flg = FALSE;
        G_Over_H_flg = TRUE;
        WTflg[0] = TRUE;
    }


    //リザルト画面表示用フラグ
    if (a >= 3 && G_Over_H_flg == FALSE) {

        if (ps1 > es1 && P_Fould_H_flg == FALSE) {
            Winflg = TRUE;
        }
        else if (ps1 < es1 && P_Fould_H_flg == FALSE) {
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

//描画
void Porker::Draw() const
{

    //                   カードの表示               //
    if (Drawflg == FALSE && Winflg == FALSE && Loseflg == FALSE) {
        DrawFormatString(400, 600, 0xffffff, "prand1: %d", P_rand[0], TRUE); //プレイヤーのホールカード1
        DrawFormatString(600, 600, 0xffffff, "prand2: %d", P_rand[1], TRUE); //プレイヤーのホールカード2
        DrawGraph(400, 500, Tranpu_Img[P_rand[0]], TRUE);
        DrawGraph(600, 500, Tranpu_Img[P_rand[1]], TRUE);

        //DrawFormatString(400, 50, 0xffffff, "erand1: %d", E_rand[1], TRUE); //敵のホールカード1
        //DrawFormatString(600, 50, 0xffffff, "erand2: %d", E_rand[2], TRUE); //敵のホールカード2
        //敵カード裏
        if (CARD_URA_H_flg == FALSE) {
            DrawGraph(400, 0, Tranpu_Img[E_rand[0]], TRUE);
            DrawGraph(600, 0, Tranpu_Img[E_rand[1]], TRUE);
        }
        //敵カード表
        if (CARD_URA_H_flg == TRUE) {
            DrawGraph(400, 0, Tranpu_Img[0], TRUE);
            DrawGraph(600, 0, Tranpu_Img[0], TRUE);
        }



        //1回目コールした時コミュニティカードを三枚出す
        if (C_flg[0] == TRUE) {
            //DrawFormatString(100, 300, 0xffffff, "crand1: %d", C_rand1, TRUE); //コミュニティカード1
            //DrawFormatString(300, 300, 0xffffff, "crand2: %d", C_rand2, TRUE); //コミュニティカード2
            //DrawFormatString(500, 300, 0xffffff, "crand3: %d", C_rand3, TRUE); //コミュニティカード3
            DrawGraph(100, 250, Tranpu_Img[C_rand[0]], TRUE);
            DrawGraph(300, 250, Tranpu_Img[C_rand[1]], TRUE);
            DrawGraph(500, 250, Tranpu_Img[C_rand[2]], TRUE);
        }

        //2回目コールした時コミュニティカードを1枚出す
        if (C_flg[1] == TRUE) {
            //DrawFormatString(700, 300, 0xffffff, "crand4: %d", C_rand4, TRUE); //コミュニティカード4
            DrawGraph(700, 250, Tranpu_Img[C_rand[3]], TRUE);

        }

        //3回目コールした時コミュニティカードを1枚出す
        if (C_flg[2] == TRUE) {
            //DrawFormatString(900, 300, 0xffffff, "crand5: %d", C_rand5, TRUE); //コミュニティカード4
            DrawGraph(900, 250, Tranpu_Img[C_rand[4]], TRUE);
        }



        //               キー表示              //

        if (C_flg[2] == FALSE) {
            DrawString(100, 600, "[Y]BUTTONでコール", 0xffffff, TRUE);
        }

        if (C_flg[2] == FALSE) {
            DrawString(100, 640, "[B]BUTTONでレイズ", 0xffffff, TRUE);
        }

        if (C_flg[2] == FALSE) {
            DrawString(100, 680, "[X]BUTTONでフォールド", 0xffffff, TRUE);
        }

        if (C_flg[2] == TRUE) {
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


    DrawFormatString(1100, 10, 0xffffff, "E2A: %d", E_CARD_A[1], TRUE);
    DrawFormatString(1100, 30, 0xffffff, "E1A: %d", E_CARD_A[0], TRUE);
    DrawFormatString(1100, 50, 0xffffff, "E2S: %d", E_CARD_S[1], TRUE);
    DrawFormatString(1100, 70, 0xffffff, "E1S: %d", E_CARD_S[0], TRUE);
    DrawFormatString(1100, 350, 0xffffff, "P_PEA: %d", P_PEA_FLG[0], TRUE);
    DrawFormatString(1100, 370, 0xffffff, "P_PEA2: %d", P_PEA_FLG[1], TRUE);
    DrawFormatString(1100, 390, 0xffffff, "C_PEA: %d", P_PEA_FLG[2], TRUE);
    DrawFormatString(1100, 410, 0xffffff, "2PEA: %d", P_2PEA_FLG, TRUE);
    DrawFormatString(1100, 430, 0xffffff, "3CARD: %d", P_3CARD_FLG, TRUE);
    DrawFormatString(1100, 450, 0xffffff, "FULL_H: %d", P_FH_FLG, TRUE);
    DrawFormatString(1100, 470, 0xffffff, "4CARD: %d", P_4CARD_FLG, TRUE);
    DrawFormatString(100, 450, 0xffffff, "YP[0]: %d", YP[0], TRUE);
    DrawFormatString(100, 470, 0xffffff, "YP[2]: %d", YP[2], TRUE);
    DrawFormatString(0, 340, 0xffffff, "YP2[0]: %d", YP2[0], TRUE);
    DrawFormatString(0, 360, 0xffffff, "YP2[1]: %d", YP2[1], TRUE);
    DrawFormatString(0, 380, 0xffffff, "YP2[2]: %d", YP2[2], TRUE);
    DrawFormatString(0, 400, 0xffffff, "YP2[3]: %d", YP2[3], TRUE);
    DrawFormatString(0, 420, 0xffffff, "YP2[4]: %d", YP2[4], TRUE);

    DrawFormatString(1100, 540, 0xffffff, "P1A: %d", P_CARD_A[0], TRUE);
    DrawFormatString(1100, 560, 0xffffff, "P2A: %d", P_CARD_A[1], TRUE);
    DrawFormatString(100, 520, 0xffffff, "C1A: %d", C_CARD_A[0], TRUE);
    DrawFormatString(300, 520, 0xffffff, "C2A: %d", C_CARD_A[1], TRUE);
    DrawFormatString(500, 520, 0xffffff, "C3A: %d", C_CARD_A[2], TRUE);
    DrawFormatString(700, 520, 0xffffff, "C4A: %d", C_CARD_A[3], TRUE);
    DrawFormatString(900, 520, 0xffffff, "C5A: %d", C_CARD_A[4], TRUE);
    

   /* DrawGraph(0, 0, Back, TRUE);*/
   
    
}
