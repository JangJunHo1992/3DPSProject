#pragma once

#include "Component.h"

#include "MyAssimp.h"
#include "MyAIScene.h"

BEGIN(Engine)

class ENGINE_DLL CModel abstract : public CComponent
{
public:
	enum TYPE { TYPE_NONANIM, TYPE_ANIM, TYPE_END };

public:
	enum ANIM_STATE { ANIM_STATE_NORMAL, ANIM_STATE_LOOP, ANIM_STATE_REVERSE, ANIM_STATE_STOP, ANIM_STATE_END };

protected:
	CModel(ID3D11Device* pDevice , ID3D11DeviceContext* pContext);
	CModel(const CModel& rhs);
	virtual ~CModel() = default;

public:
	_uint Get_NumMeshes() const 
	{ 
		return m_iNumMeshes; 
	}

	vector<class CMesh*>* Get_Meshes()
	{
		return &m_Meshes;
	}

	class CBone* Get_BonePtr(const _char* pBoneName) const;

	_uint Get_NumAnimations()
	{
		return m_iNumAnimations;
	}

	_uint Get_CurrentAnimIndex() 
	{
		return m_iCurrentAnimIndex;
	};

	void Set_AnimationIndex(_uint iAnimIndex) 
	{
		if (m_iNumAnimations - 1 <= iAnimIndex || 0 > iAnimIndex)
			return;

		m_iCurrentAnimIndex = iAnimIndex;
	}

	_bool Is_AnimEnd() { return m_bIsAnimEnd; };

	//void Rotate_PivotMatrix(_float )


public:
	virtual HRESULT Initialize_Prototype(TYPE eType, const string & strModelFilePath, _fmatrix PivotMatrix);
	virtual HRESULT Initialize(void* pArg);
	virtual HRESULT Render(_uint iMeshIndex);

public:
	HRESULT Bind_BoneMatrices(class CShader* pShader, const _char* pConstantName, _uint iMeshIndex);
	HRESULT Bind_ShaderResource(class CShader* pShader, const _char* pConstantName, _uint iMeshIndex, aiTextureType eTextureType);

public:
	void	Play_Animation(_float fTimeDelta, _float3& _Pos);
	void	Play_Animation(_float fTimeDelta, _float3& _Pos, _float& fMinY);

	void	Set_Animation(_uint _iAnimationIndex, CModel::ANIM_STATE _eAnimState = CModel::ANIM_STATE::ANIM_STATE_END, _bool _bIsTransition = true, _float _fTransitionDuration = 0.2f, _uint iTargetKeyFrameIndex = 0);
	void	Set_Animation_Transition(_uint _iAnimationIndex, _float _fTransitionDuration = 0.2f, _uint iTargetKeyFrameIndex = 0);
	void	Reset_Animation(_int iAnimIndex = -1);
	
	_float	Get_TickPerSecond();
	_bool	Is_Transition();

	void	Set_UseAnimationPos(_bool _bUseAnimationPos) { m_bUseAnimationPos = _bUseAnimationPos; };

	_bool	Is_Inputable_Front(_uint _iIndexFront);
	_bool	Is_Inputable_Back(_uint _iIndexBack);


protected:
	CMyAssimp					m_MyAssimp;
	CMyAIScene					m_pAIScene;
	

protected:
	_float4x4						m_PivotMatrix;
	TYPE							m_eModelType = { TYPE_END };

	_uint							m_iNumMeshes = { 0 };
	vector<class CMesh*>			m_Meshes;

	_uint							m_iNumMaterials = { 0 };
	vector<MATERIAL_DESC>			m_Materials;

	_uint							m_iNumAnimations = { 0 };
	_uint							m_iCurrentAnimIndex = { 0 };
	vector<class CAnimation*>		m_Animations;

	_bool							m_bIsAnimEnd = { false };

	ANIM_STATE						m_eAnimState = { CModel::ANIM_STATE::ANIM_STATE_END };

	_bool							m_bUseAnimationPos = false;

	

	//_char m_szRootNode[MAX_PATH] = "root";

	/* �� ���� ��ü ������ �θ���踦 �����Ͽ� �����Ѵ�. */
	vector<class CBone*>	m_Bones;
	


public:
	typedef vector<class CBone*>	BONES;


protected:
	template<class T>
	HRESULT	Ready_Meshes_Origin(_fmatrix PivotMatrix);
	virtual HRESULT	Ready_Meshes(_fmatrix PivotMatrix) PURE;

	HRESULT Ready_Materials(const string& strModelFilePath);
	HRESULT Ready_Bones(CMyAINode pAINode, _int iParentIndex);
	HRESULT Ready_Animations();


public:
	virtual CComponent* Clone(void* pArg) PURE;
	virtual void Free() override;
};

END
