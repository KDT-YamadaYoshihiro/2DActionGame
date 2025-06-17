#pragma once
// ���C�u����
#include "DxLib.h"

#include <ctime>
#include <math.h>
#include <cmath>
#include <vector>

// System.h
#include "Float2.h"
#include "Hit.h"
#include "InPutKey.h"
#include "InPutPad.h"


#define DegToRad 0.017453293f			//	�ʓx�@��
#define RadToDeg  57.29577951f


#define R2D(rad) rad * RadToDeg			// 
#define D2R(deg) deg * DegToRad			// ���W�A���Ԋ�

//	�J���[�R�[�h�ꗗ
#define BLACK	GetColor(0, 0, 0)			//	��
#define WHITE	GetColor(255, 255, 255)		//	��
#define RED		GetColor(255, 0, 0)			//	��
#define GREEN	GetColor(60, 179, 113)		//	��
#define BLUE	GetColor(0, 0, 255)			//	��
#define YELLOW	GetColor(255, 255, 0)		//	���F
#define PINK	GetColor(255, 0, 255)		//	�s���N
#define SKYBLUE	GetColor(0, 255, 255)		//	���F

// �Q�[�����[�v�N���X
class CGame {

public:
	// �R���X�g���N�^
	CGame();
	// �f�X�g���N�^
	virtual ~CGame();
	// ������
	bool Init();
	// ���[�v����
	void Run();
	// �X�V
	void Update();
	// �`��
	void Render();
	// �I��
	void End();

};
