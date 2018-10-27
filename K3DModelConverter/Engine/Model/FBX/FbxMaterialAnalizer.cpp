#include "FbxMaterialAnalizer.h"





FbxMaterialAnalizer::FbxMaterialAnalizer()
{
}


FbxMaterialAnalizer::~FbxMaterialAnalizer()
{
}


void FbxMaterialAnalizer::SetLambertInfo(FbxSurfaceLambert * lambert)
{
	_ambient.x = (float)lambert->Ambient.Get()[0];
	_ambient.y = (float)lambert->Ambient.Get()[1];
	_ambient.z = (float)lambert->Ambient.Get()[2];
	SetTextureInfo(lambert, FbxSurfaceLambert::sAmbient,_ambientTex);

	//model->m_materials[i].ambientFactor = (float)lambert->AmbientFactor.Get();

	_diffuse.x = (float)lambert->Diffuse.Get()[0];
	_diffuse.y = (float)lambert->Diffuse.Get()[1];
	_diffuse.z = (float)lambert->Diffuse.Get()[2];
	SetTextureInfo(lambert, FbxSurfaceLambert::sDiffuse, _diffuseTex);

	//model->m_materials[i].diffuseFactor = (float)lambert->DiffuseFactor.Get();

	_emissive.x = (float)lambert->Emissive.Get()[0];
	_emissive.y = (float)lambert->Emissive.Get()[1];
	_emissive.z = (float)lambert->Emissive.Get()[2];
	SetTextureInfo(lambert, FbxSurfaceLambert::sEmissive, _emissiveTex);

	//model->m_materials[i].emissiveFactor = (float)lambert->EmissiveFactor.Get();

	_bump.x = (float)lambert->Bump.Get()[0];
	_bump.y = (float)lambert->Bump.Get()[1];
	_bump.z = (float)lambert->Bump.Get()[2];
	SetTextureInfo(lambert, FbxSurfaceLambert::sBump, _bumpTex);

	_transparency = (float)lambert->TransparencyFactor.Get();

}

void FbxMaterialAnalizer::SetTextureInfo(FbxSurfaceMaterial * material, const char * matFlag, std::string& outTexName)
{
	FbxProperty prop = material->FindProperty(matFlag);
	int layerNum = prop.GetSrcObjectCount<fbxsdk::FbxLayeredTexture>();

	//レイヤードテクスチャのローディング
	if (layerNum > 0) {


	}
	else {
		int texNum = prop.GetSrcObjectCount<fbxsdk::FbxFileTexture>();
		for (int j = 0; j < texNum; j++) {
			//j番目のテクスチャオブジェクトを取得
			fbxsdk::FbxFileTexture* texture = fbxsdk::FbxCast<fbxsdk::FbxFileTexture>(prop.GetSrcObject<fbxsdk::FbxFileTexture>(j));
			//テクスチャ名の取得
			if (texture) {
				//std::string textureName = texture->GetName();
				std::string textureName = texture->GetRelativeFileName();
				//UVset名の取得
				std::string uvSetName = texture->UVSet.Get().Buffer();
				
				outTexName.swap(textureName);

				//Fbx::FbxTexture texRes;
				//texRes.texturePath = GetRelativeTexturePath(path, textureName);
				//texRes.textureName = texture->GetName();
				//texRes.textureCount = 0;
				//texRes.uvSetName = uvSetName;
				
			}
		}
	}

}

void FbxMaterialAnalizer::Analize(FbxSurfaceMaterial * material)
{

	if (material->GetClassId().Is(FbxSurfaceLambert::ClassId)) {
		SetLambertInfo(reinterpret_cast<FbxSurfaceLambert*>(material));
	}
	else if (material->GetClassId().Is(FbxSurfacePhong::ClassId)) {
		auto phong = reinterpret_cast<FbxSurfacePhong*>(material);
		//Up cast
		SetLambertInfo(reinterpret_cast<FbxSurfacePhong*>(material));

		_specular.x = (float)phong->Specular.Get()[0];
		_specular.y = (float)phong->Specular.Get()[1];
		_specular.z = (float)phong->Specular.Get()[2];

		SetTextureInfo(phong, FbxSurfaceMaterial::sSpecular, _specularTex);

		_shininess = (float)phong->Shininess.Get();

		_reflectance = (float)phong->ReflectionFactor.Get();
	}

}

Vector3 & FbxMaterialAnalizer::GetAmbient()
{
	return _ambient;
}

Vector3 & FbxMaterialAnalizer::GetDiffuse()
{
	return _diffuse;
}

Vector3 & FbxMaterialAnalizer::GetSpecular()
{
	return _specular;
}

Vector3 & FbxMaterialAnalizer::GetEmissive()
{
	return _emissive;
}

Vector3 & FbxMaterialAnalizer::GetBump()
{
	return _bump;
}

float FbxMaterialAnalizer::GetTransparency()
{
	return 0.0f;
}

float FbxMaterialAnalizer::GetShininess()
{
	return 0.0f;
}

float FbxMaterialAnalizer::GetReflectivity()
{
	return 0.0f;
}

std::string FbxMaterialAnalizer::GetTextureFileName(PROPERTY_TYPES propertyType)
{
	switch (propertyType)
	{
	case FbxMaterialAnalizer::PROPERTY_TYPE_DIFFUSE:
		return this->_diffuseTex;
		break;
	case FbxMaterialAnalizer::PROPERTY_TYPE_SPECULAR:
		return this->_specularTex;
		break;
	case FbxMaterialAnalizer::PROPERTY_TYPE_EMISSIVE:
		return this->_emissiveTex;
		break;
	case FbxMaterialAnalizer::PROPERTY_TYPE_BUMP:
		return this->_bumpTex;
		break;
	default:
		break;
	}
	return std::string();
}
