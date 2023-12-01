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
        WTflg[3] = FALSE;
        WT2flg[0] = FALSE;
        WT2flg[1] = FALSE;
        WT2flg[2] = FALSE;
        WTRelese[0] = FALSE;
        WTRelese[1] = FALSE;
        WTRelese[2] = FALSE;
        for (int x = 0; x <= 5; x++){
            BTN_RELESE_FLG[x] = FALSE;
        }
     
        BTN_flg = FALSE;
        RC_H_flg = FALSE;
        P_Fould_H_flg = FALSE;
        E_Fould_H_flg = FALSE;
        G_Over_H_flg = FALSE;
        CARD_URA_H_flg = TRUE;


        P_PEA_FLG = FALSE;
        P_2PEA_FLG = FALSE;
        P_3CARD_FLG = FALSE;
        P_FH_FLG = FALSE;
        P_FLASH_FLG = FALSE;
        P_STRAIGHT_FLG = FALSE;
        P_4CARD_FLG = FALSE;
        P_SF_FLG = FALSE;
        P_RSF_FLG = FALSE;


        E_PEA_FLG = FALSE;
        E_2PEA_FLG = FALSE;
        E_3CARD_FLG = FALSE;
        E_FH_FLG = FALSE;
        E_FLASH_FLG = FALSE;
        E_STRAIGHT_FLG = FALSE;
        E_4CARD_FLG = FALSE;
        E_SF_FLG = FALSE;
        E_RSF_FLG = FALSE;

        for (int x = 0; x <= 19; x++) {
            WP_FLG[x] = FALSE;
        }
      
       
        for (int x = 0; x <= 30; x++) {
            YP[x] = 0;
        }
       
        
        for (int x = 0; x <= 30; x++) {
            YP2[x] = 0;
        }
     
        for (int x = 0; x <= 1; x++) {
            WINandLOSE[x] = 0;
        }
        
        for (int x = 0; x <= 15; x++) {
            P_SORT[x] = 0;
        }
        
        for (int x = 0; x <= 15; x++) {
            E_SORT[x] = 0;
        }
       
        for (int x = 0; x <= 1; x++) {
            R_Win_FLG[x] = FALSE;
        }
       
     
      
       
    }
}


//カード呼び出し
void Porker::CARD_SETTING()
{
    if (WP_FLG[11] == FALSE) {
        P_rand[0] = 0 /*GetRand(55)*/;   //プレイヤーのホールカード1

        P_rand[1] = 0/*GetRand(55)*/;   //プレイヤーのホールカード2

        E_rand[0] = 0/*GetRand(55)*/;   //敵のホールカード1

        E_rand[1] = 0/* GetRand(55)*/;   //敵のホールカード2

        C_rand[0] = 0/*GetRand(55)*/;   //コミュニティカード1

        C_rand[1] = 0/*GetRand(55)*/;   //コミュニティカード2

        C_rand[2] = 0/*GetRand(55)*/;   //コミュニティカード3

        C_rand[3] = 0/*GetRand(55)*/;   //コミュニティカード4

        C_rand[4] = 0/*GetRand(55)*/;  //コミュニティカード5   
        WP_FLG[11] = TRUE;

       
      

    }
}


//カード調整
void Porker::CARD_SETTING2()
{

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



//1ペア2ペア判断用
void Porker::P_CARD_PEA()
{
    if (WP_FLG[5] == FALSE) {

       
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


//フラッシュ用
void Porker::P_CARD_FLASH()
{
    if (WP_FLG[2] == FALSE) {

            for (YP[8] = 0; YP[8] <= 4; YP[8]++) {

                if (P_CARD_S[0] == C_CARD_S[YP[8]]) {

                    YP2[5] = YP2[5] + 1;

                }

                if (P_CARD_S[1] == C_CARD_S[YP[8]]) {

                    YP2[6] = YP2[6] + 1;

                }
            }

            if (P_CARD_S[0] == P_CARD_S[1]) {

                YP2[5] = YP2[5] + 1;

                YP2[6] = YP2[6] + 1;
            }
        
            if (C_CARD_S[0] == C_CARD_S[1] && C_CARD_S[0] == C_CARD_S[2] && C_CARD_S[0] == C_CARD_S[3] && C_CARD_S[0] == C_CARD_S[4]) {
                YP2[5] = YP2[5] + 4;
            }

        if (YP[8] == 5) {
            WP_FLG[2] = TRUE;
        }
    }
}


//ストレート用
void Porker::P_CARD_STRAIGHT()
{
    if (WP_FLG[4] == FALSE) {     


        //ソート用
        P_SORT[0] = C_CARD_A[0];
        P_SORT[1] = C_CARD_A[1];
        P_SORT[2] = C_CARD_A[2];
        P_SORT[3] = C_CARD_A[3];
        P_SORT[4] = C_CARD_A[4];
        P_SORT[5] = P_CARD_A[0];
        P_SORT[6] = P_CARD_A[1];

        for (int x = 0; x <= 6; x++) {
            P_SORT[14] = P_SORT[14] + P_SORT[x];
        }
        int sort;
        for (int a = 0; a <= 5; a++) {
            for (int b = a + 1; b <= 6; b++) {
                if (P_SORT[a] > P_SORT[b]) {
                    sort = P_SORT[a];
                    P_SORT[a] = P_SORT[b];
                    P_SORT[b] = sort;
                }
            }
        }
       

        //ストレート
        if (P_SORT[0] == P_SORT[1] - 1 && P_SORT[0] == P_SORT[2] - 2 && P_SORT[0] == P_SORT[3] - 3 && P_SORT[0] == P_SORT[4] - 4) {
            YP2[12] = YP2[12] + 1;

        }

        else  if (P_SORT[1] == P_SORT[2] - 1 && P_SORT[1] == P_SORT[3] - 2 && P_SORT[1] == P_SORT[4] - 3 && P_SORT[1] == P_SORT[5] - 4) {
            YP2[12] = YP2[12] + 1;
        }

        else  if (P_SORT[2] == P_SORT[3] - 1 && P_SORT[2] == P_SORT[4] - 2 && P_SORT[2] == P_SORT[5] - 3 && P_SORT[2] == P_SORT[6] - 4) {
            YP2[12] = YP2[12] + 1;
        }


        if (YP2[12] == 1) {
            WP_FLG[4] = TRUE;
        }

    }
}


//4カード用
void Porker::P_CARD_4_CARD() 
{
    if (WP_FLG[3] == FALSE) {

        for (YP[9] = 0; YP[9] <= 4; YP[9]++) {

            if (P_CARD_A[0] == C_CARD_A[YP[9]]) {

                YP2[7] = YP2[7] + 1;

            }

            if (P_CARD_A[1] == C_CARD_A[YP[9]]) {

                YP2[8] = YP2[8] + 1;

            }
        }

        if (P_CARD_A[0] == P_CARD_A[1]) {

            YP2[7] = YP2[7] + 1;

            YP2[8] = YP2[8] + 1;
        }

        for (YP[10] = 0; YP[10] <= 3; YP[10]++) {
            for (YP[11] = YP[10] + 1; YP[11] <= 4; YP[11]++) {
                if (C_CARD_A[YP[10]] == C_CARD_A[YP[11]]) {
                    YP2[9] = YP2[9] + 1;
                }
            }
        }

        if (YP[9] == 5&&YP[10]==4) {
            WP_FLG[3] = TRUE;
        }
    }
}


//ストレートフラッシュ用
void Porker::P_CARD_STRAIGHTFALSH()
{
    if (WP_FLG[15] == FALSE) {


        //ソート用
        P_SORT[7] = C_CARD_A[0] + C_CARD_S[0];
        P_SORT[8] = C_CARD_A[1] + C_CARD_A[1];
        P_SORT[9] = C_CARD_A[2] + C_CARD_A[2];
        P_SORT[10] = C_CARD_A[3] + C_CARD_A[3];
        P_SORT[11] = C_CARD_A[4] + C_CARD_A[4];
        P_SORT[12] = P_CARD_A[0] + P_CARD_A[0];
        P_SORT[13] = P_CARD_A[1] + P_CARD_A[1];
        int sort;
        for (int a = 7; a <= 12; a++) {
            for (int b = a + 1; b <= 13; b++) {
                if (P_SORT[a] > P_SORT[b]) {
                    sort = P_SORT[a];
                    P_SORT[a] = P_SORT[b];
                    P_SORT[b] = sort;
                }
            }
        }


        //ストレート
        if (P_SORT[7] == P_SORT[8] - 1 && P_SORT[7] == P_SORT[9] - 2 && P_SORT[7] == P_SORT[10] - 3 && P_SORT[7] == P_SORT[11] - 4) {
            YP2[24] = YP2[24] + 1;

        }

        else  if (P_SORT[8] == P_SORT[9] - 1 && P_SORT[8] == P_SORT[10] - 2 && P_SORT[8] == P_SORT[11] - 3 && P_SORT[8] == P_SORT[12] - 4) {
            YP2[24] = YP2[24] + 1;
        }

        else  if (P_SORT[9] == P_SORT[10] - 1 && P_SORT[9] == P_SORT[11] - 2 && P_SORT[9] == P_SORT[12] - 3 && P_SORT[9] == P_SORT[13] - 4) {
            YP2[24] = YP2[24] + 1;
        }


        WP_FLG[15] == TRUE;

    }
}


//役のフラグ(プレイヤー)
void Porker::P_YAKU()
{
    //PEA
    if (YP2[0] + YP2[1] + YP2[2] + YP2[3] == 1) {
        P_PEA_FLG = TRUE;
    }
    //2PEA
    if (YP2[0] + YP2[1] + YP2[2] + YP2[3] >= 2) {
        P_2PEA_FLG = TRUE;
    }
    //3CARD
    if (YP2[4] >= 1) {
        P_3CARD_FLG = TRUE;
        P_2PEA_FLG = FALSE;
    }
    //STRAIGHT
    if (YP2[12] == 1) {
        P_STRAIGHT_FLG = TRUE;
        P_3CARD_FLG = FALSE;
        P_2PEA_FLG = FALSE;
    }
    //FLASH
    if (YP2[5] >= 4 || YP2[6] >= 4) {
        P_FLASH_FLG = TRUE;
        P_3CARD_FLG = FALSE;
        P_2PEA_FLG = FALSE;
    }
    //FULLHOUSE
    if (YP2[0] + YP2[1] + YP2[2] + YP2[3] + YP2[4] >= 5&&YP2[3]>0) {
        P_FH_FLG = TRUE;
        P_FLASH_FLG = FALSE;
        P_3CARD_FLG = FALSE;
        P_2PEA_FLG = FALSE;
    }
    //4CARD
    if (YP2[7] >= 3|| YP2[8] >= 3 || YP2[9] >= 6) {
        P_4CARD_FLG = TRUE;
        P_FH_FLG = FALSE;
        P_FLASH_FLG = FALSE;
        P_3CARD_FLG = FALSE;
        P_2PEA_FLG = FALSE;
    }
    //STRAIGHT&FLASH
    if (YP2[24] == 1) {
        P_SF_FLG = TRUE;
        P_4CARD_FLG = FALSE;
        P_FH_FLG = FALSE;
        P_FLASH_FLG = FALSE;
        P_3CARD_FLG = FALSE;
        P_2PEA_FLG = FALSE;
    }
    //ROYAL&STRAIGHT&FLASH
    if (P_SORT[6] == 14 && P_SORT[5] == 13 && P_SORT[4] == 12 && P_SORT[3] == 11 && P_SORT[2] == 10 && P_SF_FLG == TRUE) {
        P_RSF_FLG = TRUE;
        P_SF_FLG = FALSE;
        P_4CARD_FLG = FALSE;
        P_FH_FLG = FALSE;
        P_FLASH_FLG = FALSE;
        P_3CARD_FLG = FALSE;
        P_2PEA_FLG = FALSE;
    }
}




//1ペア2ペア判断用(敵）
void Porker::E_CARD_PEA()
{
    if (WP_FLG[5] == FALSE) {


        if (E_CARD_A[0] == E_CARD_A[1]) {
            YP2[13] = YP2[13] + 1;
        }
        for (YP[11] = 0; YP[11] <= 4; YP[11]++) {
            if (E_CARD_A[0] == C_CARD_A[YP[11]]) {
                YP2[14] = YP2[14] + 1;
            }
            if (E_CARD_A[1] == C_CARD_A[YP[11]]) {
                YP2[15] = YP2[15] + 1;
            }
        }

        for (YP[12] = 0; YP[12] <= 3; YP[12]++) {
            for (YP[13] = YP[12] + 1; YP[13] <= 4; YP[13]++)
                if (C_CARD_A[YP[12]] == C_CARD_A[YP[13]]) {
                    YP2[16] = YP2[16] + 1;
                }

        }


        if (YP[11] == 5) {
            WP_FLG[5] = TRUE;
        }
    }
}


//3カードフルハウス用(敵）
void Porker::E_CARD_3_CARD()
{
    if (WP_FLG[6] == FALSE) {



        for (YP[14] = 0; YP[14] <= 3; YP[14]++) {

            for (YP[15] = YP[14] + 1; YP[15] <= 4; YP[15]++) {

                if (C_CARD_A[YP[14]] == C_CARD_A[YP[15]]) {

                    for (YP[16] = YP[15] + 1; YP[16] <= 4; YP[16]++) {

                        if (C_CARD_A[YP[15]] == C_CARD_A[YP[16]]) {

                            YP2[17] = YP2[17] + 1;
                            break;

                        }
                    }

                }

            }

        }


        for (YP[17] = 0; YP[17] <= 1; YP[17]++) {
            for (YP[18] = 0; YP[18] <= 4; YP[18]++) {
                if (E_CARD_A[YP[17]] == C_CARD_A[YP[18]]) {
                    for (YP[19] = YP[18] + 1; YP[19] <= 4; YP[19]++) {
                        if (E_CARD_A[YP[17]] == C_CARD_A[YP[17]] || E_CARD_A[0] == E_CARD_A[1]) {



                            YP2[17] = YP2[17] + 1;
                            break;
                        }
                    }
                }
            }
        }



        if (YP[14] == 4 && YP[17] == 2) {
            WP_FLG[6] = TRUE;
        }
    }
}


//フラッシュ用(敵）
void Porker::E_CARD_FLASH()
{
    if (WP_FLG[7] == FALSE) {

        for (YP[20] = 0; YP[20] <= 4; YP[20]++) {

            if (E_CARD_S[0] == C_CARD_S[YP[20]]) {

                YP2[19] = YP2[19] + 1;

            }

            if (E_CARD_S[1] == C_CARD_S[YP[20]]) {

                YP2[20] = YP2[20] + 1;

            }
        }

        if (E_CARD_S[0] == E_CARD_S[1]) {

            YP2[19] = YP2[19] + 1;

            YP2[20] = YP2[20] + 1;
        }

        if (C_CARD_S[0] == C_CARD_S[1] && C_CARD_S[0] == C_CARD_S[2] && C_CARD_S[0] == C_CARD_S[3] && C_CARD_S[0] == C_CARD_S[4]) {
            YP2[19] = YP2[19] + 4;
        }

        if (YP[20] == 5) {
            WP_FLG[7] = TRUE;
        }
    }
}


//ストレート用(敵）
void Porker::E_CARD_STRAIGHT()
{
    if (WP_FLG[8] == FALSE) {


        //ソート用
        E_SORT[0] = C_CARD_A[0];
        E_SORT[1] = C_CARD_A[1];
        E_SORT[2] = C_CARD_A[2];
        E_SORT[3] = C_CARD_A[3];
        E_SORT[4] = C_CARD_A[4];
        E_SORT[5] = E_CARD_A[0];
        E_SORT[6] = E_CARD_A[1];

        for (int x = 0; x <= 6; x++) {
            E_SORT[14] = E_SORT[14] + E_SORT[x];
        }

        int sort;
        for (int a = 0; a <= 5; a++) {
            for (int b = a + 1; b <= 6; b++) {
                if (E_SORT[a] > E_SORT[b]) {
                    sort = E_SORT[a];
                    E_SORT[a] = E_SORT[b];
                    E_SORT[b] = sort;
                }
            }
        }


        //ストレート
        if (E_SORT[0] == E_SORT[1] - 1 && E_SORT[0] == E_SORT[2] - 2 && E_SORT[0] == E_SORT[3] - 3 && E_SORT[0] == E_SORT[4] - 4) {
            YP2[21] = YP2[21] + 1;
        }

        else  if (E_SORT[1] == E_SORT[2] - 1 && E_SORT[1] == E_SORT[3] - 2 && E_SORT[1] == E_SORT[4] - 3 && E_SORT[1] == E_SORT[5] - 4) {
            YP2[21] = YP2[21] + 1;
        }

        else  if (E_SORT[2] == E_SORT[3] - 1 && E_SORT[2] == E_SORT[4] - 2 && E_SORT[2] == E_SORT[5] - 3 && E_SORT[2] == E_SORT[6] - 4) {
            YP2[21] = YP2[21] + 1;
        }


        if (YP2[21] == 1) {
            WP_FLG[8] = TRUE;
        }

    }
}



//4カード用(敵）
void Porker::E_CARD_4_CARD()
{
    if (WP_FLG[9] == FALSE) {

        for (YP[22] = 0; YP[22] <= 4; YP[22]++) {

            if (E_CARD_A[0] == C_CARD_A[YP[22]]) {

                YP2[22] = YP2[22] + 1;

            }

            if (E_CARD_A[1] == C_CARD_A[YP[22]]) {

                YP2[23] = YP2[23] + 1;

            }
        }

        if (E_CARD_A[0] == E_CARD_A[1]) {

            YP2[22] = YP2[22] + 1;

            YP2[23] = YP2[23] + 1;
        }

        for (YP[23] = 0; YP[23] <= 3; YP[23]++) {
            for (YP[24] = YP[23] + 1; YP[24] <= 4; YP[24]++) {
                if (C_CARD_A[YP[23]] == C_CARD_A[YP[24]]) {
                    YP2[24] = YP2[24] + 1;
                }
            }
        }

        if (YP[22] == 5 && YP[23] == 4) {
            WP_FLG[9] = TRUE;
        }
    }
}


//ストレートフラッシュ用(敵）
void Porker::E_CARD_STRAIGHTFALSH()
{
    if (WP_FLG[16] == FALSE) {


        //ソート用
        E_SORT[7] = C_CARD_A[0] + C_CARD_S[0];
        E_SORT[8] = C_CARD_A[1] + C_CARD_A[1];
        E_SORT[9] = C_CARD_A[2] + C_CARD_A[2];
        E_SORT[10] = C_CARD_A[3] + C_CARD_A[3];
        E_SORT[11] = C_CARD_A[4] + C_CARD_A[4];
        E_SORT[12] = E_CARD_A[0] + E_CARD_A[0];
        E_SORT[13] = E_CARD_A[1] + E_CARD_A[1];
        int sort;
        for (int a = 7; a <= 12; a++) {
            for (int b = a + 1; b <= 13; b++) {
                if (E_SORT[a] > E_SORT[b]) {
                    sort = E_SORT[a];
                    E_SORT[a] = E_SORT[b];
                    E_SORT[b] = sort;
                }
            }
        }


        //ストレート
        if (E_SORT[7] == E_SORT[8] - 1 && E_SORT[7] == E_SORT[9] - 2 && E_SORT[7] == E_SORT[10] - 3 && E_SORT[7] == E_SORT[11] - 4) {
            YP2[25] = YP2[25] + 1;

        }

        else  if (E_SORT[8] == E_SORT[9] - 1 && E_SORT[9] == E_SORT[10] - 2 && E_SORT[8] == E_SORT[11] - 3 && E_SORT[8] == E_SORT[12] - 4) {
            YP2[25] = YP2[25] + 1;
        }

        else  if (E_SORT[9] == E_SORT[10] - 1 && E_SORT[9] == E_SORT[11] - 2 && E_SORT[9] == E_SORT[12] - 3 && E_SORT[9] == E_SORT[13] - 4) {
            YP2[25] = YP2[25] + 1;
        }


        WP_FLG[16] == TRUE;

    }
}


//役のフラグ(敵）
void Porker::E_YAKU()
{
    //PEA
    if (YP2[13] + YP2[14] + YP2[15] + YP2[16] == 1) {
        E_PEA_FLG = TRUE;
    }
    //2PEA
    if (YP2[13] + YP2[14] + YP2[15] + YP2[16] >= 2) {
        E_2PEA_FLG = TRUE;
    }
    //3CARD
    if (YP2[17] >= 1) {
        E_3CARD_FLG = TRUE;
        E_2PEA_FLG = FALSE;
    }
    //STRAIGHT
    if (YP2[21] == 1) {
        E_STRAIGHT_FLG = TRUE;
        E_3CARD_FLG = FALSE;
        E_2PEA_FLG = FALSE;
        E_PEA_FLG = FALSE;
    }
    //FLASH
    if (YP2[19] >= 4 || YP2[20] >= 4) {
        E_FLASH_FLG = TRUE;
        E_3CARD_FLG = FALSE;
        E_2PEA_FLG = FALSE;
    }
    //FULLHOUSE
    if (YP2[13] + YP2[14] + YP2[15] + YP2[16] + YP2[17] >= 5 && YP2[16] > 0) {
        E_FH_FLG = TRUE;
        E_FLASH_FLG = FALSE;
        E_3CARD_FLG = FALSE;
        E_2PEA_FLG = FALSE;
    }
    //4CARD
    if (YP2[22] >= 3 || YP2[23] >= 3 || YP2[23] >= 6) {
        E_4CARD_FLG = TRUE;
        E_FH_FLG = FALSE;
        E_FLASH_FLG = FALSE;
        E_3CARD_FLG = FALSE;
        E_2PEA_FLG = FALSE;
    }
    //STRAIGHT&FLASH
    if (YP2[25] == 1) {
        E_SF_FLG = TRUE;
        E_4CARD_FLG = FALSE;
        E_FH_FLG = FALSE;
        E_FLASH_FLG = FALSE;
        E_3CARD_FLG = FALSE;
        E_2PEA_FLG = FALSE;
    }
    //ROYAL&STRAIGHT&FLASH
    if (E_SORT[6] == 14 && E_SORT[5] == 13 && E_SORT[4] == 12 && E_SORT[3] == 11 && E_SORT[2] == 10&& E_SF_FLG == TRUE) {
        E_RSF_FLG = TRUE;
        E_SF_FLG = FALSE;
        E_4CARD_FLG = FALSE;
        E_FH_FLG = FALSE;
        E_FLASH_FLG = FALSE;
        E_3CARD_FLG = FALSE;
        E_2PEA_FLG = FALSE;
    }
}


//勝ち負け
void Porker::WINANDLOSE()
{
    if (P_PEA_FLG == TRUE) 
    {
        WINandLOSE[0] = 1;
    }
    if (E_PEA_FLG == TRUE)
    {
        WINandLOSE[1] = 1;
    }

    if (P_2PEA_FLG == TRUE)
    {
        WINandLOSE[0] = 2;
    }
    if (E_2PEA_FLG == TRUE)
    {
        WINandLOSE[1] = 2;
    }

    if (P_3CARD_FLG == TRUE)
    {
        WINandLOSE[0] = 3;
    }
    if (E_3CARD_FLG == TRUE)
    {
        WINandLOSE[1] = 3;
    }

    if (P_STRAIGHT_FLG == TRUE)
    {
        WINandLOSE[0] = 4;
    }
    if (E_STRAIGHT_FLG == TRUE)
    {
        WINandLOSE[1] = 4;
    }

    if (P_FLASH_FLG == TRUE)
    {
        WINandLOSE[0] = 5;
    }
    if (E_FLASH_FLG == TRUE)
    {
        WINandLOSE[1] = 5;
    }

    if (P_FH_FLG == TRUE)
    {
        WINandLOSE[0] = 6;
    }
    if (E_FH_FLG == TRUE)
    {
        WINandLOSE[1] = 6;
    }

    if (P_4CARD_FLG == TRUE)
    {
        WINandLOSE[0] = 7;
    }
    if (E_4CARD_FLG == TRUE)
    {
        WINandLOSE[1] = 7;
    }

    if (P_SF_FLG == TRUE)
    {
        WINandLOSE[0] = 8;
    }
    if (E_SF_FLG == TRUE)
    {
        WINandLOSE[1] = 8;
    }

    if (P_RSF_FLG == TRUE)
    {
        WINandLOSE[0] = 9;
    }
    if (E_RSF_FLG == TRUE)
    {
        WINandLOSE[1] = 9;
    }

    if (WINandLOSE[0] > WINandLOSE[1]) 
    {
        R_Win_FLG[0] = TRUE;
    }
    else if(WINandLOSE[0] < WINandLOSE[1])
    {
        R_Win_FLG[1] = TRUE;
    }
    else if (WINandLOSE[0] == WINandLOSE[1])
    {
        if (P_SORT[14] > E_SORT[14])
        {
            R_Win_FLG[0] = TRUE;
        }
        if (P_SORT[14] < E_SORT[14])
        {
            R_Win_FLG[1] = TRUE;
        }
    }
    if (R_Win_FLG[0] == TRUE) {
        ps1 = Bs + ps1;
        Bs = 0;
    }
    else if (R_Win_FLG[1] == TRUE) {
        es1 = Bs + es1;
        Bs = 0;
    }
}



//アップデート
AbstractScene* Porker::Update()
{
    if (PAD_INPUT::OnButton(XINPUT_BUTTON_LEFT_SHOULDER) && PAD_INPUT::OnButton(XINPUT_BUTTON_RIGHT_SHOULDER)) {
        return new Title;
    } 
    CARD_SETTING();
    CARD_SETTING2();
    CARD_ANALYSIS();
    P_CARD_PEA();
    P_CARD_3_CARD();
    P_CARD_FLASH();
    P_CARD_STRAIGHT();
    P_CARD_4_CARD();
    P_YAKU();
    E_CARD_PEA();
    E_CARD_3_CARD();
    E_CARD_FLASH();
    E_CARD_STRAIGHT();
    E_CARD_4_CARD();
    E_YAKU();
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
            WINANDLOSE();
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
          
            DrawGraph(100, 250, Tranpu_Img[C_rand[0]], TRUE);
            DrawGraph(300, 250, Tranpu_Img[C_rand[1]], TRUE);
            DrawGraph(500, 250, Tranpu_Img[C_rand[2]], TRUE);
        }

        //2回目コールした時コミュニティカードを1枚出す
        if (C_flg[1] == TRUE) {
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

    //ROUND WIN
    if (R_Win_FLG[0] == TRUE) {
        DrawBox(470, 300, 700, 360, 0xffffff, TRUE);
        SetFontSize(36);
        DrawString(485, 300, "YOUR WIN", 0x000000, TRUE);
    }

    //ROUND LOSE
    if (R_Win_FLG[1] == TRUE) {
        DrawBox(470, 300, 700, 380, 0x1c1c66, TRUE);
        SetFontSize(36);
        DrawString(485, 300, "YOUR LOSE", 0xffffff, TRUE);
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
    DrawFormatString(1100, 350, 0xffffff, "P_PEA: %d", P_PEA_FLG, TRUE);
    DrawFormatString(1100, 370, 0xffffff, "2PEA: %d", P_2PEA_FLG, TRUE);
    DrawFormatString(1100, 390, 0xffffff, "3CARD: %d", P_3CARD_FLG, TRUE);
    DrawFormatString(1100, 410, 0xffffff, "FLASH: %d", P_FLASH_FLG, TRUE);
    DrawFormatString(1100, 430, 0xffffff, "STRAIGHT: %d", P_STRAIGHT_FLG, TRUE);
    DrawFormatString(1100, 450, 0xffffff, "FULL_H: %d", P_FH_FLG, TRUE);
    DrawFormatString(1100, 470, 0xffffff, "4CARD: %d", P_4CARD_FLG, TRUE);
    DrawFormatString(1100, 490, 0xffffff, "SF: %d", P_SF_FLG, TRUE);

    DrawFormatString(1100, 90, 0xffffff, "E_PEA: %d", E_PEA_FLG, TRUE);
    DrawFormatString(1100, 110, 0xffffff, "2PEA: %d", E_2PEA_FLG, TRUE);
    DrawFormatString(1100, 130, 0xffffff, "3CARD: %d", E_3CARD_FLG, TRUE);
    DrawFormatString(1100, 150, 0xffffff, "FLASH: %d", E_FLASH_FLG, TRUE);
    DrawFormatString(1100, 170, 0xffffff, "STRAIGHT: %d", E_STRAIGHT_FLG, TRUE);
    DrawFormatString(1100, 190, 0xffffff, "FULL_H: %d", E_FH_FLG, TRUE);
    DrawFormatString(1100, 210, 0xffffff, "4CARD: %d", E_4CARD_FLG, TRUE);
    DrawFormatString(1100, 230, 0xffffff, "SF: %d", E_SF_FLG, TRUE);


   /* DrawFormatString(100, 450, 0xffffff, "YP[0]: %d", YP[0], TRUE);
    DrawFormatString(100, 470, 0xffffff, "YP[2]: %d", YP[2], TRUE);*/
    DrawFormatString(0, 300, 0xffffff, "YP2[0]: %d", YP2[0], TRUE);
    DrawFormatString(0, 320, 0xffffff, "YP2[1]: %d", YP2[1], TRUE);
    DrawFormatString(0, 340, 0xffffff, "YP2[2]: %d", YP2[2], TRUE);
    DrawFormatString(0, 360, 0xffffff, "YP2[3]: %d", YP2[3], TRUE);
    DrawFormatString(0, 380, 0xffffff, "YP2[4]: %d", YP2[4], TRUE);
    DrawFormatString(0, 400, 0xffffff, "YP2[5]: %d", YP2[5], TRUE);
    DrawFormatString(0, 420, 0xffffff, "YP2[6]: %d", YP2[6], TRUE);
    DrawFormatString(0, 440, 0xffffff, "YP2[7]: %d", YP2[7], TRUE);
    DrawFormatString(0, 460, 0xffffff, "YP2[8]: %d", YP2[8], TRUE);
    DrawFormatString(0, 480, 0xffffff, "YP2[9]: %d", YP2[9], TRUE);
    DrawFormatString(0, 500, 0xffffff, "YP2[12]: %d", YP2[12], TRUE);

    DrawFormatString(1100, 540, 0xffffff, "P1A: %d", P_CARD_A[0], TRUE);
    DrawFormatString(1100, 560, 0xffffff, "P2A: %d", P_CARD_A[1], TRUE);
    DrawFormatString(100, 520, 0xffffff, "C1A: %d", C_CARD_A[0], TRUE);
    DrawFormatString(300, 520, 0xffffff, "C2A: %d", C_CARD_A[1], TRUE);
    DrawFormatString(500, 520, 0xffffff, "C3A: %d", C_CARD_A[2], TRUE);
    DrawFormatString(700, 520, 0xffffff, "C4A: %d", C_CARD_A[3], TRUE);
    DrawFormatString(900, 520, 0xffffff, "C5A: %d", C_CARD_A[4], TRUE);
    
    DrawFormatString(50, 200, 0xffffff, "SC1A: %d", P_SORT[0], TRUE);
    DrawFormatString(170, 200, 0xffffff, "SC2A: %d", P_SORT[1], TRUE);
    DrawFormatString(290, 200, 0xffffff, "SC3A: %d", P_SORT[2], TRUE);
    DrawFormatString(410, 200, 0xffffff, "SC4A: %d", P_SORT[3], TRUE);
    DrawFormatString(530, 200, 0xffffff, "SC5A: %d", P_SORT[4], TRUE);
    DrawFormatString(650, 200, 0xffffff, "SC6A: %d", P_SORT[5], TRUE);
    DrawFormatString(770, 200, 0xffffff, "SC7A: %d", P_SORT[6], TRUE);
   
    DrawFormatString(50, 220, 0xffffff, "ESC1A: %d", E_SORT[0], TRUE);
    DrawFormatString(170, 220, 0xffffff, "ESC2A: %d", E_SORT[1], TRUE);
    DrawFormatString(290, 220, 0xffffff, "ESC3A: %d", E_SORT[2], TRUE);
    DrawFormatString(410, 220, 0xffffff, "ESC4A: %d", E_SORT[3], TRUE);
    DrawFormatString(530, 220, 0xffffff, "ESC5A: %d", E_SORT[4], TRUE);
    DrawFormatString(650, 220, 0xffffff, "ESC6A: %d", E_SORT[5], TRUE);
    DrawFormatString(770, 220, 0xffffff, "ESC7A: %d", E_SORT[6], TRUE);
   /* DrawGraph(0, 0, Back, TRUE);*/
   
    
}
