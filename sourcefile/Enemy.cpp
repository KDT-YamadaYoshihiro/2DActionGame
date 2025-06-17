#include "Enemy.h"

// コンストラクタ
CEnemy::CEnemy()
{
	// メンバー変数の初期化
	dis = 0.0f;
	jumpMode = 0;
	stunNum = 0;

	flyMode = 0;
	CyclePosX = 0.0f;
	CyclePosY = 0.0f;
	CycleSize = 0;

	flyNum = 0;

	flyPattern = 0;
	standbyframe = 0;

	for (int i = 0; i < FLAREMAX; i++) {
		flarePosX[i] = 0.0f;
		flarePosY[i] = 0.0f;
		flareRate = 0;
		flareSize = 0;
		flareNum = 0;

		LBoxPosX[i] = 0.0f;
		LBoxPosY[i] = 0.0f;
		RBoxPosX[i] = 0.0f;
		RBoxPosY[i] = 0.0f;
	}
}

// デストラクタ
CEnemy::~CEnemy()
{
}

// 初期化
void CEnemy::Init()
{
	// フレーム管理
	frame = 0;
	// 各キャラクターHP
	hp = EHPMAX;
	// 各キャラクターの攻撃力
	atk = 0;
	// 各キャラクターのフラグ
	flag = 0;

	// 重力加速度
	vec = 0.0f;
	// 重力
	gr = 0.0f;

	// 存在判定
	enable = true;
	// 座標x
	posX = 1500.0f;
	// 座標y
	posY = FLOOR - JUMPDIS;
	// 拡縮率
	rate = RATE;
	// 角度
	angle = 0.0f;
	// サイズ
	size = 200;
	// 反転判定
	tran = false;
	// 移動速度
	speed = 0.0f;

	// プレイヤーとの距離を求める変数
	dis = 0.0f;
	// ジャンプモード
	jumpMode = JWAIT;
	// ジャンプ制限
	jumpLimit = true;
	// 何回ジャンプしたか
	jumpNum = 0;
	// ブレイク値
	stunNum = 0;

	// 飛行モード
	flyMode = FLYWAIT;
	// 円の座標
	CyclePosX = posX;
	CyclePosY = posY;
	// 円のサイズ
	CycleSize = 0;

	// 何回目飛行攻撃か
	flyNum = 0;

	//　飛行攻撃パターンモード
	flyPattern = -1;

	// 炎攻撃変数(座標、各縮率、サイズ、カウント)
	for (int i = 0; i < FLAREMAX; i++) {
		flarePosX[i] = 0.0f;
		flarePosY[i] = 0.0f;
		flareRate = 1.0;
		flareSize = 120;
		flareNum = 0;

		// 予測線のボックス座標
		LBoxPosX[i] = 0.0f;
		LBoxPosY[i] = 0.0f;
		RBoxPosX[i] = 0.0f;
		RBoxPosY[i] = 0.0f;
	}

}

// 更新
void CEnemy::Update(float playerX, float playerY)
{
	// 有効判定
	if (enable != true) {
		return;
	}

	// フレーム管理
	frame++;

	// ===============================
	// 重力設定
	// ===============================
	vec += 0.02;
	gr += vec;
	posY += gr;

	// ===============================
	// 床設定
	// ===============================
	if (posY >= FLOOR - SIZE * 0.4 ) {
		posY = FLOOR - SIZE * 0.4;
		vec = 0.0f;
		gr = 0.0f;
	}

	// ================================
	// 攻撃
	// ================================
	
	// 非ブレイク状態時のみ行動
	if (flag != BREAK) {

		// 飛行攻撃でないとき
		if (flag != FLYAT) {
			// 2秒毎にジャンプ
			if (this->frame % 120 == 0 ) {
				this->jumpLimit = true;
				JumpStart(playerX, playerY);
				jumpNum += 1;

			}

			// 制限解除時
			if (this->jumpLimit == true) {
				// ジャンプフラグに変更
				flag = JUMPAT;
			}
			else {
				// 制限時はwaitにしておく
				flag = ENEMYWAIT;
			}
			
			// ジャンプフラグの時
			if (this->flag == JUMPAT) {
				// ジャンプ関数を呼ぶ
				Jump(playerX, playerY);
			}
		}

		// 飛行状態でないとき&& ジャンプした回数が/5のあまり４のとき
		if (flyMode == FLYWAIT  && jumpNum % 5 == 4) {
			// 飛行攻撃フラグにする
			flag = FLYAT;
		}
		// 飛行攻撃フラグの時飛行攻撃関数を呼ぶ
		if (flag == FLYAT) { Fly(playerX, playerY); }
		
	}


	// =================================
	// 他設定
	// =================================

	//　スタン値がマックスの時
	if (stunNum >= STUN) {
		flag = BREAK;
	}
	// ブレイク時の時
	if (flag == BREAK) {
		// スタン値の減少
		stunNum -= 0.5f;
	}
	// スタン値がゼロになったら
	if (stunNum <= 0.0f) {
		// フラグ終了
		flag = !BREAK;
	}

	// HPがゼロになったとき
	if (this->hp < 0) {
		// hpを0未満にしない
		hp = 0;
	}
	// スタンのマックス
	if (this->stunNum >= STUN) {
		stunNum = STUN;
	}

}

// 描画
void CEnemy::Draw(int enemyGrh, int flareGrh)
{
	// ボス本体
	DrawRotaGraph(posX, posY, rate, angle, enemyGrh, TRUE, tran);
	
	// 炎
	for (int i = 0; i < FLAREMAX; i++) {
		if (CyclePosX >= flarePosX[i] && flyPattern == ONE) {
			// 予測線（色の透明度をあげて描画）
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
			DrawFillBox(LBoxPosX[i], LBoxPosY[i], RBoxPosX[i], RBoxPosY[i], GetColor(255, 255, 255));
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

			// 炎
			DrawRotaGraph(flarePosX[i], flarePosY[i], flareRate, 0, flareGrh, TRUE, FALSE);
		}
	}
	// ボス飛行攻撃時の円
	DrawCircle(CyclePosX, CyclePosY, CycleSize, GetColor(125, 125, 125), true);

	// HP
	CChar::Draw(WINDOW_W - 50.0f, 20.0f, -this->hp, -EHPMAX);
	// ブレイクゲージ
	DrawBox((WINDOW_W - 50) - (stunNum*4), 60, WINDOW_W - 50, 80, GetColor(0, 0, 255),true);
	DrawBox((WINDOW_W - 50) - 400, 60, WINDOW_W - 50, 80, GetColor(255, 255, 255), false);
}

// 終了
void CEnemy::End()
{

}

// ジャンプスタート関数
void CEnemy::JumpStart(float playerX, float PlayerY)
{
	// プレイヤーとの距離を求める
	dis = playerX - posX;

}

// ジャンプ関数
void CEnemy::Jump(float playerX, float playerY)
{
	switch (jumpMode) {

	case JWAIT:

		jumpMode = JMOVE;

		break;

	case JMOVE:

		// 移動量の設定
		speed = JUMPSPEED;
		
		// 移動
		posY -= speed;

		// プレイヤーとの距離
		if (jumpLimit == true) {

			if (dis > 0) {
				tran = true;
				posX =  posX + 10;
			}
			else if (dis < 0) {
				tran = false;
				posX = posX - 10;
			}
		}

		// 移動上限
		if (posY <= FLOOR - JUMPDIS) {
			// 制限
			// ジャンプ制限OFF
			jumpLimit = false;
			// ダメージ制限OFF
			damageLimit = true;
		}
		
		break;

	}

}

 //飛行攻撃関数
void CEnemy::Fly(float playerX, float playerY)
{
	flag = FLYAT;

	switch (flyMode) {
	
	case FLYWAIT:

		CyclePosX = posX;
		CyclePosY = posY;


		if (flag == FLYAT) {
			flyMode = FLYSTART;
		}

		break;


	// 開始処理（ボス描画の非表示、円の表示、速度更新）
	case FLYSTART:

		// ボス画像の退去
		rate -= 0.1;
 		if (rate <= 0.00f) {rate = 0.00f;}

		// 円描画の出現
		CycleSize += 2;
		if (CycleSize >= 100) { CycleSize = 100; }

		// 速度更新
		speed = FLYSPEED;

		// モードの切り替え
		if (rate == 0.0f && CycleSize == 100) { flyMode = FLY; }

		break;

	// 表示した円の画面上部移動、攻撃スタンバイ処理
	case FLY:

		// ダメージ制限解除
		damageLimit = true;

		// 画面上部に移動
		CyclePosY -= speed;

		// 画面外に行ったらモードの切り替え
		if (CyclePosY <= -CycleSize) {
			// 何回目のfly攻撃なのかによってパターンが変化
			if (flyNum % 3 == 0) {

				// 座標の更新
				CyclePosX = WINDOW_W + CycleSize;
				CyclePosY = FLOOR - CycleSize;

				flyMode = FLYMOVE;
				// パターン1モードに
				flyPattern = ZERO;

			}
			else if (flyNum % 3 == 1) {

				// 座標更新
				CyclePosX = -CycleSize;
				CyclePosY = +CycleSize;

				// 炎攻撃スタンバイ
				FlareStart();

				flyMode = FLYMOVE;
				// パターン2モードに
				flyPattern = ONE;
				

			}
			else {

				// 座標更新
				CyclePosX = WINDOW_W + CycleSize;
				CyclePosY = FLOOR + CycleSize;

				flyMode = FLYMOVE;
				// パターン3モードに
				flyPattern = ZERO;

			}

		}

		break;

	// 移動攻撃処理
	case FLYMOVE:

		// パターン数(flyNum++)
		switch (flyPattern) {

		// 1パターン目:地面座標
		case ZERO:

			// 左側から右側へ移動
			CyclePosX -= speed;

			// 左画面外に行ったとき
			if (CyclePosX <= -CycleSize) {

				// 座標更新
				CyclePosX = 1500.0f;
				CyclePosY = -CycleSize;

				// スタンバイフレームの更新
				standbyframe = 2 * SECONDS;

				// モードの変更
				if (flyNum % 3 == 0){
					flyMode = DWON;				
					// モードfalseに
					flyPattern = -1;
				}
				else if (flyNum % 3 == 2) { flyPattern = TWOSTANDBY; }
			}

			break;

			// 2パターン目：プレイヤー上空
			// 炎を落とす
		case ONE:

			// 右側から左側へ移動
			CyclePosX += speed;

			// 円が炎座標を超えたら。
			for (int i = 0; i < FLAREMAX; i++) {

				if (CyclePosX >= flarePosX[i]) {
					RBoxPosY[i] += speed;
				}


				if (RBoxPosY[i] >= FLOOR) {

					// 移動停止
					RBoxPosY[i] = FLOOR;

					if (CyclePosX >= WINDOW_W + CycleSize && RBoxPosY[i] == FLOOR) {
						// カウントダウン開始
						flareFrame--;
					}
				}

			}
			if (flareFrame <= 0) {
				FlareMove();
			}
			// 炎のすべてが地面につくまたはプレイヤーに当たっていれば
			if (flareNum >= FLAREMAX) {
				//　座標更新
				CyclePosX = 1500.0f;
				CyclePosY = -CycleSize;
				// カウントリセット
				flareNum = 0;
				// モードの変更
				flyPattern = -1;
				flyMode = DWON;
			}

			break;

		case TWOSTANDBY:

			// 画面外から出てくる
			CyclePosY += 4;

			// 指定地についたら一旦停止
			if (CyclePosY >= CycleSize) {
				CyclePosY = CycleSize;
				standbyframe--;
			}

			// フレームがゼロになるまでプレイヤーXを追尾
			if (standbyframe >= ZEROFRAME) {
				CyclePosX = playerX;
			}
			// ゼロになったらモード変更
			if (standbyframe <= ZEROFRAME) {
				flyPattern = TWO;
			}

			break;

		// 3パターン目：プレイヤーに向かって直下堕ち
		case TWO:

			// 地面に向かって落下
			CyclePosY += speed;
			// 地面についたらモード変更
			if (CyclePosY >= FLOOR - CycleSize) {
				// 地面にめり込まない
				CyclePosY = FLOOR - CycleSize;
				// 座標更新
				posX = CyclePosX;
				// モードfalseに
				flyPattern = -1;
				// モード変更
				flyMode = FLYEND;
			}

			break;

		}


		break;

	// 地面に降りる
	case DWON:

		// 地面に降りる
		CyclePosY += speed;

		if (CyclePosY >= FLOOR - CycleSize) {
			// 地面で止まる
			CyclePosY = FLOOR - CycleSize;
			// ボス画像の座標移動
			posX = CyclePosX;
			posY = CyclePosY;
			// モードの変更
			flyMode = FLYEND;
		}

		break;

	// 終了処理(ボス画像の表示、円の非表示、攻撃モードの終了)
	case FLYEND:

		// ボス画像の出現
		rate += 0.05;
		if (rate >= RATE) { rate = RATE; }

		// 円描画の退去
		CycleSize -= 2;
		if (CycleSize <= 0) { CycleSize = 0; }

		// 速度更新
		speed = FLYSPEED;

		// モードの切り替え
		if (rate == RATE && CycleSize == 0) {
			flyNum++;
			jumpNum++;
			flyMode = FLYWAIT;
			flag = ENEMYWAIT;
		}

		break;

	}

	return;

}

// 炎攻撃スタート関数
void CEnemy::FlareStart()
{
	// 座標の更新
	for (int i = 0; i < FLAREMAX; i++) {
		// 炎座標
		flarePosX[i] = flareSize + i * (flareSize * 2);
		flarePosY[i] = flareSize;

		// 発射カウントフレーム更新
		flareFrame = 60;
	
		// 予測線座標
		LBoxPosX[i] = flarePosX[i] - FLARESIZE/2;
		LBoxPosY[i] = flarePosY[i];
		RBoxPosX[i] = LBoxPosX[i] + FLARESIZE;
		RBoxPosY[i] = flarePosY[i];

	}
}

// 炎攻撃ムーブ関数
void CEnemy::FlareMove()
{
	// ループ処理
	for (int i = 0; i < FLAREMAX; i++) {
		// 予測戦の停止
		RBoxPosY[i] = FLOOR;

		// 炎を直下移動
		flarePosY[i] += FLARESPEED;
		LBoxPosY[i] += FLARESPEED;
		// 地面と接触したとき
		if (flarePosY[i] >= FLOOR - (flareSize / 2)) {
			// 座標の更新
			flarePosY[i] = 0.0f;
			// カウント+1する
			flareNum++;
		}
	}

}

