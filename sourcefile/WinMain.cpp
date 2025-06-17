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

// �R���X�g���N�^
CGame::CGame()
{

}
// �f�X�g���N�^
CGame::~CGame()
{
}

// ����������
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
	SetMainWindowText("2D�A�N�V����");
	if (DxLib_Init() == -1) { return -1; }

	SetDrawScreen(DX_SCREEN_BACK);

	load->Init();
	stage->Init();
	player->Init();
	ken->Init();
	enemy->Init();

}
// ���[�v����
void CGame::Run()
{
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//	���t���b�V�����[�g��ݒ肷�邽�߂̏���
		clock_t check_fps = clock() + CLOCKS_PER_SEC / 60;
		
		clsDx();
		ClearDrawScreen();
		InputKeyUpdate();
		InputPadUpdate();

		this->Update();
		this->Render();

		//	���t���b�V�����[�g�����ɂȂ�܂ő҂���
		while (clock() < check_fps) {}

		ScreenFlip();
	}

}
// �X�V����
void CGame::Update()
{

	// �X�e�[�W�X�V
	stage->Update(player->hp, player->deadFrame, enemy->hp, enemy->deadFrame);

	// �Q�[���{�҂̍X�V
	if (stage->mode == stage->GAME) {
		// �v���C���[�A�b�v�f�[�g
		player->Update(enemy->posX, enemy->posY, enemy->size);
		// ���A�b�v�f�[�g
		ken->Update(player->posX, player->posY, player->flag, player->tran ,
			enemy->posX, enemy->posY, enemy->size, enemy->flag, enemy->tran, enemy->hp, enemy->stunNum);
		// �G�l�~�[�A�b�v�f�[�g
		enemy->Update(player->posX, player->posY);
	}

	if (stage->mode == stage->OVER) {
		player->flag = DEAD;
	}

	// =============================
	// �q�b�g�֐�
	// =============================
	// �v���C���[�U��
	if (enemy->flag != FLYAT) {
		// �ʏ�U��
		if (player->AtCool <= ZEROFRAME && IsKeyOn(KEY_INPUT_A)) {

			if (player->flag == ATTACK) {
				// �N�[���^�C�����N��
				player->AtCool = ATCOOL;
				// �G�t�F�N�g�̏�����
				load->scrX[ATTACKEF] = 0.0f;
				load->scrY[ATTACKEF] = 0.0f;
				// Hit�֐�
				if (CheckCircleHit(ken->posX, ken->posY, ken->size, enemy->posX, enemy->posY, enemy->size)) {
					// HP�̕ω�
					enemy->hp -= ATTACKDAMAGE;
					// �X�^���l�̕ω�
					if (enemy->flag != BREAK) {
						enemy->stunNum += ATTACKSTUN;
					}

					// �J�E���g++
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
		// �X�L��1
		if (player->Sk1Cool <= ZEROFRAME && IsKeyOn(KEY_INPUT_S)) {

			if (player->flag == SKILL1) {
				// �N�[���^�C�����N��
				player->Sk1Cool = SK1COOL;

				// �G�t�F�N�g�̏�����
				load->scrX[SKILLEF1] = 0.0f;
				load->scrY[SKILLEF1] = 0.0f;

				if (CheckCircleHit(ken->posX, ken->posY, ken->size, enemy->posX, enemy->posY, enemy->size)) {
					// HP�̕ω�
					enemy->hp -= SKILL1DAMAGE;
					// �X�^���l�̕ω�
					if (enemy->flag != BREAK) {
						enemy->stunNum += SKILL1STUN;
					}

					// �J�E���g++
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
		// �X�L���Q
		if (player->Sk2Cool <= ZEROFRAME && IsKeyOn(KEY_INPUT_D)) {

			if (player->flag == SKILL2) {
				// �N�[���^�C�����N��
				player->Sk2Cool = SK2COOL;

				// �G�t�F�N�g�̏�����
				load->scrX[SKILLEF2] = 0.0f;
				load->scrY[SKILLEF2] = 0.0f;

				if (CheckCircleHit(ken->posX, ken->posY, ken->size, enemy->posX, enemy->posY, enemy->size)) {
					// HP�̕ω�
					enemy->hp -= SKILL2DAMAGE;
					// �X�^���l�̕ω�
					if (enemy->flag != BREAK) {
						enemy->stunNum += SKILL2STUN;
					}

					// �J�E���g++
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

	// �G�l�~�[�U��
	// �G�l�~�[�W�����v�U��
	if (enemy->jumpMode == JMOVE && enemy->flag != FLYAT && enemy->damageLimit == true ) {
		if (CheckCircleHit(enemy->posX, enemy->posY, enemy->size * 0.5, player->posX, player->posY, player->size)) {
			// HP�̕ω�
			player->hp -= JUMPDAMAGE;
			// �_���[�W����ON
			enemy->damageLimit = false;
			// �v���C���[�̃t���O�ύX�ƍ��W���ړ�
			player->damageFrame = SECONDS;
			// �G�l�~�[�W�����v���n�̎�
			if (enemy->posY <= FLOOR - enemy->size * 0.4) {
				load->SoundPlay(load->se[load->SEJUMP], DX_PLAYTYPE_BACK);
			}

		}

	}

	// ��s�U��
	if (enemy->flag == FLYAT) {
		if (CheckCircleHit(enemy->CyclePosX, enemy->CyclePosY, enemy->CycleSize,
			player->posX, player->posY, player->size) && enemy->damageLimit == true)
		{
			// HP�̕ω�
			player->hp -= FLYDAMAGE;
			// �_���[�W����ON
			enemy->damageLimit = false;
			// �v���C���[�̃t���O�ύX�ƍ��W���ړ�
			player->damageFrame = SECONDS;

		}
	}

	// ���U��0
	if (enemy->flyPattern == enemy->ONE) {
		for (int i = 0; i < FLAREMAX; i++) {
			if (CheckCircleHit(enemy->flarePosX[i], enemy->flarePosY[i], FLARESIZE,
				player->posX, player->posY, player->size)) {
				// �J�E���g����
				enemy->flareNum++;
				//�@���W�X�V
				enemy->flarePosX[i] = -enemy->flareSize;
				enemy->flarePosY[i] = -enemy->flareSize;
				// �v���C���[HP�̕ύX
				player->hp -= FLAREDAMAGE;
				// �v���C���[�̃t���O�ύX�ƍ��W���ړ�
				player->damageFrame = SECONDS;
			}
		}
	}

	// ============================
	// �G�t�F�N�g�X�V
	// ============================
	// �{�X����s�U�����ȊO�̎�
	if (enemy->flag != FLYAT) {
		if (enemy->flag == BREAK) {
			load->BRUpdate(IMAGESIZE_BREAKX, IMAGESIZE_BREAKY, BREAKEFSIZE, BREAKEFSIZE, 10);
		}
		if (player->flag == ATTACK) {
			// �G�t�F�N�g
			if (CheckCircleHit(ken->posX, ken->posY, ken->size, enemy->posX, enemy->posY, enemy->size)) {
				load->ATUpdate(IMAGESIZE_ATTACKX, IMAGESIZE_ATTACKY, ATTACKSIZE, ATTACKSIZE, 8);
			}
		}
		if (player->flag == SKILL1) {
			// �G�t�F�N�g
			if (CheckCircleHit(ken->posX, ken->posY, ken->size, enemy->posX, enemy->posY, enemy->size)) {
				load->SK1Update(IMAGESIZE_SKILL1X, IMAGESIZE_SKILL1Y, SKILLSIZE, SKILLSIZE, 3);
			}
		}
		if (player->flag == SKILL2) {
			// �G�t�F�N�g
			if (CheckCircleHit(ken->posX, ken->posY, ken->size, enemy->posX, enemy->posY, enemy->size)) {
				load->SK2Update(IMAGESIZE_SKILL2X, IMAGESIZE_SKILL2Y, IMAGESIZE_SKILL2X, SKILL2SIZE, 3);
			}
		}
	}


	// ============================
	// �T�E���h�X�V
	// ============================
	
	// ���ʐݒ�
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

	// �Đ��E��~�ݒ�
	switch (stage->mode) {

	case stage->TITLE:

		// �^�C�g��BGM���Đ�
		load->SoundPlay(load->bgm[load->BTITLE], DX_PLAYTYPE_LOOP);

		// �X�y�[�X�L�[����͂����Ƃ�
		if (IsKeyOn(KEY_INPUT_SPACE)) {
			// ���艹��炷
			load->SoundPlay(load->se[load->SSPACE], DX_PLAYTYPE_BACK);
			// �X�e�[�W�`���[�g���A���ɕύX
			stage->mode = stage->TUTORIAL;
		}

		break;

	case stage->TUTORIAL:

		// �X�y�[�X�L�[����͂����Ƃ�
		if (IsKeyOn(KEY_INPUT_SPACE)) {
			// ���艹��炷
			load->SoundPlay(load->se[load->SSPACE], DX_PLAYTYPE_NORMAL);
			load->SoundPlay(load->cv[load->CSTRAT], DX_PLAYTYPE_BACK);
		}

		// �X�e�[�W�`���[�g���A���ɕύX
		if (stage->catPosX >= WINDOW_W + 300) {
			stage->catinMode = stage->CATWAIT;
			stage->mode = stage->GAME;
			// bgm���~
			load->SoundStop(load->bgm[load->BTITLE]);
		}

		break;

	case stage->GAME:

		// �o�g��bgm�Đ�
		load->SoundPlay(load->bgm[load->BBATTLE], DX_PLAYTYPE_LOOP);

		// �v���C���[�W�����v���@���؂艹
		if (player->flag == JUMP) {
			load->SoundPlay(load->se[load->SPJUMP], DX_PLAYTYPE_BACK);
		}

		// �v���C���[�_���[�W�󂯎�cv
		if (player->flag == DAMAGE) {
			load->SoundPlay(load->cv[load->CDAMAGE], DX_PLAYTYPE_BACK);
		}

		// �G�l�~�[��s�U���H�΂�����
		if (enemy->flyPattern == enemy->ZERO || enemy->flyPattern == enemy->ONE) {
			load->SoundPlay(load->se[load->SFLY], DX_PLAYTYPE_BACK);
		}
		
		// �G�l�~�[�u���C�N��Ԃ̎�
		if (enemy->flag == BREAK) {
			// �X�^��SE���o�b�N�O���E���h�Đ�
			load->SoundPlay(load->se[load->SSTUN], DX_PLAYTYPE_BACK);
		}

		// �v���C���[��HP��0�̎�
		if (player->hp <= 0) {
			// BGM���~
			load->SoundStop(load->bgm[load->BBATTLE]);
			// �s�kvc�Đ�
			load->SoundPlay(load->cv[load->COVER],DX_PLAYTYPE_NORMAL);
			// ���[�h���I�[�o�[��
			stage->mode = stage->OVER;
		}
		// �G�l�~�[��HP��0�̎�
		if (enemy->hp <= 0) {
			// BGM���~
			load->SoundStop(load->bgm[load->BBATTLE]);
			// �N���Avc�Đ�
			load->SoundPlay(load->cv[load->CCLEAR], DX_PLAYTYPE_NORMAL);
			// ���[�h���N���A��
			stage->mode = stage->CLEAR;
		}

		break;

	case stage->CLEAR:

		// bgm�Đ�
		load->SoundPlay(load->bgm[load->BCLEAR], DX_PLAYTYPE_LOOP);

		if (IsKeyOn(KEY_INPUT_SPACE)) {
			// �^�C�g�����[�h��
			stage->mode = stage->RESULT;
			// bgm��~
			load->SoundStop(load->bgm[load->BCLEAR]);
		}

		break;

	case stage->OVER:

		// bgm�Đ�
		load->SoundPlay(load->bgm[load->BOVER], DX_PLAYTYPE_LOOP);

		if (IsKeyOn(KEY_INPUT_SPACE)) {
			// �^�C�g�����[�h��
			stage->mode = stage->RESULT;
			// bgm��~
			load->SoundStop(load->bgm[load->BOVER]);
		}

		break;

	case stage->RESULT:

		//  bgm�̒�~
		load->SoundStop(load->bgm[load->BCLEAR]);
		load->SoundStop(load->bgm[load->BOVER]);

		break;
	}

	// ============================
	// RESULT(Init�֐��̌Ăяo��)
	// ============================
	if (stage->mode == stage->RESULT) {
		stage->Init();
		player->Init();
		ken->Init();
		enemy->Init();
		//flame->Init();
	}
}

// �`�揈��
void CGame::Render()
{
	stage->Draw(load->bgGrh,load->titleGrh);		// �w�i,�^�C�g������,�J�b�g�C���摜

	if (stage->mode == stage->TUTORIAL) {
		stage->CatinDraw(load->playerGrh[CAT]);
	}

	if (stage->mode == stage->GAME) {
		enemy->Draw(load->enemyGrh, load->flameGrh);		// �G�l�~�[&&��
		//flame->Draw(load->flameGrh);			// ��
		ken->Draw(load->kenGrh, player->flag);	// ��	

		// �{�X����s�U�����ȊO�̎�
		if (enemy->flag != FLYAT) {

			// �u���C�N�G�t�F�N�g�X�V
			if (enemy->flag == BREAK) {
				load->Draw(enemy->posX, enemy->posY, BREAKEFSIZE, BREAKEFSIZE, 1.0f, load->efGrh[STUNEF], false, STUNEF);
			}
			// �ʏ�U���G�t�F�N�g�X�V
			if (player->flag == ATTACK) {
				if (CheckCircleHit(ken->posX, ken->posY, ken->size, enemy->posX, enemy->posY, enemy->size)) {
					load->Draw(enemy->posX, enemy->posY, ATTACKSIZE, ATTACKSIZE, 1.0f, load->efGrh[ATTACKEF], player->tran, ATTACKEF);
				}
			}
			// �X�L���G�t�F�N�g1�X�V
			if (player->flag == SKILL1) {
				if (CheckCircleHit(ken->posX, ken->posY, ken->size, enemy->posX, enemy->posY, enemy->size)) {
					load->Draw(enemy->posX, enemy->posY, SKILLSIZE, SKILLSIZE, 1.0f, load->efGrh[SKILLEF1], player->tran, SKILLEF1);
				}
			}
			// �X�L���G�t�F�N�g2�X�V
			if (player->flag == SKILL2) {

				if (CheckCircleHit(ken->posX, ken->posY, ken->size, enemy->posX, enemy->posY, enemy->size)) {
					load->Draw(enemy->posX, enemy->posY, IMAGESIZE_SKILL2X, SKILL2SIZE, 1.0f, load->efGrh[SKILLEF2], player->tran, SKILLEF2);
				}
			}
		}
	
	}

	if (stage->mode == stage->GAME || stage->mode == stage->OVER || stage->mode == stage->CLEAR) {
		player->Draw(load->playerGrh[player->flag]);	// �v���C���[
	}
}

// �I������
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