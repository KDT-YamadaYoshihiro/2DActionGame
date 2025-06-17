//#pragma once
//#include "CTecture.h"
//#include <map>
//#include<string>
//#include <memory>
//#include "DxLib.h"
//
////�@�摜�̓ǂݍ��݂ƊǗ�������
//
//class CTectureFactry {
//private:
//	//�@�摜�v�[�������Č����ł���悤��
//	std::map <std::string, std::shared_ptr<CTecture>> textureContainer;
//
//	// �摜�N���X�̐���
//	std::shared_ptr<CTecture> createTexture(std::string fileName) {
//		// �摜�̓ǂݍ���
//		int handle = LoadGraph(fileName.c_str());
//		// �摜�N���X�̐���
//		auto newTexture = std::make_shared<CTecture>(handle);
//		// ���������摜�N���X��Ԃ�
//		return newTexture;
//	}
//
//public:
//
//	// �摜�N���X�̎擾
//	std::shared_ptr<CTecture> GetTexture(std::string fileName) {
//		// �t�@�C�����ŉ摜����
//		auto ite = textureContainer.find(fileName);
//
//		// �R���e�i�Ȃ��񂠂�΂��̉摜�N���X�|�C���^��Ԃ�
//		if (ite != textureContainer.end()) {
//			return ite->second;
//		}
//
//		// �R���e�i���ɂȂ�����ΐV���ɉ摜�N���X�𐶐����ăR���e�i�ɓo�^
//		auto newTecture = createTexture(fileName);
//		textureContainer.insert(std::make_pair(fileName, newTecture));
//
//		// �쐬�����摜�N���X��Ԃ�
//		return newTecture;
//	}
//
//};