#pragma once
#include"AbstractScene.h"

class HitAndBlow : public AbstractScene {
private:
	/* �摜�ǂݍ��� */
	int ColorImg[6]; // �F�̋�̉摜�z��
	int HitBlowImg[2]; // �q�b�g�s���ƃu���[�s���̉摜�����z��
	int TableBgImg; // �w�i��ʂ̉摜�����ϐ�
	int BoardImg; // �{�[�h�摜�����ϐ�

	/* SE */
	int PutPinSE; // �s����u��SE
	int HitPinSE; // �q�b�g�s����SE
	int BlowPinSE; // �u���[�s����SE

	/* �z�� */
	int Color[6]; // �F�̋������z��
	int Answer[4];  // �F�Əꏊ�𓖂Ă�z��
	int Reasoning[4];  // �F�Əꏊ�𐄗�����z��
	int SaveReasoning[8][4]; // �F�Əꏊ�����肵���z��
	int SaveHit[8]; // ���̃^�[���̃q�b�g���������i�[
	int SaveBlow[8];// ���̃^�[���̃u���[���������i�[
	/* �ϐ� */
	int SaveColor; // �m�肵���F��\��
	int DecisionFlg;  // ��������t���O
	int Hit;     // �q�b�g���𐔂���ϐ�
	int Blow;    // �u���[���𐔂���ϐ�
	int WarpPosition;  // ������悤�Ƃ��Ă���ꏊ�̕ϐ�
	int SidePosition;  // �F��I������ꏊ�̕ϐ�
	int Turns; // �^�[�����𐔂���ϐ�
	int ChangeColor; // �F���S�������������A���Ԃ��������ւ��邽�߂̕ϐ�
	int Count; // ��ʑJ�ڂ̎��ԊǗ�����ϐ�
	int Covering; // �F�Əꏊ����ĂȂ����m�F���鎞�ɕK�v�ȕϐ�
	int MoveFlg; // ��U��U���߂�t���O(0:�G�l�~�[�^�[�� 1:�v���C���[�^�[��)
	int FirstMoveFlg; // �ŏ�����U����U�����ËL����ϐ�
	bool TurnFlg; // �^�[���������߂�t���O
	int WaitTimeFlg; // �҂����Ԃ���邽�߂̕ϐ�
	int CoveringFlg; // �F�Əꏊ������Ă��邩�m�F����t���O
	int DescriptionFlg; // �ŏ��ɐ��������邽�߂̃t���O��ǉ�
	int OperationFlg; // �Q�[���̑�����@���m�F���邽�߂̃t���O
	int WinLoseDrawFlg; // ���s�܂��͈��������Ă��邩��������t���O(0:�������� 1:���� 2:����)

	int FontSize; // ������ʈȊO�̃t�H���g�̑傫���𓝈�ɂ��邽�߂̕ϐ�

public:
	// �C���N�������g
	HitAndBlow();
	// �f�N�������g
	~HitAndBlow();
	// �`��ȊO���A�b�v�f�[�g
	AbstractScene* Update();
	// �`����A�b�v�f�[�g
	virtual void Draw() const override;

	// �����_���ɐ����̐F�Əꏊ�A���Ԃ����߂�֐�
	void RandomDecision();

	// ����̊֐�
	void Judgment();

	// �G�̗\�z������֐�
	void ERandomChoice();

	// �F�����Z�b�g����֐�
	void ResetColor();

	// �z��̏������֐�
	void ArrayInit();

	// ���܂ł̃^�[���Ɣ��Ȃ����m�F����֐�
	void CheckCovered();

	// �q�b�g�ƃu���[��SE�炷�֐�
	void PlaySoundSE();
};