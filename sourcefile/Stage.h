#pragma once
#include "Base.h"
#include "Load.h"

#define FLOOR					 850						// �����W

//	�E�B���h�E�T�C�Y
#define WINDOW_W				1792
#define WINDOW_H				1008

#define BACKGROUND_SPEED		  15			// �w�i�̈ړ����x

#define FONTSIZE				  60

#define CATIN					  60
#define CATSTOP					   0.2
#define CATOUT					  60

// CBase >�p�� �X�e�[�W�N���X
class CStage : public CBase {

public:
	CLoad* load = new CLoad();

	// �Q�[���i�s���[�h
	enum STFLAG {
		TITLE,			// �^�C�g��
		TUTORIAL,		// �`���[�g���A��
		GAME,			// �Q�[���{��
		CLEAR,			// �Q�[���N���A
		OVER,			// �Q�[���I�[�o�[
		RESULT,
	};

	enum CATINMODE {
		CATWAIT,
		CATMOVE,
	};

	// �i�s���[�h�ϐ�
	int mode = 0;

	// �J�b�g�C���p�ϐ�
	float catPosX = 0.0f;
	float catPosY = 0.0f;

	// �J�b�g�C�����[�hGG
	int catinMode = -1;


	// �R���X�g���N�^
	CStage();
	// �f�X�g���N�^
	virtual ~CStage();
	// ������
	bool Init();
	// �X�V����
	void Update(int pHP, int pFrame, int eHP, int eFrame);
	// �`��
	void Draw(int bgGrh,int titleGrh);
	// �J�b�g�C���摜�`��
	void CatinDraw(int catGrh);
	// �I������
	void End();

	// �J�b�g�C�����[�u
	void CatinMove();

private:

	
};