#include "Porker.h"
#include"DxLib.h"
#include"PadInput.h"
#include<stdlib.h>
#include"math.h"
#include "GameSelect.h"



Porker::Porker()
{
	if (LoadDivGraph("../GameCollect/images/TexasHoldem/PlayingCards.png", 56, 14, 4, 128, 256, Tranpu_Img, FALSE)) {}

	BackGround[0] = LoadGraph("../GameCollect/images/TexasHoldem/Poker_Back.png");
	BackGround[1] = LoadGraph("../GameCollect/images/TexasHoldem/���w�i2.png");
	BackGround[2] = LoadGraph("../GameCollect/images/TexasHoldem/���w�i.png");
	Round_Count = 1;//���E���h��
	
	ROUND_INIT();//���E���h������
}


Porker::~Porker()
{

}


//���E���h������
void Porker::ROUND_INIT()
{

  //�v���C���[�ƓG���q���Ă�X�R�A(�`�b�v)�̍��v
  Pot = 0;         

  //�s���I�����UI(1���x�b�g�A2�����C�Y�A3���t�H�[���h�A4���G�̃R�[���A5���G�̃t�H�[���h)
  Action_UI = 0;


  //FB�ҋ@���ԗp
  FB_UI = 0;


  //�^�[���\��UI
  Turn = 1;


  //���E���h�\��UI
  Round_UI = TRUE;
 

  //�V���E�_�E��
  ShowDawn = FALSE;              


  //�V���E�_�E��UI
  ShowDawnUI = FALSE;


  //���U���g���
  Result = FALSE;


  //�c��Q�[����
  LastGame = 4;


  //�Q�[���I��
  GameOver = FALSE;


   P_NOPEA_FLG = FALSE;

   P_2PEA_FLG = FALSE;

   P_3CARD_FLG = FALSE;

   P_STRAIGHT_FLG = FALSE;

   P_FLASH_FLG = FALSE;

   P_FULLHOUSE_FLG = FALSE;

   P_4CARD_FLG = FALSE;

   P_SF_FLG = FALSE;

   P_RSF_FLG = FALSE;

   E_NOPEA_FLG = FALSE;

   E_2PEA_FLG = FALSE;

   E_3CARD_FLG = FALSE;

   E_STRAIGHT_FLG = FALSE;

   E_FLASH_FLG = FALSE;

   E_FULLHOUSE_FLG = FALSE;

   E_4CARD_FLG = FALSE;

   E_SF_FLG = FALSE;

   E_RSF_FLG = FALSE;


  //�y�A�t���O
  for (int x = 0; x <= 1; x++)
  {
	  P_PEA_FLG[x] = FALSE;
  }



  //�������E���h��1�Ȃ珉�������X�R�A��1000�ɂȂ� Score[0]���v���C���[�AScore[1]���G
  if (Round_Count == 1) {             
	  for (int x = 0; x <= 1; x++)
	  {
		  Score[x] = 5000;           
	  }
  }



  // �K���ȕϐ��̔��p
  for (int x = 0; x <= 29; x++)
  {
	  a[x] = 0;                    
  }


  //�m�F�p��UI(�x�b�g��0,���C�Y��1,�t�H�[���h��2)
  for (int x = 0; x <= 2; x++)
  {
	  CheckUI[x] = FALSE;
  }


  //�m�F�p��UI�̃J�[�\�����W�p
  for (int x = 0; x <= 1; x++)
  {
	  Cursor[x] = 0;
  }


  //�v���C���[�̑I��(0���R�[���A1�����C�Y�A2���t�H�[���h)
  for (int x = 0; x <= 2; x++)
  {
	  Player_Choice[x] = FALSE;
  }


  //�G�̑I��(0���R�[���A1���t�H�[���h)
  for (int x = 0; x <= 2; x++)
  {
	  Enemy_Choice[x] = FALSE;
  }


  //�ҋ@���ԗp
  for (int x = 0; x <= 4; x++)
  {
	  Poker_Second[x] = FALSE;
  }


  //�ҋ@���Ԕ����̃t���O
  for (int x = 0; x <= 4; x++)
  {
	  Wait_TimeFLG[x] = FALSE; 
  }


  //�\�[�g�p
  for (int x = 0; x <= 14; x++)
  {
	  P_SORT[x] = 0;
  }

  //�\�[�g�p2
  for (int x = 0; x <= 4; x++)
  {
	  P_SORT2[x] = 0;
  }

  //�\�[�g�p3
  for (int x = 0; x <= 5; x++)
  {
	  P_SORT3[x] = 0;
  }

  //�\�[�g�p4
  for (int x = 0; x <= 14; x++)
  {
	  E_SORT[x] = 0;
  }

  //�n���hUI
  for (int x = 0; x <= 8; x++)
  {
	 Hand[x] = FALSE;
  }

  //���Ƃ�[�Ɣԍ��i�[�p
  for (int x = 0; x <= 14; x++)
  {
	  P_Straight[x] = 0;
  }

  //���Ƃ�[�Ɣԍ��i�[�penemy
  for (int x = 0; x <= 14; x++)
  {
	  E_Straight[x] = 0;
  }


  CARD_SETTING();
}


//�ŏ��ɕ����Q����
void Porker::FIRST_BET()
{

	//���E���h1�J�n���ɎQ����250����
	if (Round_Count == 1 && a[1] == 0)
	{	
		Wait_TimeFLG[1] = TRUE;
		for (int x = 0; x <= 1; x++)
		{
			
			Score[x] = Score[x] - 250;
			Pot += 250;
			a[1] = 1;
			a[5] = 250;
		}
		
	}

	//���E���h2�J�n���ɎQ����500����
	if (Round_Count == 2 && a[1] == 0)
	{
		Wait_TimeFLG[1] = TRUE;
		for (int x = 0; x <= 1; x++)
		{
			
			Score[x] = Score[x] - 500;
			Pot += 500;
			a[1] = 1;
			a[5] = 500;
		}
		
	}

	//���E���h3�J�n���ɎQ����750����
	if (Round_Count == 3 && a[1] == 0)
	{
		Wait_TimeFLG[1] = TRUE;
		for (int x = 0; x <= 1; x++)
		{
			
			Score[x] = Score[x] - 750;
			Pot += 750;
			a[1] = 1;
			a[5] = 750;
		}
	
	}

}


//�J�[�h
void Porker::CARD_SETTING()
{
	
	//�ŏ��ɔz����J�[�h�G�������ꂼ��2������
	
		P_Rand[0] = 15 /*GetRand(55)*/;   //�v���C���[�̃z�[���J�[�h1

		P_Rand[1] = 10/*GetRand(55)*/;   //�v���C���[�̃z�[���J�[�h2

		E_Rand[0] = 0/*GetRand(55)*/;   //�G�̃z�[���J�[�h1

		E_Rand[1] = 0/*GetRand(55)*/;   //�G�̃z�[���J�[�h2

	//2�^�[���ڂ̎O��

		C_Rand[0] = 9/*GetRand(55)*/;   //�e�[�u���J�[�h1

		C_Rand[1] = 12/*GetRand(55)*/;   //�e�[�u���J�[�h2

		C_Rand[2] = 11/*GetRand(55)*/;   //�e�[�u���J�[�h3

	//3�^�[���ڂ̎O��

		C_Rand[3] = 24/*GetRand(55)*/;   //�e�[�u���J�[�h4

	//4�^�[���ڂ̎O��
	
		C_Rand[4] = 25/*GetRand(55)*/;   //�e�[�u���J�[�h4


}


//�J�[�h�̂��Ԃ�h�~�ƌv�Z
void Porker::CARD_SETTING2()
{
	//�_�u�薳���p



		if (P_Rand[0] == 0 || P_Rand[0] == 14 || P_Rand[0] == 28 || P_Rand[0] == 42) {
			P_Rand[0] = GetRand(55);
		}
		if (P_Rand[1] == 0 || P_Rand[1] == 14 || P_Rand[1] == 28 || P_Rand[1] == 42 || P_Rand[1] == P_Rand[0]) {
			P_Rand[1] = GetRand(55);
		}
		if (E_Rand[0] == 0 || E_Rand[0] == 14 || E_Rand[0] == 28 || E_Rand[0] == 42 || E_Rand[0] == P_Rand[0] ||
			E_Rand[0] == P_Rand[1]) {
			E_Rand[0] = GetRand(55);
		}
		if (E_Rand[1] == 0 || E_Rand[1] == 14 || E_Rand[1] == 28 || E_Rand[1] == 42 || E_Rand[1] == P_Rand[0] ||
			E_Rand[1] == P_Rand[1] || E_Rand[1] == E_Rand[0]) {
			E_Rand[1] = GetRand(55);
		}

		if (C_Rand[0] == 0 || C_Rand[0] == 14 || C_Rand[0] == 28 || C_Rand[0] == 42 || C_Rand[0] == P_Rand[0] ||
			C_Rand[0] == P_Rand[1] || C_Rand[0] == E_Rand[0] || C_Rand[0] == E_Rand[1]) {
			C_Rand[0] = GetRand(55);
		}
		if (C_Rand[1] == 0 || C_Rand[1] == 14 || C_Rand[1] == 28 || C_Rand[1] == 42 || C_Rand[1] == P_Rand[0] ||
			C_Rand[1] == P_Rand[1] || C_Rand[1] == E_Rand[0] || C_Rand[1] == E_Rand[1] || C_Rand[1] == C_Rand[0]) {
			C_Rand[1] = GetRand(55);
		}
		if (C_Rand[2] == 0 || C_Rand[2] == 14 || C_Rand[2] == 28 || C_Rand[2] == 42 || C_Rand[2] == P_Rand[0] ||
			C_Rand[2] == P_Rand[1] || C_Rand[2] == E_Rand[0] || C_Rand[2] == E_Rand[1] || C_Rand[2] == C_Rand[0] ||
			C_Rand[2] == C_Rand[1]) {
			C_Rand[2] = GetRand(55);
		}
		if (C_Rand[3] == 0 || C_Rand[3] == 14 || C_Rand[3] == 28 || C_Rand[3] == 42 || C_Rand[3] == P_Rand[0] ||
			C_Rand[3] == P_Rand[1] || C_Rand[3] == E_Rand[0] || C_Rand[3] == E_Rand[1] || C_Rand[3] == C_Rand[0] ||
			C_Rand[3] == C_Rand[1] || C_Rand[3] == C_Rand[2]) {
			C_Rand[3] = GetRand(55);
		}
		if (C_Rand[4] == 0 || C_Rand[4] == 14 || C_Rand[4] == 28 || C_Rand[4] == 42 || C_Rand[4] == P_Rand[0] ||
			C_Rand[4] == P_Rand[1] || C_Rand[4] == E_Rand[0] || C_Rand[4] == E_Rand[1] || C_Rand[4] == C_Rand[0] ||
			C_Rand[4] == C_Rand[1] || C_Rand[4] == C_Rand[2] || C_Rand[4] == C_Rand[3]) {
			C_Rand[4] = GetRand(55);
		}


}


//�J�[�h����
void Porker::CARD_ANALAYSIS()
{
	//�ŏ���Rand�łƂ�������14�Ŋ���


		for (int i = 0; i < 2; i++) {
			P_CARD_A[i] = P_Rand[i] % 14;
			//�����]�肪1�������ꍇ�G�[�X�ɂȂ�̂Ő�����14�ɂ��čŋ��ɂ���
			if (P_CARD_A[i] == 1)
			{
				P_CARD_A[i] = 14;
			}
			P_CARD_S[i] = P_Rand[i] / 14;
		}

		for (int j = 0; j < 2; j++) {
			E_CARD_A[j] = E_Rand[j] % 14;
			//�����]�肪1�������ꍇ�G�[�X�ɂȂ�̂Ő�����14�ɂ��čŋ��ɂ���
			if (E_CARD_A[j] == 1)
			{
				E_CARD_A[j] = 14;
			}
			E_CARD_S[j] = E_Rand[j] / 14;
		}

		for (int c = 0; c < 5; c++) {
			//�����]�肪1�������ꍇ�G�[�X�ɂȂ�̂Ő�����14�ɂ��čŋ��ɂ���
			C_CARD_A[c] = C_Rand[c] % 14;
			if (C_CARD_A[c] == 1)
			{
				C_CARD_A[c] = 14;
			}
			C_CARD_S[c] = C_Rand[c] / 14;
		}

		//�v���C���[�̃J�[�h2���ł̃y�A
		if (P_CARD_A[0] == P_CARD_A[1])
		{
			P_PEA_FLG[0] = TRUE;
			Wait_TimeFLG[3] = TRUE;
		}
	

}


//�J�[�h�̃\�[�g�p
void Porker::CARD_SORT()
{
	

		P_SORT[0] = C_CARD_A[0];
		P_SORT[1] = C_CARD_A[1];
		P_SORT[2] = C_CARD_A[2];
		P_SORT[3] = C_CARD_A[3];
		P_SORT[4] = C_CARD_A[4];
		P_SORT[5] = P_CARD_A[0];
		P_SORT[6] = P_CARD_A[1];
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


		E_SORT[0] = C_CARD_A[0];
		E_SORT[1] = C_CARD_A[1];
		E_SORT[2] = C_CARD_A[2];
		E_SORT[3] = C_CARD_A[3];
		E_SORT[4] = C_CARD_A[4];
		E_SORT[5] = E_CARD_A[0];
		E_SORT[6] = E_CARD_A[1];
		int sort2;
		for (int a = 0; a <= 5; a++) {
			for (int b = a + 1; b <= 6; b++) {
				if (E_SORT[a] > E_SORT[b]) {
					sort2 = E_SORT[a];
					E_SORT[a] = E_SORT[b];
					E_SORT[b] = sort2;
				}
			}
		}




		P_SORT[7] = P_Rand[0];
		P_SORT[8] = P_Rand[1];
		P_SORT[9] = C_Rand[0];
		P_SORT[10] = C_Rand[1];
		P_SORT[11] = C_Rand[2];
		P_SORT[12] = C_Rand[3];
		P_SORT[13] = C_Rand[4];

		for (int x = 7; x <= 13; x++) 
		{
			if (P_SORT[x] == 1)
			{
				P_SORT[x] = 14;
			}
			if (P_SORT[x] == 15)
			{
				P_SORT[x] = 28;
			}
			if (P_SORT[x] == 29)
			{
				P_SORT[x] = 42;
			}
			if (P_SORT[x] == 43)
			{
				P_SORT[x] = 56;
			}
		}

		int sort5;
		for (int a = 7; a <= 12; a++) {
			for (int b = a + 1; b <= 13; b++) {
				if (P_SORT[a] > P_SORT[b]) {
					sort5 = P_SORT[a];
					P_SORT[a] = P_SORT[b];
					P_SORT[b] = sort5;
				}
			}
		}

		E_SORT[7] = E_Rand[0];
		E_SORT[8] = E_Rand[1];
		E_SORT[9] = C_Rand[0];
		E_SORT[10] = C_Rand[1];
		E_SORT[11] = C_Rand[2];
		E_SORT[12] = C_Rand[3];
		E_SORT[13] = C_Rand[4];
		int sort6;
		for (int a = 7; a <= 12; a++) {
			for (int b = a + 1; b <= 13; b++) {
				if (E_SORT[a] > E_SORT[b]) {
					sort6 = E_SORT[a];
					E_SORT[a] = E_SORT[b];
					E_SORT[b] = sort6;
				}
			}
		}
	

	if (Turn == 2) {
		P_SORT2[0] = P_CARD_A[0];
		P_SORT2[1] = P_CARD_A[1];
		P_SORT2[2] = C_CARD_A[0];
		P_SORT2[3] = C_CARD_A[1];
		P_SORT2[4] = C_CARD_A[2];

		int sort3;
		for (int a = 0; a <= 3; a++) {
			for (int b = a + 1; b <= 4; b++) {
				if (P_SORT2[a] > P_SORT2[b]) {
					sort3 = P_SORT2[a];
					P_SORT2[a] = P_SORT2[b];
					P_SORT2[b] = sort3;
				}
			}
		}
	}
	
	if (Turn == 3) {
		P_SORT3[0] = P_CARD_A[0];
		P_SORT3[1] = P_CARD_A[1];
		P_SORT3[2] = C_CARD_A[0];
		P_SORT3[3] = C_CARD_A[1];
		P_SORT3[4] = C_CARD_A[2];
		P_SORT3[5] = C_CARD_A[3];

		int sort4;
		for (int a = 0; a <= 4; a++) {
			for (int b = a + 1; b <= 5; b++) {
				if (P_SORT3[a] > P_SORT3[b]) {
					sort4 = P_SORT2[a];
					P_SORT3[a] = P_SORT3[b];
					P_SORT3[b] = sort4;
				}
			}
		}
	}
}




//�m�FUI
void Porker::UI()
{
	//����UI���o�Ă��炸Y�{�^�����������Ƃ��x�b�g
	if(PAD_INPUT::OnButton(XINPUT_BUTTON_Y) && CheckUI[1] == FALSE && CheckUI[2] == FALSE)
	{
		CheckUI[0] = TRUE;//�x�b�g�t���O

	}


	//����UI���o�Ă��炸B�{�^�����������Ƃ����C�Y
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_B) && CheckUI[0] == FALSE && CheckUI[2] == FALSE)
	{
		CheckUI[1] = TRUE;
	}


	//����UI���o�Ă��炸X�{�^�����������Ƃ��t�H�[���h
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_X) && CheckUI[1] == FALSE && CheckUI[0] == FALSE)
	{
		CheckUI[2] = TRUE;
		
	}




	//�J�[�\���̍��ړ�
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT)) {
		Cursor[0] = 1;//��
	}

	//�J�[�\���̉E�ړ�
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT)) {
		Cursor[0] = 0;//�E
	}

	//A�{�^���Ō����
	if (Cursor[0] == 1)
	{
		//A�{�^���Ō���(�x�b�g)
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_A) && CheckUI[0] == TRUE) {
			Player_Choice[0] = TRUE;//�x�b�g�t���O
			Cursor[0] = 0;
			CheckUI[0] = FALSE;
		}

		//A�{�^���Ō���(���C�Y)
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_A) && CheckUI[1] == TRUE) {
			Player_Choice[1] = TRUE;//���C�Y�t���O
			Cursor[0] = 0;
			CheckUI[1] = FALSE;
		}

		//A�{�^���Ō���(�t�H�[���h)
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_A) && CheckUI[2] == TRUE) {
			Player_Choice[2] = TRUE;//�t�H�[�J�[�h�t���O
			Cursor[0] = 0;
			CheckUI[2] = FALSE;
		}
	}

	//A�{�^���ŋ��ی�
	if (Cursor[0] == 0)
	{
		//A�{�^���Ō���
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_A) && CheckUI[0] == TRUE) {
			CheckUI[0] = FALSE;
		}
		//A�{�^���Ō���
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_A) && CheckUI[1] == TRUE) {
			CheckUI[1] = FALSE;
		}
		//A�{�^���Ō���
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_A) && CheckUI[2] == TRUE) {
			CheckUI[2] = FALSE;
		}
	}
}


//�v���C���[�̑I��(�x�b�g�A���C�Y�A�t�H�[���h)
void Porker::PLAYER_CHOICE()
{
	
	//�x�b�g�Ȃ�
	if (Player_Choice[0] == TRUE)
	{
		//���E���h1�Ȃ�100
		if (Round_Count == 1) {
			Score[0] = Score[0] - 100;
			Pot = Pot + 100;
			a[2] = 100;
		}

		//���E���h2�Ȃ�200
		if (Round_Count == 2) {
			Score[0] = Score[0] - 200;
			Pot = Pot + 200;
			a[2] = 200;
			
		}

		//���E���h3�Ȃ�300
		if (Round_Count == 3) {
			Score[0] = Score[0] - 300;
			Pot = Pot + 300;
			a[2] = 300;
		}
		Wait_TimeFLG[0] = TRUE;
		

	}

	


	//���C�Y�Ȃ�
	if (Player_Choice[1] == TRUE)
	{
		//���E���h1�Ȃ�200
		if (Round_Count == 1) {
			Score[0] = Score[0] - 200;
			Pot = Pot + 200;
			a[2] = 200;
		}

		//���E���h2�Ȃ�300
		if (Round_Count == 2) {
			Score[0] = Score[0] - 300; 
			Pot = Pot + 300;
			a[2] = 300;
		}

		//���E���h3�Ȃ�400
		if (Round_Count == 3) {
			Score[0] = Score[0] - 400;
			Pot = Pot + 400;
			a[2] = 400;
		}
		
		Wait_TimeFLG[0] = TRUE;
	
	}

	//�t�H�[���h�Ȃ�G�̃X�R�A�Ƀ|�b�g�̃X�R�A�����Z���ă��E���h�����Z
	if (Player_Choice[2] == TRUE)
	{
		Wait_TimeFLG[0] = TRUE;
	}

}


//�G�̑I��(�R�[���A�t�H�[���h)
void Porker::ENEMY_CHOICE()
{
	//�����_���œG�̑I��
	if (Poker_Second[0] == 120 && Action_UI != 3)
	{
		a[4] = GetRand(99);

		//90�p�[�Z���g�ŃR�[��
		if (a[4] <= 99)
		{
			Enemy_Choice[0] = TRUE;
			Action_UI = 4;
		
		}
		///*10%�Ńt�H�[���h*/
		//else if (a[4] >= 89)
		//{
		//	Enemy_Choice[1] = TRUE;
		//}



		//�G�̃R�[��
		if (Enemy_Choice[0] == TRUE) {

			//���E���h1
			if (Round_Count == 1)
			{
				Score[1] = Score[1] - a[2];
				Pot = Pot + a[2];
			}

			//���E���h2
			if (Round_Count == 2)
			{
				Score[1] = Score[1] - a[2];
				Pot = Pot + a[2];
			}

			//���E���h3
			if (Round_Count == 3)
			{
				Score[1] = Score[1] - a[2];
				Pot = Pot + a[2];
			}

			Action_UI = 4; //�R�[���\��
			Enemy_Choice[0] = FALSE;
		}

	}
}


//���E���h�I���̏���
void Porker::ROUND_END()
{

	
	if (Turn == 5 )
	{
		Wait_TimeFLG[2] = TRUE;
		
	}
	

	if(ShowDawn == TRUE && PAD_INPUT::OnButton(XINPUT_BUTTON_A))
	{
		Turn += 1;
	}
	if (ShowDawn == TRUE && PAD_INPUT::OnRelease(XINPUT_BUTTON_A))
	{
		Result = TRUE;
	}
	

	if(Result == TRUE && PAD_INPUT::OnButton(XINPUT_BUTTON_A))
	{
		Round_Count += 1;
		ROUND_INIT();
		
	}



}


//�҂����Ԋ֌W
void Porker::WAIT_TIME()
{
	
	Poker_Second[4]++;
	if (Poker_Second[4] == 60)
	{
		Poker_Second[4] = 0;
	}
	

	if (Wait_TimeFLG[0] == TRUE)
	{
		Poker_Second[0]++;

		for (int x = 0; x <= 2; x++) {
			if (Poker_Second[0] >= 1 && Poker_Second[0] <= 120 && Player_Choice[x] == TRUE)
			{
				Action_UI = x + 1;
			}
		}

		if (Player_Choice[2] == TRUE && Poker_Second[0] >= 121)
		{
			Action_UI = 0;

			Poker_Second[0] = 0;

			Player_Choice[2] = FALSE;

			Result = TRUE;
			Score[1] += Pot;
			Pot = 0;

			Wait_TimeFLG[0] = FALSE;
		}


		for (int x = 0; x <= 1; x++) {
			if (Poker_Second[0] >= 121 && Enemy_Choice[x] == TRUE)
			{
				for (int x = 0; x <= 2; x++)
				{
					Player_Choice[x] = FALSE;
				}
				Action_UI = 4 + x;
			}
		}
		

		if (Poker_Second[0] == 240 && Action_UI != 5)
		{
			Action_UI = 0;
			for (int x = 0; x <= 2; x++)
			{
				Player_Choice[x] = FALSE;
			}
			Enemy_Choice[0] = FALSE;
			Poker_Second[0] = 0;
			Turn = Turn + 1;//�^�[���\��UI+1
			LastGame -= 1;  //�c��Q�[����-1
			Wait_TimeFLG[0] = FALSE;
		}

		//�G���t�H�[���h
		if (Poker_Second[0] == 240 && Action_UI == 5)
		{
			Action_UI = 0;

			Result = TRUE;
			Score[0] += Pot;
			Pot = 0;

			Wait_TimeFLG[0] = FALSE;
		}
	}

	//FB�\������
	if (Wait_TimeFLG[1] == TRUE)
	{
		Poker_Second[1]++;

		if (Poker_Second[1] >= 1 && Poker_Second[1] <= 120)
		{
			FB_UI = 1;
		}

		if (Poker_Second[1] >= 121)
		{
			FB_UI = 2;
		}

		if (Poker_Second[1] == 240)
		{
			FB_UI = 0;

			Poker_Second[1] = 0;

			Wait_TimeFLG[1] = FALSE;
		}
	}
	
	//�V���E�_�E���\������
	if (Wait_TimeFLG[2] == TRUE)
	{
		Poker_Second[2]++;
		ShowDawnUI = TRUE;

		if (Poker_Second[2] == 120)
		{
			ShowDawnUI = FALSE;
			ShowDawn = TRUE;
			Wait_TimeFLG[2] = FALSE;
			Poker_Second[2] = 0;
			Turn += 1;
		}
	}


	if (Wait_TimeFLG[3] == TRUE)
	{
		Poker_Second[3]++;
		if (Poker_Second[3] == 60) 
		{
			Poker_Second[3] = 0;
		}
	}
}


//���E���h�\��UI
void Porker::ROUND_UI()
{
	for (int x = 0; x <= 2; x++)
	{
		if (Round_UI == TRUE && Round_Count == x + 1 && PAD_INPUT::OnButton(XINPUT_BUTTON_A))
		{
			
			Round_UI = FALSE;
			Wait_TimeFLG[3] = FALSE;
		}
	}
}


//
void Porker::HAND()
{
	if (a[7] == 0) {

		int x = 0;
		int y = 0;
		int z = 0;
		int v = 0;

		//RSF
		for (x = 7; x <= 10; x++)
		{
			z = 1;
			P_Straight[0] = 0;
			for (y = x + 1; y <= 13; y++)
			{
				if (P_SORT[x] + z == P_SORT[y])
				{
					P_Straight[0] += 1;
					z += 1;

				}
			}
		}




		if (P_Straight[0] >= 4 && P_Straight[1] == 14 || P_Straight[1] == 28 || P_Straight[1] == 42 || P_Straight[1] == 56)
		{
			P_RSF_FLG = TRUE;
			a[7] = 1;
		}




		//SF
		if (P_RSF_FLG == FALSE)
		{


			for (x = 7; x <= 10; x++)
			{
				z = 1;
				P_Straight[2] = 0;
				for (y = x + 1; y <= 13; y++)
				{
					if (P_SORT[x] + z == P_SORT[y])
					{
						P_Straight[2] += 1;
						z += 1;
						if (P_Straight[2] >= 4)
						{
							P_SF_FLG = TRUE;
							a[7] = 1;
						}
					}
				}
			}
		}
		//4card
		if (P_SF_FLG == FALSE && P_RSF_FLG == FALSE) {

			for (x = 0; x <= 3; x++)
			{
				for (y = x + 1; y <= 4; y++) {

					if (P_SORT[x] == P_SORT[y])
					{

						for (z = y + 1; z <= 5; z++) {

							if (P_SORT[y] == P_SORT[z])
							{

								for (v = z + 1; v <= 6; v++) {

									if (P_SORT[z] == P_SORT[v])
									{

										P_4CARD_FLG = TRUE;
										a[7] = 1;
									}
								}
							}
						}
					}

				}
			}
		}
		//fullhouse
		if (P_4CARD_FLG == FALSE && P_SF_FLG == FALSE && P_RSF_FLG == FALSE)
		{
			for (x = 0; x <= 3; x++)
			{
				for (y = x + 1; y <= 4; y++) {

					if (P_SORT[x] == P_SORT[y])
					{

						for (z = y + 1; z <= 5; z++) {

							if (P_SORT[y] == P_SORT[z])
							{
								a[9] += 1;
							}
							else if (P_SORT[y] != P_SORT[z])
							{
								a[8] += 1;
							}
						}
					}

				}
			}
			if (a[9] >= 1 && a[8] >= 1)
			{
				P_FULLHOUSE_FLG = TRUE;
				a[7] = 1;
			}

		}
		//flash
		if (P_FULLHOUSE_FLG == FALSE && P_4CARD_FLG == FALSE && P_SF_FLG == FALSE && P_RSF_FLG == FALSE)
		{
			if (P_CARD_S[0] == P_CARD_S[1])
			{
				a[10] += 1;
				a[11] += 1;
			}
			for (x = 0; x <= 4; x++)
			{
				if (P_CARD_S[0] == C_CARD_S[x])
				{
					a[10] += 1;
				}
				if (P_CARD_S[1] == C_CARD_S[x])
				{
					a[11] += 1;
				}
			}
			if (a[10] >= 4 || a[11] >= 4)
			{
				P_FLASH_FLG = TRUE;
				a[7] = 1;
			}

		}
		//straight
		if (P_FLASH_FLG == FALSE && P_FULLHOUSE_FLG == FALSE && P_4CARD_FLG == FALSE && P_SF_FLG == FALSE && P_RSF_FLG == FALSE)
		{

			for (x = 0; x <= 3; x++)
			{
				z = 1;
				P_Straight[3] = 0;
				for (y = x + 1; y <= 6; y++)
				{
					if (P_SORT[x] + z == P_SORT[y])
					{
						P_Straight[3] += 1;
						z += 1;
						if (P_Straight[3] >= 4)
						{
							P_STRAIGHT_FLG = TRUE;
							a[7] = 1;
						}
					}
				}
			}



		}
		//3card
		if (P_STRAIGHT_FLG == FALSE && P_FLASH_FLG == FALSE && P_FULLHOUSE_FLG == FALSE && P_4CARD_FLG == FALSE && P_SF_FLG == FALSE && P_RSF_FLG == FALSE)
		{

			for (x = 0; x <= 3; x++)
			{
				for (y = x + 1; y <= 4; y++) {

					if (P_SORT[x] == P_SORT[y])
					{

						for (z = y + 1; z <= 5; z++) {

							if (P_SORT[y] == P_SORT[z])
							{
								P_3CARD_FLG = TRUE;
								a[7] = 1;
							}
						}
					}

				}
			}
		}
		//pea 2pea
		if (P_3CARD_FLG == FALSE && P_STRAIGHT_FLG == FALSE && P_FLASH_FLG == FALSE && P_FULLHOUSE_FLG == FALSE && P_4CARD_FLG == FALSE && P_SF_FLG == FALSE && P_RSF_FLG == FALSE) {

			for (x = 0; x <= 5; x++)
			{
				for (y = x + 1; y <= 6; y++) {

					if (P_SORT[x] == P_SORT[y])
					{
						a[6] += 1;
						break;
					}

				}
			}

			if (a[6] == 1)
			{
				P_PEA_FLG[1] = TRUE;

			}
			else if (a[6] >= 2)
			{
				P_2PEA_FLG = TRUE;
				P_PEA_FLG[0] = FALSE;
			}
		}

		if (P_PEA_FLG[0] == FALSE && P_PEA_FLG[1] == FALSE && P_2PEA_FLG == FALSE && P_3CARD_FLG == FALSE && P_STRAIGHT_FLG == FALSE && P_FLASH_FLG == FALSE && P_FULLHOUSE_FLG == FALSE && P_4CARD_FLG == FALSE && P_SF_FLG == FALSE && P_RSF_FLG == FALSE)
		{
			P_NOPEA_FLG = TRUE;
		}

		a[7] = 1;


	}


		//enemy
		if (a[7] == 1) {

			int x = 0;
			int y = 0;
			int z = 0;
			int v = 0;

			//RSF
			for (x = 7; x <= 10; x++)
			{
				z = 1;
				E_Straight[0] = 0;
				for (y = x + 1; y <= 13; y++)
				{
					if (E_SORT[x] + z == E_SORT[y])
					{
						E_Straight[0] += 1;
						z += 1;
						
					}
				}
			}




			if (E_Straight[0] >= 4 && E_Straight[1] == 14 || E_Straight[1] == 28 || E_Straight[1] == 42 || E_Straight[1] == 56)
			{
				E_RSF_FLG = TRUE;
				a[7] = 2;
			}




			//SF
			if (E_RSF_FLG == FALSE)
			{


				for (x = 7; x <= 10; x++)
				{
					z = 1;
					E_Straight[2] = 0;
					for (y = x + 1; y <= 13; y++)
					{
						if (E_SORT[x] + z == E_SORT[y])
						{
							E_Straight[2] += 1;
							z += 1;
							if (E_Straight[2] >= 4)
							{
								E_SF_FLG = TRUE;
								a[7] = 2;
							}
						}
					}
				}
			}
			//4card
			if (E_SF_FLG == FALSE && E_RSF_FLG == FALSE) {

				for (x = 0; x <= 3; x++)
				{
					for (y = x + 1; y <= 4; y++) {

						if (E_SORT[x] == E_SORT[y])
						{

							for (z = y + 1; z <= 5; z++) {

								if (E_SORT[y] == E_SORT[z])
								{

									for (v = z + 1; v <= 6; v++) {

										if (E_SORT[z] == E_SORT[v])
										{

											E_4CARD_FLG = TRUE;
											a[7] = 2;
										}
									}
								}
							}
						}

					}
				}
			}
			//fullhouse
			if (E_4CARD_FLG == FALSE && E_SF_FLG == FALSE && E_RSF_FLG == FALSE)
			{
				for (x = 0; x <= 3; x++)
				{
					for (y = x + 1; y <= 4; y++) {

						if (E_SORT[x] == E_SORT[y])
						{

							for (z = y + 1; z <= 5; z++) {

								if (E_SORT[y] == E_SORT[z])
								{
									a[13] += 1;
								}
								else if (E_SORT[y] != E_SORT[z])
								{
									a[14] += 1;
								}
							}
						}

					}
				}
				if (a[13] >= 1 && a[14] >= 1)
				{
					E_FULLHOUSE_FLG = TRUE;
					a[7] = 2;
				}

			}
			//flash
			if (E_FULLHOUSE_FLG == FALSE && E_4CARD_FLG == FALSE && E_SF_FLG == FALSE && E_RSF_FLG == FALSE)
			{
				if (E_CARD_S[0] == E_CARD_S[1])
				{
					a[15] += 1;
					a[16] += 1;
				}
				for (x = 0; x <= 4; x++)
				{
					if (E_CARD_S[0] == C_CARD_S[x])
					{
						a[15] += 1;
					}
					if (E_CARD_S[1] == C_CARD_S[x])
					{
						a[16] += 1;
					}
				}
				if (a[15] >= 4 || a[16] >= 4)
				{
					E_FLASH_FLG = TRUE;
					a[7] = 2;
				}

			}
			//straight
			if (E_FLASH_FLG == FALSE && E_FULLHOUSE_FLG == FALSE && E_4CARD_FLG == FALSE && E_SF_FLG == FALSE && E_RSF_FLG == FALSE)
			{

				for (x = 0; x <= 3; x++)
				{
					z = 1;
					E_Straight[3] = 0;
					for (y = x + 1; y <= 6; y++)
					{
						if (E_SORT[x] + z == E_SORT[y])
						{
							E_Straight[3] += 1;
							z += 1;
							if (E_Straight[3] >= 4)
							{
								E_STRAIGHT_FLG = TRUE;
								a[7] = 2;
							}
						}
					}
				}



			}
			//3card
			if (E_STRAIGHT_FLG == FALSE && E_FLASH_FLG == FALSE && E_FULLHOUSE_FLG == FALSE && E_4CARD_FLG == FALSE && E_SF_FLG == FALSE && E_RSF_FLG == FALSE)
			{

				for (x = 0; x <= 3; x++)
				{
					for (y = x + 1; y <= 4; y++) {

						if (E_SORT[x] == E_SORT[y])
						{

							for (z = y + 1; z <= 5; z++) {

								if (E_SORT[y] == E_SORT[z])
								{
									E_3CARD_FLG = TRUE;
									a[7] = 2;
								}
							}
						}

					}
				}
			}
			//pea 2pea
			if (E_3CARD_FLG == FALSE && E_STRAIGHT_FLG == FALSE && E_FLASH_FLG == FALSE && E_FULLHOUSE_FLG == FALSE && E_4CARD_FLG == FALSE && E_SF_FLG == FALSE && E_RSF_FLG == FALSE) {

				for (x = 0; x <= 5; x++)
				{
					for (y = x + 1; y <= 6; y++) {

						if (E_SORT[x] == E_SORT[y])
						{
							a[17] += 1;
							break;
						}

					}
				}

				if (a[17] == 1)
				{
					E_PEA_FLG[1] = TRUE;

				}
				else if (a[17] >= 2)
				{
					E_2PEA_FLG = TRUE;
					E_PEA_FLG[1] = FALSE;
				}
			}

			if (E_PEA_FLG[0] == FALSE && E_PEA_FLG[1] == FALSE && E_2PEA_FLG == FALSE && E_3CARD_FLG == FALSE && E_STRAIGHT_FLG == FALSE && E_FLASH_FLG == FALSE && E_FULLHOUSE_FLG == FALSE && E_4CARD_FLG == FALSE && E_SF_FLG == FALSE && E_RSF_FLG == FALSE)
			{
				E_NOPEA_FLG = TRUE;
			}

			a[7] = 2;



		}

	
}


//
void Porker::GAMEOVER()
{
	if (Round_Count == 4)
	{
		GameOver = TRUE;
	}
	
}


//�A�b�v�f�[�g
AbstractScene* Porker::Update()
{
	if (GameOver == TRUE && PAD_INPUT::OnButton(XINPUT_BUTTON_A))
	{
		return new GameSelect();
	}
	CARD_SETTING2();
	CARD_ANALAYSIS();
	CARD_SORT();
	HAND();
	ROUND_UI();
	WAIT_TIME();
	GAMEOVER();
	if (Round_UI == FALSE) {

		FIRST_BET();
		
		ENEMY_CHOICE();
		ROUND_END();
		

		if (Wait_TimeFLG[0] == FALSE && Wait_TimeFLG[1] == FALSE && Wait_TimeFLG[2] == FALSE)
		{

			

			if (Turn < 5 && Result == FALSE && GameOver == FALSE)
			{
				PLAYER_CHOICE();
				UI();
			}

			
		}
	}
	return this;
}


//�`��
void Porker::Draw() const
{

	DrawGraph(0, 0, BackGround[0], FALSE);

	


	//DrawString(1150, 20, "SCORE", 0x000000);
	SetFontSize(50);
	DrawFormatString(50, 80, 0xffffff, "%d", Round_Count);  //���E���h��
	DrawFormatString(30, 329, 0xffffff, "%d", LastGame);  //���E���h��
	/*DrawFormatString(10, 85, 0xffffff, "%d", Turn);   */       //�^�[����
	DrawFormatString(1140, 580, /*0x000000,*/0xffffff, "%d", Score[0]); //�v���C���[�̃X�R�A
	DrawFormatString(1140, 110, /*0x000000,*/0xffffff, "%d", Score[1]);  //�G�̃X�R�A
	DrawFormatString(1140, 350, /*0x000000,*/0xffffff, "%d", Pot);          //�q���Ă�X�R�A�̍��v



	if (Turn >= 4 && P_RSF_FLG == TRUE)
	{
		SetFontSize(40);
		if (Poker_Second[4] >= 0 && Poker_Second[4] <= 20) {
			DrawString(905, 560, "ROYAL", 0x0055ff, TRUE);
		}
		if (Poker_Second[4] >= 20 && Poker_Second[4] <= 40) {
			DrawString(870, 610, "STRAIGHT", 0xffff1a, TRUE);
		}
		if (Poker_Second[4] >= 40 && Poker_Second[4] <= 60) {
			DrawString(905, 660, "FLUSH", 0xff0000, TRUE);
		}
	}




	if (Turn >= 4 && P_SF_FLG == TRUE)
	{
		SetFontSize(40);
		if (Poker_Second[4] >= 30) {
			DrawString(870, 580, "STRAIGHT", 0xffff1a, TRUE);
			DrawString(905, 630, "FLUSH", 0xffff1a, TRUE);
			DrawString(910, 530, "", 0xffff1a, TRUE);
			DrawString(950, 530, "", 0xffff1a, TRUE);
		}
	}

	if (Turn >= 4 && P_4CARD_FLG == TRUE)
	{
		SetFontSize(40);
		if (Poker_Second[4] >= 30) {
			DrawString(910, 550, "FOUR", 0xffff1a, TRUE);
			DrawString(910, 600, "OF A", 0xffff1a, TRUE);
			DrawString(915, 650, "KIND", 0xffff1a, TRUE);
			DrawString(910, 530, "", 0xffff1a, TRUE);
			DrawString(950, 530, "", 0xffff1a, TRUE);
		}
	}


	if (Turn >= 4 && P_FULLHOUSE_FLG == TRUE)
	{
		SetFontSize(40);
		if (Poker_Second[4] >= 30) {
			DrawString(920, 570, "FULL", 0xff0000, TRUE);
			DrawString(910, 640, "HOUSE", 0xff0000, TRUE);
		}
	}

	if (Turn >= 4 && P_FLASH_FLG == TRUE)
	{
		SetFontSize(40);
		DrawString(890, 600, "FLUSH", 0x00ff2b, TRUE);
	}
	
	if (Turn >= 4 && P_STRAIGHT_FLG == TRUE)
	{
		SetFontSize(40);
		DrawString(870, 600, "STRAIGHT", 0xffff00, TRUE);
	}

	if (Turn >= 4 && P_3CARD_FLG == TRUE)
	{
		SetFontSize(40);
		DrawString(900, 550, "THREE", 0x0055ff, TRUE);
		DrawString(930, 600, "OF", 0x0055ff, TRUE);
		DrawString(915, 650, "KIND", 0x0055ff, TRUE);
	}
	if (Turn >= 4 && P_2PEA_FLG == TRUE)
	{
		SetFontSize(40);
		DrawString(870, 600, "TWO PAIR", 0xffffff, TRUE);
	}
	if (Turn >= 4 && P_PEA_FLG[0] == TRUE || Turn == 4 && P_PEA_FLG[1] == TRUE&& P_2PEA_FLG == FALSE)
	{
		SetFontSize(40);
		DrawString(870, 600, "ONE PAIR", 0xffffff, TRUE);
	}
	if (Turn >= 4 &&P_NOPEA_FLG == TRUE)
	{
		SetFontSize(40);
		DrawString(880, 600, "NO PAIR", 0xffffff, TRUE);
	}


	if (ShowDawn == FALSE)
	{
		SetFontSize(40);
		DrawString(900, 100, "? ? ?", 0xffffff, TRUE);
	}

	if (ShowDawn == FALSE && E_RSF_FLG == TRUE)
	{
		SetFontSize(40);
		if (Poker_Second[4] >= 0 && Poker_Second[4] <= 20) {
			DrawString(905, 160, "ROYAL", 0x0055ff, TRUE);
		}
		if (Poker_Second[4] >= 20 && Poker_Second[4] <= 40) {
			DrawString(870, 210, "STRAIGHT", 0xffff1a, TRUE);
		}
		if (Poker_Second[4] >= 40 && Poker_Second[4] <= 60) {
			DrawString(905, 260, "FLUSH", 0xff0000, TRUE);
		}
	}
	
		if (ShowDawn == FALSE && E_SF_FLG == TRUE)
		{
			SetFontSize(40);
			if (Poker_Second[4] >= 30) {
				DrawString(870, 140, "STRAIGHT", 0xffff1a, TRUE);
				DrawString(905, 190, "FLUSH", 0xffff1a, TRUE);
				DrawString(910, 530, "", 0xffff1a, TRUE);
				DrawString(950, 530, "", 0xffff1a, TRUE);
			}
		}

		if (ShowDawn == FALSE && E_4CARD_FLG == TRUE)
		{
			SetFontSize(40);
			if (Poker_Second[4] >= 30) {
				DrawString(910, 170, "FOUR", 0xffff1a, TRUE);
				DrawString(910, 220, "OF A", 0xffff1a, TRUE);
				DrawString(915, 270, "KIND", 0xffff1a, TRUE);
				DrawString(910, 530, "", 0xffff1a, TRUE);
				DrawString(950, 530, "", 0xffff1a, TRUE);
			}
		}


		if (ShowDawn == FALSE && E_FULLHOUSE_FLG == TRUE)
		{
			SetFontSize(40);
			if (Poker_Second[4] >= 30) {
				DrawString(920, 150, "FULL", 0xff0000, TRUE);
				DrawString(910, 640, "HOUSE", 0xff0000, TRUE);
			}
		}

		if (ShowDawn == FALSE && E_FLASH_FLG == TRUE)
		{
			SetFontSize(40);
			DrawString(890, 120, "FLUSH", 0x00ff2b, TRUE);
		}

		if (ShowDawn == FALSE && E_STRAIGHT_FLG == TRUE)
		{
			SetFontSize(40);
			DrawString(870, 120, "STRAIGHT", 0xffff00, TRUE);
		}

		if (ShowDawn == FALSE && E_3CARD_FLG == TRUE)
		{
			SetFontSize(40);
			DrawString(900, 170, "THREE", 0x0055ff, TRUE);
			DrawString(930, 220, "OF", 0x0055ff, TRUE);
			DrawString(915, 270, "KIND", 0x0055ff, TRUE);
		}
		if (ShowDawn == FALSE && E_2PEA_FLG == TRUE)
		{
			SetFontSize(40);
			DrawString(870, 120, "TWO PAIR", 0xffffff, TRUE);
		}
		if (ShowDawn == FALSE && E_PEA_FLG[0] == TRUE || Turn == 4 && E_PEA_FLG[1] == TRUE && E_2PEA_FLG == FALSE)
		{
			SetFontSize(40);
			DrawString(870, 120, "ONE PAIR", 0xffffff, TRUE);
		}
		if (ShowDawn == FALSE && E_NOPEA_FLG == TRUE)
		{
			SetFontSize(40);
			DrawString(880, 120, "NO PAIR", 0xffffff, TRUE);
		}
	

	                           //�J�[�h//
	SetFontSize(30);
	DrawGraph(460, 495, Tranpu_Img[P_Rand[0]], TRUE); //�v���C���[�̃J�[�h1
	DrawGraph(635, 495, Tranpu_Img[P_Rand[1]], TRUE); //�v���C���[�̃J�[�h2
	DrawFormatString(430, 650, /*0x000000,*/0xffffff, "%d", P_CARD_A[0]);
	DrawFormatString(615, 650, /*0x000000,*/0xffffff, "%d", P_CARD_A[1]);

	//�V���E�_�E�������猻���
	if (ShowDawn == TRUE)
	{
		DrawGraph(460, -10, Tranpu_Img[E_Rand[0]], TRUE);   //�G�̃J�[�h1
		DrawGraph(635, -10, Tranpu_Img[E_Rand[1]], TRUE);   //�G�̃J�[�h2
		DrawFormatString(430, 40, /*0x000000,*/0xffffff, "%d", E_CARD_A[0]);
		DrawFormatString(615, 40, /*0x000000,*/0xffffff, "%d", E_CARD_A[1]);

	}

	//�V���E�_�E�������������
	if (ShowDawn == FALSE) 
	{
		DrawGraph(460, -10, Tranpu_Img[0], TRUE);           //�G�̗��J�[�h1
		DrawGraph(635, -10, Tranpu_Img[0], TRUE);           //�G�̗��J�[�h2
	}
	

	if (Turn >=2)
	{
		DrawGraph(150, 225, Tranpu_Img[C_Rand[0]], TRUE);   //�e�[�u���J�[�h1
		DrawGraph(350, 225, Tranpu_Img[C_Rand[1]], TRUE);   //�e�[�u���J�[�h2
		DrawGraph(550, 225, Tranpu_Img[C_Rand[2]], TRUE);   //�e�[�u���J�[�h3	

		DrawFormatString(150, 470, /*0x000000,*/0xffffff, "%d", P_SORT[7]);
		DrawFormatString(250, 470, /*0x000000,*/0xffffff, "%d", P_SORT[8]);
		DrawFormatString(350, 470, /*0x000000,*/0xffffff, "%d", P_SORT[9]);
		DrawFormatString(450, 470, /*0x000000,*/0xffffff, "%d", P_SORT[10]);
		DrawFormatString(550, 470, /*0x000000,*/0xffffff, "%d", P_SORT[11]);
		DrawFormatString(650, 470, /*0x000000,*/0xffffff, "%d", P_SORT[12]);
		DrawFormatString(750, 470, /*0x000000,*/0xffffff, "%d", P_SORT[13]);

		DrawFormatString(150, 430, /*0x000000,*/0xffffff, "%d", P_SORT[0]);
		DrawFormatString(250, 430, /*0x000000,*/0xffffff, "%d", P_SORT[1]);
		DrawFormatString(350, 430, /*0x000000,*/0xffffff, "%d", P_SORT[2]);
		DrawFormatString(450, 430, /*0x000000,*/0xffffff, "%d", P_SORT[3]);
		DrawFormatString(550, 430, /*0x000000,*/0xffffff, "%d", P_SORT[4]);
		DrawFormatString(650, 430, /*0x000000,*/0xffffff, "%d", P_SORT[5]);
		DrawFormatString(750, 430, /*0x000000,*/0xffffff, "%d", P_SORT[6]);

		//DrawFormatString(150, 430, /*0x000000,*/0xffffff, "%d", P_SORT2[0]);
		//DrawFormatString(250, 430, /*0x000000,*/0xffffff, "%d", P_SORT2[1]);
		//DrawFormatString(350, 430, /*0x000000,*/0xffffff, "%d", P_SORT2[2]);
		//DrawFormatString(450, 430, /*0x000000,*/0xffffff, "%d", P_SORT2[3]);
		//DrawFormatString(550, 430, /*0x000000,*/0xffffff, "%d", P_SORT2[4]);
		

	}
	if (Turn >= 3)
	{
		DrawGraph(750, 225, Tranpu_Img[C_Rand[3]], TRUE);   //�e�[�u���J�[�h4
	}
	if (Turn >= 4)
	{
		DrawGraph(950, 225, Tranpu_Img[C_Rand[4]], TRUE);   //�e�[�u���J�[�h3
	}


	                       //���U���g���//

	if (Result == TRUE)
	{
		DrawBox(0, 0, 1280, 720, 0xffffff, TRUE);
		SetFontSize(40);
		DrawString(580, 200, "RESULT", 0x000000, TRUE);
		SetFontSize(30);
		DrawString(480, 650, "A�{�^����NEXT ROUND", 0x000000, TRUE);
	}


	if (GameOver == TRUE)
	{
		DrawBox(0, 0, 1280, 720, 0xffffff, TRUE);
		SetFontSize(40);
		DrawString(580, 200, "GameOver", 0x000000, TRUE);
		SetFontSize(30);
		DrawString(480, 650, "A�{�^����Game Select", 0x000000, TRUE);
	}



	                        //      UI     //

	//�V���E�_�E��UI
	if (ShowDawnUI == TRUE)
	{
		DrawBox(250, 250, 980, 500, 0xffffff, TRUE);
		DrawBox(250, 250, 980, 500, 0x000000, FALSE);
		SetFontSize(50);
		DrawString(520, 300, "SHOW DAWN", 0x000000, TRUE);
	}


	//Round1�\��UI
	if (Round_UI == TRUE && Round_Count == 1)
	{
		DrawBox(0, 0, 1280, 720, 0x000000, TRUE);
		//11pea
		if (P_PEA_FLG[0] == TRUE && P_CARD_A[0] == 11)
		{
			if (Poker_Second[3] >= 30) {
				SetFontSize(40);
				DrawString(580, 100, "ROUND1", 0x0055ff, TRUE);
				SetFontSize(30);
				DrawString(485, 650, "Press the A button", 0x0055ff, TRUE);
			}
		}
	
		//12pea
		else if (P_PEA_FLG[0] == TRUE && P_CARD_A[0] == 12)
		{
			if (Poker_Second[3] >= 30) {
				SetFontSize(40);
				DrawString(580, 100, "ROUND1", 0xffff00, TRUE);
				SetFontSize(30);
				DrawString(485, 650, "Press the A button", 0xffff00, TRUE);
			}
		}

		//13pea
		else if (P_PEA_FLG[0] == TRUE && P_CARD_A[0] == 13)
		{
			
			if (Poker_Second[3] >= 30) {
				SetFontSize(40);
				DrawString(580, 100, "ROUND1", 0x00ff2b, TRUE);
				SetFontSize(30);
				DrawString(485, 650, "Press the A button", 0x00ff2b, TRUE);
			}
			
				SetFontSize(60);
				DrawString(530, 320, "CHANCE!", 0x00ff2b, TRUE);
			
			
		}

		//14pea
		else if (P_PEA_FLG[0] == TRUE && P_CARD_A[0] == 14)
		{
	
			if (Poker_Second[3] >= 30) {
				SetFontSize(40);
				DrawString(580, 100, "ROUND1", 0xff0000, TRUE);
				SetFontSize(30);
				DrawString(485, 650, "Press the A button", 0xff0000, TRUE);
			}

			
				SetFontSize(70);
				DrawString(450, 350, "SUPER HOT!!", 0xff0000, TRUE);
		
		}

		//nomal pea
		else if (P_PEA_FLG[0] == TRUE && P_CARD_A[0] <= 10) {
			if (Poker_Second[3] >= 30) {
				SetFontSize(40);
				DrawString(580, 100, "ROUND1", 0xffffff, TRUE);
				SetFontSize(30);
				DrawString(485, 650, "Press the A button", 0xffffff, TRUE);
			}
		}

		//no pea
		else if (P_PEA_FLG[0] == FALSE) {
			SetFontSize(40);
			DrawString(580, 100, "ROUND1", 0xffffff, TRUE);
			SetFontSize(30);
			DrawString(485, 650, "Press the A button", 0xffffff, TRUE);
		}

		//RSF
		if (P_RSF_FLG == TRUE)
		{
			DrawGraph(0, 0, BackGround[2], FALSE);
			SetFontSize(40);
			DrawString(580, 100, "ROUND1", 0x000000, TRUE);
			SetFontSize(30);
			DrawString(485, 650, "Press the A button", 0x000000, TRUE);
		}
	}
	//Round2�\��UI
	if (Round_UI == TRUE && Round_Count == 2)
	{
		DrawBox(0, 0, 1280, 720, 0x000000, TRUE);
		//11pea
		if (P_PEA_FLG[0] == TRUE && P_CARD_A[0] == 11)
		{
			if (Poker_Second[3] >= 30) {
				SetFontSize(40);
				DrawString(580, 100, "ROUND2", 0x0055ff, TRUE);
				SetFontSize(30);
				DrawString(485, 650, "Press the A button", 0x0055ff, TRUE);
			}
		}

		//12pea
		else if (P_PEA_FLG[0] == TRUE && P_CARD_A[0] == 12)
		{
			if (Poker_Second[3] >= 30) {
				SetFontSize(40);
				DrawString(580, 100, "ROUND2", 0xffff00, TRUE);
				SetFontSize(30);
				DrawString(485, 650, "Press the A button", 0xffff00, TRUE);
			}
		}

		//13pea
		else if (P_PEA_FLG[0] == TRUE && P_CARD_A[0] == 13)
		{

			if (Poker_Second[3] >= 30) {
				SetFontSize(40);
				DrawString(580, 100, "ROUND1", 0x00ff2b, TRUE);
				SetFontSize(30);
				DrawString(485, 650, "Press the A button", 0x00ff2b, TRUE);
			}
			
				SetFontSize(60);
				DrawString(530, 320, "CHANCE!", 0x00ff2b, TRUE);
			

		}

		//14pea
		else if (P_PEA_FLG[0] == TRUE && P_CARD_A[0] == 14)
		{

			if (Poker_Second[3] >= 30) {
				SetFontSize(40);
				DrawString(580, 100, "ROUND2", 0xff0000, TRUE);
				SetFontSize(30);
				DrawString(485, 650, "Press the A button", 0xff0000, TRUE);
			}

			
				SetFontSize(70);
				DrawString(450, 350, "SUPER HOT!!", 0xff0000, TRUE);
			
		}

		//nomal pea
		else if (P_PEA_FLG[0] == TRUE && P_CARD_A[0] <= 10) {
			if (Poker_Second[3] >= 30) {
				SetFontSize(40);
				DrawString(580, 100, "ROUND2", 0xffffff, TRUE);
				SetFontSize(30);
				DrawString(485, 650, "Press the A button", 0xffffff, TRUE);
			}
		}

		//no pea
		else if (P_PEA_FLG[0] == FALSE) {
			SetFontSize(40);
			DrawString(580, 100, "ROUND2", 0xffffff, TRUE);
			SetFontSize(30);
			DrawString(485, 650, "Press the A button", 0xffffff, TRUE);
		}
	}
	//Round3�\��UI
	if (Round_UI == TRUE && Round_Count == 3)
	{
		DrawBox(0, 0, 1280, 720, 0x000000, TRUE);
		//11pea
		if (P_PEA_FLG[0] == TRUE && P_CARD_A[0] == 11)
		{
			if (Poker_Second[3] >= 30) {
				SetFontSize(40);
				DrawString(580, 100, "ROUND3", 0x0055ff, TRUE);
				SetFontSize(30);
				DrawString(485, 650, "Press the A button", 0x0055ff, TRUE);
			}
		}

		//12pea
		else if (P_PEA_FLG[0] == TRUE && P_CARD_A[0] == 12)
		{
			if (Poker_Second[3] >= 30) {
				SetFontSize(40);
				DrawString(580, 100, "ROUND3", 0xffff00, TRUE);
				SetFontSize(30);
				DrawString(485, 650, "Press the A button", 0xffff00, TRUE);
			}
		}

		//13pea
		else if (P_PEA_FLG[0] == TRUE && P_CARD_A[0] == 13)
		{

			if (Poker_Second[3] >= 30) {
				SetFontSize(40);
				DrawString(580, 100, "ROUND3", 0x00ff2b, TRUE);
				SetFontSize(30);
				DrawString(485, 650, "Press the A button", 0x00ff2b, TRUE);
			}
			
				SetFontSize(60);
				DrawString(530, 320, "CHANCE!", 0x00ff2b, TRUE);
			

		}

		//14pea
		else if (P_PEA_FLG[0] == TRUE && P_CARD_A[0] == 14)
		{

			if (Poker_Second[3] >= 30) {
				SetFontSize(40);
				DrawString(580, 100, "ROUND3", 0xff0000, TRUE);
				SetFontSize(30);
				DrawString(485, 650, "Press the A button", 0xff0000, TRUE);
			}

		
				SetFontSize(70);
				DrawString(450, 350, "SUPER HOT!!", 0xff0000, TRUE);
			
		}

		//nomal pea
		else if (P_PEA_FLG[0] == TRUE && P_CARD_A[0] <= 10) {
			if (Poker_Second[3] >= 30) {
				SetFontSize(40);
				DrawString(580, 100, "ROUND3", 0xffffff, TRUE);
				SetFontSize(30);
				DrawString(485, 650, "Press the A button", 0xffffff, TRUE);
			}
		}

		//no pea
		else if (P_PEA_FLG[0] == FALSE) {
			SetFontSize(40);
			DrawString(580, 100, "ROUND3", 0xffffff, TRUE);
			SetFontSize(30);
			DrawString(485, 650, "Press the A button", 0xffffff, TRUE);
		}
	}


	//FB�\��UI
	if (FB_UI == 1)
	{
		DrawBox(300, 200, 980, 500, 0x00d5ff, TRUE);
		DrawBox(300, 200, 980, 500, 0x000000, FALSE);
		SetFontSize(30);
		DrawString(510, 230, "PLAYER'S BLIND BET", 0x000000, TRUE);
		DrawFormatString(580, 340, 0x000000,"COST:%d",a[5]);
		DrawFormatString(350, 450, 0x000000, "SCORE:%d", Score[0] + a[5]);
		DrawString(620, 450, "��", 0x000000, TRUE);
		DrawFormatString(800, 450, 0x000000, "SCORE:%d", Score[0]);
	}
	if (FB_UI == 2)
	{
		DrawBox(300, 200, 980, 500, 0xff00aa, TRUE);
		DrawBox(300, 200, 980, 500, 0x000000, FALSE);
		SetFontSize(30);
		DrawString(515, 230, "ENEMY'S BLIND BET", 0x000000, TRUE);
		DrawFormatString(580, 340, 0x000000, "COST:%d", a[5]);
		DrawFormatString(350, 450, 0x000000, "SCORE:%d", Score[1] + a[5]);
		DrawString(620, 450, "��", 0x000000, TRUE);
		DrawFormatString(800, 450, 0x000000, "SCORE:%d", Score[1]);
	}


	//�x�b�g�m�FUI
	if (CheckUI[0] == TRUE) 
	{
		DrawBox(0, 0, 1280, 720, 0x000000, TRUE);
		SetFontSize(40);
		DrawString(470, 150, "�x�b�g���܂����H", 0xffffff, TRUE);
		DrawString(250, 450, "YES", 0xffffff, TRUE);
		DrawString(1000, 450, "NO", 0xffffff, TRUE);
		SetFontSize(30);
		DrawString(420, 650, "�\���L�[�őI��,A�{�^���Ō���", 0xffffff, TRUE);
		

		//������
		if (Cursor[0] == 1) 
		{
			DrawTriangle(180, 420, 210, 470, 180, 520, GetColor(255, 0, 0), TRUE);

		}
		//�E����
		if (Cursor[0] == 0)
		{
			DrawTriangle(930, 420, 960, 470, 930, 520, GetColor(255, 0, 0), TRUE);

		}
		
	}
	
	//���C�Y�m�FUI
	if (CheckUI[1] == TRUE)
	{
		DrawBox(0, 0, 1280, 720, 0x000000, TRUE);
		SetFontSize(40);
		DrawString(470, 150, "���C�Y���܂����H", 0xffffff, TRUE);
		DrawString(250, 450, "YES", 0xffffff, TRUE);
		DrawString(1000, 450, "NO", 0xffffff, TRUE);
		SetFontSize(30);
		DrawString(420, 650, "�\���L�[�őI��,A�{�^���Ō���", 0xffffff, TRUE);
		//������
		if (Cursor[0] == 1)
		{
			DrawTriangle(180, 420, 210, 470, 180, 520, GetColor(255, 0, 0), TRUE);
		}
		//�E����
		if (Cursor[0] == 0)
		{
			DrawTriangle(930, 420, 960, 470, 930, 520, GetColor(255, 0, 0), TRUE);
		}
	}

	//�t�H�[���h�m�FUI
	if (CheckUI[2] == TRUE)
	{
		DrawBox(0, 0, 1280, 720, 0x000000, TRUE);
		SetFontSize(40);
		DrawString(460, 150, "�t�H�[���h���܂����H", 0xffffff, TRUE);
		DrawString(250, 450, "YES", 0xffffff, TRUE);
		DrawString(1000, 450, "NO", 0xffffff, TRUE);
		SetFontSize(30);
		DrawString(420, 650, "�\���L�[�őI��,A�{�^���Ō���", 0xffffff, TRUE);
		//������
		if (Cursor[0] == 1)
		{
			DrawTriangle(180, 420, 210, 470, 180, 520, GetColor(255, 0, 0), TRUE);
		}
		//�E����
		if (Cursor[0] == 0)
		{
			DrawTriangle(930, 420, 960, 470, 930, 520, GetColor(255, 0, 0), TRUE);
		}
	}

	//�x�b�g�\��UI
	if (Action_UI == 1)
	{
		DrawBox(300, 200, 980, 500, 0x00d5ff, TRUE);
		DrawBox(300, 200, 980, 500, 0x000000, FALSE);
		SetFontSize(30);
		DrawString(600, 200, "Player", 0x000000, TRUE);
		DrawString(620, 300, "BET", 0x000000, TRUE);
		DrawFormatString(350, 400, 0x000000, "SCORE:%d", Score[0] + a[2]);
		DrawString(620, 400, "��", 0x000000, TRUE);
		DrawFormatString(800, 400, 0x000000, "SCORE:%d", Score[0]);
	}

	//���C�Y�\��UI
	if (Action_UI == 2)
	{

		DrawBox(300, 200, 980, 500, 0x00d5ff, TRUE);
		DrawBox(300, 200, 980, 500, 0x000000, FALSE);
		SetFontSize(30);
		DrawString(600, 200, "Player", 0x000000, TRUE);
		DrawString(610, 300, "RAISE", 0x000000, TRUE);
		DrawFormatString(350, 400, 0x000000, "SCORE:%d", Score[0] + a[2]);
		DrawString(620, 400, "��", 0x000000, TRUE);
		DrawFormatString(800, 400, 0x000000, "SCORE:%d", Score[0]);
	}

	//�t�H�[���h�\��UI
	if (Action_UI == 3)
	{
		DrawBox(300, 200, 980, 500, 0x00d5ff, TRUE);
		DrawBox(300, 200, 980, 500, 0x000000, FALSE);
		SetFontSize(30);
		DrawString(600, 200, "Player", 0x000000, TRUE);
		DrawString(610, 300, "FOLD", 0x000000, TRUE);
		DrawFormatString(350, 400, 0x000000, "SCORE:%d", Score[0] + a[2]);
		DrawString(620, 400, "��", 0x000000, TRUE);
		DrawFormatString(800, 400, 0x000000, "SCORE:%d", Score[0]);
	}

	//�G�R�[���\��UI
	if (Action_UI == 4)
	{
		DrawBox(300, 200, 980, 500, 0xff00aa, TRUE);
		DrawBox(300, 200, 980, 500, 0x000000, FALSE);
		SetFontSize(30);
		DrawString(600, 200, "ENEMY", 0x000000, TRUE);
		DrawString(605, 300, "CALL", 0x000000, TRUE);
		DrawFormatString(350, 400, 0x000000, "SCORE:%d", Score[1] + a[2]);
		DrawString(620, 400, "��", 0x000000, TRUE);
		DrawFormatString(800, 400, 0x000000, "SCORE:%d", Score[1]);
	}

	//�G�t�H�[���h�\��UI
	if (Action_UI == 5)
	{
		DrawBox(300, 200, 980, 500, 0xff00aa, TRUE);
		DrawBox(300, 200, 980, 500, 0x000000, FALSE);
		SetFontSize(30);
		DrawString(600, 200, "ENEMY", 0x000000, TRUE);
		DrawString(605, 300, "FOLD", 0x000000, TRUE);
		DrawFormatString(350, 400, 0x000000, "SCORE:%d", Score[1] + a[2]);
		DrawString(620, 400, "��", 0x000000, TRUE);
		DrawFormatString(800, 400, 0x000000, "SCORE:%d", Score[1]);
	}


}


