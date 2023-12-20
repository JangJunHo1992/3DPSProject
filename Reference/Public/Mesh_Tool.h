#pragma once
#include "Mesh.h"

BEGIN(Engine)

class CMesh_Tool : public CMesh
{
protected:
	CMesh_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CMesh_Tool(const CMesh_Tool& rhs);
	virtual ~CMesh_Tool() = default;

public:
	// CMesh을(를) 통해 상속됨
	virtual HRESULT Initialize_Prototype(const MODEL_TYPE eModelType, const MESH_DATA* pAIMesh, _fmatrix PivotMatrix, const vector<class CBone*>& Bones) override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual HRESULT Ready_Vertices_NonAnim(const MESH_DATA* pAIMesh, DirectX::XMMATRIX PivotMatrix);
	virtual HRESULT Ready_Vertices_Anim(const MESH_DATA* pAIMesh, const std::vector<Engine::CBone*, std::allocator<Engine::CBone*>>& Bones);

public:
	_bool			Picking(RAY ray, _float3* out);
	class CGameInstance* m_pGameInstance = nullptr;

public:
	static CMesh_Tool* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, const MODEL_TYPE eModelType, const MESH_DATA* pAIMesh, _fmatrix PivotMatrix, const vector<class CBone*>& Bones);
	virtual CComponent* Clone(void* pArg);
	virtual void Free() override;

};

END