#pragma once
#include"AbstractScene.h"

class HitAndBlow : public AbstractScene {
private:
	int Color[6]; // �F�̋������z��
	int Hit;     // �q�b�g���𐔂���ϐ�
	int Blow;    // �u���[���𐔂���ϐ� 

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