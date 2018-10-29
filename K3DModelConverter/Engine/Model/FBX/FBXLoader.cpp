#include <fbxsdk.h>
#include "FBXLoader.h"




FBXLoader::FBXLoader()
{
}


FBXLoader::~FBXLoader()
{
}

void FBXLoader::Load(std::string filePath)
{

	fbxsdk::FbxManager* manager = fbxsdk::FbxManager::Create();

	fbxsdk::FbxIOSettings* ioSettings = fbxsdk::FbxIOSettings::Create(manager, IOSROOT);

	manager->SetIOSettings(ioSettings);

	fbxsdk::FbxImporter* importer = fbxsdk::FbxImporter::Create(manager, "");
	//インポーター初期化
	if (!importer->Initialize(filePath.c_str(), -1, manager->GetIOSettings())) {

	}

	//シーンの作成
	fbxsdk::FbxScene* scene = fbxsdk::FbxScene::Create(manager, "Scene");

	//ロードしたファイルをシーンにインポート
	importer->Import(scene);
	//インポーターの破棄（FbxSceneが設定されるとインポーターが安全に破棄できるらしい）
	importer->Destroy();

	//メインアナライズ
	_analizer.Analize(scene);


}
