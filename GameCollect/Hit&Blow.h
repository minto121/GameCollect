#pragma once
#include"AbstractScene.h"

class HitAndBlow : public AbstractScene {
private:
	/* �摜�ǂݍ��� */
	int ColorImg[6]; // �F�̋�̉摜�z��
	int HitBlowImg[2]; // �q�b�g�s���ƃu���[�s���̉摜�����z��
	int TableBgImg; // �w�i��ʂ̉摜�����ϐ�
	int BoardImg; // �{�[�h�摜�����ϐ�

	/* �ϐ� */
	int Color[6]; // �F�̋������z��
	int Answer[4];  // �F�Əꏊ�𓖂Ă�z��
	int Reasoning[4];  // �F�Əꏊ�𐄗�����z��
	int SaveReasoning[8][4]; // �F�Əꏊ�����肵���z��
	int SaveHit[8]; // ���̃^�[���̃q�b�g���������i�[
	int SaveBlow[8];// ���̃^�[���̃u���[���������i�[
	int SaveColor; // �m�肵���F��\��
	int DecisionFlg;  // ��������t���O
	int Hit;     // �q�b�g���𐔂���ϐ�
	int Blow;    // �u���[���𐔂���ϐ�
	int WarpPosition;  // ������悤�Ƃ��Ă���ꏊ�̕ϐ�
	int SidePosition;  // �F��I������ꏊ�̕ϐ�
	int Turns; // �^�[�����𐔂���ϐ�
	int count; // ���ԊǗ�����ϐ�
	int ChangeColor; // �F���S�������������A���Ԃ��������ւ��邽�߂̕ϐ�
	int MoveFlg; // ��U��U���߂�t���O
	bool TurnFlg; // �^�[���������߂�t���O

public:
	// �C���N�������g
	HitAndBlow();
	// �f�N�������g
	~HitAndBlow();
	// �`��ȊO���A�b�v�f�[�g
	AbstractScene* Update();
	// �`����A�b�v�f�[�g
	void Draw() const override;

	// �����_���ɐ����̐F�Əꏊ�A���Ԃ����߂�֐�
	void RandomDecision();

	// ����̊֐�
	void Judgment();

	// �G�̗\�z������֐�
	void ERandomChoice();

	//// ���Ԍ��߂�֐�
	//void FirstMove();

	// �F�����Z�b�g����֐�
	void ResetColor();

};