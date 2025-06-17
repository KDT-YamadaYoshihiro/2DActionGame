#include "Ken.h"

// コンストラクタ
CKen::CKen()
{
	// 剣フラグ
	flag = 0;
	// 剣座標の角度
	rot = 0.0f;
	// プレイヤーとの距離
	distance = 0.0f;
}

// デストラクタ
CKen::~CKen()
{
}

// 初期化
void CKen::Init()
{
	posX = 0.0f;			
	posY = 0.0f;
	rate = 0.6f;
	angle = 0.0f;
	tran = false;
	speed = 0.0f;
	size = 50;

	flag = KENWAIT;
	distance = 0.0f;
}

// 更新処理
void CKen::Update(float px, float py, int pfl, bool ptr, 
	float ex, float ey, int esize, int efl, bool etr ,int ehp, int estun)
{
	// 有効判定
	if (enable != true) {
		return;
	}

	// 攻撃中でないとき、剣フラグをWAITにする
	if (pfl != ATTACK && pfl != SKILL1 && pfl != SKILL2) {
		this->flag = KENWAIT;
	}
	// スタート関数
	if (pfl == ATTACK || pfl == SKILL1 || pfl == SKILL2) {
		AtStart(px, py, pfl, ptr);
	}

}

// 描画処理
void CKen::Draw( int grh, int fl)
{
	// 有効判定
	if (enable != true) {
		return;
	}

	// プレイヤーフラグがアタック||スキルの場合描画
	if (fl == ATTACK || fl == SKILL1 || fl == SKILL2) {
		DrawRotaGraph(posX, posY, rate, D2R(angle), grh, TRUE, tran);
	}
}

// 終了処理
void CKen::End()
{
}

// 攻撃スタート関数
void CKen::AtStart(float x, float y, int fl, bool tr)
{
	// 有効判定
	if (enable != true) {
		return;
	}

	switch (flag) {

	case KENWAIT:

		speed = SPEED;

		// Player->flag == ATTACKの時
		if (fl == ATTACK) {

			// 剣の座標初期化
			if (tr == RIGHT) {
				posX = x + DIS;
				posY = y;
				angle = 0.0f;
				this->tran = RIGHT;
			}
			else if (tr == LEFT) {
				posX = x - DIS;
				posY = y;
				angle = 0.0f;
				this->tran = LEFT;
			}

			// スイッチの切り替え
			this->flag = ATMOVE;
		}

		// Player->flag == SKILLのとき
		if (fl == SKILL1 || fl == SKILL2) {

			// 剣の座標初期化
			if (tr == RIGHT) {
				posX = x + DIS;
				posY = y;
				angle = -90;
				rot = -90;
				this->tran = RIGHT;
			}
			else if (tr == LEFT) {
				posX = x - DIS;
				posY = y;
				angle = 90;
				rot = 90;
				this->tran = LEFT;
			}

			// スイッチの切り替え
			this->flag = SKMOVE;
		}

		break;

	case ATMOVE:
		
		// 通常攻撃の呼び出し
		AttackMotion(x, y, tran);

		break;

	case SKMOVE:

		// スキル関数の呼び出し
		SkillMotion(x, y, tran);

		break;
	}


}

// 通常攻撃関数
void CKen::AttackMotion(float x, float y, bool tr) {

	// 有効判定
	if (enable != true) {
		return;
	}

	// 距離を求める
	distance = x - posX;

	// 剣x座標を指定範囲まで可変
	// それぞれ向いている方向に
	if (this->flag == ATMOVE) {
		if (tr == RIGHT) {
			posX += speed;
		}
		else if (tr == LEFT) {
			posX -= speed;
		}
	}

	// 間合い以上の時wait状態にする
	if (distance >= INTERVAL || distance <= -INTERVAL) {
		this->flag = STOP;
		speed = 0.0f;
	}
}

// スキルモーション関数
void CKen::SkillMotion(float x, float y, bool tr) {

	// 有効判定
	if (enable != true) {
		return;
	}

	// プレイヤーの向きが右向きの時
	if (tr == RIGHT) {

		// 角度(rot)を増やす
		rot += speed;
		// ｘ軸
		posX = x + DIS * cos(D2R(rot));
		// ｙ軸
		posY = y + DIS * sin(D2R(rot));
		// 画像角度（angle）の変更
		angle += speed;
		// 終了処理
		if (rot >= 90) {
			speed = 0;
		}

	}// プレイヤーの向きが左向きの時0
	else if (tr == LEFT) {


		// 角度(rot)を増やす
		rot -= speed;
		// ｘ軸
		posX = x - DIS * cos(D2R(rot));
		// ｙ軸
		posY = y - DIS * sin(D2R(rot));
		// 画像角度（angle）の変更
		angle -= speed;
		// 終了処理
		if (rot <= -90) {
			speed = 0;
		}

	}
}

