#pragma once

#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CModel abstract : public CComponent
{
public:
	enum TYPE { TYPE_NONANIM, TYPE_ANIM, TYPE_END };

protected:
	CModel(ID3D11Device* pDevice , ID3D11DeviceContext* pContext);
	CModel(const CModel& rhs);
	virtual ~CModel() = default;

public:
	_uint Get_NumMeshes() const {
		return m_iNumMeshes;
	}
	vector<class CMesh*>* Get_Meshes() {
		return &m_Meshes;
	}

public:
	virtual HRESULT Initialize_Prototype(TYPE eType, const string & strModelFilePath, _fmatrix PivotMatrix);
	virtual HRESULT Initialize(void* pArg);
	virtual HRESULT Render(_uint iMeshIndex);

public:
	void Play_Animation(_float fTimeDelta);

public:
	HRESULT Bind_BoneMatrices(class CShader* pShader, const _char* pConstantName, _uint iMeshIndex);
	HRESULT Bind_ShaderResource(class CShader* pShader, const _char* pConstantName, _uint iMeshIndex, aiTextureType eTextureType);

protected:
	const aiScene*			m_pAIScene = { nullptr };
	Assimp::Importer		m_Importer;

protected:
	_float4x4				m_PivotMatrix;
	TYPE					m_eModelType = { TYPE_END };

	_uint					m_iNumMeshes = { 0 };
	vector<class CMesh*>	m_Meshes;

	_uint					m_iNumMaterials = { 0 };
	vector<MATERIAL_DESC>	m_Materials;

	//string									m_szModelKey;

	_uint							m_iNumAnimations = { 0 };
	_uint							m_iCurrentAnimIndex = { 0 };
	vector<class CAnimation*>		m_Animations;

	/* 내 모델의 전체 뼈들을 부모관계를 포함하여 저장한다. */
	vector<class CBone*>	m_Bones;
public:
	typedef vector<class CBone*>	BONES;


protected:
	template<class T>
	HRESULT	Ready_Meshes_Origin(_fmatrix PivotMatrix);
	virtual HRESULT	Ready_Meshes(_fmatrix PivotMatrix) PURE;

	HRESULT Ready_Materials(const string& strModelFilePath);
	HRESULT Ready_Bones(aiNode* pAINode, _int iParentIndex);
	HRESULT Ready_Animations();

//public:
//	virtual void Write_Json(json& Out_Json) override;
//	virtual void Load_FromJson(const json& In_Json) override;

public:
	//static CModel* Create(ID3D11Device * pDevice, ID3D11DeviceContext * pContext, TYPE eType, const string & strModelFilePath, _fmatrix PivotMatrix);
	virtual CComponent* Clone(void* pArg) PURE;
	virtual void Free() override;
};

END
