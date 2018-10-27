#pragma once
#include <fbxsdk.h>
#include <string>

//レイヤ解析クラス
class FbxLayerAnalizer
{
private:

public:
	enum TEXTURE_TYPES {
		TEXTURE_TYPE_AmbientFactor = 0,
		TEXTURE_TYPE_Ambient,
		TEXTURE_TYPE_Bump,
		TEXTURE_TYPE_DiffuseFactor,
		TEXTURE_TYPE_Diffuse,
		TEXTURE_TYPE_EmissiveFactor,
		TEXTURE_TYPE_Emissive,
		TEXTURE_TYPE_NormalMap,
		TEXTURE_TYPE_ReflectionFactor,
		TEXTURE_TYPE_Reflection,
		TEXTURE_TYPE_Shininess,
		TEXTURE_TYPE_SpecularFactor,
		TEXTURE_TYPE_Specular,
		TEXTURE_TYPE_TransparencyFactor,
		TEXTURE_TYPE_Transparency,
		TEXTURE_TYPE_Num
	};
private:

protected:

	// テクスチャ名
	union {
		const char* textureNameAry[24];
		struct _textureName {
			const char* ambientFactor;
			const char* ambient;
			const char* bump;
			const char* diffuseFactor;
			const char* diffuse;
			const char* emissiveFactor;
			const char* emissive;
			const char* normalMap;
			const char* reflectionFactor;
			const char* reflection;
			const char* shininess;
			const char* specularFactor;
			const char* specular;
			const char* transparencyFactor;
			const char* transparency;
		} textureName;
	};

	const char* materialName;		//! マテリアル名

public:

	virtual bool Analize(fbxsdk::FbxLayer* layer, fbxsdk::FbxNode* node);

	std::string GetTextureLabel(int index);

	std::string GetTextureLabel(TEXTURE_TYPES type);

	std::string GetTextureName(int index);

	std::string GetTextureName(TEXTURE_TYPES type);

	FbxLayerAnalizer();
	virtual ~FbxLayerAnalizer();
};

