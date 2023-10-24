#include "Porker.h"
#include "GameSelect.h"
#include"PadInput.h"
#include "DxLib.h"
#include "Title.h"

Porker::Porker()
{
    if ((Back = LoadGraph("../GameCollect/images/TexasHoldem/BG_Dummy.png"))) {}
    /*if (LoadDivGraph("../GameCollect/images/TexasHoldem/", 52, 13, 4, 100, 150, Tranpu_Img,FALSE)) {}*/

    ROUND_INIT();

    a = 0;
   
}

Porker::~Porker()
{

}


void Porker::ROUND_INIT() 
{

    P_rand1 = GetRand(51);   //プレイヤーのホールカード1
    P_rand2 = GetRand(51);   //プレイヤーのホールカード2

    E_rand1 = GetRand(51);   //敵のホールカード1
    E_rand2 = GetRand(51);   //敵のホールカード2

    C_rand1 = GetRand(51);   //コミュニティカード1
    C_rand2 = GetRand(51);   //コミュニティカード2
    C_rand3 = GetRand(51);   //コミュニティカード3
    C_rand4 = GetRand(51);   //コミュニティカード4
    C_rand5 = GetRand(51);   //コミュニティカード5

    C_flg1 = FALSE;
    C_flg2 = FALSE;
    C_flg3 = FALSE;
}



AbstractScene* Porker::Update()
{

    //               カードのかぶり防止               //

    //ホールカード1がかぶった時やり直し用(プレイヤー)
    if (P_rand2 == P_rand1) {
        P_rand2 = GetRand(51);
    }
   
    //ホールカード1がかぶった時やり直し用(敵)
    if (E_rand1 == P_rand1 || E_rand1 == P_rand2) {
        E_rand1 = GetRand(51);
    }
    //ホールカード2がかぶった時やり直し用(敵)
    if (E_rand2 == P_rand1 || E_rand2 == P_rand2|| E_rand2 == E_rand1) {
        E_rand2 = GetRand(51);
    }
    
    //コミュニティカードがかぶった時やり直し用(1回目)
    if (C_rand1 == P_rand1 || C_rand1 == P_rand2 || C_rand1 == E_rand1 || C_rand1 == E_rand2) {
        C_rand1 = GetRand(51);
    }

    //コミュニティカードがかぶった時やり直し用(2回目)
    if (C_rand2== P_rand1 || C_rand2 == P_rand2 || C_rand2 == E_rand1 || C_rand2 == E_rand2 || C_rand2 == C_rand1) {
        C_rand2 = GetRand(51);
    }

    //コミュニティカードがかぶった時やり直し用(3回目)
    if (C_rand3 == P_rand1 || C_rand3 == P_rand2 || C_rand3 == E_rand1 || C_rand3 == E_rand2 || C_rand3 == C_rand1 || C_rand3==C_rand2) {
        C_rand3 = GetRand(51);
    }

    //コミュニティカードがかぶった時やり直し用(4回目)
    if (C_rand4 == P_rand1 || C_rand4 == P_rand2 || C_rand4 == E_rand1 || C_rand4 == E_rand2 || C_rand4 == C_rand1 || C_rand4 == C_rand2||C_rand4 == C_rand3) {
        C_rand4 = GetRand(51);
    }

    //コミュニティカードがかぶった時やり直し用(5回目)
    if (C_rand5 == P_rand1 || C_rand5 == P_rand2 || C_rand5 == E_rand1 || C_rand5 == E_rand2 || C_rand5 == C_rand1 || C_rand5 == C_rand2 || C_rand5 == C_rand3||C_rand5==C_rand4) {
        C_rand5 = GetRand(51);
    }




    //           コールするかどうかのフラグ管理              //

    //コール(今はA押す)
    if (CheckHitKey(KEY_INPUT_A)) {
        C_flg1 = TRUE;
    }
   
    //コール(今はS押す)
    if (CheckHitKey(KEY_INPUT_S)&&C_flg1 ==TRUE) {
        C_flg2 = TRUE;
    }

    //コール(今はD押す)
    if (CheckHitKey(KEY_INPUT_D)&&C_flg2 == TRUE) {
        C_flg3 = TRUE;
    }



    //         ラウンドを変える(3回目でタイトル)          //

    //Rを押したらラウンドチェンジ
    if (CheckHitKey(KEY_INPUT_R)&&C_flg3 == TRUE) {
        ROUND_INIT();
        a++;
    }
    if (a == 3) {
        return new Title;
    }

    return this;
}



void Porker::Draw() const
{

    //                   カードの表示               //

    DrawFormatString(400, 600, 0xffffff, "prand1: %d", P_rand1, TRUE); //プレイヤーのホールカード1
    DrawFormatString(600, 600, 0xffffff, "prand2: %d", P_rand2, TRUE); //プレイヤーのホールカード2

    DrawFormatString(400, 50, 0xffffff, "erand1: %d", E_rand1, TRUE); //敵のホールカード1
    DrawFormatString(600, 50, 0xffffff, "erand2: %d", E_rand2, TRUE); //敵のホールカード2

    //1回目コールした時コミュニティカードを三枚出す
    if (C_flg1 == TRUE) {
        DrawFormatString(100, 300, 0xffffff, "crand1: %d", C_rand1, TRUE); //コミュニティカード1
        DrawFormatString(300, 300, 0xffffff, "crand2: %d", C_rand2, TRUE); //コミュニティカード2
        DrawFormatString(500, 300, 0xffffff, "crand3: %d", C_rand3, TRUE); //コミュニティカード3
    }

    //2回目コールした時コミュニティカードを1枚出す
    if (C_flg2 == TRUE) {
        DrawFormatString(700, 300, 0xffffff, "crand4: %d", C_rand4, TRUE); //コミュニティカード4
    }

    //3回目コールした時コミュニティカードを1枚出す
    if (C_flg3 == TRUE) {
        DrawFormatString(900, 300, 0xffffff, "crand5: %d", C_rand5, TRUE); //コミュニティカード4
    }



    //               キー表示              //

    if (C_flg1 == FALSE) {
        DrawString(500, 650, "PRESS [A] KEY", 0xffffff, TRUE);
    }

    if (C_flg1 == TRUE&&C_flg2 == FALSE) {
        DrawString(500, 650, "PRESS [S] KEY", 0xffffff, TRUE);
    }

    if (C_flg1 == TRUE && C_flg2 == TRUE&&C_flg3 == FALSE) {
        DrawString(500, 650, "PRESS [D] KEY", 0xffffff, TRUE);
    }

    if (C_flg3 == TRUE) {
        DrawString(500, 650, "PRESS [R] KEY", 0xffffff, TRUE);
    }



    //              表示               //

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

   /* DrawGraph(0, 0, Back, TRUE);*/
   /* DrawGraph(400, 450, Tranpu_Img[1], TRUE);*/
   
}
