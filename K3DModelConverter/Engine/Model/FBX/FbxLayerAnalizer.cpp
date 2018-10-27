#include <fbxsdk.h>
#include "FbxLayerAnalizer.h"

namespace {
	// テクスチャラベル
	const char* textureLabel_g[] = {
		"Ambient Factor",
		"Ambient",
		"Bump",
		"Diffuse Factor",
		"Diffuse",
		"Emissive Factor",
		"Emissive",
		"NormalMap",
		"Reflection Factor",
		"Reflection",
		"Shininess",
		"Specular Factor",
		"Specular",
		"Transparency Factor",
		"Transparency"
	};

	const char* nullStr_g = "";
}

bool FbxLayerAnalizer::Analize(fbxsdk::FbxLayer * layer, fbxsdk::FbxNode * node)
{
	return false;
}

std::string FbxLayerAnalizer::GetTextureLabel(int index)
{
	return std::string();
}

std::string FbxLayerAnalizer::GetTextureLabel(TEXTURE_TYPES type)
{
	return std::string();
}

std::string FbxLayerAnalizer::GetTextureName(int index)
{
	return std::string();
}

std::string FbxLayerAnalizer::GetTextureName(TEXTURE_TYPES type)
{
	return std::string();
}

FbxLayerAnalizer::FbxLayerAnalizer()
{
	for (int i = 0; i < sizeof(textureNameAry) / sizeof(const char*); ++i) {
		textureNameAry[i] = nullStr_g;
	}
}


FbxLayerAnalizer::~FbxLayerAnalizer()
{
}

