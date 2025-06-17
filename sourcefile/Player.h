#pragma once

#include "Load.h"
#include "Stage.h"
#include "character.h"

// �萔
#define IMGSIZE_W	140				// �v���C���[�T�C�Y����
#define IMGSIZE_H	180				// �v���C���[�T�C�Y�c��

#define WALKSPEED	  4.0f			// �������̈ړ��ʒ萔
#define DASHSPEED	  6.0f			// �_�b�V�����̈ړ��ʒ萔
#define DAMAGESPEED	  5.0f			// �_���[�W���󂯂����̈ړ���

#define JUMPVECTOR	 20.0f			// �Î~�A�����W�����v�ړ��ʒ萔
#define WJUMPDIS	300.0f			// �������̃W�����v����
#define DJUMPDIS	500.0f			// �_�b�V�����̃W�����v����
#define IMAGEMAX	 11				// �摜����
#define PHPMAX		 30				// �v���C���[�̍ő�HP

// �N�[���^�C��
#define ATCOOL		 30,.0f			// �ʏ�U���N�[���^�C��
#define SK1COOL		200.0f			// �X�L��1�N�[���^�C��
#define SK2COOL		500.0f			// �X�L��2�N�[���^�C��

// �N�[���^�C���\�L
#define ROT			 40.0f

// �t���O
enum  FLAG {
	STOP0,
	STOP1,
	WALK,
	DASH,
	JUMP,
	ATTACK,
	SKILL1,
	SKILL2,
	DAMAGE,
	DEAD,
	CAT,
};


// CChar >�p�� player�N���X
class CPlayer : public CChar {

public:

	// �e��N�[���^�C��
	float  AtCool = 0;		// �ʏ�U��
	float  Sk1Cool = 0;		// �X�L���P
	float  Sk2Cool = 0;		// �X�L���Q

	// �N�[���^�C���\�L�p�̔��a�ϐ�
	float AtCRot = 0.0f;
	float Sk1CRot = 0.0f;
	float Sk2CRot = 0.0f;
 

	// �_���[�W���󂯂�Ԃ̖��G����
	int damageFrame = 0;

	// cv�Đ��̂��߂̊֐�
	int CVplayCount = 0;

	// �R���X�g���N�^
	CPlayer();
	// �f�X�g���N�^
	virtual ~CPlayer();
	// ������
	void Init();
	// �X�V	
	void Update(float eX, float eY, int eSize);
	// �`��	
	void Draw(int grh);
	// �I��
	void End();

	// ����֐�
	void Operation();
	// �ړ�����֐�
	void MoveRestrict();
	// �U���֐�
	void Attack();
	// �X�L���֐�
	void Skill();
	// damage�֐�
	void Damage(float eX, float eY, int eSize);
	// ���S�����֐�
	void DeadCheck();

private:
	
	// �ҋ@�摜�̐؂�ւ��p�t���[���ϐ�
	int imageFrame = 0;


};