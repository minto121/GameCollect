#include "sinkeisuijaku.h"
#include "DxLib.h"
#include <stdlib.h>
#include <time.h>

sinkeisuijaku::sinkeisuijaku()
{
    testflg = 0;

    // ��s��U����
    //srand((unsigned int)time(NULL)); // ���݂̎��Ԃ��g���ď�����q
    //first = (rand() % 2) + 1; // 1�܂���2�������_���ɐ���
    //srand((unsigned int)time(NULL));
    first = 0;
    // ����̃v���C���[�ƃR���s���[�^�[�̐ݒ�
    if (first == 1) {
        isPlayerTurn = 1;
    }
    else {
        isComputerTurn = 1;
    }
}


AbstractScene* sinkeisuijaku::Update()
{
    // �g�����v�̉摜�𕪊��ǂݍ���
    LoadDivGraph("images/Concentration/PlayingCards.png", 56, 14, 4, 128, 256, S_T);

    // �L�[���͏���
    // ���̓L�[�擾
    g_OldKey = g_NowKey;
    g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
    g_KeyFlg = g_NowKey & ~g_OldKey;

    // �Q�[�����W�b�N
    count++;
   
  

   
    // �g�����v�ɒl������
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


    if (isPlayerTurn == 1) {

        if (testcount == 0) {
            for (int j = 0; j < 4; j++) {
                for (int i = 0; i < 5; i++) {
                    test1 = trumps[j][i].syurui;
                }
            }
        }
    
            // �J�[�h��I�������Ƃ��̎�ނ�2��܂ŋL�^
            if (peacount == 1) {
                test1 = trumps[S_ber][S2_ber].syurui;
                testcount += 1;
            }
            if (testcount == 0) {
                test3 = test1;
            }
            if (testcount == 2) {
                test2 = test3;
            }

            else if (peacount == 2) {
                if (test1 != trumps[S_ber][S2_ber].syurui) {
                    test2 = trumps[S_ber][S2_ber].syurui;
                }
            }
        
        trumpflg = 0;
        if (peacount >= 3) {
            peacount = 0;
        }




        // �v���C���[�̃^�[��
      
    // ��ړ�
        if (g_KeyFlg & PAD_INPUT_UP) {
            if (S_ber >= 0 && S_ber <= 4) {
                S_ber = S_ber - 1;
            }
            if (S_ber < 0) {
                S_ber = 3;
            }
        }

        // ���ړ�
        if (g_KeyFlg & PAD_INPUT_DOWN) {
            if (S_ber >= 0 && S_ber <= 4) {
                S_ber = S_ber + 1;
            }
            if (S_ber >= 4) {
                S_ber = 0;
            }
        }

        // �E�ړ�
        if (g_KeyFlg & PAD_INPUT_RIGHT) {
            S2_ber = S2_ber + 1;
            if (S2_ber == 5 || S2_ber == 9 || S2_ber == 14 || S2_ber == 19 || S2_ber == 24) {
                S2_ber = S2_ber - 5;
            }
        }

        // ���ړ�
        if (g_KeyFlg & PAD_INPUT_LEFT) {
            S2_ber = S2_ber - 1;
            if (S2_ber == -1 || S2_ber == 6 || S2_ber == 11 || S2_ber == 16 || S2_ber == 21) {
                S2_ber = S2_ber + 5;
            }
        }

        // �Ō�ɑI�����ꂽ�J�[�h�̈ʒu��ǐՂ���ϐ���ǉ�
        int lastSelect = -1;

        if (count >= 10) {
            // �J�[�h�I��
            if (g_KeyFlg & PAD_INPUT_1 && rCount < 2 && (trumps[S_ber][S2_ber].syurui != lastSelect )) {
                if (trumpflg == 0 ) {

                    trumps[S_ber][S2_ber].flg = 1;

                    trumpflg = 1;
                    rCount++;
                    peacount++;

                    // �J�[�h���܂��I������Ă��Ȃ����m�F
                    // �J�[�h��I�������Ƃ��̎�ނ�1��ڂɋL�^
                    test1 = trumps[S_ber][S2_ber].syurui;
                    testcount++;

                    // �Ō�ɑI�����ꂽ�J�[�h�̈ʒu���X�V
                    lastSelect = trumps[S_ber][S2_ber].syurui;
                 
                }
                else if (rCount < 2 ) {
                    // 2��ڂ̃J�[�h�I�����ɑ����Ă��邩����
                    test2 = trumps[S_ber][S2_ber].syurui;
                    rCount++;

               

                    // �J�[�h�𗠕Ԃ�
                    for (int j = 0; j < 4; j++) {
                        for (int i = 0; i < 5; i++) {
                            trumps[j][i].flg = 0;
                        }
                    }

                    // �J�[�h�����̏�Ԃł���΁A�\�ɂ���
                    if (trumpflg == 1) {
                        trumps[S_ber][S2_ber].flg = 1;
                        trumpflg = 1;
                    }

                    // �J�[�h�I������ rCount ��2���傫���ꍇ�ł��A�����ė��Ԃ��Ȃ��悤�Ƀ��Z�b�g
                    rCount = 0;
                }
            }


            if (count >= 10) {

                if (trumpflg == 1 && rCount <= 2 ) {
                  
                    //test

                    trumps[S_ber][S2_ber].flg2 = trumps[S_ber][S2_ber].syurui;

                }


                randend = 1;
            }
        
            //�g�����v�̑I��3��ڂŗ��ʂɖ߂�

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
                    test1 = 0;
                    test2 = 0;
                    rCount = 0;
                    peacount = 0;

                    // �v���C���[�̎�Ԃ��I��������AisPlayerTurn �t���O�� false �ɐݒ肵�A�R���s���[�^�[�̃^�[���ֈڍs���܂��B
                    isPlayerTurn = 0;
                    isComputerTurn = 1;
                }
            }





            // �������J�[�h�̊m�F�ƃ��b�Z�[�W�\��
            for (int j = 0; j < 4; j++) {
                for (int i = 0; i < 5; i++) {
                    if (trumps[j][i].flg == 1 ) {
                        for (int k = 0; k < 4; k++) {
                            for (int l = 0; l < 5; l++) {
                                if (trumps[j][i].flg2 + 10 == trumps[k][l].flg2 || trumps[j][i].flg2 - 10 == trumps[k][l].flg2) {
                                    trumps[j][i].visible = 1;
                                    pea = 1;
                               }
                            }
                        }
                    }
                }
            }

            pea = 0;




            // �J�[�h��I�������Ƃ��̎�ނ�2��܂ŋL�^
            if (peacount == 1) {
                test1 = trumps[S_ber][S2_ber].syurui;
                testcount++;
            }
            else if (peacount == 2) {
                test2 = trumps[S_ber][S2_ber].syurui;
                testcount = 0;
            }

        }
    }

    

  

    if (isComputerTurn == 1) {
        // �R���s���[�^�[�̃^�[��
        ComputerTurn();

        // �R���s���[�^�[�̎�Ԃ��I��������A�J�[�h�̑�������m�F���鏈�������s���܂��B
        CheckMatched();
    }





    return this;
}

void sinkeisuijaku::Draw() const
{
    SetFontSize(50);
    DrawFormatString(20, 100, 0x00ffff, "�c�莞�� %d", 5 - pTime / 10);

    DrawFormatString(100, 120, 0x00ffff, "visible %d", trumps[S_ber][S2_ber].flg2);

  
    if (pea == 1) {
        DrawFormatString(100, 120, 0x00ffff, "������� ");
    }



     // �g�����v�̕\��
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 5; i++) {
            
            if (trumps[j][i].visible == 0) {
            if (trumps[j][i].flg == 0) {
                // �J�[�h���I������Ă��Ȃ��ꍇ�A�J�[�h�̗���\��
                DrawRotaGraph(400 + i * 120, 130 + j * 150, 1, 0, S_T[0], TRUE);
            }
            else {
                if (trumps[j][i].syurui <= 10) {
                    // �J�[�h���I������Ă���ꍇ�A�J�[�h�̕\��\��
                    DrawGraph(340 + i * 120, 0 + j * 150, S_T[trumps[j][i].syurui], TRUE);
                }
                if (trumps[j][i].syurui > 10) {
                    DrawGraph(340 + i * 120, 0 + j * 150, S_T[trumps[j][i].syurui + 18], TRUE);
                }
            }
        }
            //�v���C���[���J�[�h�𑵂�����
            if (trumps[j][i].visible == 1) {
                DrawGraph(340 + i * 120, 0 + j * 150, S_T[42], TRUE);
            }

            //�R���s���[�^�[���J�[�h�𑵂�����
            if (trumps[j][i].visible == 2) {
                DrawGraph(340 + i * 120, 0 + j * 150, S_T[39], TRUE);

            }
    }
}

    // �I�𒆂̃g�����v�Ƀn�C���C�g��\��
    DrawBox(355 + S2_ber * 120, 55 + S_ber * 150, 450 + S2_ber * 120, 200 + S_ber * 150, 0xff0000, FALSE);


 


    // ���̑��̏��\��
    DrawFormatString(100, 180, 0xfff00f, "���%d", trumps[S_ber][S2_ber].syurui);

    // �^�[�����\��
    if (first == 1) {
        DrawFormatString(50, 30, 0xff00ff, "��s�ł��I");
    }
    else {
        DrawFormatString(50, 30, 0xff00ff, "��U�ł��I");
    }
}

void sinkeisuijaku::ComputerTurn()
{
 
    if (count >= 10) {
        //�J�E���g
        cTime++;


        if (rebirth == 0) {

            int randRow, randCol, randRow2, randCol2;

            // �����_���ȍ��W�𐶐�
            do {
                randRow = rand() % 4;
                randCol = rand() % 5;
            } while (trumps[randRow][randCol].visible == 1 || trumps[randRow][randCol].visible == 2);

            do {
                randRow2 = rand() % 4;
                randCol2 = rand() % 5;
            } while (randRow2 == randRow && randCol2 == randCol || trumps[randRow2][randCol2].visible == 1 || trumps[randRow][randCol].visible == 2);  // 2���ڂ�1���ڂƈقȂ���W�ɂȂ�悤��



                // �I������2���̃J�[�h���߂���
            trumps[randRow][randCol].flg = 1;
            trumps[randRow2][randCol2].flg = 1;
            rebirth = rebirth + 1;

            if (trumps[randRow][randCol].syurui + 10 == trumps[randRow2][randCol2].syurui || trumps[randRow][randCol].syurui == trumps[randRow2][randCol2].syurui - 10) {
                trumps[randRow][randCol].visible = 2;
                trumps[randRow2][randCol2].visible = 2;

            }

        }

        //�Ƃ肠�����J�[�h�𗠖ʂɖ߂�

        if (cTime % 50 == 0) {

            for (int j = 0; j < 4; j++) {
                for (int i = 0; i < 5; i++) {
                    trumps[j][i].flg = 0;
                    trumps[j][i].flg2 = 100;
                }
            }
            // �R���s���[�^�[�̎�Ԃ��I��������AisComputerTurn �t���O�� false �ɐݒ肵�A�v���C���[�̃^�[���ֈڍs���܂��B
            isComputerTurn = 0;
            isPlayerTurn = 1;
            rebirth = 0;
        }
    }
}

void sinkeisuijaku::CheckMatched()
{
    // �����ɃJ�[�h�̑�������m�F���鏈�����������܂��B
     // �v���C���[�ƃR���s���[�^�[�̗����ɑ΂��ēK�؂ȏ������s���܂��B

     // �J�[�h���������ꍇ�A�������t���O��ݒ肷��Ȃǂ̏������l�����܂��B
}