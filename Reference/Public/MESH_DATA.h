#pragma once
#include "Base.h"
#include "BONE_DATA.h"
#include "Model.h"
BEGIN(Engine)

struct ENGINE_DLL MESH_DATA
{
	vector<BONE_DATA*>					Bone_Datas;
	VTXMESH*							pVertices;
	VTXANIMMESH*						pAnimVertices;
	VTXPOS*								pPosVertices;
	FACEINDICES32*						pIndices;

	string                              szName;

	_uint                               iNumVertices;
	_uint                               iNumFaces;
	_uint                               iNumBones;
	_uint                               iMaterialIndex;

	CModel::TYPE                        eModelType;

	HRESULT Make_MeshData(const CModel::TYPE& In_eModelType, aiMesh* In_pAiMesh, const _fmatrix& In_TransformMatrix, MESH_VTX_INFO* In_pVertexInfo);

public:
	void Bake_Binary(ofstream& os);
	void Load_FromBinary(ifstream& is);

private:
	void Check_Position(_float3& _vRecodePosion, _float3 _vValue, _bool(*_pFncPtr)(_float, _float));
};

END