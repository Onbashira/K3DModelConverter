#pragma once
#include <fbxsdk.h>
#include <vector>
#include <map>
#include <memory>

class FbxMeshAnalizer;
 
class FbxNodeAnalizer
{
private:
	int _hierarchy;
	std::vector<std::shared_ptr<FbxMeshAnalizer>> _meshAnalzier;
protected:

public:

private:

protected:
	
	int GetHierarchy();

	bool NodeDistributer(FbxNode* scene);

	virtual bool PreAnalize(FbxScene* scene);

	virtual bool PostAnalize(FbxScene* scene);

	virtual bool PreAnalizeChildren(FbxNode* node);

	virtual bool PostAnalizeChildren(FbxNode* node);

	virtual bool CatchErr(FbxNode* errNode);

	virtual bool RootNode(FbxNode* root);

	virtual bool UnidentifiedNode(FbxNode* node);

	virtual bool NullNode(FbxNode* node,FbxNull* null);

	virtual bool MarkerNode(FbxNode* node, FbxMarker* marker);

	virtual bool SkeletonNode(FbxNode* node, FbxSkeleton* skelton);

	virtual bool MeshNode(FbxNode* node, FbxMesh* mesh);

	virtual bool NURBNode(FbxNode* node, FbxNurbs* nurb);

	virtual bool PatchNode(FbxNode* node, FbxPatch* nurb);

	virtual bool CameraNode(FbxNode* node, FbxCamera* nurb);

	virtual bool CameraSwitcherNode(FbxNode* node, FbxCameraSwitcher* nurb);

	virtual bool LightNode(FbxNode* node,FbxLight* light);

	virtual bool OpticaReferenceNode(FbxNode* node,FbxOpticalReference* optRef);

	virtual bool OpticalMakerNode(FbxNode* node);

	virtual bool ConstraintNode(FbxNode* node);

	virtual bool NurbCurveNode(FbxNode* node,FbxNurbsCurve* nurbsCurve);

	virtual bool TrimNurbSurfaceNode(FbxNode* node , FbxTrimNurbsSurface* trimNurbSurface);

	virtual bool NurbSurfaceNode(FbxNode* node, FbxNurbsSurface* nurbSurface);

	virtual bool BoundaryNode(FbxNode* node , FbxBoundary* boundary);

	virtual bool ShapeNode(FbxNode* node , FbxShape* shape);

public:

	FbxNodeAnalizer();

	virtual ~FbxNodeAnalizer();

	bool Analize(FbxScene* scene);


};

