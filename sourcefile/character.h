#pragma once
#include "Base.h"
#include "WinMain.h"

#define HPSIZEH		30
#define HPSIZEW		10.0f

// ジャンプ状態
enum JUMPMODE{
	JWAIT,
	JMOVE,
};


// CBase >継承 キャラクタークラス
class CChar : public CBase{

public:
	// 各キャラクターHP
	int hp = 0;
	// 各キャラクターの攻撃力
	int atk = 0;
	// 各キャラクターのフラグ
	int flag = 0;
	// ジャンプ制限用変数
	bool jumpLimit = true;
	// ダメージ制限
	bool damageLimit = true;
	// 死亡カウント時間
	int deadFrame = 0;


	// 重力
	float vec = 0.0f;
	float gr = 0.0f;

	// 最大Hp
	int HP = 0;

	// コンストラクタ
	CChar() {
		frame = 0;
		hp = 0;
		atk = 0;
		flag = 0;
		jumpLimit = true;
		vec = 0.0f;
		gr = 0.0f;
		HP = 0;
	}

	// デストラクタ
	virtual ~CChar() {};

	// キャラクターHP表記
	virtual void Draw(float x, float y, int hp, int HP);

};

