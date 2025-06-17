#include "Player.h"

// �R���X�g���N�^
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

	// �d�͌n
	gr = 0.0f;
	vec = 0.0f;

	// �����o�[�ϐ�
	// �e��N�[���^�C��
	AtCool = 0;
	Sk1Cool = 0;
	Sk2Cool = 0;

	// �N�[���^�C���\�L�p�̔��a�ϐ�
	AtCRot = 0.0f;
	Sk1CRot = 0.0f;
	Sk2CRot = 0.0f;
	
	// cv�Đ��J�E���g
	CVplayCount = 0;
}

// �f�X�g���N�^
CPlayer::~CPlayer()
{

}

// ������
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

	// �d��
	gr = 0.0f;
	vec = 0.0f;

	// �����o�[�ϐ�
	// �e��N�[���^�C��
	AtCool = 0;
	Sk1Cool = 0;
	Sk2Cool = 0;

	// �N�[���^�C���\�L�p�̔��a�ϐ�
	AtCRot = 0.0f;
	Sk1CRot = 0.0f;
	Sk2CRot = 0.0f;

	// cv�Đ��J�E���g
	CVplayCount = 0;


}

// �X�V����
void CPlayer::Update(float eX, float eY, int eSize)
{
	// �L������
	if (enable != true) {
		return;
	}

	// ===============================
	// �d�͐ݒ�
	// ===============================
	vec += 0.02;
	gr += vec;
	posY += gr;

	// ===============================
	// ���ݒ�
	// ===============================
	if (posY >= FLOOR) {
		posY = FLOOR;
		vec = 0.0f;
		gr = 0.0f;
		jumpLimit = true;
	}

	// �U�����̃t���[���J�E���g
	frame--;

	// �N�[���^�C��
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

	// �J�E���g���Z�b�g
	// �U���t���[��
	if (frame <= ZEROFRAME) {frame = ZEROFRAME;}
	// �N�[���^�C��
	if (AtCool <= ZEROFRAME) {AtCool = ZEROFRAME;}
	if (Sk1Cool <= ZEROFRAME) {Sk1Cool = ZEROFRAME;}
	if (Sk2Cool <= ZEROFRAME) {Sk2Cool = ZEROFRAME;}

	// ����֐��̌Ăяo��
	if (flag != DAMAGE) {
		Operation();
	}
	
	// �ړ�����
	MoveRestrict();
	
	// �U���֐�
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

	// �@�_���[�W���󂯂��Ƃ��̏����֐��Ăяo��
	Damage(eX, eY, eSize);
	
}

// �`��
void CPlayer::Draw(int grh)
{
	// �L�����N�^�[�{��
	DrawRotaGraph(posX, posY, rate, angle, grh, TRUE, tran);

	// HP
	CChar::Draw(10.0f, WINDOW_H - 50.0f, this->hp , PHPMAX);

	// �X�L���N�[���^�C��
	for (int i = 0; i < 3; i++) {
		// �~�̉�
		DrawCircle(400 + i * (ROT*2 + 10), WINDOW_H - 50, ROT, WHITE, false);
	}
	// �~�̒��g
	DrawCircle(400, WINDOW_H - 50,  AtCRot, WHITE, true);
	DrawCircle(410 + ROT * 2, WINDOW_H - 50, Sk1CRot, WHITE, true);
	DrawCircle(420 + ROT * 4, WINDOW_H - 50, Sk2CRot, WHITE, true);

}

// �I��
void CPlayer::End()
{

}

// ����֐�
void CPlayer::Operation()
{
	// �L������
	if (enable != true) {
		return;
	}
	// �ړ���ɓ����蔻��

	// ����
	// �L�[���͎�
	if (frame <= ZEROFRAME) {
		if (IsKeyRepeat(KEY_INPUT_RIGHT)) {

			// �`��؂�ւ�
			flag = WALK;
			// �ړ���
			speed = WALKSPEED;
			// �ړ�
			posX += speed;
			// �摜���]�L��
			tran = false;

		}
		else if (IsKeyRepeat(KEY_INPUT_LEFT)) {

			// �`��؂�ւ�
			flag = WALK;
			// �ړ���
			speed = WALKSPEED;
			// �ړ�
			posX -= speed;
			// �摜���]�L��
			tran = true;
		}
		else {
			// �t���[������
			imageFrame--;

			// �`��̐؂�ւ�
			if (flag != STOP0 && imageFrame <= ZEROFRAME && jumpLimit == true) {
				flag = STOP0;
				imageFrame = HALFSECONDS;
			}
			if (flag != STOP1 && imageFrame <= ZEROFRAME && jumpLimit == true) {
				flag = STOP1;
				imageFrame = HALFSECONDS;
			}
		}


		// �E�_�b�V����
		if (IsKeyRepeat(KEY_INPUT_RIGHT) && IsKeyRepeat(KEY_INPUT_LSHIFT)) {
			// �摜�̕ύX
			flag = DASH;
			// �ړ��ʂ̕ύX
			speed = DASHSPEED;
			// �ړ�
			posX += speed;
		}
		// ���_�b�V����
		if (IsKeyRepeat(KEY_INPUT_LEFT) && IsKeyRepeat(KEY_INPUT_LSHIFT)) {
			// �摜�̕ύX
			flag = DASH;
			// �ړ��ʂ̕ύX
			speed = DASHSPEED;
			// �ړ�
			posX -= speed;
		}

		// �Î~�W�����v
		// ��L�[���͎�
		if ((flag == STOP0 || flag == STOP1) && IsKeyRepeat(KEY_INPUT_UP) && jumpLimit == true) {
			// �`��؂�ւ�
			flag = JUMP;
			// �ړ��ʂ̐ݒ�
			speed = JUMPVECTOR;
			// �ړ�
			posY -= speed;
			// �ړ����
			if (posY <= FLOOR - WJUMPDIS) {
				// ����
				jumpLimit = false;
			}
		}
		// �����W�����v
		if (flag == WALK && IsKeyRepeat(KEY_INPUT_UP) && jumpLimit == true) {

			// �`��؂�ւ�
			flag = JUMP;
			// �ړ��ʂ̐ݒ�
			speed = JUMPVECTOR;
			// �ړ�
			posY -= speed;
			// �ړ����
			if (posY <= FLOOR - WJUMPDIS) {
				// ����
				jumpLimit = false;
			}

		}
		// �_�b�V���W�����v
		// ��L�[���͎�
		if (flag == DASH && IsKeyRepeat(KEY_INPUT_UP) && jumpLimit == true) {
			// �`��؂�ւ�
			flag = JUMP;
			// �ړ��ʂ̐ݒ�
			speed = JUMPVECTOR;
			// �ړ�
			posY -= speed;
			// �ړ����
			if (posY <= FLOOR - DJUMPDIS) {
				// ����
				jumpLimit = false;
			}

		}
	}
}
// �ړ�����֐�
void CPlayer::MoveRestrict()
{
	// �L������
	if (enable != true) {
		return;
	}
	// �ړ�����
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
// �U���֐�
void CPlayer::Attack()
{
	// �L������
	if (enable != true) {
		return;
	}
	// �t���[����0�ȏ�̎�
	if (frame >= ZEROFRAME) {
		flag = ATTACK;
	}
	// �t���[����30�ȏ�̎�
	if (frame <= ZEROFRAME) {
		// flag��ATTACK�ɂ���
		flag = !ATTACK;
	}

}
// �X�L���֐�
void CPlayer::Skill()
{
		// �L������
	if (enable != true) {
		return;
	}
	// �t���[����0�̎�&&�L�[���͎�
	if (frame >= ZEROFRAME) {

		if(flag == SKILL1){
			flag = SKILL1;
		}
		if (flag == SKILL2) {
			flag = SKILL2;
		}
	}
	// �t���[����0�ȉ��̎�
	if (frame <= ZEROFRAME) {
		// flag��!SKILL�ɂ���
		flag = !SKILL1;
		flag = !SKILL2;
	}

}
// �_���[�W�󂯊֐�
void CPlayer::Damage(float eX, float eY, int eSize)
{
	// �t���[���͏�Ɍ���
	damageFrame--;

	// �t���[�����[���ȏ�̎�
	if (damageFrame >= ZEROFRAME) {
		// �t���O�ύX
		flag = DAMAGE;
		// �E�����̎�
		if (posX <= eX) {
			tran = RIGHT;
			speed = -DAMAGESPEED;
			posX += speed;
		}
		// ������
		else if (posX >= eX) {
			tran = LEFT;
			speed = DAMAGESPEED;
			posX += speed;
		}

		if (damageFrame <= ZEROFRAME) {
			flag = !DAMAGE;
		}
		// HP��0�̎�
		if (this->hp <= 0) {
			// hp��0�����ɂȂ�Ȃ��悤�ɂ���
			this->hp = 0;
			flag = DEAD;
		}
	}


}
// ���S�����֐�
void CPlayer::DeadCheck()
{
	// �L������
	if (enable != true) {
		return;
	}

	if (hp <= 0) {
		hp = 0;
		this->flag = DEAD;
	}
}


