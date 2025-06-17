#include "Ken.h"

// �R���X�g���N�^
CKen::CKen()
{
	// ���t���O
	flag = 0;
	// �����W�̊p�x
	rot = 0.0f;
	// �v���C���[�Ƃ̋���
	distance = 0.0f;
}

// �f�X�g���N�^
CKen::~CKen()
{
}

// ������
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

// �X�V����
void CKen::Update(float px, float py, int pfl, bool ptr, 
	float ex, float ey, int esize, int efl, bool etr ,int ehp, int estun)
{
	// �L������
	if (enable != true) {
		return;
	}

	// �U�����łȂ��Ƃ��A���t���O��WAIT�ɂ���
	if (pfl != ATTACK && pfl != SKILL1 && pfl != SKILL2) {
		this->flag = KENWAIT;
	}
	// �X�^�[�g�֐�
	if (pfl == ATTACK || pfl == SKILL1 || pfl == SKILL2) {
		AtStart(px, py, pfl, ptr);
	}

}

// �`�揈��
void CKen::Draw( int grh, int fl)
{
	// �L������
	if (enable != true) {
		return;
	}

	// �v���C���[�t���O���A�^�b�N||�X�L���̏ꍇ�`��
	if (fl == ATTACK || fl == SKILL1 || fl == SKILL2) {
		DrawRotaGraph(posX, posY, rate, D2R(angle), grh, TRUE, tran);
	}
}

// �I������
void CKen::End()
{
}

// �U���X�^�[�g�֐�
void CKen::AtStart(float x, float y, int fl, bool tr)
{
	// �L������
	if (enable != true) {
		return;
	}

	switch (flag) {

	case KENWAIT:

		speed = SPEED;

		// Player->flag == ATTACK�̎�
		if (fl == ATTACK) {

			// ���̍��W������
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

			// �X�C�b�`�̐؂�ւ�
			this->flag = ATMOVE;
		}

		// Player->flag == SKILL�̂Ƃ�
		if (fl == SKILL1 || fl == SKILL2) {

			// ���̍��W������
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

			// �X�C�b�`�̐؂�ւ�
			this->flag = SKMOVE;
		}

		break;

	case ATMOVE:
		
		// �ʏ�U���̌Ăяo��
		AttackMotion(x, y, tran);

		break;

	case SKMOVE:

		// �X�L���֐��̌Ăяo��
		SkillMotion(x, y, tran);

		break;
	}


}

// �ʏ�U���֐�
void CKen::AttackMotion(float x, float y, bool tr) {

	// �L������
	if (enable != true) {
		return;
	}

	// ���������߂�
	distance = x - posX;

	// ��x���W���w��͈͂܂ŉ�
	// ���ꂼ������Ă��������
	if (this->flag == ATMOVE) {
		if (tr == RIGHT) {
			posX += speed;
		}
		else if (tr == LEFT) {
			posX -= speed;
		}
	}

	// �ԍ����ȏ�̎�wait��Ԃɂ���
	if (distance >= INTERVAL || distance <= -INTERVAL) {
		this->flag = STOP;
		speed = 0.0f;
	}
}

// �X�L�����[�V�����֐�
void CKen::SkillMotion(float x, float y, bool tr) {

	// �L������
	if (enable != true) {
		return;
	}

	// �v���C���[�̌������E�����̎�
	if (tr == RIGHT) {

		// �p�x(rot)�𑝂₷
		rot += speed;
		// ����
		posX = x + DIS * cos(D2R(rot));
		// ����
		posY = y + DIS * sin(D2R(rot));
		// �摜�p�x�iangle�j�̕ύX
		angle += speed;
		// �I������
		if (rot >= 90) {
			speed = 0;
		}

	}// �v���C���[�̌������������̎�0
	else if (tr == LEFT) {


		// �p�x(rot)�𑝂₷
		rot -= speed;
		// ����
		posX = x - DIS * cos(D2R(rot));
		// ����
		posY = y - DIS * sin(D2R(rot));
		// �摜�p�x�iangle�j�̕ύX
		angle -= speed;
		// �I������
		if (rot <= -90) {
			speed = 0;
		}

	}
}

