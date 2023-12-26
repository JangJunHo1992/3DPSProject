#pragma once

#include "GameObject.h"

BEGIN(Engine)

class CShader;
class CModel;
class CBone;


class ENGINE_DLL CBody abstract : public CGameObject
{
public:
	typedef struct
	{
		class CTransform* m_pParentTransform = { nullptr };
	}BODY_DESC;
protected:
	CBody(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CBody(const CBody& rhs);
	virtual ~CBody() = default;

public:
	class CBone* Get_BonePtr(const _char* pBoneName);

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Tick(_float fTimeDelta) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void Late_Tick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

public:
	void SetUp_Animation(_uint iAnimIndex, CModel::ANIM_STATE _eAnimState = CModel::ANIM_STATE::ANIM_STATE_END, _bool _bIsTransition = true, _float _fTransitionDuration = 0.2f);

protected:
	CShader* m_pShaderCom = { nullptr };
	CModel* m_pModelCom = { nullptr };

protected:
	class CTransform* m_pParentTransform = { nullptr };
	_float4x4			m_WorldMatrix = {};

protected:
	virtual HRESULT Ready_Components() PURE;
	HRESULT Bind_ShaderResources();


public:
	/* 원형객체를 생성한다. */
	//static CBody* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* 사본객체를 생성한다. */
	virtual CGameObject* Clone(void* pArg) PURE;

	virtual void Free() override;
};

END