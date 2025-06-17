#include "Load.h"
using namespace std;

// コンストラクタ
CLoad::CLoad()
{
	// 背景
	bgGrh = -1;
	// タイトル文字
	titleGrh = -1;
	// プレイヤー
	for (int i = 0; i < IMAGEMAX; i++) {
		playerGrh[i] = -1;
	}
	// エネミー
	enemyGrh = -1;
	// 剣
	kenGrh = -1;
	// エフェクト
	for (int i = 0; i < EFFECTMAX; i++) {
		efGrh[i] = -1;
	}
	// 炎
	flameGrh = -1;

	// アニメーションフレーム
	for (int i = 0; i < EFFECTMAX; i++) {
		efFrame[i] = 0;
		// DrawRectRotaGraph　画像の描画する左上の位置座標
		scrX[i] = 0.0f;
		scrY[i] = 0.0f;
	}

	// BGM
	for (int i = 0; i < BGMMAX; i++) {
		bgm[i] = -1;
	}

	// SE
	for (int i = 0; i < SEMAX; i++) {
		se[i] = -1;
	}

	// CV
	for (int i = 0; i < CVMAX; i++) {
		cv[i] = -1;
	}
}

// デストラクタ
CLoad::~CLoad()
{
}

// 初期化
void CLoad::Init()
{
	//  背景画像の読み込み
	// ブロック画像引用：https://plicy.net/GuidebookObject/12794
	// 背景画像引用：https://www.ac-illust.com/main/detail.php?id=24090202
	bgGrh = LoadGraph("data/bg/bg2.png");
	
	// タイトル文字
	titleGrh = LoadGraph("data/bg/title.png");

	// プレイヤーの読み込み
		// 1:立ち1 , 2:立ち2 , 3:ダッシュ , 4:ジャンプ , 5:通常攻撃 , 6:スキル1 , 7:スキル2　8:ダメージ受け時 , 9:死亡時, 10:カットイン画像
	for (int i = 0; i < IMAGEMAX; i++) {
		char filepath[64];
		// プレイヤーの画像7枚を読み込み
		// 引用：https://yurudora.com/tkool/
		sprintf_s(filepath, "data/character/%d.png", i);
		//
		playerGrh[i] = LoadGraph(filepath);
	}

	// エネミーの読み込み
	// 引用：https://www.ac-illust.com/main/detail.php?id=22397840&word=
	enemyGrh = LoadGraph("data/enemy/boss0.png");

	// 剣の画像読み込み
	// 引用：https://www.ac-illust.com/main/detail.php?id=24772600&word=
	kenGrh = LoadGraph("data/character/ken.png");

	// 各種エフェクトの読み込み
	// 0:通常撃ヒットEF, 1:スキル1EF, 2:スキル2EF, 3:エネミースタンEF
	for (int i = 0; i < EFFECTMAX; i++) {
		char filepath[64];
		// 画像4枚を読み込み
		// 引用：https://pipoya.net/sozai/
		sprintf_s(filepath, "data/effect/effect%d.png", i);
		//
		efGrh[i] = LoadGraph(filepath);

	}

	// 炎画像の読み込み
	// 引用:https://www.ac-illust.com/main/detail.php?id=1032229&word=
	flameGrh = LoadGraph("data/effect/flame.png");

	 // BGM
	for (int i = 0; i < BGMMAX; i++) {
		char filepath[64];
		// BGM4曲の読み込み
		// 引用：
		sprintf_s(filepath, "data/BGM/bgm%d.mp3", i);
		// 
		bgm[i] = LoadSoundMem(filepath);

	}

	// SE
	for (int i = 0; i < SEMAX; i++) {
		char filepath[64];
		// SE8曲の読み込み
		// 引用：
		sprintf_s(filepath, "data/SE/se%d.mp3", i);
		// 
		se[i] = LoadSoundMem(filepath);

	}

	// CV
	for (int i = 0; i < CVMAX; i++) {
		char filepath[64];
		// BGM4曲の読み込み
		// 引用：
		sprintf_s(filepath, "data/CV/cv%d.mp3", i);
		// 
		cv[i] = LoadSoundMem(filepath);

	}


}

// 通常攻撃エフェクト処理
void CLoad::ATUpdate(float imageSizeW, float imageSizeH, float sizeW, float sizeH ,int fr)
{
	// アニメーション処理
	efFrame[ATTACKEF]++;

	if (efFrame[ATTACKEF] % fr == 0) {

		// 描画位置座標＋size
		scrX[ATTACKEF] += sizeW;

		// 縦方向に+size
		if (scrX[ATTACKEF] >= imageSizeW && imageSizeH >= sizeH) {
			scrX[ATTACKEF] = 0.0f;
			scrY[ATTACKEF] += sizeH;
		}
		// ループ
		if (scrY[ATTACKEF] >= imageSizeH) {
			scrX[ATTACKEF] = 0.0f;
			scrY[ATTACKEF] = 0.0f;
		}
	}
}
// スキルエフェクト1更新
void CLoad::SK1Update(float imageSizeW, float imageSizeH, float sizeW, float sizeH, int fr)
{
	// アニメーション処理
	efFrame[SKILLEF1]++;

	if (efFrame[SKILLEF1] % fr == 0) {

		// 描画位置座標＋size
		scrX[SKILLEF1] += sizeW;

		// 縦方向に+size
		if (scrX[SKILLEF1] >= imageSizeW && imageSizeH >= sizeH) {
			scrX[SKILLEF1] = 0.0f;
			scrY[SKILLEF1] += sizeH;
		}
		// ループ
		if (scrY[SKILLEF1] >= imageSizeH) {
			scrX[SKILLEF1] = 0.0f;
			scrY[SKILLEF1] = 0.0f;
		}
	}

}
// スキルエフェクト2更新
void CLoad::SK2Update(float imageSizeW, float imageSizeH, float sizeW, float sizeH, int fr)
{
	// アニメーション処理
	efFrame[SKILLEF2]++;

	if (efFrame[SKILLEF2] % fr == 0) {

		// 描画位置座標＋size
		scrX[SKILLEF2] += sizeW;

		// 縦方向に+size
		if (scrX[SKILLEF2] >= imageSizeW && imageSizeH >= sizeH) {
			scrX[SKILLEF2] = 0.0f;
			scrY[SKILLEF2] += sizeH;
		}
		// ループ
		if (scrY[SKILLEF2] >= imageSizeH) {
			scrX[SKILLEF2] = 0.0f;
			scrY[SKILLEF2] = 0.0f;
		}
	}

}
// ブレイクエフェクト更新
void CLoad::BRUpdate(float imageSizeW, float imageSizeH, float sizeW, float sizeH, int fr)
{
	// アニメーション処理
	efFrame[STUNEF]++;

	if (efFrame[STUNEF] % fr == 0) {

		// 描画位置座標＋size
		scrX[STUNEF] += sizeW;

		// 縦方向に+size
		if (scrX[STUNEF] >= imageSizeW && imageSizeH >= sizeH) {
			scrX[STUNEF] = 0.0f;
			scrY[STUNEF] += sizeH;
		}
		// ループ
		if (scrY[STUNEF] >= imageSizeH) {
			scrX[STUNEF] = 0.0f;
			scrY[STUNEF] = 0.0f;
		}
	}

}

// アニメーション描画
void CLoad::Draw(float x, float y, float sizeW, float sizeH, float rate, int grh, bool tr, int i)
{

	DrawRectRotaGraph(x, y, scrX[i], scrY[i], sizeW, sizeH, rate, 0.0f, grh, TRUE, tr);
	
}

// 音楽再生関数
void CLoad::SoundPlay(int soundGrh, int HowTo)
{
	if (CheckSoundMem(soundGrh) == false) {
		PlaySoundMem(soundGrh,HowTo);
	}
}

// 音楽停止関数
void CLoad::SoundStop(int soundGrh)
{
	if (CheckSoundMem(soundGrh) == true) {
		StopSoundMem(soundGrh);
	}
}

// 終了処理
void CLoad::End()
{
	DeleteGraph(bgGrh);

	DeleteGraph(titleGrh);

	for (int i = 0; i < IMAGEMAX; i++) {
		DeleteGraph(playerGrh[i]);
	}

	DeleteGraph(enemyGrh);

	DeleteGraph(kenGrh);

	for (int i = 0; i < EFFECTMAX; i++) {
		DeleteGraph(efGrh[i]);
	}

	DeleteGraph(flameGrh);

	for (int i = 0; i < BGMMAX; i++) {
		DeleteSoundMem(bgm[i]);
	}

	for (int i = 0; i < SEMAX; i++) {
		DeleteSoundMem(se[i]);
	}

	for (int i = 0; i < CVMAX; i++) {
		DeleteSoundMem(cv[i]);
	}
}

