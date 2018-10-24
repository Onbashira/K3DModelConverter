#pragma once
#include <fbxsdk.h>
#include <string>
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

public:

	virtual bool Analize(fbxsdk::FbxLayer* layer, fbxsdk::FbxNode* node);

	std::string GetTextureLavel(int index);

	FbxLayerAnalizer();
	virtual ~FbxLayerAnalizer();
};

