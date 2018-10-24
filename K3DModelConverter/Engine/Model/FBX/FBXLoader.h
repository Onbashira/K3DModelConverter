#pragma once
#include <string>
class FBXLoader
{
private:
public:
private:
	//void VertexLoad( );
	//void IndexLoad( );
	//void UVLoad( );
	//void MaterialLoad();
	//void TextureLoad();
	//void MetaDataLoad();
	//void SkeltonLoad();
	//void MorphLoad();

	//void VertexFix();
	//void UVFix();
	//void IndexFix();
	//void TextureFix();
	//void SkeltonFix();
public:
	static FBXLoader& GetInstance() {
		static FBXLoader instance;
		return instance;
	}

	void Load(std::string filePath);
	FBXLoader();
	virtual ~FBXLoader();
};

