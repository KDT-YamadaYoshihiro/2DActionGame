#include "Stage.h"


// �R���X�g���N�^
CStage::CStage()
{
	mode = 0;

	catPosX = 0.0f;
	catPosY = 0.0f;

}
// �f�X�g���N�^
CStage::~CStage()
{
}
// ������
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

		// ������_�Ńt���[��
		frame++;

		speed = 0;

		catPosX = -300;
		catPosY = WINDOW_H / 2;

		catinMode = CATWAIT;

		break;

	case TUTORIAL:

		// ������_�Ńt���[��
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


		// �X�e�[�W���I�[�o�[��
		if (pHP == 0 && pFrame <= ZEROFRAME) {
			mode = OVER;
		}
		// �X�e�[�W���N���A��
		if (eHP == 0 && eFrame <= ZEROFRAME) {
			mode = CLEAR;
		}

		break;

	case CLEAR:

		// ������_�Ńt���[��
		frame++;

		// ���U���g�Ɉڍs
		if (IsKeyOn(KEY_INPUT_SPACE)) {
			mode = RESULT;
		}


		break;

	case OVER:

		// ������_�Ńt���[��
		frame++;

		// �v���C���[��HP�͂O�����ɂȂ�Ȃ�
		pHP = 0;

		// ���U���g�Ɉڍs
		if (IsKeyOn(KEY_INPUT_SPACE)) {
			mode = RESULT;
		}

		break;

	case RESULT:

		// ������������^�C�g���Ɏ����ړ�
		mode = TITLE;

		break;
	}
}

// �`��
void CStage::Draw(int bgGrh, int titleGrh)
{
	// �w�i�摜
	DrawRotaGraph(WINDOW_W / 2, WINDOW_H / 2, 1, 0, bgGrh, TRUE, tran);

	switch (mode)
	{
	case TITLE:		// �^�C�g��

		// �^�C�g������
		DrawRotaGraph(WINDOW_W / 2, WINDOW_H / 2, 1, 0, titleGrh, TRUE, tran);

		if ((frame % (SECONDS * 2)) / SECONDS == 0) {
			SetFontSize(FONTSIZE);
			DrawFormatString(posX - 100, posY, GetColor(255, 255, 255), "SPACE to TUTORIAL");
		}
		break;

	case TUTORIAL:	// �`���[�g���A��

		DrawFormatString(100, 100, GetColor(255, 255, 255), "�������");
		DrawFormatString(150, 150 + FONTSIZE, GetColor(255, 255, 255),		"���ړ�  �F���E�L�[");
		DrawFormatString(150, 180 + FONTSIZE*2, GetColor(255, 255, 255),	"�W�����v�F��L�[");
		DrawFormatString(150, 210 + FONTSIZE*3, GetColor(255, 255, 255),	"�ʏ�U���FA�L�[");
		DrawFormatString(150, 240 + FONTSIZE*4, GetColor(255, 255, 255),	"�X�L��1 �FS�L�[");
		DrawFormatString(150, 270 + FONTSIZE*5, GetColor(255, 255, 255),	"�X�L��2 �FD�L�[");

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


// �I��
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
