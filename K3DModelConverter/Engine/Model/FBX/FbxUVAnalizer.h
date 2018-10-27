#pragma once
#include <vector>
#include <string>

#include "../../Util/Math.h"



struct UVInfo {
	std::string _uvSetName;
	std::vector<Vector2> _uv;

};

class FbxUVAnalizer
{
private:

	UVInfo _meshUV;
	UVInfo _diffuseUV;
	UVInfo _specularUV;
	UVInfo _bumpUV;
	UVInfo _emmisiveUV;
	UVInfo _normalMapUV;

protected:

public:

private:

protected:
	void SetPropertyUV(FbxLayerElementUV* elem, UVInfo& uvinfo);
public:
	FbxUVAnalizer();

	~FbxUVAnalizer();

	bool Analize(FbxMesh* mesh);

	bool Analizer(FbxLayer* layer);

	unsigned int GetUVsNum();

	
};

