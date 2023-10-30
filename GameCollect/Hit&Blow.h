#pragma once
#include"AbstractScene.h"

class HitAndBlow : public AbstractScene {
private:
	/* �摜�ǂݍ��� */
	int ColorImg[6]; // �F�̋�̉摜�z��
	int HitImg;  // �q�b�g�s���̉摜�\��
	int BlowImg; // �u���[�s���̉摜�\��

	/* �ϐ� */
	int Color[6]; // �F�̋������z��
	int Answer[4];  // �F�Əꏊ�𓖂Ă�z��
	int Reasoning[4];  // �F�Əꏊ�𐄗�����z��
	int SaveReasoning[4][8]; // �F�����肵���z��
	int SaveColor; // �m�肵���F��\��
	int ColorDecision; // �F�̏ꏊ����ϐ�
	int DecisionFlg;  // ��������t���O
	int Hit;     // �q�b�g���𐔂���ϐ�
	int Blow;    // �u���[���𐔂���ϐ�
	int WarpPosition;  // ������悤�Ƃ��Ă���ꏊ�̕ϐ�
	int SidePosition;  // �F��I������ꏊ�̕ϐ�
	int Change;  // �������鎞�Ɏg���ϐ�
	int Turns; // �^�[�����𐔂���ϐ�
	int ColorFlg; // �F����ꂽ���m�F����t���O

public:
	// �C���N�������g
	HitAndBlow();
	// �f�N�������g
	~HitAndBlow();
	// �`��ȊO���A�b�v�f�[�g
	AbstractScene* Update();
	// �`����A�b�v�f�[�g
	void Draw() const override;

	// �����_���ɐ����̐F�Əꏊ���߂�֐�
	void RandomDecision();
};