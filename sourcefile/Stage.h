#pragma once
#include "Base.h"
#include "Load.h"

#define FLOOR					 850						// 床座標

//	ウィンドウサイズ
#define WINDOW_W				1792
#define WINDOW_H				1008

#define BACKGROUND_SPEED		  15			// 背景の移動速度

#define FONTSIZE				  60

#define CATIN					  60
#define CATSTOP					   0.2
#define CATOUT					  60

// CBase >継承 ステージクラス
class CStage : public CBase {

public:
	CLoad* load = new CLoad();

	// ゲーム進行モード
	enum STFLAG {
		TITLE,			// タイトル
		TUTORIAL,		// チュートリアル
		GAME,			// ゲーム本編
		CLEAR,			// ゲームクリア
		OVER,			// ゲームオーバー
		RESULT,
	};

	enum CATINMODE {
		CATWAIT,
		CATMOVE,
	};

	// 進行モード変数
	int mode = 0;

	// カットイン用変数
	float catPosX = 0.0f;
	float catPosY = 0.0f;

	// カットインモードGG
	int catinMode = -1;


	// コンストラクタ
	CStage();
	// デストラクタ
	virtual ~CStage();
	// 初期化
	bool Init();
	// 更新処理
	void Update(int pHP, int pFrame, int eHP, int eFrame);
	// 描画
	void Draw(int bgGrh,int titleGrh);
	// カットイン画像描画
	void CatinDraw(int catGrh);
	// 終了処理
	void End();

	// カットインムーブ
	void CatinMove();

private:

	
};