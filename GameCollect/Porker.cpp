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

//���E���h������
void Porker::ROUND_INIT() 
{
    if (Winflg == FALSE && Loseflg == FALSE && Drawflg == FALSE) {
        P_rand1 = GetRand(51);   //�v���C���[�̃z�[���J�[�h1
        P_rand2 = GetRand(51);   //�v���C���[�̃z�[���J�[�h2

        E_rand1 = GetRand(51);   //�G�̃z�[���J�[�h1
        E_rand2 = GetRand(51);   //�G�̃z�[���J�[�h2

        C_rand1 = GetRand(51);   //�R�~���j�e�B�J�[�h1
        C_rand2 = GetRand(51);   //�R�~���j�e�B�J�[�h2
        C_rand3 = GetRand(51);   //�R�~���j�e�B�J�[�h3
        C_rand4 = GetRand(51);   //�R�~���j�e�B�J�[�h4
        C_rand5 = GetRand(51);   //�R�~���j�e�B�J�[�h5

        C_flg1 = FALSE;
        C_flg2 = FALSE;
        C_flg3 = FALSE;
        P_TEKI = 0;
        E_Fouldflg = FALSE;
        E_CAllflg = FALSE;
        E_Raiseflg = FALSE;
    }
}





//�v���C���[�̃R�[��
void Porker::P_CALL()
{
    if (Winflg == FALSE && Loseflg == FALSE && Drawflg == FALSE) {
        Bs = Bs + 50;
        ps1 = ps1 - 50;
    }
}




//�v���C���[�̃��C�Y
void Porker::PLAYER_RAISE()
{
    if (Winflg == FALSE && Loseflg == FALSE && Drawflg == FALSE) {
        Bs = Bs + 100;
        ps1 = ps1 - 100;
    }
}




//�G�̃R�[���ƃ��C�Y
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


    //               �J�[�h�̂��Ԃ�h�~               //

    //�z�[���J�[�h1�����Ԃ�������蒼���p(�v���C���[)
    if (P_rand2 == P_rand1) {
        P_rand2 = GetRand(51);
    }
   
    //�z�[���J�[�h1�����Ԃ�������蒼���p(�G)
    if (E_rand1 == P_rand1 || E_rand1 == P_rand2) {
        E_rand1 = GetRand(51);
    }
    //�z�[���J�[�h2�����Ԃ�������蒼���p(�G)
    if (E_rand2 == P_rand1 || E_rand2 == P_rand2|| E_rand2 == E_rand1) {
        E_rand2 = GetRand(51);
    }
    
    //�R�~���j�e�B�J�[�h�����Ԃ�������蒼���p(1���)
    if (C_rand1 == P_rand1 || C_rand1 == P_rand2 || C_rand1 == E_rand1 || C_rand1 == E_rand2) {
        C_rand1 = GetRand(51);
    }

    //�R�~���j�e�B�J�[�h�����Ԃ�������蒼���p(2���)
    if (C_rand2== P_rand1 || C_rand2 == P_rand2 || C_rand2 == E_rand1 || C_rand2 == E_rand2 || C_rand2 == C_rand1) {
        C_rand2 = GetRand(51);
    }

    //�R�~���j�e�B�J�[�h�����Ԃ�������蒼���p(3���)
    if (C_rand3 == P_rand1 || C_rand3 == P_rand2 || C_rand3 == E_rand1 || C_rand3 == E_rand2 || C_rand3 == C_rand1 || C_rand3==C_rand2) {
        C_rand3 = GetRand(51);
    }

    //�R�~���j�e�B�J�[�h�����Ԃ�������蒼���p(4���)
    if (C_rand4 == P_rand1 || C_rand4 == P_rand2 || C_rand4 == E_rand1 || C_rand4 == E_rand2 || C_rand4 == C_rand1 || C_rand4 == C_rand2||C_rand4 == C_rand3) {
        C_rand4 = GetRand(51);
    }

    //�R�~���j�e�B�J�[�h�����Ԃ�������蒼���p(5���)
    if (C_rand5 == P_rand1 || C_rand5 == P_rand2 || C_rand5 == E_rand1 || C_rand5 == E_rand2 || C_rand5 == C_rand1 || C_rand5 == C_rand2 || C_rand5 == C_rand3||C_rand5==C_rand4) {
        C_rand5 = GetRand(51);
    }


   

    //           �R�[�����邩�ǂ����̃t���O�Ǘ�              //

    //�R�[��(����Y����)
    if (PAD_INPUT::OnButton(XINPUT_BUTTON_Y) && C_flg1 == FALSE && Winflg == FALSE && Loseflg == FALSE && Drawflg == FALSE) {
        C_flg1 = TRUE;
        P_CALL();
        ENEMIE_CHOISE();
        BTN_flg = TRUE;
    }
    else if (PAD_INPUT::OnRelease(XINPUT_BUTTON_Y)) {
        BTN_flg = FALSE;
    }
    //�R�[��(����Y����)
    if (PAD_INPUT::OnButton(XINPUT_BUTTON_Y) && C_flg1 ==TRUE && C_flg2 == FALSE && BTN_flg == FALSE && Winflg == FALSE && Loseflg == FALSE && Drawflg == FALSE) {
        C_flg2 = TRUE;
        P_CALL();
        ENEMIE_CHOISE();
        BTN_flg = TRUE;
    }
    else if (PAD_INPUT::OnRelease(XINPUT_BUTTON_Y)) {
        BTN_flg = FALSE;
    }
    //�R�[��(����Y����)
    if (PAD_INPUT::OnButton(XINPUT_BUTTON_Y) && C_flg2 == TRUE && C_flg3 == FALSE && BTN_flg == FALSE && Winflg == FALSE && Loseflg == FALSE && Drawflg == FALSE) {
        C_flg3 = TRUE;
        P_CALL();
        ENEMIE_CHOISE();
    }
    else if (PAD_INPUT::OnRelease(XINPUT_BUTTON_Y)) {
        BTN_flg = FALSE;
    }




    //               ���C�Y               //

    //���C�Y(����B����)
    if (PAD_INPUT::OnButton(XINPUT_BUTTON_B) && C_flg1 == FALSE && Winflg == FALSE && Loseflg == FALSE && Drawflg == FALSE) {
        C_flg1 = TRUE;
        PLAYER_RAISE();
        ENEMIE_CHOISE();
        BTN_flg = TRUE;
    }
    else if (PAD_INPUT::OnRelease(XINPUT_BUTTON_B)) {
        BTN_flg = FALSE;
    }
    //���C�Y(����B����)
    if (PAD_INPUT::OnButton(XINPUT_BUTTON_B) && C_flg1 == TRUE && C_flg2 == FALSE && BTN_flg == FALSE && Winflg == FALSE && Loseflg == FALSE && Drawflg == FALSE) {
        C_flg2 = TRUE;
        PLAYER_RAISE();
        ENEMIE_CHOISE();
        BTN_flg = TRUE;
    }
    else if (PAD_INPUT::OnRelease(XINPUT_BUTTON_B)) {
        BTN_flg = FALSE;
    }
    //���C�Y(����B����)
    if (PAD_INPUT::OnButton(XINPUT_BUTTON_B) && C_flg2 == TRUE && C_flg3 == FALSE && BTN_flg == FALSE && Winflg == FALSE && Loseflg == FALSE && Drawflg == FALSE) {
        C_flg3 = TRUE;
        PLAYER_RAISE();
        ENEMIE_CHOISE();
    }




    //         ���E���h��ς���(3��ڂŃ^�C�g��)          //

    //X���������烉�E���h�`�F���W
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

    //                   �J�[�h�̕\��               //

    DrawFormatString(400, 600, 0xffffff, "prand1: %d", P_rand1, TRUE); //�v���C���[�̃z�[���J�[�h1
    DrawFormatString(600, 600, 0xffffff, "prand2: %d", P_rand2, TRUE); //�v���C���[�̃z�[���J�[�h2

    DrawFormatString(400, 50, 0xffffff, "erand1: %d", E_rand1, TRUE); //�G�̃z�[���J�[�h1
    DrawFormatString(600, 50, 0xffffff, "erand2: %d", E_rand2, TRUE); //�G�̃z�[���J�[�h2

    //1��ڃR�[���������R�~���j�e�B�J�[�h���O���o��
    if (C_flg1 == TRUE) {
        DrawFormatString(100, 300, 0xffffff, "crand1: %d", C_rand1, TRUE); //�R�~���j�e�B�J�[�h1
        DrawFormatString(300, 300, 0xffffff, "crand2: %d", C_rand2, TRUE); //�R�~���j�e�B�J�[�h2
        DrawFormatString(500, 300, 0xffffff, "crand3: %d", C_rand3, TRUE); //�R�~���j�e�B�J�[�h3
    }

    //2��ڃR�[���������R�~���j�e�B�J�[�h��1���o��
    if (C_flg2 == TRUE) {
        DrawFormatString(700, 300, 0xffffff, "crand4: %d", C_rand4, TRUE); //�R�~���j�e�B�J�[�h4
    }

    //3��ڃR�[���������R�~���j�e�B�J�[�h��1���o��
    if (C_flg3 == TRUE) {
        DrawFormatString(900, 300, 0xffffff, "crand5: %d", C_rand5, TRUE); //�R�~���j�e�B�J�[�h4
    }



    //               �L�[�\��              //

    if (C_flg3 == FALSE) {
        DrawString(100, 600, "[Y]BUTTON�ŃR�[��", 0xffffff, TRUE);
    }

    if (C_flg3 == FALSE) {
        DrawString(100, 640, "[B]BUTTON�Ń��C�Y", 0xffffff, TRUE);
    }

    if (C_flg3 == FALSE) {
        DrawString(100, 680, "[X]BUTTON�Ńt�H�[���h", 0xffffff, TRUE);
    }

    if (C_flg3 == TRUE) {
        DrawString(400, 650, "[X]BUTTON��ROUND�I��", 0xffffff, TRUE);
    }



    //              �\��               //

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

    //��ɏo�Ă���`�b�v(�X�R�A)
    if (Winflg == FALSE && Loseflg == FALSE && Drawflg == FALSE) {
        DrawFormatString(1100, 300, 0xffffff, "�`�b�v: %d", Bs, TRUE);
        DrawFormatString(1000, 600, 0xffffff, "�`�b�v(����): %d", ps1, TRUE);
        DrawFormatString(50, 100, 0xffffff, "�`�b�v(�G): %d", es1, TRUE);
        DrawFormatString(1100, 700, 0xffffff, "�`�b�v: %d", P_TEKI, TRUE);
    }

    //���������̃��U���g���
    if (Winflg == TRUE && Loseflg == FALSE && Drawflg == FALSE) {
        DrawBox(0, 0, 1000, 780, 0x000000, TRUE);
        DrawString(600, 100, "You Win", 0xffffff, TRUE);
        DrawString(500, 650, "[A]BUTTON�Ń^�C�g����", 0xffffff, TRUE);
        DrawFormatString(1000, 300, 0xffe000, "�`�b�v(����): %d", ps1, TRUE);
        DrawFormatString(50, 300, 0xffffff, "�`�b�v(�G): %d", es1, TRUE);
    }

    //���������̃��U���g���
    if (Loseflg == TRUE && Winflg == FALSE && Drawflg == FALSE) {
        DrawBox(0, 0, 1000, 780, 0x000000, TRUE);
        DrawString(600, 100, "You Lose", 0xffffff, TRUE);
        DrawString(500, 650, "[A]BUTTON�Ń^�C�g����", 0xffffff, TRUE);
        DrawFormatString(1000, 300, 0xffffff, "�`�b�v(����): %d", ps1, TRUE);
        DrawFormatString(50, 300, 0xffe000, "�`�b�v(�G): %d", es1, TRUE);
    }

    //�����������̃��U���g���
    if (Drawflg == TRUE&& Winflg == FALSE && Loseflg == FALSE) {
        DrawBox(0, 0, 1000, 780, 0x000000, TRUE);
        DrawString(600, 100, "DRAW", 0xffffff, TRUE);
        DrawString(500, 650, "[A]BUTTON�Ń^�C�g����", 0xffffff, TRUE);
    }


    DrawFormatString(500, 500, 0xffffff, "E_F_FLG: %d", E_Fouldflg, TRUE);
    DrawFormatString(500, 470, 0xffffff, "E_C_FLG: %d", E_CAllflg, TRUE);
    DrawFormatString(500, 440, 0xffffff, "E_R_FLG: %d", E_Raiseflg, TRUE);
    


   /* DrawGraph(0, 0, Back, TRUE);*/
   /* DrawGraph(400, 450, Tranpu_Img[1], TRUE);*/
   
}
