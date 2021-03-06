#pragma once
#include <fbxsdk.h>
#include <string>
#include <vector>
#include <memory>
#include <map>
#include "../../Util/Math.h"
#include "FbxMaterialAnalizer.h"
#include "FbxUVAnalizer.h"

class FbxMeshAnalizer
{
private:

protected:

	unsigned int										_polygonNum;

	unsigned int										_polygonVertexNum;

	std::vector<unsigned int>							_indexAry;

	unsigned int										_layerNum;

	unsigned int										_controlPointNum;
	
	std::vector<Vector4>								_controlPointAry;

	unsigned int										_vertexNum;

	std::vector<Vector3>								_vetexAry;

	unsigned int										_normalNum;

	std::vector<Vector3>								_normalAry;

	std::map<int, int>									_primitiveMap;

	FbxMesh*											_mesh;

	unsigned int										_materialNum;

	std::vector<std::shared_ptr<FbxMaterialAnalizer>>	_material;

	unsigned int										_uvNum;

	std::vector<std::shared_ptr<FbxUVAnalizer>>			_uv;

public:

private:

protected:


	void AnalizeCoordinate(FbxMesh* mesh);

	void AnalizeNormal(FbxMesh* mesh);

	void AnalizeMaterial(FbxMesh* mesh);

	void AnalizeUV(FbxMesh* mesh);

public:

	FbxMeshAnalizer();

	~FbxMeshAnalizer();

	bool Analize(FbxNode* node, FbxMesh* mesh);

	unsigned int GetPolygonNum();

	unsigned int GetIndexNum();

	unsigned int* GetIndexArray();

	std::vector<unsigned int>& GetIndexVector();

	std::map<int, int>& GetPrimitiveNumMap();

	unsigned int GetControlNum();

	Vector4* GetControlPointArray();

	std::vector<Vector4>& GetControlPointVector();

	unsigned int GetVertexNum();

	Vector3* GetVertexArray();

	std::vector<Vector3>& GetVertexVector();

	unsigned int GetNormalNum();

	Vector3* GetNormalArray();

	std::vector<Vector3>& GetNormalVector();

	unsigned int GetMaterialNum();

	std::shared_ptr<FbxMaterialAnalizer> GetMaterial(int index);

	unsigned int GetUVNum(unsigned int index);

	std::shared_ptr<FbxUVAnalizer> GetUV(int index);

};

