#include "JobMob2_GamePlay.h"

//#include "JobMob2_Idle.h"

CJobMob2_GamePlay::CJobMob2_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CJobMob2(pDevice, pContext)
{
}

CJobMob2_GamePlay::CJobMob2_GamePlay(const CJobMob2_GamePlay& rhs)
	: CJobMob2(rhs)
{
}


HRESULT CJobMob2_GamePlay::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CJobMob2_GamePlay::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	//m_pActor = new CActor<CJobMob2_GamePlay>(this);
	//m_pActor->Set_State(new CJobMob2_Idle);

	Search_Target();


	return S_OK;
}

void CJobMob2_GamePlay::Priority_Tick(_float fTimeDelta)
{
	__super::Priority_Tick(fTimeDelta);
	if (nullptr == m_pTargetPlayer)
		Search_Target();
	if (m_bLookAt == true)
	{
		Look_At_Target();
		m_bLookAt = false;
	}
}

void CJobMob2_GamePlay::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
	//m_pActor->Update_State(fTimeDelta);
}

void CJobMob2_GamePlay::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);
}

HRESULT CJobMob2_GamePlay::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

HRESULT CJobMob2_GamePlay::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL_GAMEPLAY)))
		return E_FAIL;

	return S_OK;
}


CJobMob2_GamePlay* CJobMob2_GamePlay::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CJobMob2_GamePlay* pInstance = new CJobMob2_GamePlay(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CJobMob2_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CJobMob2_GamePlay* CJobMob2_GamePlay::Clone(void* pArg)
{
	CJobMob2_GamePlay* pInstance = new CJobMob2_GamePlay(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CJobMob2_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CJobMob2_GamePlay::Free()
{
	__super::Free();
	Safe_Delete(m_pActor);
}
