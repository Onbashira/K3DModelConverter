
#include <stdio.h>  /* printf */
#include <stdlib.h>  /* system */
#include <iostream>
#include <string>
#include "Engine/Util/Utility.h"
#include "Engine/Util/Logger.h"
#include "Engine/Model/PMD/PMDLoader.h"
#include "Engine/Model/PMX/PMXLoader.h"
#include "Engine/Model/FBX/FBXLoader.h"

const std::string FILE_EXTENSION[] = {
	{"fbx"},
	{"pmx"},
	{"pmd"},
};

static std::string TEST_LOAD_PATH = "./Model/神楽/神楽（アニメver1.02）Kagura_animeVer.fbx";

int main(int argc,char *argv[]) {

	if (argc >= 2) {
		printf("ファイルパス = %s\n", argv[1]);
	}
	else {
		printf("引数なし\n");
	}
	std::string filepath(TEST_LOAD_PATH);
	
	std::string extension = K3D12::Util::ExtensionExtruction(filepath);
	
	K3D12::SystemLogger::GetInstance().Log(K3D12::LogLevel::Info,"拡張子 = " + extension);


	if (extension == FILE_EXTENSION[0]) {
		FBXLoader::GetInstance().Load(filepath);
	}
	else if (extension == FILE_EXTENSION[1]){
		auto model = K3D12::PMXLoader::GetInstance().Load(filepath);

	}
	else {
		auto model = K3D12::PMDLoader::GetInstance().Load(filepath);
	}

	/* Windowsから直接起動すると一瞬でコマンドプロンプトが閉じるので対策 */
	system("pause");

	return 0;

};