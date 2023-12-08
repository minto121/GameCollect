#include "Porker.h"
#include"DxLib.h"
#include"PadInput.h"
#include<stdlib.h>
#include"math.h"


Porker::Porker()
{
	
	Round_Count = 1;//���E���h��
	
	ROUND_INIT();//���E���h������
}


Porker::~Porker()
{

}


//���E���h������
void Porker::ROUND_INIT()
{

  //�q���Ă�X�R�A�̍��v�@
  Pot = 0;         


  Wait_TimeFLG = FALSE;


   //�������E���h��1�Ȃ珉�������X�R�A��1000�ɂȂ� Score[0]���v���C���[�AScore[1]���G
  if (Round_Count == 1) {             
	  for (int x = 0; x <= 1; x++)
	  {
		  Score[x] = 2500;           
	  }
  }


  // �K���ȕϐ��̔��p
  for (int x = 0; x <= 9; x++)
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


  //�G�̑I��(0���R�[���A1�����C�Y�A2���t�H�[���h)
  for (int x = 0; x <= 2; x++)
  {
	  Enemy_Choice[x] = FALSE;
  }


  //�ҋ@���ԗp
  for (int x = 0; x <= 1; x++)
  {
	  Poker_Second[x] = FALSE;
  }

}


//�ŏ��ɕ����Q����
void Porker::FIRST_BET()
{
	//���E���h1
	if (Round_Count == 1 && a[1] == 0)
	{
		for (int x = 0; x <= 1; x++)
		{
			Score[x] = Score[x] - 100;
			Pot += 100;

		}
		a[1] = 1;
	}

	//���E���h2
	if (Round_Count == 2 && a[1] == 1)
	{
		for (int x = 0; x <= 1; x++)
		{
			Score[x] = Score[x] - 100;
			Pot += 200;
		}
		a[1] = 2;
	}

	//���E���h3
	if (Round_Count == 3 && a[1] == 2)
	{
		for (int x = 0; x <= 1; x++)
		{
			Score[x] = Score[x] - 500;
			Pot += 400;
		}
		a[1] = 3;
	}

}


//���E���h���̏���
void Porker::ROUND()
{
	//1���E���h��




}


//�J�[�h
void Porker::CARD_SETTING()
{
	//�ŏ��ɔz����J�[�h�G�������ꂼ��2������
	if (a[0] == 0) {
		P_Rand[0] = GetRand(55);   //�v���C���[�̃z�[���J�[�h1

		P_Rand[1] = GetRand(55);   //�v���C���[�̃z�[���J�[�h2

		E_Rand[0] = GetRand(55);   //�G�̃z�[���J�[�h1

		E_Rand[1] = GetRand(55);   //�G�̃z�[���J�[�h2

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
		a[0] = 1;
	}

	//�ŏ���Rand�łƂ�������14�Ŋ���
	if (a[0] == 1) 
	{
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
	}



	C_Rand[0] = GetRand(55);   //�R�~���j�e�B�J�[�h1

	C_Rand[1] = GetRand(55);   //�R�~���j�e�B�J�[�h2

	C_Rand[2] = GetRand(55);   //�R�~���j�e�B�J�[�h3

	C_Rand[3] = GetRand(55);   //�R�~���j�e�B�J�[�h4

	C_Rand[4] = GetRand(55);  //�R�~���j�e�B�J�[�h5   

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
			Player_Choice[1] = TRUE;//�x�b�g�t���O
			Cursor[0] = 0;
			CheckUI[1] = FALSE;
		}

		//A�{�^���Ō���(�t�H�[���h)
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_A) && CheckUI[2] == TRUE) {
			Player_Choice[2] = TRUE;//�x�b�g�t���O
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
		//���E���h1�Ȃ�
		if (Round_Count == 1) {
			Score[0] = Score[0] - 100;
			Pot = Pot + 100;
		}

		//���E���h2�Ȃ�
		if (Round_Count == 2) {
			Score[0] = Score[0] - 200;
			Pot = Pot + 200;
		}

		//���E���h3�Ȃ�
		if (Round_Count == 3) {
			Score[0] = Score[0] - 300;
			Pot = Pot + 300;
		}

		Player_Choice[0] = FALSE;
		Wait_TimeFLG = TRUE;
	}

	//���C�Y�Ȃ�
	if (Player_Choice[1] == TRUE)
	{
		//���E���h1�Ȃ�
		if (Round_Count == 1) {
			Score[0] = Score[0] - 200;
			Pot = Pot + 200;
		}

		//���E���h2�Ȃ�
		if (Round_Count == 2) {
			Score[0] = Score[0] - 300;
			Pot = Pot + 300;
		}

		//���E���h3�Ȃ�
		if (Round_Count == 3) {
			Score[0] = Score[0] - 400;
			Pot = Pot + 400;
		}

		Player_Choice[1] = FALSE;
		Wait_TimeFLG = TRUE;
	}

	//�t�H�[���h�Ȃ�
	if (Player_Choice[2] == TRUE)
	{
		Score[1] = Score[1] + Pot;
		Pot = 0;
		Player_Choice[2] = FALSE;
		ROUND_INIT();
		Round_Count = Round_Count + 1;
	}

}


//�G�̑I��
void Porker::ENEMY_CHOICE()
{


}


//�҂�����
void Porker::WAIT_TIME()
{
	//�v���C���[�̌����
	if (Wait_TimeFLG == TRUE)
	{

		Poker_Second[0]++;

		if (Poker_Second[0] > 60)
		{
			
			

		}
		if (Poker_Second[0] == 120)
		{
			Wait_TimeFLG = FALSE;
		}
	}

}

//�A�b�v�f�[�g
AbstractScene* Porker::Update()
{

	CARD_SETTING();
	FIRST_BET();
	UI();
	PLAYER_CHOICE();
	return this;
}


//�`��
void Porker::Draw() const
{
	DrawFormatString(10, 15, 0xffffff, "ROUND:%d", Round_Count); //���E���h��
	DrawFormatString(1120, 600, 0xffffff, "PLAYER:%d", Score[0]);//�v���C���[�̃X�R�A
	DrawFormatString(1120, 100, 0xffffff, "ENEMY:%d", Score[1]); //�G�̃X�R�A
	DrawFormatString(1150, 350, 0xffffff, "POT:%d",Pot); //�q���Ă�X�R�A�̍��v

	DrawFormatString(400, 600, 0xffffff, "P_CARD1:%d", P_Rand[0]); //�v���C���[�̃J�[�h1
	DrawFormatString(600, 600, 0xffffff, "P_CARD2:%d", P_Rand[1]); //�v���C���[�̃J�[�h2
	DrawFormatString(400, 0, 0xffffff, "E_CARD1:%d", E_Rand[0]); //�G�̃J�[�h1
	DrawFormatString(600, 0, 0xffffff, "E_CARD2:%d", E_Rand[1]); //�G�̃J�[�h2
	
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

}


