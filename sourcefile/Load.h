#pragma once
#include "DxLib.h"

// �萔
#define IMAGEMAX			  11
#define EFFECTMAX			   4
#define BGMMAX				   4
#define SEMAX				   8
#define CVMAX				   7

// �T�E���h����

// ATTACK
#define IMAGESIZE_ATTACKX	2160.0f
#define IMAGESIZE_ATTACKY	 240.0f
#define ATTACKSIZE			 240.0f

// SKILL1
#define IMAGESIZE_SKILL1X	2400.0f
#define IMAGESIZE_SKILL1Y	1440.0f
#define SKILLSIZE			 480.0f

// SKILL2
#define IMAGESIZE_SKILL2X	 640.0f
#define IMAGESIZE_SKILL2Y	4800.0f
#define SKILL2SIZE			 480.0f

// BREAK
#define IMAGESIZE_BREAKX	2000.0f
#define IMAGESIZE_BREAKY	800.0f
#define BREAKEFSIZE			400.0f		


enum EF {
	ATTACKEF,
	SKILLEF1,
	SKILLEF2,
	STUNEF,
};

// ���[�h�N���X
class CLoad {

public:

	enum BGM {
		BTITLE,
		BBATTLE,
		BCLEAR,
		BOVER,
	};

	enum SE{
		SSPACE,
		SPJUMP,
		SPAT,
		SPSKILL1,
		SPSKILL2,
		SEJUMP,
		SFLY,
		SSTUN,

	};

	enum CV {
		CSTRAT,
		CAT,
		CSKILL1,
		CSKILL2,
		CDAMAGE,
		CCLEAR,
		COVER,
	};

	// �O���t�B�b�N�n���h��
	int bgGrh = -1;
	int titleGrh = -1;
	int playerGrh[IMAGEMAX];
	int enemyGrh = -1;
	int kenGrh = -1;
	int efGrh[EFFECTMAX];
	int flameGrh = -1;


	// �A�j���[�V�����t���[��
	int efFrame[EFFECTMAX];

	// DrawRectRotaGraph�@�摜�̕`�悷�鍶��̈ʒu���W
	float scrX[EFFECTMAX];
	float scrY[EFFECTMAX];

	// BGM�n���h��
	int bgm[BGMMAX];

	// SE�n���h��
	int se[SEMAX];

	// cv�n���h��
	int cv[CVMAX];

	// �R���X�g���N�^
	CLoad();
	// �f�X�g���N�^
	virtual ~CLoad();

	// ������
	// Init
	void Init();

	// �X�V
			// �֐�(�����F�v���C���[�t���O)
	// Update
	void ATUpdate(float imageSizeW, float imageSizeH, float sizeW, float sizeH, int fr);

	void SK1Update(float imageSizeW, float imageSizeH, float sizeW, float sizeH, int fr);

	void SK2Update(float imageSizeW, float imageSizeH, float sizeW, float sizeH, int fr);
	
	void BRUpdate(float imageSizeW, float imageSizeH, float sizeW, float sizeH, int fr);
	// �`��
				// �֐�(�����F�v���C���[�t���O)
	void Draw(float x, float y, float sizeW, float sizeH, float rate, int grh, bool tr, int i);

	// ���y�̍Đ�
	void SoundPlay(int soundGrh, int HowTo);

	// ���y�̒�~
	void SoundStop(int soundGrh);

	// �I��
	// End
	void End();

private:


};