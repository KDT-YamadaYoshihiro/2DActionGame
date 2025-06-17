#pragma once
#include "DxLib.h"

// 定数
#define IMAGEMAX			  11
#define EFFECTMAX			   4
#define BGMMAX				   4
#define SEMAX				   8
#define CVMAX				   7

// サウンド音量

// ATTACK
#define IMAGESIZE_ATTACKX	2160.0f
#define IMAGESIZE_ATTACKY	 240.0f
#define ATTACKSIZE			 240.0f

// SKILL1
#define IMAGESIZE_SKILL1X	2400.0f
#define IMAGESIZE_SKILL1Y	1440.0f
#define SKILLSIZE			 480.0f

// SKILL2
#define IMAGESIZE_SKILL2X	 640.0f
#define IMAGESIZE_SKILL2Y	4800.0f
#define SKILL2SIZE			 480.0f

// BREAK
#define IMAGESIZE_BREAKX	2000.0f
#define IMAGESIZE_BREAKY	800.0f
#define BREAKEFSIZE			400.0f		


enum EF {
	ATTACKEF,
	SKILLEF1,
	SKILLEF2,
	STUNEF,
};

// ロードクラス
class CLoad {

public:

	enum BGM {
		BTITLE,
		BBATTLE,
		BCLEAR,
		BOVER,
	};

	enum SE{
		SSPACE,
		SPJUMP,
		SPAT,
		SPSKILL1,
		SPSKILL2,
		SEJUMP,
		SFLY,
		SSTUN,

	};

	enum CV {
		CSTRAT,
		CAT,
		CSKILL1,
		CSKILL2,
		CDAMAGE,
		CCLEAR,
		COVER,
	};

	// グラフィックハンドル
	int bgGrh = -1;
	int titleGrh = -1;
	int playerGrh[IMAGEMAX];
	int enemyGrh = -1;
	int kenGrh = -1;
	int efGrh[EFFECTMAX];
	int flameGrh = -1;


	// アニメーションフレーム
	int efFrame[EFFECTMAX];

	// DrawRectRotaGraph　画像の描画する左上の位置座標
	float scrX[EFFECTMAX];
	float scrY[EFFECTMAX];

	// BGMハンドル
	int bgm[BGMMAX];

	// SEハンドル
	int se[SEMAX];

	// cvハンドル
	int cv[CVMAX];

	// コンストラクタ
	CLoad();
	// デストラクタ
	virtual ~CLoad();

	// 初期化
	// Init
	void Init();

	// 更新
			// 関数(引数：プレイヤーフラグ)
	// Update
	void ATUpdate(float imageSizeW, float imageSizeH, float sizeW, float sizeH, int fr);

	void SK1Update(float imageSizeW, float imageSizeH, float sizeW, float sizeH, int fr);

	void SK2Update(float imageSizeW, float imageSizeH, float sizeW, float sizeH, int fr);
	
	void BRUpdate(float imageSizeW, float imageSizeH, float sizeW, float sizeH, int fr);
	// 描画
				// 関数(引数：プレイヤーフラグ)
	void Draw(float x, float y, float sizeW, float sizeH, float rate, int grh, bool tr, int i);

	// 音楽の再生
	void SoundPlay(int soundGrh, int HowTo);

	// 音楽の停止
	void SoundStop(int soundGrh);

	// 終了
	// End
	void End();

private:


};