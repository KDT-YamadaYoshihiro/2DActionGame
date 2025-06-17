#pragma once
#include "Base.h"
#include "WinMain.h"

#define HPSIZEH		30
#define HPSIZEW		10.0f

// �W�����v���
enum JUMPMODE{
	JWAIT,
	JMOVE,
};


// CBase >�p�� �L�����N�^�[�N���X
class CChar : public CBase{

public:
	// �e�L�����N�^�[HP
	int hp = 0;
	// �e�L�����N�^�[�̍U����
	int atk = 0;
	// �e�L�����N�^�[�̃t���O
	int flag = 0;
	// �W�����v�����p�ϐ�
	bool jumpLimit = true;
	// �_���[�W����
	bool damageLimit = true;
	// ���S�J�E���g����
	int deadFrame = 0;


	// �d��
	float vec = 0.0f;
	float gr = 0.0f;

	// �ő�Hp
	int HP = 0;

	// �R���X�g���N�^
	CChar() {
		frame = 0;
		hp = 0;
		atk = 0;
		flag = 0;
		jumpLimit = true;
		vec = 0.0f;
		gr = 0.0f;
		HP = 0;
	}

	// �f�X�g���N�^
	virtual ~CChar() {};

	// �L�����N�^�[HP�\�L
	virtual void Draw(float x, float y, int hp, int HP);

};

