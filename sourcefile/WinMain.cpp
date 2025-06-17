#include "WinMain.h"

// Class.h
#include "Load.h"
#include "Base.h"
#include "character.h"
#include "Stage.h"
#include "Player.h"
#include "Enemy.h"
#include "Ken.h"
#include "Flame.h"

#include "CTecture.h"
#include "CTectureFactry.h"


static int is_window_mode = true;

CLoad* load = new CLoad();
CStage* stage = new CStage();
CWeapon* weapon = new CWeapon();
CPlayer* player = new CPlayer();
CKen* ken = new CKen();
CEnemy* enemy = new CEnemy();

// コンストラクタ
CGame::CGame()
{

}
// デストラクタ
CGame::~CGame()
{
}

// 初期化処理
bool CGame::Init()
{
	SRand((int)time(NULL));
	InputKeyInit();
	InputPadInit();

	SetOutApplicationLogValidFlag(FALSE);
	ChangeWindowMode(is_window_mode);
	SetGraphMode(WINDOW_W, WINDOW_H, 32);

	if (is_window_mode == TRUE)
	{
		SetWindowSize(WINDOW_W, WINDOW_H);
	}
	SetBackgroundColor(0, 0, 0);
	SetMainWindowText("2Dアクション");
	if (DxLib_Init() == -1) { return -1; }

	SetDrawScreen(DX_SCREEN_BACK);

	load->Init();
	stage->Init();
	player->Init();
	ken->Init();
	enemy->Init();

}
// ループ処理
void CGame::Run()
{
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//	リフレッシュレートを設定するための処理
		clock_t check_fps = clock() + CLOCKS_PER_SEC / 60;
		
		clsDx();
		ClearDrawScreen();
		InputKeyUpdate();
		InputPadUpdate();

		this->Update();
		this->Render();

		//	リフレッシュレートが一定になるまで待つ処理
		while (clock() < check_fps) {}

		ScreenFlip();
	}

}
// 更新処理
void CGame::Update()
{

	// ステージ更新
	stage->Update(player->hp, player->deadFrame, enemy->hp, enemy->deadFrame);

	// ゲーム本編の更新
	if (stage->mode == stage->GAME) {
		// プレイヤーアップデート
		player->Update(enemy->posX, enemy->posY, enemy->size);
		// 剣アップデート
		ken->Update(player->posX, player->posY, player->flag, player->tran ,
			enemy->posX, enemy->posY, enemy->size, enemy->flag, enemy->tran, enemy->hp, enemy->stunNum);
		// エネミーアップデート
		enemy->Update(player->posX, player->posY);
	}

	if (stage->mode == stage->OVER) {
		player->flag = DEAD;
	}

	// =============================
	// ヒット関数
	// =============================
	// プレイヤー攻撃
	if (enemy->flag != FLYAT) {
		// 通常攻撃
		if (player->AtCool <= ZEROFRAME && IsKeyOn(KEY_INPUT_A)) {

			if (player->flag == ATTACK) {
				// クールタイムを起動
				player->AtCool = ATCOOL;
				// エフェクトの初期化
				load->scrX[ATTACKEF] = 0.0f;
				load->scrY[ATTACKEF] = 0.0f;
				// Hit関数
				if (CheckCircleHit(ken->posX, ken->posY, ken->size, enemy->posX, enemy->posY, enemy->size)) {
					// HPの変化
					enemy->hp -= ATTACKDAMAGE;
					// スタン値の変化
					if (enemy->flag != BREAK) {
						enemy->stunNum += ATTACKSTUN;
					}

					// カウント++
					player->CVplayCount++;

					// SE
					load->SoundPlay(load->se[load->SPAT], DX_PLAYTYPE_BACK);
					// CV
					if (player->CVplayCount % 3 == 0) {
						load->SoundPlay(load->cv[load->CAT], DX_PLAYTYPE_BACK);
					}
				}
			}
		}
		// スキル1
		if (player->Sk1Cool <= ZEROFRAME && IsKeyOn(KEY_INPUT_S)) {

			if (player->flag == SKILL1) {
				// クールタイムを起動
				player->Sk1Cool = SK1COOL;

				// エフェクトの初期化
				load->scrX[SKILLEF1] = 0.0f;
				load->scrY[SKILLEF1] = 0.0f;

				if (CheckCircleHit(ken->posX, ken->posY, ken->size, enemy->posX, enemy->posY, enemy->size)) {
					// HPの変化
					enemy->hp -= SKILL1DAMAGE;
					// スタン値の変化
					if (enemy->flag != BREAK) {
						enemy->stunNum += SKILL1STUN;
					}

					// カウント++
					player->CVplayCount++;

					// SE
					load->SoundPlay(load->se[load->CSKILL1], DX_PLAYTYPE_BACK);
					// CV
					if (player->CVplayCount % 3 == 0) {
						load->SoundPlay(load->cv[load->CSKILL1], DX_PLAYTYPE_BACK);
					}
				}
			}
		}
		// スキル２
		if (player->Sk2Cool <= ZEROFRAME && IsKeyOn(KEY_INPUT_D)) {

			if (player->flag == SKILL2) {
				// クールタイムを起動
				player->Sk2Cool = SK2COOL;

				// エフェクトの初期化
				load->scrX[SKILLEF2] = 0.0f;
				load->scrY[SKILLEF2] = 0.0f;

				if (CheckCircleHit(ken->posX, ken->posY, ken->size, enemy->posX, enemy->posY, enemy->size)) {
					// HPの変化
					enemy->hp -= SKILL2DAMAGE;
					// スタン値の変化
					if (enemy->flag != BREAK) {
						enemy->stunNum += SKILL2STUN;
					}

					// カウント++
					player->CVplayCount++;

					// SE
					load->SoundPlay(load->se[load->CSKILL2], DX_PLAYTYPE_BACK);
					// CV
					if (player->CVplayCount % 3 == 0) {
						load->SoundPlay(load->cv[load->CSKILL2], DX_PLAYTYPE_BACK);
					}

				}

			}
		}
	}

	// エネミー攻撃
	// エネミージャンプ攻撃
	if (enemy->jumpMode == JMOVE && enemy->flag != FLYAT && enemy->damageLimit == true ) {
		if (CheckCircleHit(enemy->posX, enemy->posY, enemy->size * 0.5, player->posX, player->posY, player->size)) {
			// HPの変化
			player->hp -= JUMPDAMAGE;
			// ダメージ制限ON
			enemy->damageLimit = false;
			// プレイヤーのフラグ変更と座標を移動
			player->damageFrame = SECONDS;
			// エネミージャンプ着地の時
			if (enemy->posY <= FLOOR - enemy->size * 0.4) {
				load->SoundPlay(load->se[load->SEJUMP], DX_PLAYTYPE_BACK);
			}

		}

	}

	// 飛行攻撃
	if (enemy->flag == FLYAT) {
		if (CheckCircleHit(enemy->CyclePosX, enemy->CyclePosY, enemy->CycleSize,
			player->posX, player->posY, player->size) && enemy->damageLimit == true)
		{
			// HPの変化
			player->hp -= FLYDAMAGE;
			// ダメージ制限ON
			enemy->damageLimit = false;
			// プレイヤーのフラグ変更と座標を移動
			player->damageFrame = SECONDS;

		}
	}

	// 炎攻撃0
	if (enemy->flyPattern == enemy->ONE) {
		for (int i = 0; i < FLAREMAX; i++) {
			if (CheckCircleHit(enemy->flarePosX[i], enemy->flarePosY[i], FLARESIZE,
				player->posX, player->posY, player->size)) {
				// カウント増加
				enemy->flareNum++;
				//　座標更新
				enemy->flarePosX[i] = -enemy->flareSize;
				enemy->flarePosY[i] = -enemy->flareSize;
				// プレイヤーHPの変更
				player->hp -= FLAREDAMAGE;
				// プレイヤーのフラグ変更と座標を移動
				player->damageFrame = SECONDS;
			}
		}
	}

	// ============================
	// エフェクト更新
	// ============================
	// ボスが飛行攻撃時以外の時
	if (enemy->flag != FLYAT) {
		if (enemy->flag == BREAK) {
			load->BRUpdate(IMAGESIZE_BREAKX, IMAGESIZE_BREAKY, BREAKEFSIZE, BREAKEFSIZE, 10);
		}
		if (player->flag == ATTACK) {
			// エフェクト
			if (CheckCircleHit(ken->posX, ken->posY, ken->size, enemy->posX, enemy->posY, enemy->size)) {
				load->ATUpdate(IMAGESIZE_ATTACKX, IMAGESIZE_ATTACKY, ATTACKSIZE, ATTACKSIZE, 8);
			}
		}
		if (player->flag == SKILL1) {
			// エフェクト
			if (CheckCircleHit(ken->posX, ken->posY, ken->size, enemy->posX, enemy->posY, enemy->size)) {
				load->SK1Update(IMAGESIZE_SKILL1X, IMAGESIZE_SKILL1Y, SKILLSIZE, SKILLSIZE, 3);
			}
		}
		if (player->flag == SKILL2) {
			// エフェクト
			if (CheckCircleHit(ken->posX, ken->posY, ken->size, enemy->posX, enemy->posY, enemy->size)) {
				load->SK2Update(IMAGESIZE_SKILL2X, IMAGESIZE_SKILL2Y, IMAGESIZE_SKILL2X, SKILL2SIZE, 3);
			}
		}
	}


	// ============================
	// サウンド更新
	// ============================
	
	// 音量設定
	// bgm
	for (int i = 0; i < BGMMAX; i++) {
		ChangeVolumeSoundMem(120,load->bgm[i]);
	}
	// se
	for (int i = 0; i < SEMAX; i++) {
		ChangeVolumeSoundMem(180, load->se[i]);
	}
	// cv
	for (int i = 0; i < CVMAX; i++) {
		ChangeVolumeSoundMem(200, load->cv[i]);
	}

	// 再生・停止設定
	switch (stage->mode) {

	case stage->TITLE:

		// タイトルBGMを再生
		load->SoundPlay(load->bgm[load->BTITLE], DX_PLAYTYPE_LOOP);

		// スペースキーを入力したとき
		if (IsKeyOn(KEY_INPUT_SPACE)) {
			// 決定音を鳴らす
			load->SoundPlay(load->se[load->SSPACE], DX_PLAYTYPE_BACK);
			// ステージチュートリアルに変更
			stage->mode = stage->TUTORIAL;
		}

		break;

	case stage->TUTORIAL:

		// スペースキーを入力したとき
		if (IsKeyOn(KEY_INPUT_SPACE)) {
			// 決定音を鳴らす
			load->SoundPlay(load->se[load->SSPACE], DX_PLAYTYPE_NORMAL);
			load->SoundPlay(load->cv[load->CSTRAT], DX_PLAYTYPE_BACK);
		}

		// ステージチュートリアルに変更
		if (stage->catPosX >= WINDOW_W + 300) {
			stage->catinMode = stage->CATWAIT;
			stage->mode = stage->GAME;
			// bgmを停止
			load->SoundStop(load->bgm[load->BTITLE]);
		}

		break;

	case stage->GAME:

		// バトルbgm再生
		load->SoundPlay(load->bgm[load->BBATTLE], DX_PLAYTYPE_LOOP);

		// プレイヤージャンプ自　風切り音
		if (player->flag == JUMP) {
			load->SoundPlay(load->se[load->SPJUMP], DX_PLAYTYPE_BACK);
		}

		// プレイヤーダメージ受け時cv
		if (player->flag == DAMAGE) {
			load->SoundPlay(load->cv[load->CDAMAGE], DX_PLAYTYPE_BACK);
		}

		// エネミー飛行攻撃羽ばたき音
		if (enemy->flyPattern == enemy->ZERO || enemy->flyPattern == enemy->ONE) {
			load->SoundPlay(load->se[load->SFLY], DX_PLAYTYPE_BACK);
		}
		
		// エネミーブレイク状態の時
		if (enemy->flag == BREAK) {
			// スタンSEをバックグラウンド再生
			load->SoundPlay(load->se[load->SSTUN], DX_PLAYTYPE_BACK);
		}

		// プレイヤーのHPが0の時
		if (player->hp <= 0) {
			// BGMを停止
			load->SoundStop(load->bgm[load->BBATTLE]);
			// 敗北vc再生
			load->SoundPlay(load->cv[load->COVER],DX_PLAYTYPE_NORMAL);
			// モードをオーバーに
			stage->mode = stage->OVER;
		}
		// エネミーのHPが0の時
		if (enemy->hp <= 0) {
			// BGMを停止
			load->SoundStop(load->bgm[load->BBATTLE]);
			// クリアvc再生
			load->SoundPlay(load->cv[load->CCLEAR], DX_PLAYTYPE_NORMAL);
			// モードをクリアに
			stage->mode = stage->CLEAR;
		}

		break;

	case stage->CLEAR:

		// bgm再生
		load->SoundPlay(load->bgm[load->BCLEAR], DX_PLAYTYPE_LOOP);

		if (IsKeyOn(KEY_INPUT_SPACE)) {
			// タイトルモードへ
			stage->mode = stage->RESULT;
			// bgm停止
			load->SoundStop(load->bgm[load->BCLEAR]);
		}

		break;

	case stage->OVER:

		// bgm再生
		load->SoundPlay(load->bgm[load->BOVER], DX_PLAYTYPE_LOOP);

		if (IsKeyOn(KEY_INPUT_SPACE)) {
			// タイトルモードへ
			stage->mode = stage->RESULT;
			// bgm停止
			load->SoundStop(load->bgm[load->BOVER]);
		}

		break;

	case stage->RESULT:

		//  bgmの停止
		load->SoundStop(load->bgm[load->BCLEAR]);
		load->SoundStop(load->bgm[load->BOVER]);

		break;
	}

	// ============================
	// RESULT(Init関数の呼び出し)
	// ============================
	if (stage->mode == stage->RESULT) {
		stage->Init();
		player->Init();
		ken->Init();
		enemy->Init();
		//flame->Init();
	}
}

// 描画処理
void CGame::Render()
{
	stage->Draw(load->bgGrh,load->titleGrh);		// 背景,タイトル文字,カットイン画像

	if (stage->mode == stage->TUTORIAL) {
		stage->CatinDraw(load->playerGrh[CAT]);
	}

	if (stage->mode == stage->GAME) {
		enemy->Draw(load->enemyGrh, load->flameGrh);		// エネミー&&炎
		//flame->Draw(load->flameGrh);			// 炎
		ken->Draw(load->kenGrh, player->flag);	// 剣	

		// ボスが飛行攻撃時以外の時
		if (enemy->flag != FLYAT) {

			// ブレイクエフェクト更新
			if (enemy->flag == BREAK) {
				load->Draw(enemy->posX, enemy->posY, BREAKEFSIZE, BREAKEFSIZE, 1.0f, load->efGrh[STUNEF], false, STUNEF);
			}
			// 通常攻撃エフェクト更新
			if (player->flag == ATTACK) {
				if (CheckCircleHit(ken->posX, ken->posY, ken->size, enemy->posX, enemy->posY, enemy->size)) {
					load->Draw(enemy->posX, enemy->posY, ATTACKSIZE, ATTACKSIZE, 1.0f, load->efGrh[ATTACKEF], player->tran, ATTACKEF);
				}
			}
			// スキルエフェクト1更新
			if (player->flag == SKILL1) {
				if (CheckCircleHit(ken->posX, ken->posY, ken->size, enemy->posX, enemy->posY, enemy->size)) {
					load->Draw(enemy->posX, enemy->posY, SKILLSIZE, SKILLSIZE, 1.0f, load->efGrh[SKILLEF1], player->tran, SKILLEF1);
				}
			}
			// スキルエフェクト2更新
			if (player->flag == SKILL2) {

				if (CheckCircleHit(ken->posX, ken->posY, ken->size, enemy->posX, enemy->posY, enemy->size)) {
					load->Draw(enemy->posX, enemy->posY, IMAGESIZE_SKILL2X, SKILL2SIZE, 1.0f, load->efGrh[SKILLEF2], player->tran, SKILLEF2);
				}
			}
		}
	
	}

	if (stage->mode == stage->GAME || stage->mode == stage->OVER || stage->mode == stage->CLEAR) {
		player->Draw(load->playerGrh[player->flag]);	// プレイヤー
	}
}

// 終了処理
void CGame::End()
{
	InputKeyExit();
	InputPadExit();
	DxLib_End();

	stage->End();
	player->End();
	ken->End();
	enemy->End();
	//flame->End();
}
// 
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	CGame* game = new CGame();

	game->Init();
	game->Run();
	game->End();

	return 0;
}