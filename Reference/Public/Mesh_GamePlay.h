#pragma once
#include "Mesh.h"

BEGIN(Engine)

class CMesh_GamePlay : public CMesh
{
protected:
	CMesh_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CMesh_GamePlay(const CMesh_GamePlay& rhs);
	virtual ~CMesh_GamePlay() = default;

public:
	virtual HRESULT Initialize_Prototype(CModel::TYPE eModelType, const aiMesh* pAIMesh, _fmatrix PivotMatrix, const vector<class CBone*>& Bones);
	virtual HRESULT Ready_Vertices_NonAnim(const aiMesh* pAIMesh, DirectX::XMMATRIX PivotMatrix);
	virtual HRESULT Ready_Vertices_Anim(const aiMesh* pAIMesh, const std::vector<Engine::CBone*, std::allocator<Engine::CBone*>>& Bones);

public:
	static CMesh_GamePlay* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, CModel::TYPE eModelType, const aiMesh* pAIMesh, _fmatrix PivotMatrix, const vector<class CBone*>& Bones);
	virtual CComponent* Clone(void* pArg);
	virtual void Free() override;


};
END