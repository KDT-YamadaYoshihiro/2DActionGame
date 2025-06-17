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
//// weapon class 継承 > CFlame class
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
//	// 現在のモード
//	int mode = 0;
//
//
//	// コンストラクタ
//	CFlame();
//
//	// デストラクタ
//	virtual ~CFlame();
//
//
//	// 初期化
//	void Init();
//
//	// 更新処理
//	void Update(float eneX,float eneY,bool eneTr, int eneFl, float px, float py,int psize,int pfl,int pHp);
//
//	// 描画処理
//	void Draw(int grh);
//
//	//　終了処理
//	void End();
//
//	// スタート関数
//	void Start(float eneX, float eneY, bool eneTr, int eneFl, float plaX, float plaY);
//
//	// ムーブ関数
//	void Move();
//
//private:
//
//
//	// ゴール座標
//	float goalX = 0.0f;
//	float goalY = 0.0f;
//
//};