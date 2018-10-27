#pragma once
#include <fbxsdk.h>
#include <string>
#include "../../Util/Math.h"

//マテリアル解析
class FbxMaterialAnalizer
{
private:
	Vector3 _ambient;
	Vector3 _diffuse;
	Vector3 _specular;
	Vector3 _emissive;
	Vector3 _bump;
	float	_transparency;
	float	_shininess;
	float   _reflectance;
	std::string _ambientTex;
	std::string _diffuseTex;
	std::string _specularTex;
	std::string _emissiveTex;
	std::string _bumpTex;
public:
	enum PROPERTY_TYPES {
		PROPERTY_TYPE_DIFFUSE = 0,
		PROPERTY_TYPE_SPECULAR,
		PROPERTY_TYPE_EMISSIVE,
		PROPERTY_TYPE_BUMP
	};
private:

	//! Lambert情報セット
	void SetLambertInfo(FbxSurfaceLambert* lambert);

	//! テクスチャ情報を取得
	void SetTextureInfo(FbxSurfaceMaterial* material, const char* matFlag, std::string& outTexName);

public:

	FbxMaterialAnalizer();

	virtual	~FbxMaterialAnalizer();

	//! 解析
	void Analize(FbxSurfaceMaterial* material);

	//! アンビエントを取得
	Vector3& GetAmbient();

	//! ディフューズを取得
	Vector3& GetDiffuse();

	//! スペキュラを取得
	Vector3& GetSpecular();

	//! エミッシブを取得
	Vector3& GetEmissive();

	//! バンプを取得
	Vector3& GetBump();

	//! 透過度を取得
	float GetTransparency();

	//! 光沢を取得
	float GetShininess();

	//! 反射を取得
	float GetReflectivity();

	//! テクスチャファイル名を取得
	std::string GetTextureFileName(PROPERTY_TYPES propertyType);
};

