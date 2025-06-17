#include "Stage.h"


// コンストラクタ
CStage::CStage()
{
	mode = 0;

	catPosX = 0.0f;
	catPosY = 0.0f;

}
// デストラクタ
CStage::~CStage()
{
}
// 初期化
bool CStage::Init()
{

	mode = TITLE;

	frame = 0;
	posX = WINDOW_W / 2 - FONTSIZE*3;
	posY = WINDOW_H / 2 + 300;

	catPosX = -300;
	catPosY = WINDOW_H / 2;


	return false;
}

void CStage::Update(int pHP, int pFrame ,int eHP, int eFrame)
{

	if (mode != TITLE) {
		load->SoundStop(load->se[load->SSPACE]);
	}

	switch (mode)
	{
	case TITLE:

		// 文字列点滅フレーム
		frame++;

		speed = 0;

		catPosX = -300;
		catPosY = WINDOW_H / 2;

		catinMode = CATWAIT;

		break;

	case TUTORIAL:

		// 文字列点滅フレーム
		frame++;

		if (IsKeyOn(KEY_INPUT_SPACE)) {
			catinMode = CATMOVE;
		}

		if (catinMode == CATMOVE) {
			CatinMove();
		}

		

		break;

	case GAME:

		load->SoundStop(load->bgm[load->BTITLE]);


		// ステージをオーバーに
		if (pHP == 0 && pFrame <= ZEROFRAME) {
			mode = OVER;
		}
		// ステージをクリアに
		if (eHP == 0 && eFrame <= ZEROFRAME) {
			mode = CLEAR;
		}

		break;

	case CLEAR:

		// 文字列点滅フレーム
		frame++;

		// リザルトに移行
		if (IsKeyOn(KEY_INPUT_SPACE)) {
			mode = RESULT;
		}


		break;

	case OVER:

		// 文字列点滅フレーム
		frame++;

		// プレイヤーのHPは０未満にならない
		pHP = 0;

		// リザルトに移行
		if (IsKeyOn(KEY_INPUT_SPACE)) {
			mode = RESULT;
		}

		break;

	case RESULT:

		// 初期化完了後タイトルに自動移動
		mode = TITLE;

		break;
	}
}

// 描画
void CStage::Draw(int bgGrh, int titleGrh)
{
	// 背景画像
	DrawRotaGraph(WINDOW_W / 2, WINDOW_H / 2, 1, 0, bgGrh, TRUE, tran);

	switch (mode)
	{
	case TITLE:		// タイトル

		// タイトル文字
		DrawRotaGraph(WINDOW_W / 2, WINDOW_H / 2, 1, 0, titleGrh, TRUE, tran);

		if ((frame % (SECONDS * 2)) / SECONDS == 0) {
			SetFontSize(FONTSIZE);
			DrawFormatString(posX - 100, posY, GetColor(255, 255, 255), "SPACE to TUTORIAL");
		}
		break;

	case TUTORIAL:	// チュートリアル

		DrawFormatString(100, 100, GetColor(255, 255, 255), "操作説明");
		DrawFormatString(150, 150 + FONTSIZE, GetColor(255, 255, 255),		"横移動  ：左右キー");
		DrawFormatString(150, 180 + FONTSIZE*2, GetColor(255, 255, 255),	"ジャンプ：上キー");
		DrawFormatString(150, 210 + FONTSIZE*3, GetColor(255, 255, 255),	"通常攻撃：Aキー");
		DrawFormatString(150, 240 + FONTSIZE*4, GetColor(255, 255, 255),	"スキル1 ：Sキー");
		DrawFormatString(150, 270 + FONTSIZE*5, GetColor(255, 255, 255),	"スキル2 ：Dキー");

		if ((frame % (SECONDS * 2)) / SECONDS == 0) {
			SetFontSize(FONTSIZE);
			DrawFormatString(posX - 50, posY, GetColor(255, 255, 255), "SPACE to START");
		}

		break;

	case GAME:

		break;

	case CLEAR:
		SetFontSize(100);
		DrawFormatString(WINDOW_W / 2 - 140, WINDOW_H / 2, GetColor(255, 255, 255), "CLEAR!");
		
		SetFontSize(FONTSIZE);
		if ((frame % (SECONDS * 2)) / SECONDS == 0) {
			DrawFormatString(posX , posY, GetColor(255, 255, 255), "SPACE TITLE");
		}

		break;

	case OVER:

		SetFontSize(100);
		DrawFormatString(WINDOW_W / 2 - 110, WINDOW_H / 2, GetColor(255, 255, 255), "GAME\nOVER");

		SetFontSize(FONTSIZE);
		if ((frame % (SECONDS*2)) / SECONDS == 0) {
			DrawFormatString(posX , posY, GetColor(255, 255, 255), "SPACE TITLE");
		}

		break;

	case RESULT:

		break;
	}

}

void CStage::CatinDraw(int catGrh)
{
	DrawRotaGraph(catPosX, catPosY, 1.0f, 0, catGrh, true, false);
}


// 終了
void CStage::End()
{

}

void CStage::CatinMove()
{
	catPosX += speed;

	if (catPosX >= WINDOW_W / 2 && catPosX <= WINDOW_W / 2 + 15) {
		speed = CATSTOP;
	}
	else if (catPosX >= WINDOW_W / 2 + 15) {
		speed = CATOUT;
	}
	else {
		speed = CATIN;
	}

}
