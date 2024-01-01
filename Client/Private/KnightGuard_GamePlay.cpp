#include "..\Public\KnightGuard_GamePlay.h"

#include "GameInstance.h"
#include "Spear_Shield_Attacker_Idle.h"
#include "Spear_Shield_Hit_Body_Front.h"

CKnightGuard_GamePlay::CKnightGuard_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CKnightGuard(pDevice, pContext)
{
}

CKnightGuard_GamePlay::CKnightGuard_GamePlay(const CKnightGuard_GamePlay& rhs)
	: CKnightGuard(rhs)
{
}


HRESULT CKnightGuard_GamePlay::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CKnightGuard_GamePlay::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(-25.f, 0.f, 20.f, 1.f));

	m_pActor = new CActor<CKnightGuard_GamePlay>(this);
	m_pActor->Set_State(new CSpear_Shield_Attacker_Idle());

	return S_OK;
}

void CKnightGuard_GamePlay::Priority_Tick(_float fTimeDelta)
{
	__super::Priority_Tick(fTimeDelta);
}

void CKnightGuard_GamePlay::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
	m_pActor->Update_State(fTimeDelta);
}

void CKnightGuard_GamePlay::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);
}

HRESULT CKnightGuard_GamePlay::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

void CKnightGuard_GamePlay::Set_Hitted()
{
	CKnightGuard::KnightGuard_State eHitted = CKnightGuard::KnightGuard_State::Spear_Shield_Hit_Body_Front;
	m_pActor->Set_State(new CSpear_Shield_Hit_Body_Front());
}

HRESULT CKnightGuard_GamePlay::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL_GAMEPLAY)))
		return E_FAIL;

	return S_OK;
}


CKnightGuard_GamePlay* CKnightGuard_GamePlay::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CKnightGuard_GamePlay* pInstance = new CKnightGuard_GamePlay(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CKnightGuard_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CKnightGuard_GamePlay* CKnightGuard_GamePlay::Clone(void* pArg)
{
	CKnightGuard_GamePlay* pInstance = new CKnightGuard_GamePlay(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CKnightGuard_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CKnightGuard_GamePlay::Free()
{
	__super::Free();
	Safe_Delete(m_pActor);
}
