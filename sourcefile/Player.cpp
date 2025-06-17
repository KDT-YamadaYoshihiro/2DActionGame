#include "Player.h"

// コンストラクタ
CPlayer::CPlayer()
{
	// base
	enable = true;
	posX = 0.0f;
	posY = 0.0f;
	rate = 0.0f;
	angle = 0.0f;
	size = 0;
	tran = false;
	speed = 0.0f;
	damageFrame = 0;
	deadFrame = 0;

	// character
	flag = STOP1;
	frame = SECONDS;
	hp = PHPMAX;
	atk = 0;

	// 重力系
	gr = 0.0f;
	vec = 0.0f;

	// メンバー変数
	// 各種クールタイム
	AtCool = 0;
	Sk1Cool = 0;
	Sk2Cool = 0;

	// クールタイム表記用の半径変数
	AtCRot = 0.0f;
	Sk1CRot = 0.0f;
	Sk2CRot = 0.0f;
	
	// cv再生カウント
	CVplayCount = 0;
}

// デストラクタ
CPlayer::~CPlayer()
{

}

// 初期化
void CPlayer::Init()
{
	// base
	enable = true;
	posX = 300.0f;
	posY = FLOOR;
	rate = 2.0f;
	angle = 0.0f;
	size = 40;
	tran = false;
	speed = 0.0f;
	damageFrame = 0;
	deadFrame = 0;

	// character
	flag = STOP1;
	frame = SECONDS;
	hp = PHPMAX;
	atk = 5;

	// 重力
	gr = 0.0f;
	vec = 0.0f;

	// メンバー変数
	// 各種クールタイム
	AtCool = 0;
	Sk1Cool = 0;
	Sk2Cool = 0;

	// クールタイム表記用の半径変数
	AtCRot = 0.0f;
	Sk1CRot = 0.0f;
	Sk2CRot = 0.0f;

	// cv再生カウント
	CVplayCount = 0;


}

// 更新処理
void CPlayer::Update(float eX, float eY, int eSize)
{
	// 有効判定
	if (enable != true) {
		return;
	}

	// ===============================
	// 重力設定
	// ===============================
	vec += 0.02;
	gr += vec;
	posY += gr;

	// ===============================
	// 床設定
	// ===============================
	if (posY >= FLOOR) {
		posY = FLOOR;
		vec = 0.0f;
		gr = 0.0f;
		jumpLimit = true;
	}

	// 攻撃時のフレームカウント
	frame--;

	// クールタイム
	AtCool--;
	Sk1Cool--;
	Sk2Cool--;

	float ctime[3];
	ctime[0] = ROT / ATCOOL;
	ctime[1] = ROT / SK1COOL;
	ctime[2] = ROT / SK2COOL;

	AtCRot = ROT - AtCool * ctime[0];
	Sk1CRot = ROT - Sk1Cool * ctime[1];
	Sk2CRot = ROT - Sk2Cool * ctime[2];

	// カウントリセット
	// 攻撃フレーム
	if (frame <= ZEROFRAME) {frame = ZEROFRAME;}
	// クールタイム
	if (AtCool <= ZEROFRAME) {AtCool = ZEROFRAME;}
	if (Sk1Cool <= ZEROFRAME) {Sk1Cool = ZEROFRAME;}
	if (Sk2Cool <= ZEROFRAME) {Sk2Cool = ZEROFRAME;}

	// 操作関数の呼び出し
	if (flag != DAMAGE) {
		Operation();
	}
	
	// 移動制限
	MoveRestrict();
	
	// 攻撃関数
	if ((flag != ATTACK && flag != SKILL1 && flag != SKILL2) && IsKeyOn(KEY_INPUT_A) && AtCool <= ZEROFRAME) {
		flag = ATTACK;
		frame = SECONDS;
	}
	if ((flag != ATTACK && flag != SKILL1 && flag != SKILL2) && IsKeyOn(KEY_INPUT_S) && Sk1Cool <= ZEROFRAME) {
		flag = SKILL1;
		frame = SECONDS;
	}
	if ((flag != ATTACK && flag != SKILL1 && flag != SKILL2) && IsKeyOn(KEY_INPUT_D) && Sk2Cool <= ZEROFRAME) {
		flag = SKILL2;
		frame = SECONDS;
	}

	if (flag == ATTACK) { Attack(); }
	if (flag == SKILL1 || flag == SKILL2) { Skill(); }

	// 　ダメージを受けたときの処理関数呼び出し
	Damage(eX, eY, eSize);
	
}

// 描画
void CPlayer::Draw(int grh)
{
	// キャラクター本体
	DrawRotaGraph(posX, posY, rate, angle, grh, TRUE, tran);

	// HP
	CChar::Draw(10.0f, WINDOW_H - 50.0f, this->hp , PHPMAX);

	// スキルクールタイム
	for (int i = 0; i < 3; i++) {
		// 円の縁
		DrawCircle(400 + i * (ROT*2 + 10), WINDOW_H - 50, ROT, WHITE, false);
	}
	// 円の中身
	DrawCircle(400, WINDOW_H - 50,  AtCRot, WHITE, true);
	DrawCircle(410 + ROT * 2, WINDOW_H - 50, Sk1CRot, WHITE, true);
	DrawCircle(420 + ROT * 4, WINDOW_H - 50, Sk2CRot, WHITE, true);

}

// 終了
void CPlayer::End()
{

}

// 操作関数
void CPlayer::Operation()
{
	// 有効判定
	if (enable != true) {
		return;
	}
	// 移動先に当たり判定

	// 歩く
	// キー入力時
	if (frame <= ZEROFRAME) {
		if (IsKeyRepeat(KEY_INPUT_RIGHT)) {

			// 描画切り替え
			flag = WALK;
			// 移動量
			speed = WALKSPEED;
			// 移動
			posX += speed;
			// 画像反転有無
			tran = false;

		}
		else if (IsKeyRepeat(KEY_INPUT_LEFT)) {

			// 描画切り替え
			flag = WALK;
			// 移動量
			speed = WALKSPEED;
			// 移動
			posX -= speed;
			// 画像反転有無
			tran = true;
		}
		else {
			// フレーム減少
			imageFrame--;

			// 描画の切り替え
			if (flag != STOP0 && imageFrame <= ZEROFRAME && jumpLimit == true) {
				flag = STOP0;
				imageFrame = HALFSECONDS;
			}
			if (flag != STOP1 && imageFrame <= ZEROFRAME && jumpLimit == true) {
				flag = STOP1;
				imageFrame = HALFSECONDS;
			}
		}


		// 右ダッシュ時
		if (IsKeyRepeat(KEY_INPUT_RIGHT) && IsKeyRepeat(KEY_INPUT_LSHIFT)) {
			// 画像の変更
			flag = DASH;
			// 移動量の変更
			speed = DASHSPEED;
			// 移動
			posX += speed;
		}
		// 左ダッシュ時
		if (IsKeyRepeat(KEY_INPUT_LEFT) && IsKeyRepeat(KEY_INPUT_LSHIFT)) {
			// 画像の変更
			flag = DASH;
			// 移動量の変更
			speed = DASHSPEED;
			// 移動
			posX -= speed;
		}

		// 静止ジャンプ
		// 上キー入力時
		if ((flag == STOP0 || flag == STOP1) && IsKeyRepeat(KEY_INPUT_UP) && jumpLimit == true) {
			// 描画切り替え
			flag = JUMP;
			// 移動量の設定
			speed = JUMPVECTOR;
			// 移動
			posY -= speed;
			// 移動上限
			if (posY <= FLOOR - WJUMPDIS) {
				// 制限
				jumpLimit = false;
			}
		}
		// 歩きジャンプ
		if (flag == WALK && IsKeyRepeat(KEY_INPUT_UP) && jumpLimit == true) {

			// 描画切り替え
			flag = JUMP;
			// 移動量の設定
			speed = JUMPVECTOR;
			// 移動
			posY -= speed;
			// 移動上限
			if (posY <= FLOOR - WJUMPDIS) {
				// 制限
				jumpLimit = false;
			}

		}
		// ダッシュジャンプ
		// 上キー入力時
		if (flag == DASH && IsKeyRepeat(KEY_INPUT_UP) && jumpLimit == true) {
			// 描画切り替え
			flag = JUMP;
			// 移動量の設定
			speed = JUMPVECTOR;
			// 移動
			posY -= speed;
			// 移動上限
			if (posY <= FLOOR - DJUMPDIS) {
				// 制限
				jumpLimit = false;
			}

		}
	}
}
// 移動上限関数
void CPlayer::MoveRestrict()
{
	// 有効判定
	if (enable != true) {
		return;
	}
	// 移動条件
	if (posX <= 0.0f + IMGSIZE_W / 2) {
		posX = 0.0f + IMGSIZE_W / 2;
	}
	if (posX >= WINDOW_W - IMGSIZE_W / 2) {
		posX = WINDOW_W - IMGSIZE_W / 2;
	}
	if (posY <= 0 + IMGSIZE_H / 2) {
		posY = 0.0f + IMGSIZE_H / 2;
	}
	if (posY >= WINDOW_H - IMGSIZE_H / 2) {
		posY = WINDOW_H - IMGSIZE_H / 2;
	}
}
// 攻撃関数
void CPlayer::Attack()
{
	// 有効判定
	if (enable != true) {
		return;
	}
	// フレームが0以上の時
	if (frame >= ZEROFRAME) {
		flag = ATTACK;
	}
	// フレームが30以上の時
	if (frame <= ZEROFRAME) {
		// flagをATTACKにする
		flag = !ATTACK;
	}

}
// スキル関数
void CPlayer::Skill()
{
		// 有効判定
	if (enable != true) {
		return;
	}
	// フレームが0の時&&キー入力時
	if (frame >= ZEROFRAME) {

		if(flag == SKILL1){
			flag = SKILL1;
		}
		if (flag == SKILL2) {
			flag = SKILL2;
		}
	}
	// フレームが0以下の時
	if (frame <= ZEROFRAME) {
		// flagを!SKILLにする
		flag = !SKILL1;
		flag = !SKILL2;
	}

}
// ダメージ受け関数
void CPlayer::Damage(float eX, float eY, int eSize)
{
	// フレームは常に減少
	damageFrame--;

	// フレームがゼロ以上の時
	if (damageFrame >= ZEROFRAME) {
		// フラグ変更
		flag = DAMAGE;
		// 右向きの時
		if (posX <= eX) {
			tran = RIGHT;
			speed = -DAMAGESPEED;
			posX += speed;
		}
		// 左向き
		else if (posX >= eX) {
			tran = LEFT;
			speed = DAMAGESPEED;
			posX += speed;
		}

		if (damageFrame <= ZEROFRAME) {
			flag = !DAMAGE;
		}
		// HPが0の時
		if (this->hp <= 0) {
			// hpが0未満にならないようにする
			this->hp = 0;
			flag = DEAD;
		}
	}


}
// 死亡処理関数
void CPlayer::DeadCheck()
{
	// 有効判定
	if (enable != true) {
		return;
	}

	if (hp <= 0) {
		hp = 0;
		this->flag = DEAD;
	}
}


