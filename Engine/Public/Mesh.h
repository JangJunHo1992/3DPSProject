#pragma once

#include "VIBuffer.h"
#include "Model.h"
#include "MyAIMesh.h"

BEGIN(Engine)

class CMesh abstract : public CVIBuffer
{
protected:
	CMesh(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CMesh(const CMesh& rhs);
	virtual ~CMesh() = default;

public:
	_uint Get_MaterialIndex() const {
		return m_iMaterialIndex;
	}

public:
	HRESULT Initialize_Prototype_Origin(CModel::TYPE eModelType, CMyAIMesh pAIMesh, _fmatrix PivotMatrix, const vector<class CBone*>& Bones);
	virtual HRESULT Initialize_Prototype(CModel::TYPE eModelType, CMyAIMesh pAIMesh, _fmatrix PivotMatrix, const vector<class CBone*>& Bones) = 0;
	virtual HRESULT Initialize(void* pArg) override;

public:
	HRESULT Bind_BoneMatrices(class CShader* pShader, const _char* pConstantName, const vector<CBone*>& Bones);


protected:
	_char				m_szName[MAX_PATH];
	_uint				m_iMaterialIndex = { 0 };

	_uint				m_iNumBones = { 0 };
	vector<_uint>		m_BoneIndices;

	vector<_float4x4>	m_OffsetMatrices;

	VTXANIMMESH*		m_pAnimVertices = { nullptr };
	VTXMESH*			m_pVertices = { nullptr };
	_uint*				m_pIndices = { nullptr };

protected:
	HRESULT Ready_Vertices_NonAnim_Origin(CMyAIMesh pAIMesh, _fmatrix PivotMatrix);
	HRESULT Ready_Vertices_Anim_Origin(CMyAIMesh pAIMesh, const vector<class CBone*>& Bones);

	virtual HRESULT Ready_Vertices_NonAnim(CMyAIMesh pAIMesh, _fmatrix PivotMatrix) = 0;
	virtual HRESULT Ready_Vertices_Anim(CMyAIMesh pAIMesh, const vector<class CBone*>& Bones) = 0;



public:
	virtual CComponent* Clone(void* pArg) = 0;
	virtual void Free() override;
};

END