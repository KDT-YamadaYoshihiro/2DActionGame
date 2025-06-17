#pragma once
#include "Base.h"


// CBase >継承 ウェポンクラス(武器クラス)
class CWeapon : public CBase {

public:

	// プレイヤーとの距離用変数
	float disX = 0.0f;	// x座標
	float disY = 0.0f; // y座標

	// 攻撃力
	int atk = 0;

	// コンストラクタ
	CWeapon() {	};
	// デストラクタ
	virtual ~CWeapon() {};
	

};