#pragma once
#include "AbstractScene.h"
#include"DxLib.h"
#include"gomoku_TitleScene.h"
class gomoku_HelpScene : public AbstractScene
{
private:
	int gomokuHelp_BackImg1; // �w���v��ʂ̔w�i�摜1
	int gomokuHelp_BackImg2; // �w���v��ʂ̔w�i�摜2
	int gomokuHelp_MenuNumber; // �w���v��ʂ̃y�[�W�ԍ�
	int gomokuHelp_SelectWaitTIme; // �w���v��ʂ�I���������̃N�[���^�C��
	int g_OldKey;
	int g_NowKey;
	int g_KeyFlg;
	int gomoku_HelpSE1; // �w���v��ʂŉ�ʂ�ς���Ƃ��ɗ���
	int gomoku_HelpSE2; // �w���v��ʂ����Ƃ��ɗ���
	int gomokuHelp_ScrollWaitTIme; // �w���v��ʂ̃y�[�W���X�N���[���������̃N�[���^�C��
public:
	gomoku_HelpScene();
	~gomoku_HelpScene();
	AbstractScene* Update() override;
	void Draw() const override;
};

