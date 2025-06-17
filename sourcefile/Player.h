#pragma once

#include "Load.h"
#include "Stage.h"
#include "character.h"

// 定数
#define IMGSIZE_W	140				// プレイヤーサイズ横幅
#define IMGSIZE_H	180				// プレイヤーサイズ縦幅

#define WALKSPEED	  4.0f			// 歩く時の移動量定数
#define DASHSPEED	  6.0f			// ダッシュ時の移動量定数
#define DAMAGESPEED	  5.0f			// ダメージを受けた時の移動量

#define JUMPVECTOR	 20.0f			// 静止、歩きジャンプ移動量定数
#define WJUMPDIS	300.0f			// 歩き時のジャンプ距離
#define DJUMPDIS	500.0f			// ダッシュ時のジャンプ距離
#define IMAGEMAX	 11				// 画像枚数
#define PHPMAX		 30				// プレイヤーの最大HP

// クールタイム
#define ATCOOL		 30,.0f			// 通常攻撃クールタイム
#define SK1COOL		200.0f			// スキル1クールタイム
#define SK2COOL		500.0f			// スキル2クールタイム

// クールタイム表記
#define ROT			 40.0f

// フラグ
enum  FLAG {
	STOP0,
	STOP1,
	WALK,
	DASH,
	JUMP,
	ATTACK,
	SKILL1,
	SKILL2,
	DAMAGE,
	DEAD,
	CAT,
};


// CChar >継承 playerクラス
class CPlayer : public CChar {

public:

	// 各種クールタイム
	float  AtCool = 0;		// 通常攻撃
	float  Sk1Cool = 0;		// スキル１
	float  Sk2Cool = 0;		// スキル２

	// クールタイム表記用の半径変数
	float AtCRot = 0.0f;
	float Sk1CRot = 0.0f;
	float Sk2CRot = 0.0f;
 

	// ダメージを受ける間の無敵時間
	int damageFrame = 0;

	// cv再生のための関数
	int CVplayCount = 0;

	// コンストラクタ
	CPlayer();
	// デストラクタ
	virtual ~CPlayer();
	// 初期化
	void Init();
	// 更新	
	void Update(float eX, float eY, int eSize);
	// 描画	
	void Draw(int grh);
	// 終了
	void End();

	// 操作関数
	void Operation();
	// 移動上限関数
	void MoveRestrict();
	// 攻撃関数
	void Attack();
	// スキル関数
	void Skill();
	// damage関数
	void Damage(float eX, float eY, int eSize);
	// 死亡処理関数
	void DeadCheck();

private:
	
	// 待機画像の切り替わり用フレーム変数
	int imageFrame = 0;


};