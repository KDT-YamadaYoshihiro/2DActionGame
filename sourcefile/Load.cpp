#include "Load.h"
using namespace std;

// �R���X�g���N�^
CLoad::CLoad()
{
	// �w�i
	bgGrh = -1;
	// �^�C�g������
	titleGrh = -1;
	// �v���C���[
	for (int i = 0; i < IMAGEMAX; i++) {
		playerGrh[i] = -1;
	}
	// �G�l�~�[
	enemyGrh = -1;
	// ��
	kenGrh = -1;
	// �G�t�F�N�g
	for (int i = 0; i < EFFECTMAX; i++) {
		efGrh[i] = -1;
	}
	// ��
	flameGrh = -1;

	// �A�j���[�V�����t���[��
	for (int i = 0; i < EFFECTMAX; i++) {
		efFrame[i] = 0;
		// DrawRectRotaGraph�@�摜�̕`�悷�鍶��̈ʒu���W
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

// �f�X�g���N�^
CLoad::~CLoad()
{
}

// ������
void CLoad::Init()
{
	//  �w�i�摜�̓ǂݍ���
	// �u���b�N�摜���p�Fhttps://plicy.net/GuidebookObject/12794
	// �w�i�摜���p�Fhttps://www.ac-illust.com/main/detail.php?id=24090202
	bgGrh = LoadGraph("data/bg/bg2.png");
	
	// �^�C�g������
	titleGrh = LoadGraph("data/bg/title.png");

	// �v���C���[�̓ǂݍ���
		// 1:����1 , 2:����2 , 3:�_�b�V�� , 4:�W�����v , 5:�ʏ�U�� , 6:�X�L��1 , 7:�X�L��2�@8:�_���[�W�󂯎� , 9:���S��, 10:�J�b�g�C���摜
	for (int i = 0; i < IMAGEMAX; i++) {
		char filepath[64];
		// �v���C���[�̉摜7����ǂݍ���
		// ���p�Fhttps://yurudora.com/tkool/
		sprintf_s(filepath, "data/character/%d.png", i);
		//
		playerGrh[i] = LoadGraph(filepath);
	}

	// �G�l�~�[�̓ǂݍ���
	// ���p�Fhttps://www.ac-illust.com/main/detail.php?id=22397840&word=
	enemyGrh = LoadGraph("data/enemy/boss0.png");

	// ���̉摜�ǂݍ���
	// ���p�Fhttps://www.ac-illust.com/main/detail.php?id=24772600&word=
	kenGrh = LoadGraph("data/character/ken.png");

	// �e��G�t�F�N�g�̓ǂݍ���
	// 0:�ʏ팂�q�b�gEF, 1:�X�L��1EF, 2:�X�L��2EF, 3:�G�l�~�[�X�^��EF
	for (int i = 0; i < EFFECTMAX; i++) {
		char filepath[64];
		// �摜4����ǂݍ���
		// ���p�Fhttps://pipoya.net/sozai/
		sprintf_s(filepath, "data/effect/effect%d.png", i);
		//
		efGrh[i] = LoadGraph(filepath);

	}

	// ���摜�̓ǂݍ���
	// ���p:https://www.ac-illust.com/main/detail.php?id=1032229&word=
	flameGrh = LoadGraph("data/effect/flame.png");

	 // BGM
	for (int i = 0; i < BGMMAX; i++) {
		char filepath[64];
		// BGM4�Ȃ̓ǂݍ���
		// ���p�F
		sprintf_s(filepath, "data/BGM/bgm%d.mp3", i);
		// 
		bgm[i] = LoadSoundMem(filepath);

	}

	// SE
	for (int i = 0; i < SEMAX; i++) {
		char filepath[64];
		// SE8�Ȃ̓ǂݍ���
		// ���p�F
		sprintf_s(filepath, "data/SE/se%d.mp3", i);
		// 
		se[i] = LoadSoundMem(filepath);

	}

	// CV
	for (int i = 0; i < CVMAX; i++) {
		char filepath[64];
		// BGM4�Ȃ̓ǂݍ���
		// ���p�F
		sprintf_s(filepath, "data/CV/cv%d.mp3", i);
		// 
		cv[i] = LoadSoundMem(filepath);

	}


}

// �ʏ�U���G�t�F�N�g����
void CLoad::ATUpdate(float imageSizeW, float imageSizeH, float sizeW, float sizeH ,int fr)
{
	// �A�j���[�V��������
	efFrame[ATTACKEF]++;

	if (efFrame[ATTACKEF] % fr == 0) {

		// �`��ʒu���W�{size
		scrX[ATTACKEF] += sizeW;

		// �c������+size
		if (scrX[ATTACKEF] >= imageSizeW && imageSizeH >= sizeH) {
			scrX[ATTACKEF] = 0.0f;
			scrY[ATTACKEF] += sizeH;
		}
		// ���[�v
		if (scrY[ATTACKEF] >= imageSizeH) {
			scrX[ATTACKEF] = 0.0f;
			scrY[ATTACKEF] = 0.0f;
		}
	}
}
// �X�L���G�t�F�N�g1�X�V
void CLoad::SK1Update(float imageSizeW, float imageSizeH, float sizeW, float sizeH, int fr)
{
	// �A�j���[�V��������
	efFrame[SKILLEF1]++;

	if (efFrame[SKILLEF1] % fr == 0) {

		// �`��ʒu���W�{size
		scrX[SKILLEF1] += sizeW;

		// �c������+size
		if (scrX[SKILLEF1] >= imageSizeW && imageSizeH >= sizeH) {
			scrX[SKILLEF1] = 0.0f;
			scrY[SKILLEF1] += sizeH;
		}
		// ���[�v
		if (scrY[SKILLEF1] >= imageSizeH) {
			scrX[SKILLEF1] = 0.0f;
			scrY[SKILLEF1] = 0.0f;
		}
	}

}
// �X�L���G�t�F�N�g2�X�V
void CLoad::SK2Update(float imageSizeW, float imageSizeH, float sizeW, float sizeH, int fr)
{
	// �A�j���[�V��������
	efFrame[SKILLEF2]++;

	if (efFrame[SKILLEF2] % fr == 0) {

		// �`��ʒu���W�{size
		scrX[SKILLEF2] += sizeW;

		// �c������+size
		if (scrX[SKILLEF2] >= imageSizeW && imageSizeH >= sizeH) {
			scrX[SKILLEF2] = 0.0f;
			scrY[SKILLEF2] += sizeH;
		}
		// ���[�v
		if (scrY[SKILLEF2] >= imageSizeH) {
			scrX[SKILLEF2] = 0.0f;
			scrY[SKILLEF2] = 0.0f;
		}
	}

}
// �u���C�N�G�t�F�N�g�X�V
void CLoad::BRUpdate(float imageSizeW, float imageSizeH, float sizeW, float sizeH, int fr)
{
	// �A�j���[�V��������
	efFrame[STUNEF]++;

	if (efFrame[STUNEF] % fr == 0) {

		// �`��ʒu���W�{size
		scrX[STUNEF] += sizeW;

		// �c������+size
		if (scrX[STUNEF] >= imageSizeW && imageSizeH >= sizeH) {
			scrX[STUNEF] = 0.0f;
			scrY[STUNEF] += sizeH;
		}
		// ���[�v
		if (scrY[STUNEF] >= imageSizeH) {
			scrX[STUNEF] = 0.0f;
			scrY[STUNEF] = 0.0f;
		}
	}

}

// �A�j���[�V�����`��
void CLoad::Draw(float x, float y, float sizeW, float sizeH, float rate, int grh, bool tr, int i)
{

	DrawRectRotaGraph(x, y, scrX[i], scrY[i], sizeW, sizeH, rate, 0.0f, grh, TRUE, tr);
	
}

// ���y�Đ��֐�
void CLoad::SoundPlay(int soundGrh, int HowTo)
{
	if (CheckSoundMem(soundGrh) == false) {
		PlaySoundMem(soundGrh,HowTo);
	}
}

// ���y��~�֐�
void CLoad::SoundStop(int soundGrh)
{
	if (CheckSoundMem(soundGrh) == true) {
		StopSoundMem(soundGrh);
	}
}

// �I������
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

