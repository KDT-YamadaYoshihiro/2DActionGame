#pragma once
#include "Base.h"


// CBase >�p�� �E�F�|���N���X(����N���X)
class CWeapon : public CBase {

public:

	// �v���C���[�Ƃ̋����p�ϐ�
	float disX = 0.0f;	// x���W
	float disY = 0.0f; // y���W

	// �U����
	int atk = 0;

	// �R���X�g���N�^
	CWeapon() {	};
	// �f�X�g���N�^
	virtual ~CWeapon() {};
	

};