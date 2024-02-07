#pragma once
#include "AbstractScene.h"

#include <vector>
#include <algorithm>  // for std::shuffle
#include <random>     // for std::default_random_engine

//#define SCREEN_HEIGHT 720	//��ʃT�C�Y (�c)
//#define SCREEN_WIDTH 1280	//��ʃT�C�Y (��)

class LastCard : public AbstractScene
{
private:
    // ����Ԋu����
    const int max_input_margin = 15;
    // �X�e�B�b�N�̊��x
    const int stick_sensitivity = 20000;

    int input_margin = 0;  //���쎞�ԊԊu
    int now_Select = 0; //���ݑI�����Ă郁�j���[

    //int Card[5][13] = {
    //    // �Ԃ̃J�[�h
    //    { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },  // ��
    //    // �I�����W�̃J�[�h
    //    { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },  // �I�����W
    //    // ���̃J�[�h
    //    { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },  // ��
    //    // �̃J�[�h
    //    { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },  // ��
    //    // ���C���h�J�[�h
    //    { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }   // ���C���h
    //};


    int CardImg[65];

    std::vector<std::vector<int>> playerHands;
    std::vector<int> deck;
    std::vector<int> field;

    const int startX = 50; // �J�nX���W
    const int startY = 50; // �J�nY���W
    const int cardWidth = 50; // �J�[�h�̕�
    const int cardHeight = 80; // �J�[�h�̍���
    const int cardGap = 10; // �J�[�h�Ԃ̊Ԋu

    const int NUM_COLORS = 4;
    const int CARDS_PER_COLOR = 13;

    int Turn = 1; //�^�[������

    //�^�[�����ԊԊu
    int turn_margin = 0;    
    int max_turn_margin = 200;  

    int player_checkdraw = 0;  //1:�K�v�Ȃ��@2:�K�v


    int WildCardFlg = 0;    //���C���h�J�[�h�t���O
    int WildCardColor = -1; //0:�ԁ@1:�I�����W�@2:���@3�F���F

    int Draw2Flg = 0;   //�h���[2�t���O
    int Draw3Flg = 0;   //�h���[3�t���O

    int SkipFlg = 0;    //�X�L�b�v�t���O

    int ReverseFlg = 0; //���o�[�X�t���O

    int Draw2Count = 0; //�h���[2�J�E���g
    int Draw3Count = 0; //�h���[3�J�E���g

    int a;

public:
    //�R���X�g���N�^
    LastCard();

    //�f�X�g���N�^
    ~LastCard();

    //�`��ȊO�̍X�V�����s
    AbstractScene* Update() override;

    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;

    // �v���C���[�̎�D������������֐�
    void InitPlayerHands();

    //�o����J�[�h�̃`�F�b�N
    bool CardCheck(int select_card);

    //�G�s��
    void EnemyAction();

    //�J�[�h�h���[
    void CardDraw(int num);

    //����J�[�h�̃t���O�N��
    void CardFlgCheck(int select_card);

    //���C���h�J�[�h�̏���
    void Wildcard();
};
