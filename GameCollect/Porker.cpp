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

    //�R�[��(����A����)
    if (CheckHitKey(KEY_INPUT_A)) {
        C_flg1 = TRUE;
    }
   
    //�R�[��(����S����)
    if (CheckHitKey(KEY_INPUT_S)&&C_flg1 ==TRUE) {
        C_flg2 = TRUE;
    }

    //�R�[��(����D����)
    if (CheckHitKey(KEY_INPUT_D)&&C_flg2 == TRUE) {
        C_flg3 = TRUE;
    }



    //         ���E���h��ς���(3��ڂŃ^�C�g��)          //

    //R���������烉�E���h�`�F���W
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

   /* DrawGraph(0, 0, Back, TRUE);*/
   /* DrawGraph(400, 450, Tranpu_Img[1], TRUE);*/
   
}
