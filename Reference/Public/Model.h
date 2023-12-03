#pragma once

#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CModel final : public CComponent
{
private:
	CModel(ID3D11Device * pDevice, ID3D11DeviceContext * pContext);
	CModel(const CModel& rhs);
	virtual ~CModel() = default;


public:
	virtual HRESULT Initialize_Prototype(const string & strModelFilePath, _fmatrix PivotMatrix);
	virtual HRESULT Initialize(void* pArg);
	virtual HRESULT Render();

private:
	const aiScene* m_pAIScene = { nullptr };
	Assimp::Importer		m_Importer;

private:
	_uint					m_iNumMeshes = { 0 };
	vector<class CMesh*>	m_Meshes;



private:
	HRESULT	Ready_Meshes(_fmatrix PivotMatrix);

public:
	static CModel* Create(ID3D11Device * pDevice, ID3D11DeviceContext * pContext, const string & strModelFilePath, _fmatrix PivotMatrix);
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;
};

END