#pragma once
#include "AbstractScene.h"
#include "gomoku_TitleScene.h"
class gomokuScene : public AbstractScene
{
private:
	int TitleImg; // �w�i�摜
	int wTopImg; // ���΂̉摜
	int bTopImg; // ���΂̉摜
	int gomoku_BackImg; // �Ֆʉ摜
	int gomoku_HelpImg1; // �w���v���1
	int gomoku_HelpImg2; // �w���v���2
	int cX; // �J�[�\��x���W
	int cY; // �J�[�\���Ֆ�y���W
	int g_OldKey;
	int g_NowKey;
	int g_KeyFlg;
	int bCount; // ���΂̐�
	int wCount; // ���΂̐�
	bool gomoku_TurnSetFlg; // ���������߂�t���O
	int gomoku_Turn; // ���݂̃^�[��
	int gomoku_PlayerTurn; // �v���C���[�^�[��
	int gomoku_Pfs; // �v���C���[�̊�� ������:1 ������:2
	int gomoku_AITurn; // AI�̃^�[��
	int gomoku_Efs; // �G�l�~�[(AI)�̊�� ������:1 ������:2
	int gomoku_Banmen[13][13]; // �Ֆ�[x][y]
	int gomoku_Phase; // ��U:0 ��U:1
	int gomoku_Battle; // ������:0	���̏���:1 ���̏���:2
	int gomoku_AI_MoveX; // AIx���W
	int gomoku_AI_MoveY; // AIy���W
	int gomoku_AImove_Point; // AI�̕]���l
	int gomoku_AI_think; // �s�����I��������ǂ����m�F����ϐ�(0:�s���� 1:�s���ς�)
	int Key_Count = 0; // ���͂��s��ꂽ��
	int gomoku_Player_WaitTime; // �v���C���[�̃N�[���^�C��
	int gomoku_AI_WaitTime; // // AI�̃N�[���^�C��
	int gomoku_Result_WaitTime; // ���U���g�̃N�[���^�C��
	int gomoku_elapsedturn; // �o�߃^�[�����J�E���g����ϐ�
	int gomoku_Cursordisplaytime; // �J�[�\���ɓ�������������
	int gomoku_BGM1; // �v���C����BGM
	int gomoku_SE1; // �w���v��ʕ\�����ɏo����
	int gomoku_SE2; // �w���v��ʂ����Ƃ��ɏo����
	int gomoku_SoundStart; // BGM������Ă��邩�ǂ���(0:�Đ�����Ă��Ȃ� 1:�Đ���)
	bool gomoku_HelpDisplayflg; // �w���v��ʂ��J����Ă��邩�ǂ����̃t���O(0:�Q�[����� 1:�w���v���)
	int gomokuHelp_Number; // ���݂̃w���v��ʂ̃y�[�W�ԍ�
	int gomoku_HelpWaitTime; // �w���v��ʂ̃N�[���^�C��
	int gomoku_ScrollWaitTime; // �w���v��ʂ̃y�[�W���߂��������ɔ�������N�[���^�C��
	int gomoku_ScrollSE; // �X�N���[������SE
public:
	gomokuScene();
	~gomokuScene();
	AbstractScene* Update() override;
	void Draw() const override;
	/*void gomoku_Player_Turn();
	void gomoku_AI_Turn();*/
};

