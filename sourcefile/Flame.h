//#pragma once
//#include "Weapon.h"
//#include "WinMain.h"
//#include "Stage.h"
//#include "Enemy.h"
//
//#define POSX		 20
//#define POSY		 50
//#define FLAMEDAMAGE	  5
//
//// weapon class �p�� > CFlame class
//class CFlame : public CWeapon {
//
//public:
//
//	enum FLAG {
//		FWAIT,
//		FMOVE,
//		FSTOP,
//	};
//
//	// ���݂̃��[�h
//	int mode = 0;
//
//
//	// �R���X�g���N�^
//	CFlame();
//
//	// �f�X�g���N�^
//	virtual ~CFlame();
//
//
//	// ������
//	void Init();
//
//	// �X�V����
//	void Update(float eneX,float eneY,bool eneTr, int eneFl, float px, float py,int psize,int pfl,int pHp);
//
//	// �`�揈��
//	void Draw(int grh);
//
//	//�@�I������
//	void End();
//
//	// �X�^�[�g�֐�
//	void Start(float eneX, float eneY, bool eneTr, int eneFl, float plaX, float plaY);
//
//	// ���[�u�֐�
//	void Move();
//
//private:
//
//
//	// �S�[�����W
//	float goalX = 0.0f;
//	float goalY = 0.0f;
//
//};