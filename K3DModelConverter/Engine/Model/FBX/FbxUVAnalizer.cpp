#include "FbxUVAnalizer.h"





FbxUVAnalizer::FbxUVAnalizer()
{
}


FbxUVAnalizer::~FbxUVAnalizer()
{
}


bool FbxUVAnalizer::SetPropertyUV(FbxLayerElementUV * elem, UVInfo & uvinfo)
{
	//MeshUVのロード
	//uv数を取得
	int uvDirectCount = elem->GetDirectArray().GetCount();
	int uvIndexCount = elem->GetIndexArray().GetCount();
	int size = uvDirectCount < uvIndexCount ? uvDirectCount : uvIndexCount;
	uvinfo._uv.resize(size);

	//マピングモード
	switch (fbxsdk::FbxGeometryElement::EMappingMode mappingMode = elem->GetMappingMode())
	{
		//ポリゴン毎
	case fbxsdk::FbxLayerElement::eByPolygonVertex:
		//リファレンスモード
		switch (fbxsdk::FbxGeometryElement::EReferenceMode referenceMode = elem->GetReferenceMode())
		{

		case fbxsdk::FbxLayerElement::eIndex:
			break;
		case fbxsdk::FbxLayerElement::eDirect:

			//頂点毎ループ
			for (int j = 0; j < size; j++) {
				uvinfo._uv[j].emplace_back((float)elem->GetDirectArray().GetAt(j)[0], (float)elem->GetDirectArray().GetAt(j)[1]);
			}
			uvinfo._uvSetName = std::string(elem->GetName());

			break;
		case fbxsdk::FbxLayerElement::eIndexToDirect:

			//頂点毎ループ
			for (int j = 0; j < size; j++) {

				uvinfo._uv[j].emplace_back((float)elem->GetDirectArray().GetAt(elem->GetIndexArray().GetAt(j))[0],
					(float)elem->GetDirectArray().GetAt(elem->GetIndexArray().GetAt(j))[1]);

			}
			uvinfo._uvSetName = std::string(elem->GetName());

			break;
		}
		break;
	}

	return true;
}

bool FbxUVAnalizer::Analize(FbxMesh * mesh)
{

	//MeshUVのロード
	int uvLayerCount = mesh->GetElementUVCount();
	for (int layer = 0; layer < uvLayerCount; layer++) {
		fbxsdk::FbxGeometryElementUV* uv = mesh->GetElementUV(layer);

		//uv数を取得
		int uvDirectCount = uv->GetDirectArray().GetCount();
		int uvIndexCount = uv->GetIndexArray().GetCount();
		int size = uvDirectCount < uvIndexCount ? uvDirectCount : uvIndexCount;
		this->_meshUV._uv.resize(size);

		//マピングモード
		switch (fbxsdk::FbxGeometryElement::EMappingMode mappingMode = uv->GetMappingMode())
		{
			//ポリゴン毎
		case fbxsdk::FbxLayerElement::eByPolygonVertex:
			//リファレンスモード
			switch (fbxsdk::FbxGeometryElement::EReferenceMode referenceMode = uv->GetReferenceMode())
			{

			case fbxsdk::FbxLayerElement::eIndex:
				break;
			case fbxsdk::FbxLayerElement::eDirect:

				//頂点毎ループ
				for (int j = 0; j < size; j++) {
					this->_meshUV._uv[j].emplace_back((float)uv->GetDirectArray().GetAt(j)[0], (float)uv->GetDirectArray().GetAt(j)[1]);
				}
				_meshUV._uvSetName = std::string(uv->GetName());
				break;
			case fbxsdk::FbxLayerElement::eIndexToDirect:

				//頂点毎ループ
				for (int j = 0; j < size; j++) {
					this->_meshUV._uv[j].emplace_back((float)uv->GetDirectArray().GetAt(uv->GetIndexArray().GetAt(j))[0],
						(float)uv->GetDirectArray().GetAt(uv->GetIndexArray().GetAt(j))[1]);
				}
				_meshUV._uvSetName = std::string(uv->GetName());

				break;
			}
			break;
		}
		break;
	}
	return true;
}

bool FbxUVAnalizer::Analizer(FbxLayer * layer)
{
	bool isEffective = false;
	if (SetPropertyUV(layer->GetUVs(FbxLayerElement::EType::eTextureAmbient), this->_ambientUV)) isEffective = true;
	if (SetPropertyUV(layer->GetUVs(FbxLayerElement::EType::eTextureDiffuse), _diffuseUV)) isEffective = true;
	if (SetPropertyUV(layer->GetUVs(FbxLayerElement::EType::eTextureSpecular),_specularUV)) isEffective = true;
	if (SetPropertyUV(layer->GetUVs(FbxLayerElement::EType::eTextureEmissive),_emissiveUV)) isEffective = true;
	if (SetPropertyUV(layer->GetUVs(FbxLayerElement::EType::eTextureBump), _bumpUV)) isEffective = true;
	return isEffective;

}

unsigned int FbxUVAnalizer::GetUVsNum()
{
	return _meshUV._uv.size();
}

UVInfo & FbxUVAnalizer::GetMeshUV()
{
	return _meshUV;
}
