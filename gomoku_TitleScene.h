#pragma once
#include "AbstractScene.h"
#include"DxLib.h"
#include"gomokuScene.h"
#include"gomoku_HelpScene.h"
class gomokuTitle : public AbstractScene
{
private:
	int gomokuTitle_Back; // �^�C�g����ʂ̔w�i�摜
	int gomokuMenuY; // ���j���[�J�[�\����Y���W
	int gomokuTitle_MenuNumber; // �^�C�g����ʂ̃��j���[�̔ԍ�(0:���C�� 1:�w���v 2:�o�b�N)
	int g_OldKey;
	int g_NowKey;
	int g_KeyFlg;
	int gomoku_transitionTime; // ��ʑJ�ڂ̃N�[���^�C��
	int gomoku_inputWaitTime; // ���͂������̃N�[���^�C��
	int gomoku_TitleSE1; // ���[�h�Z���N�g���ɗ���
	int gomoku_TitleSE2; // ���[�h�����肵�����ɗ���
public:
	gomokuTitle();
	~gomokuTitle();
	AbstractScene* Update() override;
	void Draw() const override;
};

