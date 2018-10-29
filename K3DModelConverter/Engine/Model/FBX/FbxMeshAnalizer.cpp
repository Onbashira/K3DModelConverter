#include "FbxMeshAnalizer.h"



FbxMeshAnalizer::FbxMeshAnalizer()
{
}


FbxMeshAnalizer::~FbxMeshAnalizer()
{
}


void FbxMeshAnalizer::AnalizeCoordinate(FbxMesh * mesh)
{
	//���_�C���f�b�N�X�̃��[�h
	int* indexBuffer = mesh->GetPolygonVertices();

	this->_polygonVertexNum = mesh->GetPolygonVertexCount();
	this->_indexAry.resize(_polygonVertexNum);
	for (int i = 0; i < _polygonVertexNum; i++) {
		this->_indexAry[i] = indexBuffer[i];
	}

	//�R���g���[���|�C���g�̎擾
	this->_controlPointNum = mesh->GetControlPointsCount(); // �R���g���[���|�C���g�̐��@���Ƃŕ���UV�l�������_�𕪗����邽�ߕύX����

	fbxsdk::FbxVector4* vertexBuffer = mesh->GetControlPoints();

	this->_controlPointAry.resize(_controlPointNum);
	for (int i = 0; i < _controlPointNum; i++) {
		_controlPointAry[i].x = (float)vertexBuffer[i][0];
		_controlPointAry[i].y = (float)vertexBuffer[i][1];
		_controlPointAry[i].z = (float)vertexBuffer[i][2];
		_controlPointAry[i].w = (float)vertexBuffer[i][3];
	}

	//
}

void FbxMeshAnalizer::AnalizeNormal(FbxMesh * mesh)
{
	int normalLayerCount = mesh->GetElementNormalCount();

	for (int layer = 0; layer < normalLayerCount; layer++) {
		//�G�������g�̎擾
		fbxsdk::FbxGeometryElementNormal* normalElement = mesh->GetElementNormal(layer);

		unsigned int normalNum = normalElement->GetDirectArray().GetCount();
		unsigned int indexNum = normalElement->GetIndexArray().GetCount();

		//�}�b�s���O���[�h�̎擾(C++17�̐V�@�\���g���Ă��܂��j
		switch (fbxsdk::FbxGeometryElement::EMappingMode mappingMode = normalElement->GetMappingMode())
		{
		case fbxsdk::FbxLayerElement::eByPolygonVertex:
			//���̂܂܏������s
		case fbxsdk::FbxLayerElement::eByControlPoint:
			//���t�@�����X���[�h�̎擾
			switch (fbxsdk::FbxGeometryElement::EReferenceMode referenceMode = normalElement->GetReferenceMode())
			{
			case fbxsdk::FbxLayerElement::eDirect:
			{

				this->_normalAry.resize(normalNum);
				this->_normalNum = normalNum;
				Vector3 normal;
				for (int i = 0; i < normalNum; i++) {
					_normalAry[i].x = (float)normalElement->GetDirectArray().GetAt(i)[0];
					_normalAry[i].y = (float)normalElement->GetDirectArray().GetAt(i)[1];
					_normalAry[i].z = (float)normalElement->GetDirectArray().GetAt(i)[2];
				}

			}
			break;
			}
			break;
		}
		//��񂾂����[�h�B�}���`Normal�ɂ͑Ή����Ȃ�
		break;
	}
}

void FbxMeshAnalizer::AnalizeMaterial(FbxMesh * mesh)
{
	auto node = mesh->GetNode();
	if (node == 0) {
		return;
	}
	unsigned int materialNum = node->GetMaterialCount();
	if (materialNum == 0) {
		return;
	}

	for (unsigned int i = 0; i < materialNum; ++i) {
		FbxSurfaceMaterial* material = node->GetMaterial(i);
		this->_material.push_back(std::make_shared<FbxMaterialAnalizer>());
		_material.back()->Analize(material);
	}
}

void FbxMeshAnalizer::AnalizeUV(FbxMesh * mesh)
{
	this->_uv.push_back(std::make_shared<FbxUVAnalizer>());
	this->_uv.back()->Analize(mesh);
}

bool FbxMeshAnalizer::Analize(FbxNode * node, FbxMesh * mesh)
{
	this->_mesh = mesh;

	this->_polygonNum = mesh->GetPolygonCount();
	this->_polygonVertexNum = mesh->GetPolygonVertexCount();
	for (unsigned int i = 0; i < _polygonNum; i++) {
		int indexNumInPolygon = mesh->GetPolygonSize(i);
		std::map<int, int>::iterator itr = _primitiveMap.find(indexNumInPolygon);
		if (itr == _primitiveMap.end()) {
			_primitiveMap.insert(std::pair<int, int>(indexNumInPolygon, 1));
		}
		else {
			itr->second += 1;
		}
	}

	AnalizeCoordinate(mesh);

	AnalizeNormal(mesh);

	AnalizeUV(mesh);

	AnalizeMaterial(mesh);


	return false;
}

unsigned int FbxMeshAnalizer::GetPolygonNum()
{
	return _polygonNum;
}

unsigned int FbxMeshAnalizer::GetIndexNum()
{
	return _indexAry.size();
}

unsigned int * FbxMeshAnalizer::GetIndexArray()
{
	return _indexAry.data();
}

std::vector<unsigned int>& FbxMeshAnalizer::GetIndexVector()
{
	return _indexAry;
}

std::map<int, int>& FbxMeshAnalizer::GetPrimitiveNumMap()
{
	return _primitiveMap;
}

unsigned int FbxMeshAnalizer::GetControlNum()
{
	return this->_controlPointNum;
}

Vector4 * FbxMeshAnalizer::GetControlPointArray()
{
	return this->_controlPointAry.data();
}

std::vector<Vector4>& FbxMeshAnalizer::GetControlPointVector()
{
	return this->_controlPointAry;
}

unsigned int FbxMeshAnalizer::GetVertexNum()
{
	return this->_vertexNum;
}

Vector3 * FbxMeshAnalizer::GetVertexArray()
{
	return this->_vetexAry.data();
}

std::vector<Vector3>& FbxMeshAnalizer::GetVertexVector()
{
	return this->_vetexAry;
}

unsigned int FbxMeshAnalizer::GetNormalNum()
{
	return _normalNum;
}

Vector3 * FbxMeshAnalizer::GetNormalArray()
{
	return _normalAry.data();
}

std::vector<Vector3>& FbxMeshAnalizer::GetNormalVector()
{
	return _normalAry;
}

unsigned int FbxMeshAnalizer::GetMaterialNum()
{
	return _materialNum;
}

std::shared_ptr<FbxMaterialAnalizer> FbxMeshAnalizer::GetMaterial(int index)
{
	return this->_material.at(index);
}

unsigned int FbxMeshAnalizer::GetUVNum(unsigned int index)
{
	return this->_uv.at(index)->GetUVsNum();
}

std::shared_ptr<FbxUVAnalizer> FbxMeshAnalizer::GetUV(int index)
{
	return this->_uv.at(index);
}


