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

// あった後の処理

// ヒット関数

// 剣とエネミー
//void CGame::HitKenToEnemy(const CKen& ken, const CEnemy& enemy)
//{
//	if (CheckCircleHit(ken.posX, ken.posY, ken.size, enemy.posX, enemy.PosY, enemy.size)) {
//		enemy.hp -= ken.atk;
//	}
//}
// 基底クラス型の参照を二つを取得
// 当たり判定そのものを