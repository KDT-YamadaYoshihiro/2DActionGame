#pragma once
#include "DxLib.h"
#include "Hit.h"
#include "InPutKey.h"
#include "InPutPad.h"


// �萔
#define SECONDS		60		// ��b
#define HALFSECONDS	30		// ���b
#define ZEROFRAME	 0		// 0�b
#define RIGHT		 0		// �E����
#define LEFT		 1		// ������

// Base�N���X
class CBase {

public:

	// �t���[���Ǘ�
	int frame = 0;

	// ���Wx
	float posX = 0.0f;
	// ���Wy
	float posY = 0.0f;
	// �g�k��
	float rate = 0.0f;
	// �p�x
	float angle = 0.0f;
	// �T�C�Y
	int size = 0;
	// �ړ����x
	float speed = 0.0f;

	// ���]����
	bool tran = true;
	// ���ݔ���
	bool enable = true;


	// �R���X�g���N�^
	CBase();

	// �f�X�g���N�^
	virtual ~CBase();


	// ===================================
	// �q�b�g�֐�
	// ===================================

};




