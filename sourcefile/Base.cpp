#include "Base.h"

CBase::CBase()
{
	enable = true;
	posX = 0.0f;
	posY = 0.0f;
	rate = 0.0f;
	angle = 0.0f;
	tran = 0;
	speed = 0.0f;
}

CBase::~CBase()
{
}

// ��������̏���

// �q�b�g�֐�

// ���ƃG�l�~�[
//void CGame::HitKenToEnemy(const CKen& ken, const CEnemy& enemy)
//{
//	if (CheckCircleHit(ken.posX, ken.posY, ken.size, enemy.posX, enemy.PosY, enemy.size)) {
//		enemy.hp -= ken.atk;
//	}
//}
// ���N���X�^�̎Q�Ƃ����擾
// �����蔻�肻�̂��̂�