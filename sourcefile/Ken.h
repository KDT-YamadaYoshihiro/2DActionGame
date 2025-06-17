#pragma once
#include "Weapon.h"
#include "Player.h"
#include "WinMain.h"
#include "Float2.h"

// �萔
#define INTERVAL	80.0f	// ���̊ԍ���
#define DIS			80.0f	// �v���C���[���痣������
#define SPEED		10.0f	// �ړ���

#define ATTACKDAMAGE	 2		// �ʏ�U���̃_���[�W�ʂ�
#define ATTACKSTUN		10		// �X�^���~�ϒl
#define SKILL1DAMAGE	 5		// �X�L��1�̃_���[�W��/1��
#define SKILL1STUN		30		// �X�L��1�̃X�^���~�ϒl/1��
#define SKILL2DAMAGE	10		// �X�L��2�̃_���[�W��/1��
#define SKILL2STUN		15		// �X�L��2�̃X�^���~�ϒl/1��

// CWeapon > �p�� ���N���X
class CKen : public CWeapon {
	
public:
	
	// �����[�h
	enum FLAG{
		KENWAIT,	// ���������[�h
		ATMOVE,		// ���ʏ퓮�����[�h
		SKMOVE,		// ���X�L���������[�h1(��E)
		STOP,		// ����~
	};


	// �R���X�g���N�^
	CKen();
	// �f�X�g���N�^
	virtual ~CKen();
	// ������
	void Init();
	// �X�V
	void Update(float px, float py, int pfl, bool ptr, 
		float ex,float ey, int esize,int efl, bool etr, int ehp,int estun);
	// �`��
	void Draw(int grh,int fl);
	// �I��
	void End();

	// �U���X�^�[�g�֐�
	void AtStart(float x, float y, int fl, bool tr );
	// �ʏ�U�����[�V�����֐�
	void AttackMotion(float x, float y, bool tr);
	// �X�L�����[�V�����֐�
	void SkillMotion(float x, float y, bool tr);

private:

	// ���̃��[�h
	int flag = 0;
	// ���W�����߂�p�x
	float rot;
	// �v���C���[����̋���
	float distance = 0.0f;

};