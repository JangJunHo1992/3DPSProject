#pragma once
#include "Base.h"

#include "ANIMATION_DATA.h"
#include "MESH_DATA.h"
#include "NODE_DATA.h"
#include "MATERIAL_DATA.h"

BEGIN(Engine)

struct ENGINE_DLL MODEL_DATA
{
	Assimp::Importer                    AiImporter;
	//const aiScene*                      pAiSceneModel = nullptr;

	NODE_DATA*							RootNode;

	vector<MATERIAL_DATA*>				Material_Datas;
	vector<MESH_DATA*>					Mesh_Datas;
	vector<ANIMATION_DATA*>				Animation_Datas;

	_float4x4                           TransformMatrix;

	_uint                               iNumMeshs;
	_uint                               iNumMaterials;
	_uint                               iNumAnimations;

	MODEL_TYPE                        eModelType;

	string                              szModelFilePath;
	string                              szModelFileName;
	string								szBinFilePath;
	MESH_VTX_INFO                       VertexInfo;


	HRESULT Make_ModelData(const char* szFilePath, const MODEL_TYPE& eInModelType, _fmatrix TransformMatrix, _bool bAnimZero = false);

	void OnDestroy();
	~MODEL_DATA();

public:
	void Bake_Binary();

	HRESULT Load_FromAssimp(const _bool bAnimZero);
	void Load_FromBinary();

	void Debug_AnimationLog(ofstream& os);
	void Debug_NonAnimLog(ofstream& os);
	void Debug_MeshLog(ofstream& os);
	void Compute_Center(MESH_VTX_INFO& _tVertexInfo);
	_float Get_MaxOffsetRange() const;
};

END
