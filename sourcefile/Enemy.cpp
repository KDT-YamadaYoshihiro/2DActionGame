#include "Enemy.h"

// �R���X�g���N�^
CEnemy::CEnemy()
{
	// �����o�[�ϐ��̏�����
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

// �f�X�g���N�^
CEnemy::~CEnemy()
{
}

// ������
void CEnemy::Init()
{
	// �t���[���Ǘ�
	frame = 0;
	// �e�L�����N�^�[HP
	hp = EHPMAX;
	// �e�L�����N�^�[�̍U����
	atk = 0;
	// �e�L�����N�^�[�̃t���O
	flag = 0;

	// �d�͉����x
	vec = 0.0f;
	// �d��
	gr = 0.0f;

	// ���ݔ���
	enable = true;
	// ���Wx
	posX = 1500.0f;
	// ���Wy
	posY = FLOOR - JUMPDIS;
	// �g�k��
	rate = RATE;
	// �p�x
	angle = 0.0f;
	// �T�C�Y
	size = 200;
	// ���]����
	tran = false;
	// �ړ����x
	speed = 0.0f;

	// �v���C���[�Ƃ̋��������߂�ϐ�
	dis = 0.0f;
	// �W�����v���[�h
	jumpMode = JWAIT;
	// �W�����v����
	jumpLimit = true;
	// ����W�����v������
	jumpNum = 0;
	// �u���C�N�l
	stunNum = 0;

	// ��s���[�h
	flyMode = FLYWAIT;
	// �~�̍��W
	CyclePosX = posX;
	CyclePosY = posY;
	// �~�̃T�C�Y
	CycleSize = 0;

	// ����ڔ�s�U����
	flyNum = 0;

	//�@��s�U���p�^�[�����[�h
	flyPattern = -1;

	// ���U���ϐ�(���W�A�e�k���A�T�C�Y�A�J�E���g)
	for (int i = 0; i < FLAREMAX; i++) {
		flarePosX[i] = 0.0f;
		flarePosY[i] = 0.0f;
		flareRate = 1.0;
		flareSize = 120;
		flareNum = 0;

		// �\�����̃{�b�N�X���W
		LBoxPosX[i] = 0.0f;
		LBoxPosY[i] = 0.0f;
		RBoxPosX[i] = 0.0f;
		RBoxPosY[i] = 0.0f;
	}

}

// �X�V
void CEnemy::Update(float playerX, float playerY)
{
	// �L������
	if (enable != true) {
		return;
	}

	// �t���[���Ǘ�
	frame++;

	// ===============================
	// �d�͐ݒ�
	// ===============================
	vec += 0.02;
	gr += vec;
	posY += gr;

	// ===============================
	// ���ݒ�
	// ===============================
	if (posY >= FLOOR - SIZE * 0.4 ) {
		posY = FLOOR - SIZE * 0.4;
		vec = 0.0f;
		gr = 0.0f;
	}

	// ================================
	// �U��
	// ================================
	
	// ��u���C�N��Ԏ��̂ݍs��
	if (flag != BREAK) {

		// ��s�U���łȂ��Ƃ�
		if (flag != FLYAT) {
			// 2�b���ɃW�����v
			if (this->frame % 120 == 0 ) {
				this->jumpLimit = true;
				JumpStart(playerX, playerY);
				jumpNum += 1;

			}

			// ����������
			if (this->jumpLimit == true) {
				// �W�����v�t���O�ɕύX
				flag = JUMPAT;
			}
			else {
				// ��������wait�ɂ��Ă���
				flag = ENEMYWAIT;
			}
			
			// �W�����v�t���O�̎�
			if (this->flag == JUMPAT) {
				// �W�����v�֐����Ă�
				Jump(playerX, playerY);
			}
		}

		// ��s��ԂłȂ��Ƃ�&& �W�����v�����񐔂�/5�̂��܂�S�̂Ƃ�
		if (flyMode == FLYWAIT  && jumpNum % 5 == 4) {
			// ��s�U���t���O�ɂ���
			flag = FLYAT;
		}
		// ��s�U���t���O�̎���s�U���֐����Ă�
		if (flag == FLYAT) { Fly(playerX, playerY); }
		
	}


	// =================================
	// ���ݒ�
	// =================================

	//�@�X�^���l���}�b�N�X�̎�
	if (stunNum >= STUN) {
		flag = BREAK;
	}
	// �u���C�N���̎�
	if (flag == BREAK) {
		// �X�^���l�̌���
		stunNum -= 0.5f;
	}
	// �X�^���l���[���ɂȂ�����
	if (stunNum <= 0.0f) {
		// �t���O�I��
		flag = !BREAK;
	}

	// HP���[���ɂȂ����Ƃ�
	if (this->hp < 0) {
		// hp��0�����ɂ��Ȃ�
		hp = 0;
	}
	// �X�^���̃}�b�N�X
	if (this->stunNum >= STUN) {
		stunNum = STUN;
	}

}

// �`��
void CEnemy::Draw(int enemyGrh, int flareGrh)
{
	// �{�X�{��
	DrawRotaGraph(posX, posY, rate, angle, enemyGrh, TRUE, tran);
	
	// ��
	for (int i = 0; i < FLAREMAX; i++) {
		if (CyclePosX >= flarePosX[i] && flyPattern == ONE) {
			// �\�����i�F�̓����x�������ĕ`��j
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
			DrawFillBox(LBoxPosX[i], LBoxPosY[i], RBoxPosX[i], RBoxPosY[i], GetColor(255, 255, 255));
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

			// ��
			DrawRotaGraph(flarePosX[i], flarePosY[i], flareRate, 0, flareGrh, TRUE, FALSE);
		}
	}
	// �{�X��s�U�����̉~
	DrawCircle(CyclePosX, CyclePosY, CycleSize, GetColor(125, 125, 125), true);

	// HP
	CChar::Draw(WINDOW_W - 50.0f, 20.0f, -this->hp, -EHPMAX);
	// �u���C�N�Q�[�W
	DrawBox((WINDOW_W - 50) - (stunNum*4), 60, WINDOW_W - 50, 80, GetColor(0, 0, 255),true);
	DrawBox((WINDOW_W - 50) - 400, 60, WINDOW_W - 50, 80, GetColor(255, 255, 255), false);
}

// �I��
void CEnemy::End()
{

}

// �W�����v�X�^�[�g�֐�
void CEnemy::JumpStart(float playerX, float PlayerY)
{
	// �v���C���[�Ƃ̋��������߂�
	dis = playerX - posX;

}

// �W�����v�֐�
void CEnemy::Jump(float playerX, float playerY)
{
	switch (jumpMode) {

	case JWAIT:

		jumpMode = JMOVE;

		break;

	case JMOVE:

		// �ړ��ʂ̐ݒ�
		speed = JUMPSPEED;
		
		// �ړ�
		posY -= speed;

		// �v���C���[�Ƃ̋���
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

		// �ړ����
		if (posY <= FLOOR - JUMPDIS) {
			// ����
			// �W�����v����OFF
			jumpLimit = false;
			// �_���[�W����OFF
			damageLimit = true;
		}
		
		break;

	}

}

 //��s�U���֐�
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


	// �J�n�����i�{�X�`��̔�\���A�~�̕\���A���x�X�V�j
	case FLYSTART:

		// �{�X�摜�̑ދ�
		rate -= 0.1;
 		if (rate <= 0.00f) {rate = 0.00f;}

		// �~�`��̏o��
		CycleSize += 2;
		if (CycleSize >= 100) { CycleSize = 100; }

		// ���x�X�V
		speed = FLYSPEED;

		// ���[�h�̐؂�ւ�
		if (rate == 0.0f && CycleSize == 100) { flyMode = FLY; }

		break;

	// �\�������~�̉�ʏ㕔�ړ��A�U���X�^���o�C����
	case FLY:

		// �_���[�W��������
		damageLimit = true;

		// ��ʏ㕔�Ɉړ�
		CyclePosY -= speed;

		// ��ʊO�ɍs�����烂�[�h�̐؂�ւ�
		if (CyclePosY <= -CycleSize) {
			// ����ڂ�fly�U���Ȃ̂��ɂ���ăp�^�[�����ω�
			if (flyNum % 3 == 0) {

				// ���W�̍X�V
				CyclePosX = WINDOW_W + CycleSize;
				CyclePosY = FLOOR - CycleSize;

				flyMode = FLYMOVE;
				// �p�^�[��1���[�h��
				flyPattern = ZERO;

			}
			else if (flyNum % 3 == 1) {

				// ���W�X�V
				CyclePosX = -CycleSize;
				CyclePosY = +CycleSize;

				// ���U���X�^���o�C
				FlareStart();

				flyMode = FLYMOVE;
				// �p�^�[��2���[�h��
				flyPattern = ONE;
				

			}
			else {

				// ���W�X�V
				CyclePosX = WINDOW_W + CycleSize;
				CyclePosY = FLOOR + CycleSize;

				flyMode = FLYMOVE;
				// �p�^�[��3���[�h��
				flyPattern = ZERO;

			}

		}

		break;

	// �ړ��U������
	case FLYMOVE:

		// �p�^�[����(flyNum++)
		switch (flyPattern) {

		// 1�p�^�[����:�n�ʍ��W
		case ZERO:

			// ��������E���ֈړ�
			CyclePosX -= speed;

			// ����ʊO�ɍs�����Ƃ�
			if (CyclePosX <= -CycleSize) {

				// ���W�X�V
				CyclePosX = 1500.0f;
				CyclePosY = -CycleSize;

				// �X�^���o�C�t���[���̍X�V
				standbyframe = 2 * SECONDS;

				// ���[�h�̕ύX
				if (flyNum % 3 == 0){
					flyMode = DWON;				
					// ���[�hfalse��
					flyPattern = -1;
				}
				else if (flyNum % 3 == 2) { flyPattern = TWOSTANDBY; }
			}

			break;

			// 2�p�^�[���ځF�v���C���[���
			// ���𗎂Ƃ�
		case ONE:

			// �E�����獶���ֈړ�
			CyclePosX += speed;

			// �~�������W�𒴂�����B
			for (int i = 0; i < FLAREMAX; i++) {

				if (CyclePosX >= flarePosX[i]) {
					RBoxPosY[i] += speed;
				}


				if (RBoxPosY[i] >= FLOOR) {

					// �ړ���~
					RBoxPosY[i] = FLOOR;

					if (CyclePosX >= WINDOW_W + CycleSize && RBoxPosY[i] == FLOOR) {
						// �J�E���g�_�E���J�n
						flareFrame--;
					}
				}

			}
			if (flareFrame <= 0) {
				FlareMove();
			}
			// ���̂��ׂĂ��n�ʂɂ��܂��̓v���C���[�ɓ������Ă����
			if (flareNum >= FLAREMAX) {
				//�@���W�X�V
				CyclePosX = 1500.0f;
				CyclePosY = -CycleSize;
				// �J�E���g���Z�b�g
				flareNum = 0;
				// ���[�h�̕ύX
				flyPattern = -1;
				flyMode = DWON;
			}

			break;

		case TWOSTANDBY:

			// ��ʊO����o�Ă���
			CyclePosY += 4;

			// �w��n�ɂ������U��~
			if (CyclePosY >= CycleSize) {
				CyclePosY = CycleSize;
				standbyframe--;
			}

			// �t���[�����[���ɂȂ�܂Ńv���C���[X��ǔ�
			if (standbyframe >= ZEROFRAME) {
				CyclePosX = playerX;
			}
			// �[���ɂȂ����烂�[�h�ύX
			if (standbyframe <= ZEROFRAME) {
				flyPattern = TWO;
			}

			break;

		// 3�p�^�[���ځF�v���C���[�Ɍ������Ē�����
		case TWO:

			// �n�ʂɌ������ė���
			CyclePosY += speed;
			// �n�ʂɂ����烂�[�h�ύX
			if (CyclePosY >= FLOOR - CycleSize) {
				// �n�ʂɂ߂荞�܂Ȃ�
				CyclePosY = FLOOR - CycleSize;
				// ���W�X�V
				posX = CyclePosX;
				// ���[�hfalse��
				flyPattern = -1;
				// ���[�h�ύX
				flyMode = FLYEND;
			}

			break;

		}


		break;

	// �n�ʂɍ~���
	case DWON:

		// �n�ʂɍ~���
		CyclePosY += speed;

		if (CyclePosY >= FLOOR - CycleSize) {
			// �n�ʂŎ~�܂�
			CyclePosY = FLOOR - CycleSize;
			// �{�X�摜�̍��W�ړ�
			posX = CyclePosX;
			posY = CyclePosY;
			// ���[�h�̕ύX
			flyMode = FLYEND;
		}

		break;

	// �I������(�{�X�摜�̕\���A�~�̔�\���A�U�����[�h�̏I��)
	case FLYEND:

		// �{�X�摜�̏o��
		rate += 0.05;
		if (rate >= RATE) { rate = RATE; }

		// �~�`��̑ދ�
		CycleSize -= 2;
		if (CycleSize <= 0) { CycleSize = 0; }

		// ���x�X�V
		speed = FLYSPEED;

		// ���[�h�̐؂�ւ�
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

// ���U���X�^�[�g�֐�
void CEnemy::FlareStart()
{
	// ���W�̍X�V
	for (int i = 0; i < FLAREMAX; i++) {
		// �����W
		flarePosX[i] = flareSize + i * (flareSize * 2);
		flarePosY[i] = flareSize;

		// ���˃J�E���g�t���[���X�V
		flareFrame = 60;
	
		// �\�������W
		LBoxPosX[i] = flarePosX[i] - FLARESIZE/2;
		LBoxPosY[i] = flarePosY[i];
		RBoxPosX[i] = LBoxPosX[i] + FLARESIZE;
		RBoxPosY[i] = flarePosY[i];

	}
}

// ���U�����[�u�֐�
void CEnemy::FlareMove()
{
	// ���[�v����
	for (int i = 0; i < FLAREMAX; i++) {
		// �\����̒�~
		RBoxPosY[i] = FLOOR;

		// ���𒼉��ړ�
		flarePosY[i] += FLARESPEED;
		LBoxPosY[i] += FLARESPEED;
		// �n�ʂƐڐG�����Ƃ�
		if (flarePosY[i] >= FLOOR - (flareSize / 2)) {
			// ���W�̍X�V
			flarePosY[i] = 0.0f;
			// �J�E���g+1����
			flareNum++;
		}
	}

}

