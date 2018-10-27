#pragma once
#include <fbxsdk.h>
#include <string>
#include "../../Util/Math.h"

//�}�e���A�����
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

	//! Lambert���Z�b�g
	void SetLambertInfo(FbxSurfaceLambert* lambert);

	//! �e�N�X�`�������擾
	void SetTextureInfo(FbxSurfaceMaterial* material, const char* matFlag, std::string& outTexName);

public:

	FbxMaterialAnalizer();

	virtual	~FbxMaterialAnalizer();

	//! ���
	void Analize(FbxSurfaceMaterial* material);

	//! �A���r�G���g���擾
	Vector3& GetAmbient();

	//! �f�B�t���[�Y���擾
	Vector3& GetDiffuse();

	//! �X�y�L�������擾
	Vector3& GetSpecular();

	//! �G�~�b�V�u���擾
	Vector3& GetEmissive();

	//! �o���v���擾
	Vector3& GetBump();

	//! ���ߓx���擾
	float GetTransparency();

	//! ������擾
	float GetShininess();

	//! ���˂��擾
	float GetReflectivity();

	//! �e�N�X�`���t�@�C�������擾
	std::string GetTextureFileName(PROPERTY_TYPES propertyType);
};

