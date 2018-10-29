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
	//�C���|�[�^�[������
	if (!importer->Initialize(filePath.c_str(), -1, manager->GetIOSettings())) {

	}

	//�V�[���̍쐬
	fbxsdk::FbxScene* scene = fbxsdk::FbxScene::Create(manager, "Scene");

	//���[�h�����t�@�C�����V�[���ɃC���|�[�g
	importer->Import(scene);
	//�C���|�[�^�[�̔j���iFbxScene���ݒ肳���ƃC���|�[�^�[�����S�ɔj���ł���炵���j
	importer->Destroy();

	//���C���A�i���C�Y
	_analizer.Analize(scene);


}
