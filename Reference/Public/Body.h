#pragma once

#include "GameObject.h"
#include "Model.h"

BEGIN(Engine)

class CCollider;
class CShader;
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
	CCollider* Get_Collider() {
		return m_pColliderCom;
	}
public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Tick(_float fTimeDelta) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void Late_Tick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

public:
	void Set_Animation(
		_uint _iNextAnimation
		, CModel::ANIM_STATE _eAnimState = CModel::ANIM_STATE::ANIM_STATE_NORMAL
		, _bool _bIsTransition = true
		, _bool _bUseAnimationPos = true
		, _uint iTargetKeyFrameIndex = 0
	);

	_bool	Is_Animation_End();
	_bool	Is_Inputable_Front(_uint _iIndexFront);
	_bool	Is_Inputable_Back(_uint _iIndexBack);
	_float3 Get_MovePos() {
		return m_vMovePos;
	}
protected:
	CShader* m_pShaderCom = { nullptr };
	CModel* m_pModelCom = { nullptr };
	CCollider* m_pColliderCom = { nullptr };

protected:
	class CTransform* m_pParentTransform = { nullptr };
	_float4x4			m_WorldMatrix = {};
	_float3		m_vMovePos = { 0.f, 0.f, 0.f };
protected:
	_bool		m_bNoUseRootY = { false };

protected:
	virtual HRESULT Ready_Components() PURE;
	virtual HRESULT Bind_ShaderResources();


public:
	virtual CGameObject* Clone(void* pArg) PURE;

	virtual void Free() override;
};

END