#include "stdafx.h"
#include "..\Public\Body_Player.h"

#include "GameInstance.h"


CBody_Player::CBody_Player(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CBody_Client(pDevice, pContext)
{

}

CBody_Player::CBody_Player(const CBody_Player& rhs)
	: CBody_Client(rhs)
{
}


HRESULT CBody_Player::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CBody_Player::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	m_pModelCom->Set_Animation(3, CModel::ANIM_STATE::ANIM_STATE_LOOP, true);

	return S_OK;
}

void CBody_Player::Priority_Tick(_float fTimeDelta)
{
	__super::Priority_Tick(fTimeDelta);
}

void CBody_Player::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
}

void CBody_Player::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);
}

HRESULT CBody_Player::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}


HRESULT CBody_Player::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL_GAMEPLAY)))
		return E_FAIL;

	return S_OK;
}

HRESULT CBody_Player::Ready_Components_Origin(LEVEL eLevel)
{
	/* For.Com_Shader */
	if (FAILED(__super::Add_Component(eLevel, TEXT("Prototype_Component_Shader_AnimModel"),
		TEXT("Com_Shader"), reinterpret_cast<CComponent**>(&m_pShaderCom))))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::Add_Component(eLevel, TEXT("Prototype_Component_Model_Fiona"),
		TEXT("Com_Model"), reinterpret_cast<CComponent**>(&m_pModelCom))))
		return E_FAIL;
}

HRESULT CBody_Player::Bind_ShaderResources()
{
	if (FAILED(__super::Bind_ShaderResources()))
		return E_FAIL;
}


CBody_Player* CBody_Player::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CBody_Player* pInstance = new CBody_Player(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CBody_Player");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CBody_Player::Clone(void* pArg)
{
	CBody_Player* pInstance = new CBody_Player(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CBody_Player");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CBody_Player::Free()
{
	__super::Free();
}

