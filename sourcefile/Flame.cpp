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
////�@������
//void CFlame::Init()
//{
//	mode = FWAIT;
//	speed = 5.0f;
//}
//
//// �X�V
//void CFlame::Update(float eneX, float eneY, bool eneTr, int eneFl, float px, float py, int psize, int pfl,int pHp)
//{
//	// �G�l�~�[�t���O���t���C���̎�
//	if (eneFl == FIREAT && mode == FWAIT) {
//		Start(eneX, eneY, eneTr, eneFl, px, py);
//	}
//
//	// ���[�u���[�h���Ɉړ�����
//	if (mode == FMOVE) {
//		// ���[�u�֐�
//		Move();
//	}
//}
//
////�@�`��
//void CFlame::Draw(int grh)
//{
//	if (mode == FMOVE) {
//		DrawRotaGraph(posX, posY, rate, angle, grh, TRUE, tran);
//	}
//}
//
//// �I������
//void CFlame::End()
//{
//}
//
//// �X�^�[�g�֐�
//void CFlame::Start(float eneX, float eneY, bool eneTr, int eneFl, float plaX, float plaY)
//{
//	// ���W�̏�����
//	// �E�����̎�
//	if (eneTr == false) {
//		posX = eneX - POSX;
//		posY = eneY - POSY;
//	}
//	else {
//		// �������̎�
//		posX = eneX + POSX;
//		posY = eneY - POSY;
//
//	}
//	// �����ݒ�(�v���C���[�Ɍ������āj
//	// ���������߂�
//	disX = plaX - posX;
//	disY = plaY - posY;
//	// �p�x�����߂�
//	angle = atan2(disY, disX);
//	// �t���O�̕ύX
//	mode = FMOVE;
//}
//// ���[�u�֐�
//void CFlame::Move()
//{
//	// �ݒ肵�������Ɍ������Ĉړ�
//	goalX += speed * cos(D2R(angle));
//	goalY += speed * sin(D2R(angle));
//
//	 //�v���C���[�@|| �� ||��ʊO�ɍs�����Ƃ��ɏ��ŁB
//	if (posX <= 0 || posX >= WINDOW_W || posY >= FLOOR || posY <= 0) {
//		mode = FWAIT;
//	}
//
//}
