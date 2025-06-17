#pragma once
#include "Weapon.h"
#include "Player.h"
#include "WinMain.h"
#include "Float2.h"

// 定数
#define INTERVAL	80.0f	// 剣の間合い
#define DIS			80.0f	// プレイヤーから離す距離
#define SPEED		10.0f	// 移動量

#define ATTACKDAMAGE	 2		// 通常攻撃のダメージ量と
#define ATTACKSTUN		10		// スタン蓄積値
#define SKILL1DAMAGE	 5		// スキル1のダメージ量/1回
#define SKILL1STUN		30		// スキル1のスタン蓄積値/1回
#define SKILL2DAMAGE	10		// スキル2のダメージ量/1回
#define SKILL2STUN		15		// スキル2のスタン蓄積値/1回

// CWeapon > 継承 剣クラス
class CKen : public CWeapon {
	
public:
	
	// 剣モード
	enum FLAG{
		KENWAIT,	// 剣準備モード
		ATMOVE,		// 剣通常動くモード
		SKMOVE,		// 剣スキル動くモード1(扇右)
		STOP,		// 剣停止
	};


	// コンストラクタ
	CKen();
	// デストラクタ
	virtual ~CKen();
	// 初期化
	void Init();
	// 更新
	void Update(float px, float py, int pfl, bool ptr, 
		float ex,float ey, int esize,int efl, bool etr, int ehp,int estun);
	// 描画
	void Draw(int grh,int fl);
	// 終了
	void End();

	// 攻撃スタート関数
	void AtStart(float x, float y, int fl, bool tr );
	// 通常攻撃モーション関数
	void AttackMotion(float x, float y, bool tr);
	// スキルモーション関数
	void SkillMotion(float x, float y, bool tr);

private:

	// 剣のモード
	int flag = 0;
	// 座標を決める角度
	float rot;
	// プレイヤーからの距離
	float distance = 0.0f;

};