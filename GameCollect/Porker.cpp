#include "Porker.h"
#include "GameSelect.h"
#include"PadInput.h"
#include "DxLib.h"
#include "Title.h"

Porker::Porker()
{
    if ((Back = LoadGraph("../GameCollect/images/TexasHoldem/BG_Dummy.png"))) {}
    /*if (LoadDivGraph("../GameCollect/images/TexasHoldem/", 52, 13, 4, 100, 150, Tranpu_Img,FALSE)) {}*/
    a = 0;
    ps1 = 1000;
    es1 = 1000;
    Bs = 0;
    BTN_flg = FALSE;
    P_FPS = 0;
    Winflg = FALSE;
    Loseflg = FALSE;
    Drawflg = FALSE;
    E_Fouldflg = FALSE;
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

        C_flg1 = FALSE;
        C_flg2 = FALSE;
        C_flg3 = FALSE;
        P_TEKI = 0;
        E_Fouldflg = FALSE;
        E_CAllflg = FALSE;
        E_Raiseflg = FALSE;
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
        else if (40 <= P_TEKI && P_TEKI <= 60) {

            Bs = Bs + 100;
            es1 = es1 - 100;
            E_Raiseflg = TRUE;
        }
        else if (60 < P_TEKI <= 100) {
            E_Fouldflg = TRUE;
        }
    }
   
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

    //コール(今はY押す)
    if (PAD_INPUT::OnButton(XINPUT_BUTTON_Y) && C_flg1 == FALSE && Winflg == FALSE && Loseflg == FALSE && Drawflg == FALSE) {
        C_flg1 = TRUE;
        P_CALL();
        ENEMIE_CHOISE();
        BTN_flg = TRUE;
    }
    else if (PAD_INPUT::OnRelease(XINPUT_BUTTON_Y)) {
        BTN_flg = FALSE;
    }
    //コール(今はY押す)
    if (PAD_INPUT::OnButton(XINPUT_BUTTON_Y) && C_flg1 ==TRUE && C_flg2 == FALSE && BTN_flg == FALSE && Winflg == FALSE && Loseflg == FALSE && Drawflg == FALSE) {
        C_flg2 = TRUE;
        P_CALL();
        ENEMIE_CHOISE();
        BTN_flg = TRUE;
    }
    else if (PAD_INPUT::OnRelease(XINPUT_BUTTON_Y)) {
        BTN_flg = FALSE;
    }
    //コール(今はY押す)
    if (PAD_INPUT::OnButton(XINPUT_BUTTON_Y) && C_flg2 == TRUE && C_flg3 == FALSE && BTN_flg == FALSE && Winflg == FALSE && Loseflg == FALSE && Drawflg == FALSE) {
        C_flg3 = TRUE;
        P_CALL();
        ENEMIE_CHOISE();
    }
    else if (PAD_INPUT::OnRelease(XINPUT_BUTTON_Y)) {
        BTN_flg = FALSE;
    }




    //               レイズ               //

    //レイズ(今はB押す)
    if (PAD_INPUT::OnButton(XINPUT_BUTTON_B) && C_flg1 == FALSE && Winflg == FALSE && Loseflg == FALSE && Drawflg == FALSE) {
        C_flg1 = TRUE;
        PLAYER_RAISE();
        ENEMIE_CHOISE();
        BTN_flg = TRUE;
    }
    else if (PAD_INPUT::OnRelease(XINPUT_BUTTON_B)) {
        BTN_flg = FALSE;
    }
    //レイズ(今はB押す)
    if (PAD_INPUT::OnButton(XINPUT_BUTTON_B) && C_flg1 == TRUE && C_flg2 == FALSE && BTN_flg == FALSE && Winflg == FALSE && Loseflg == FALSE && Drawflg == FALSE) {
        C_flg2 = TRUE;
        PLAYER_RAISE();
        ENEMIE_CHOISE();
        BTN_flg = TRUE;
    }
    else if (PAD_INPUT::OnRelease(XINPUT_BUTTON_B)) {
        BTN_flg = FALSE;
    }
    //レイズ(今はB押す)
    if (PAD_INPUT::OnButton(XINPUT_BUTTON_B) && C_flg2 == TRUE && C_flg3 == FALSE && BTN_flg == FALSE && Winflg == FALSE && Loseflg == FALSE && Drawflg == FALSE) {
        C_flg3 = TRUE;
        PLAYER_RAISE();
        ENEMIE_CHOISE();
    }




    //         ラウンドを変える(3回目でタイトル)          //

    //Xを押したらラウンドチェンジ
    if (PAD_INPUT::OnButton(XINPUT_BUTTON_X)||E_Fouldflg ==TRUE ) {
        ROUND_INIT();
        a++;
    }
    if (a >= 3) {

        if (ps1 > es1) {
            Winflg = TRUE;
        }
        else if (ps1<es1) {
            Loseflg = TRUE;
        }
        else if (ps1 == es1) {
            Drawflg = TRUE;
        }

        if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
            return new Title;
        }
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
        DrawString(400, 650, "[X]BUTTONでROUND終了", 0xffffff, TRUE);
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

    //場に出ているチップ(スコア)
    if (Winflg == FALSE && Loseflg == FALSE && Drawflg == FALSE) {
        DrawFormatString(1100, 300, 0xffffff, "チップ: %d", Bs, TRUE);
        DrawFormatString(1000, 600, 0xffffff, "チップ(自分): %d", ps1, TRUE);
        DrawFormatString(50, 100, 0xffffff, "チップ(敵): %d", es1, TRUE);
        DrawFormatString(1100, 700, 0xffffff, "チップ: %d", P_TEKI, TRUE);
    }

    //勝った時のリザルト画面
    if (Winflg == TRUE && Loseflg == FALSE && Drawflg == FALSE) {
        DrawBox(0, 0, 1000, 780, 0x000000, TRUE);
        DrawString(600, 100, "You Win", 0xffffff, TRUE);
        DrawString(500, 650, "[A]BUTTONでタイトルへ", 0xffffff, TRUE);
        DrawFormatString(1000, 300, 0xffe000, "チップ(自分): %d", ps1, TRUE);
        DrawFormatString(50, 300, 0xffffff, "チップ(敵): %d", es1, TRUE);
    }

    //負けた時のリザルト画面
    if (Loseflg == TRUE && Winflg == FALSE && Drawflg == FALSE) {
        DrawBox(0, 0, 1000, 780, 0x000000, TRUE);
        DrawString(600, 100, "You Lose", 0xffffff, TRUE);
        DrawString(500, 650, "[A]BUTTONでタイトルへ", 0xffffff, TRUE);
        DrawFormatString(1000, 300, 0xffffff, "チップ(自分): %d", ps1, TRUE);
        DrawFormatString(50, 300, 0xffe000, "チップ(敵): %d", es1, TRUE);
    }

    //引き分け時のリザルト画面
    if (Drawflg == TRUE&& Winflg == FALSE && Loseflg == FALSE) {
        DrawBox(0, 0, 1000, 780, 0x000000, TRUE);
        DrawString(600, 100, "DRAW", 0xffffff, TRUE);
        DrawString(500, 650, "[A]BUTTONでタイトルへ", 0xffffff, TRUE);
    }


    DrawFormatString(500, 500, 0xffffff, "E_F_FLG: %d", E_Fouldflg, TRUE);
    DrawFormatString(500, 470, 0xffffff, "E_C_FLG: %d", E_CAllflg, TRUE);
    DrawFormatString(500, 440, 0xffffff, "E_R_FLG: %d", E_Raiseflg, TRUE);
    


   /* DrawGraph(0, 0, Back, TRUE);*/
   /* DrawGraph(400, 450, Tranpu_Img[1], TRUE);*/
   
}
