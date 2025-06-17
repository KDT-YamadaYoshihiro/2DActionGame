#pragma once
#include "DxLib.h"
#include "Hit.h"
#include "InPutKey.h"
#include "InPutPad.h"


// 定数
#define SECONDS		60		// 一秒
#define HALFSECONDS	30		// 半秒
#define ZEROFRAME	 0		// 0秒
#define RIGHT		 0		// 右向き
#define LEFT		 1		// 左向き

// Baseクラス
class CBase {

public:

	// フレーム管理
	int frame = 0;

	// 座標x
	float posX = 0.0f;
	// 座標y
	float posY = 0.0f;
	// 拡縮率
	float rate = 0.0f;
	// 角度
	float angle = 0.0f;
	// サイズ
	int size = 0;
	// 移動速度
	float speed = 0.0f;

	// 反転判定
	bool tran = true;
	// 存在判定
	bool enable = true;


	// コンストラクタ
	CBase();

	// デストラクタ
	virtual ~CBase();


	// ===================================
	// ヒット関数
	// ===================================

};




