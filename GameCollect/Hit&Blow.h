#pragma once
#include"AbstractScene.h"

class HitAndBlow : public AbstractScene {
private:
	int ColorImg[6]; // �F�̋�̉摜�z��
	int Color[6]; // �F�̋������z��
	int Answer[4];  // �F�Əꏊ�𓖂Ă�z��
	int Reasoning[4];  // �F�Əꏊ�𐄗�����z�� 
	int Hit;     // �q�b�g���𐔂���ϐ�
	int Blow;    // �u���[���𐔂���ϐ�
	int HitImg;  // �q�b�g�s���̉摜�\��
	int BlowImg; // �u���[�s���̉摜�\��

public:
	// �C���N�������g
	HitAndBlow();
	// �f�N�������g
	~HitAndBlow();
	// �`��ȊO���A�b�v�f�[�g
	AbstractScene* Update();
	// �`����A�b�v�f�[�g
	void Draw() const override;
};