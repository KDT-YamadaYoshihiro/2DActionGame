#pragma once
#include "Load.h"

#include "character.h"
#include "Stage.h"

// �萔
#define IMAGENUM	2			// �ǂݍ��މ摜�����̍ő�
#define SIZE		300.0f		// �{�X�T�C�Y
#define RATE		  0.4f		// �{�X�g�k��

#define SPEED		8.0f		// �ʏ�ړ����x
#define JUMPSPEED	20.0f		// �W�����v���鑬�x
#define FLYSPEED	20.0f;		// ��s���x

#define JUMPDIS		600.0f		// �W�����v���̔�ԋ���
#define WADJUST		 50.0f		// �{�X�̓����蔻��X���W����
#define HADJUST		 80.0f		// �{�X�̓����蔻��Y���W�����p

#define STUN		100			// �{�X�̃X�^���l
#define EHPMAX		100			// �{�X�̍ő�HP

#define FLAREMAX	 10			// ���̐�
#define FLARESIZE	 80
#define FLARESPEED	 20.0f		// ���̈ړ���

// �_���[�W
#define JUMPDAMAGE	  5			// �W�����v�_���[�W
#define FLAREDAMAGE	  8			// ���U���_���[�W
#define FLYDAMAGE	 12			// ��s�U��

// �����X�^�[�̏�ԃt���O
enum ENEMYFLAG {
	ENEMYWAIT,				// �Î~���
	ENEMYMOVE,				// �ړ����
	JUMPAT,					// �W�����v�U��
	FIREAT,					// ���U��
	FLYAT,					// ��s�U��
	BREAK,					// �u���C�N���
	ENEMYDEDA,				// �N���A
};


// CChar > �p���@�G�l�~�[�N���X
class CEnemy : public CChar {

public:

	// ��s�U��
	enum FLY {
		FLYWAIT,
		FLYSTART,
		FLY,
		FLYMOVE,
		DWON,
		FLYEND,
	};

	// ��s�U���̃p�^�[��
	enum PATTERN {
		ZERO,
		ONE,
		TWOSTANDBY,
		TWO,
	};

	// �u���C�N�l
	float stunNum = 0;
	// �W�����v���[�h�ϐ�
	int jumpMode = 0;
	// ����W�����v������
	int jumpNum = 0;

	// ��s�U�����[�h
	int flyMode = 0;
 
	// ��s�U���ϐ�
	float CyclePosX = 0.0f;
	float CyclePosY = 0.0f;
	int CycleSize = 0;

	// ����ڂ̔�s�U����
	int flyNum = 0;			
	//�@��s�U���p�^�[�����[�h
	int flyPattern = 0;

	// ���ϐ�
	float flarePosX[FLAREMAX];
	float flarePosY[FLAREMAX];
	int flareRate = 0;
	int flareSize = 0;
	// ���e���������J�E���g
	int flareNum = 0;


	// �R���X�g���N�^
	CEnemy();
	// �f�X�g���N�^
	virtual ~CEnemy();


	// ������
	void Init();
	// �X�V
	void Update(float playerX, float playerY);
	// �`��
	void Draw(int enemyGrh, int flareGrh);
	// �I��
	void End();


	//�@�W�����v�X�^�[�g�֐�
	void JumpStart(float playerX, float PlayerY);
	//�@�W�����v�֐�
	void Jump(float playerX, float playerY);


	// ��s�U���֐�
	void Fly(float playerX, float playerY);


	// ���U���X�^�[�g�֐�
	void FlareStart();
	// ���U��
	void FlareMove();

private:

	// �v���C���[�Ƃ̋��������߂�ϐ�
	float dis = 0.0f;
	// ���˃J�E���g�t���[��
	int flareFrame = 0;
	// ��s�\�����ϐ�
	float LBoxPosX[FLAREMAX];
	float LBoxPosY[FLAREMAX];
	float RBoxPosX[FLAREMAX];
	float RBoxPosY[FLAREMAX];
	// �����U���X�^���o�C�t���[��
	int standbyframe = 0;


};