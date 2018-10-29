#include "FbxNodeAnalizer.h"
#include "FbxMeshAnalizer.h"
#include "../../Util/Logger.h"
#include <sstream>
#include <iomanip>
#include <string>

FbxNodeAnalizer::FbxNodeAnalizer()
{
}


FbxNodeAnalizer::~FbxNodeAnalizer()
{
}


int FbxNodeAnalizer::GetHierarchy()
{
	return _hierarchy;
}

bool FbxNodeAnalizer::NodeDistributer(FbxNode * node)
{
	FbxNodeAttribute *attribute = node->GetNodeAttribute();
	if (attribute == nullptr) {
		RootNode(node);
	}
	else {
		FbxNodeAttribute::EType type;

		switch (type)
		{
		case fbxsdk::FbxNodeAttribute::eUnknown:
			break;
		case fbxsdk::FbxNodeAttribute::eNull:
			NullNode(node, reinterpret_cast<FbxNull*>(attribute));
			break;
		case fbxsdk::FbxNodeAttribute::eMarker:
			MarkerNode(node, reinterpret_cast<FbxMarker*>(attribute));
			break;
		case fbxsdk::FbxNodeAttribute::eSkeleton:
			SkeletonNode(node, reinterpret_cast<FbxSkeleton*>(attribute));
			break;
		case fbxsdk::FbxNodeAttribute::eMesh:
			MeshNode(node, reinterpret_cast<FbxMesh*>(attribute));
			break;
		case fbxsdk::FbxNodeAttribute::eNurbs:
			NURBNode(node, reinterpret_cast<FbxNurbs*>(attribute));
			break;
		case fbxsdk::FbxNodeAttribute::ePatch:
			PatchNode(node, reinterpret_cast<FbxPatch*>(attribute));
			break;
		case fbxsdk::FbxNodeAttribute::eCamera:
			CameraNode(node, reinterpret_cast<FbxCamera*>(attribute));
			break;
		case fbxsdk::FbxNodeAttribute::eCameraStereo:
			break;
		case fbxsdk::FbxNodeAttribute::eCameraSwitcher:
			CameraSwitcherNode(node, reinterpret_cast<FbxCameraSwitcher*>(attribute));
			break;
		case fbxsdk::FbxNodeAttribute::eLight:
			LightNode(node, reinterpret_cast<FbxLight*>(attribute));
			break;
		case fbxsdk::FbxNodeAttribute::eOpticalReference:
			OpticaReferenceNode(node, reinterpret_cast<FbxOpticalReference*>(attribute));
			break;
		case fbxsdk::FbxNodeAttribute::eOpticalMarker:
			OpticalMakerNode(node);
			break;
		case fbxsdk::FbxNodeAttribute::eNurbsCurve:
			NurbCurveNode(node, reinterpret_cast<FbxNurbsCurve*>(attribute));
			break;
		case fbxsdk::FbxNodeAttribute::eTrimNurbsSurface:
			TrimNurbSurfaceNode(node, reinterpret_cast<FbxTrimNurbsSurface*>(attribute));
			break;
		case fbxsdk::FbxNodeAttribute::eBoundary:
			BoundaryNode(node, reinterpret_cast<FbxBoundary*>(attribute));
			break;
		case fbxsdk::FbxNodeAttribute::eNurbsSurface:
			NurbSurfaceNode(node, reinterpret_cast<FbxNurbsSurface*>(attribute));
			break;
		case fbxsdk::FbxNodeAttribute::eShape:
			ShapeNode(node, reinterpret_cast<FbxShape*>(attribute));
			break;
		case fbxsdk::FbxNodeAttribute::eLODGroup:
			break;
		case fbxsdk::FbxNodeAttribute::eSubDiv:
			break;
		case fbxsdk::FbxNodeAttribute::eCachedEffect:
			break;
		case fbxsdk::FbxNodeAttribute::eLine:
			break;
		default:
			return false;
			break;
		}
	}

	PreAnalizeChildren(node);

	int childNum = node->GetChildCount();
	++_hierarchy;

	for (int i = 0; i < childNum; ++i) {
		FbxNode* child = node->GetChild(i);
		if (!NodeDistributer(child)) {
			CatchErr(child);
		}
	}

	--_hierarchy;

	PostAnalizeChildren(node);



	return true;
}

bool FbxNodeAnalizer::PreAnalize(FbxScene * scene)
{
	return true;
}

bool FbxNodeAnalizer::PostAnalize(FbxScene * scene)
{
	return true;
}

bool FbxNodeAnalizer::PreAnalizeChildren(FbxNode * node)
{
	return true;
}

bool FbxNodeAnalizer::PostAnalizeChildren(FbxNode * node)
{
	return true;
}

bool FbxNodeAnalizer::CatchErr(FbxNode * errNode)
{
	return true;
}

bool FbxNodeAnalizer::RootNode(FbxNode * root)
{
	return true;
}

bool FbxNodeAnalizer::UnidentifiedNode(FbxNode * node)
{
	return true;
}

bool FbxNodeAnalizer::NullNode(FbxNode * node, FbxNull * null)
{
	return true;
}

bool FbxNodeAnalizer::MarkerNode(FbxNode * node, FbxMarker * marker)
{
	return true;
}

bool FbxNodeAnalizer::SkeletonNode(FbxNode * node, FbxSkeleton * skelton)
{
	return true;
}

bool FbxNodeAnalizer::MeshNode(FbxNode * node, FbxMesh * mesh)
{

	std::shared_ptr<FbxMeshAnalizer> analizer = std::make_shared<FbxMeshAnalizer>();

	this->_meshAnalzier.push_back(analizer);

	analizer->Analize(node, mesh);

	std::stringstream ss;

	{
		ss << "頂点数 : ";
		ss << analizer->GetControlNum();
		K3D12::SystemLogger::GetInstance().Log(K3D12::LogLevel::Info, ss.str());
		ss.str("");
	}

	{
		ss << "ポリゴン数 : ";
		ss << analizer->GetControlNum();
		K3D12::SystemLogger::GetInstance().Log(K3D12::LogLevel::Info, ss.str());
		ss.str("");
	}

	{
		ss << "頂点インデックス数 : ";
		ss << analizer->GetIndexNum();
		K3D12::SystemLogger::GetInstance().Log(K3D12::LogLevel::Info, ss.str());
		ss.str("");
	}

	{
		ss << "法線数 : ";
		ss << analizer->GetNormalNum();
		K3D12::SystemLogger::GetInstance().Log(K3D12::LogLevel::Info, ss.str());
		ss.str("");
	}

	{
		ss << "UV数 : ";
		ss << analizer->GetUVNum(0);
		K3D12::SystemLogger::GetInstance().Log(K3D12::LogLevel::Info, ss.str());
		ss.str("");
	}

	{
		ss << "マテリアル数 : ";
		ss << analizer->GetMaterialNum();
		K3D12::SystemLogger::GetInstance().Log(K3D12::LogLevel::Info, ss.str());
		ss.str("");
	}

	return true;
}

bool FbxNodeAnalizer::NURBNode(FbxNode * node, FbxNurbs * nurb)
{
	return true;
}

bool FbxNodeAnalizer::PatchNode(FbxNode * node, FbxPatch * nurb)
{
	return true;
}

bool FbxNodeAnalizer::CameraNode(FbxNode * node, FbxCamera * nurb)
{
	return true;
}

bool FbxNodeAnalizer::CameraSwitcherNode(FbxNode * node, FbxCameraSwitcher * nurb)
{
	return true;
}

bool FbxNodeAnalizer::LightNode(FbxNode * node, FbxLight * light)
{
	return true;
}

bool FbxNodeAnalizer::OpticaReferenceNode(FbxNode * node, FbxOpticalReference * optRef)
{
	return true;
}

bool FbxNodeAnalizer::OpticalMakerNode(FbxNode * node)
{
	return true;
}

bool FbxNodeAnalizer::ConstraintNode(FbxNode * node)
{
	return true;
}

bool FbxNodeAnalizer::NurbCurveNode(FbxNode * node, FbxNurbsCurve * nurbsCurve)
{
	return true;
}

bool FbxNodeAnalizer::TrimNurbSurfaceNode(FbxNode * node, FbxTrimNurbsSurface * trimNurbSurface)
{
	return true;
}

bool FbxNodeAnalizer::NurbSurfaceNode(FbxNode * node, FbxNurbsSurface * nurbSurface)
{
	return true;
}

bool FbxNodeAnalizer::BoundaryNode(FbxNode * node, FbxBoundary * boundary)
{
	return true;
}

bool FbxNodeAnalizer::ShapeNode(FbxNode * node, FbxShape * shape)
{
	return true;
}

bool FbxNodeAnalizer::Analize(FbxScene * scene)
{
	if (scene == nullptr) {
		return false;
	}
	if (!PreAnalize(scene)) {
		return false;
	}

	_hierarchy = 0;

	FbxNode* rootNode = scene->GetRootNode();

	bool res = NodeDistributer(rootNode);
	if (rootNode = 0) {
		return false;
	}

	if (!PostAnalize(scene)) {
		return false;
	}

	return res;
}