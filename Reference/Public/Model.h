#pragma once

#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CModel final : public CComponent
{
public:
	enum TYPE { TYPE_NONANIM, TYPE_ANIM , TYPE_END};
private:
	CModel(ID3D11Device * pDevice, ID3D11DeviceContext * pContext);
	CModel(const CModel& rhs);
	virtual ~CModel() = default;

public:
	_uint Get_NumMeshes() const {
		return m_iNumMeshes;
	}

public:
	virtual HRESULT Initialize_Prototype(TYPE eType, const string & strModelFilePath, _fmatrix PivotMatrix);
	virtual HRESULT Initialize(void* pArg);
	virtual HRESULT Render(_uint iMeshIndex);

public:
	HRESULT	Bind_ShaderResource(class CShader* pShader, const _char* pConstantName, _uint iMeshIndex, aiTextureType eTextureType);
private:
	const aiScene* m_pAIScene = { nullptr };
	Assimp::Importer		m_Importer;

private:
	TYPE					m_eModelType = { TYPE_END };

	_uint					m_iNumMeshes = { 0 };
	vector<class CMesh*>	m_Meshes;

	_uint					m_iNumMaterials = { 0 };
	vector<MATERIAL_DESC>	m_Materials;

private:
	HRESULT	Ready_Meshes(_fmatrix PivotMatrix);
	HRESULT Ready_Materials(const string& strModelFilePath);
public:
	static CModel* Create(ID3D11Device * pDevice, ID3D11DeviceContext * pContext, TYPE eType, const string & strModelFilePath, _fmatrix PivotMatrix);
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;
};

END