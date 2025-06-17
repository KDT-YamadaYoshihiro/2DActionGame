#pragma once
// ライブラリ
#include "DxLib.h"

#include <ctime>
#include <math.h>
#include <cmath>
#include <vector>

// System.h
#include "Float2.h"
#include "Hit.h"
#include "InPutKey.h"
#include "InPutPad.h"


#define DegToRad 0.017453293f			//	弧度法へ
#define RadToDeg  57.29577951f


#define R2D(rad) rad * RadToDeg			// 
#define D2R(deg) deg * DegToRad			// ラジアン返還

//	カラーコード一覧
#define BLACK	GetColor(0, 0, 0)			//	黒
#define WHITE	GetColor(255, 255, 255)		//	白
#define RED		GetColor(255, 0, 0)			//	赤
#define GREEN	GetColor(60, 179, 113)		//	緑
#define BLUE	GetColor(0, 0, 255)			//	青
#define YELLOW	GetColor(255, 255, 0)		//	黄色
#define PINK	GetColor(255, 0, 255)		//	ピンク
#define SKYBLUE	GetColor(0, 255, 255)		//	水色

// ゲームループクラス
class CGame {

public:
	// コンストラクタ
	CGame();
	// デストラクタ
	virtual ~CGame();
	// 初期化
	bool Init();
	// ループ処理
	void Run();
	// 更新
	void Update();
	// 描画
	void Render();
	// 終了
	void End();

};
