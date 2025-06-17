//#include "Flame.h"
//
//CFlame::CFlame()
//{
//	mode = 0;
//	goalX = 0.0f;
//	goalY = 0.0f;
//}
//
//CFlame::~CFlame()
//{
//}
//
////　初期化
//void CFlame::Init()
//{
//	mode = FWAIT;
//	speed = 5.0f;
//}
//
//// 更新
//void CFlame::Update(float eneX, float eneY, bool eneTr, int eneFl, float px, float py, int psize, int pfl,int pHp)
//{
//	// エネミーフラグがフレイムの時
//	if (eneFl == FIREAT && mode == FWAIT) {
//		Start(eneX, eneY, eneTr, eneFl, px, py);
//	}
//
//	// ムーブモード時に移動処理
//	if (mode == FMOVE) {
//		// ムーブ関数
//		Move();
//	}
//}
//
////　描画
//void CFlame::Draw(int grh)
//{
//	if (mode == FMOVE) {
//		DrawRotaGraph(posX, posY, rate, angle, grh, TRUE, tran);
//	}
//}
//
//// 終了処理
//void CFlame::End()
//{
//}
//
//// スタート関数
//void CFlame::Start(float eneX, float eneY, bool eneTr, int eneFl, float plaX, float plaY)
//{
//	// 座標の初期化
//	// 右向きの時
//	if (eneTr == false) {
//		posX = eneX - POSX;
//		posY = eneY - POSY;
//	}
//	else {
//		// 左向きの時
//		posX = eneX + POSX;
//		posY = eneY - POSY;
//
//	}
//	// 向き設定(プレイヤーに向かって）
//	// 差分を求める
//	disX = plaX - posX;
//	disY = plaY - posY;
//	// 角度を求める
//	angle = atan2(disY, disX);
//	// フラグの変更
//	mode = FMOVE;
//}
//// ムーブ関数
//void CFlame::Move()
//{
//	// 設定した向きに向かって移動
//	goalX += speed * cos(D2R(angle));
//	goalY += speed * sin(D2R(angle));
//
//	 //プレイヤー　|| 床 ||画面外に行ったときに消滅。
//	if (posX <= 0 || posX >= WINDOW_W || posY >= FLOOR || posY <= 0) {
//		mode = FWAIT;
//	}
//
//}
