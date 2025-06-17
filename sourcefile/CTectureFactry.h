//#pragma once
//#include "CTecture.h"
//#include <map>
//#include<string>
//#include <memory>
//#include "DxLib.h"
//
////　画像の読み込みと管理をする
//
//class CTectureFactry {
//private:
//	//　画像プール化そて検索できるように
//	std::map <std::string, std::shared_ptr<CTecture>> textureContainer;
//
//	// 画像クラスの生成
//	std::shared_ptr<CTecture> createTexture(std::string fileName) {
//		// 画像の読み込み
//		int handle = LoadGraph(fileName.c_str());
//		// 画像クラスの生成
//		auto newTexture = std::make_shared<CTecture>(handle);
//		// 生成した画像クラスを返す
//		return newTexture;
//	}
//
//public:
//
//	// 画像クラスの取得
//	std::shared_ptr<CTecture> GetTexture(std::string fileName) {
//		// ファイル名で画像検索
//		auto ite = textureContainer.find(fileName);
//
//		// コンテナない二あればその画像クラスポインタを返す
//		if (ite != textureContainer.end()) {
//			return ite->second;
//		}
//
//		// コンテナ内にないければ新たに画像クラスを生成してコンテナに登録
//		auto newTecture = createTexture(fileName);
//		textureContainer.insert(std::make_pair(fileName, newTecture));
//
//		// 作成した画像クラスを返す
//		return newTecture;
//	}
//
//};