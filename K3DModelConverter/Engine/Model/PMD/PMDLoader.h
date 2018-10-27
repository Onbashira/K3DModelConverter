#pragma once
#include <memory>
#include "../IModel.h"
namespace K3D12 {

	class PMDModel;

	class PMDLoader
	{
	private:
		 void LoadVertex(FILE* fp, PMDModel* model);
		 void LoadIndexList(FILE* fp, PMDModel* model);
		 void LoadMaterial(FILE* fp, PMDModel* model);
		 void LoadSkelton(FILE* fp, PMDModel* model);
		 void LoadIK(FILE* fp, PMDModel* model);
		 void LoadMorph(FILE* fp, PMDModel* model);

	public:
		static PMDLoader& GetInstance() {
			static PMDLoader instance;
			return instance;
		}
		 std::shared_ptr<PMDModel> Load(std::string path);
		PMDLoader();
		~PMDLoader();
	};
}