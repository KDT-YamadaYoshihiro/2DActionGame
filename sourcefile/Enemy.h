#pragma once
#include "Load.h"

#include "character.h"
#include "Stage.h"

// 定数
#define IMAGENUM	2			// 読み込む画像枚数の最大
#define SIZE		300.0f		// ボスサイズ
#define RATE		  0.4f		// ボス拡縮率

#define SPEED		8.0f		// 通常移動速度
#define JUMPSPEED	20.0f		// ジャンプする速度
#define FLYSPEED	20.0f;		// 飛行速度

#define JUMPDIS		600.0f		// ジャンプ時の飛ぶ距離
#define WADJUST		 50.0f		// ボスの当たり判定X座標調整
#define HADJUST		 80.0f		// ボスの当たり判定Y座標調整用

#define STUN		100			// ボスのスタン値
#define EHPMAX		100			// ボスの最大HP

#define FLAREMAX	 10			// 炎の数
#define FLARESIZE	 80
#define FLARESPEED	 20.0f		// 炎の移動量

// ダメージ
#define JUMPDAMAGE	  5			// ジャンプダメージ
#define FLAREDAMAGE	  8			// 炎攻撃ダメージ
#define FLYDAMAGE	 12			// 飛行攻撃

// モンスターの状態フラグ
enum ENEMYFLAG {
	ENEMYWAIT,				// 静止状態
	ENEMYMOVE,				// 移動状態
	JUMPAT,					// ジャンプ攻撃
	FIREAT,					// 炎攻撃
	FLYAT,					// 飛行攻撃
	BREAK,					// ブレイク状態
	ENEMYDEDA,				// クリア
};


// CChar > 継承　エネミークラス
class CEnemy : public CChar {

public:

	// 飛行攻撃
	enum FLY {
		FLYWAIT,
		FLYSTART,
		FLY,
		FLYMOVE,
		DWON,
		FLYEND,
	};

	// 飛行攻撃のパターン
	enum PATTERN {
		ZERO,
		ONE,
		TWOSTANDBY,
		TWO,
	};

	// ブレイク値
	float stunNum = 0;
	// ジャンプモード変数
	int jumpMode = 0;
	// 何回ジャンプしたか
	int jumpNum = 0;

	// 飛行攻撃モード
	int flyMode = 0;
 
	// 飛行攻撃変数
	float CyclePosX = 0.0f;
	float CyclePosY = 0.0f;
	int CycleSize = 0;

	// 何回目の飛行攻撃か
	int flyNum = 0;			
	//　飛行攻撃パターンモード
	int flyPattern = 0;

	// 炎変数
	float flarePosX[FLAREMAX];
	float flarePosY[FLAREMAX];
	int flareRate = 0;
	int flareSize = 0;
	// 着弾した数をカウント
	int flareNum = 0;


	// コンストラクタ
	CEnemy();
	// デストラクタ
	virtual ~CEnemy();


	// 初期化
	void Init();
	// 更新
	void Update(float playerX, float playerY);
	// 描画
	void Draw(int enemyGrh, int flareGrh);
	// 終了
	void End();


	//　ジャンプスタート関数
	void JumpStart(float playerX, float PlayerY);
	//　ジャンプ関数
	void Jump(float playerX, float playerY);


	// 飛行攻撃関数
	void Fly(float playerX, float playerY);


	// 炎攻撃スタート関数
	void FlareStart();
	// 炎攻撃
	void FlareMove();

private:

	// プレイヤーとの距離を求める変数
	float dis = 0.0f;
	// 発射カウントフレーム
	int flareFrame = 0;
	// 飛行予測線変数
	float LBoxPosX[FLAREMAX];
	float LBoxPosY[FLAREMAX];
	float RBoxPosX[FLAREMAX];
	float RBoxPosY[FLAREMAX];
	// 直下攻撃スタンバイフレーム
	int standbyframe = 0;


};