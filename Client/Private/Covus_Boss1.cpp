#include "Covus_GamePlay.h"
#include "GameInstance.h"
#include "Player_Idle.h"

CCovus_GamePlay::CCovus_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CCovus(pDevice, pContext)
{
}

CCovus_GamePlay::CCovus_GamePlay(const CCovus_GamePlay& rhs)
	: CCovus(rhs)
{
}


HRESULT CCovus_GamePlay::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CCovus_GamePlay::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	m_pActor = new CActor<CCovus_GamePlay>(this);
	m_pActor->Set_State(new CCovus_Idle);

	return S_OK;
}

void CCovus_GamePlay::Priority_Tick(_float fTimeDelta)
{
	__super::Priority_Tick(fTimeDelta);
}

void CCovus_GamePlay::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
	m_pActor->Update_State(fTimeDelta);
}

void CCovus_GamePlay::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);
}

HRESULT CCovus_GamePlay::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

HRESULT CCovus_GamePlay::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL_GAMEPLAY)))
		return E_FAIL;

	return S_OK;
}


CCovus_GamePlay* CCovus_GamePlay::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CCovus_GamePlay* pInstance = new CCovus_GamePlay(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CCovus_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CCovus_GamePlay* CCovus_GamePlay::Clone(void* pArg)
{
	CCovus_GamePlay* pInstance = new CCovus_GamePlay(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CCovus_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CCovus_GamePlay::Free()
{
	__super::Free();
	Safe_Delete(m_pActor);
}
