#pragma once
#include <memory>
#include "PMXModel.h"
#include "../IModel.h"

namespace K3D12 {

	class PMXModel;

	class PMXLoader
	{
	private:
		void LoadInfo(FILE*fp, K3D12::PMXModel* model);
		void LoadVertex(FILE*fp, K3D12::PMXModel* model);
		void LoadSurface(FILE*fp, K3D12::PMXModel* model);
		void LoadTexture(FILE*fp, K3D12::PMXModel* model);
		void LoadMaterials(FILE*fp, K3D12::PMXModel* model);
		void LoadBone(FILE*fp, K3D12::PMXModel* model);
		void LoadMorph(FILE*fp, K3D12::PMXModel* model);;
		void LoadDisplay(FILE*fp, K3D12::PMXModel* model);
		void LoadRigidBody(FILE*fp, K3D12::PMXModel* model);
		void LoadJoint(FILE*fp, K3D12::PMXModel* model);
	public:
		static PMXLoader& GetInstance() {
			static PMXLoader instance;
			return instance;
		}
		std::shared_ptr<K3D12::PMXModel>  Load(std::string modelPath);
		PMXLoader();
		~PMXLoader();
	};
}