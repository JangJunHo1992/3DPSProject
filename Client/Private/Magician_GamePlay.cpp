#include "Magician_GamePlay.h"
#include "Transform.h"
#include "Magician_Idle.h"
#include "GameInstance.h"
#include "Magician_Dead.h"
#include "Magician_Card_GamePlay.h"

CMagician_GamePlay::CMagician_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CMagician(pDevice, pContext)
{
}

CMagician_GamePlay::CMagician_GamePlay(const CMagician_GamePlay& rhs)
	: CMagician(rhs)
{
}


HRESULT CMagician_GamePlay::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CMagician_GamePlay::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	m_pActor = new CActor<CMagician_GamePlay>(this);
	m_pActor->Set_State(new CMagician_Idle());
	
	//Search_Target();

	return S_OK;
}

void CMagician_GamePlay::Priority_Tick(_float fTimeDelta)
{
	__super::Priority_Tick(fTimeDelta);
	if(nullptr == m_pTargetPlayer)
		Search_Target();
	if (m_bLookAt == true)
	{
		Look_At_Target();
		m_bLookAt = false;
	}

}

void CMagician_GamePlay::Tick(_float fTimeDelta)
{
	if (MagicianStatus.m_iHP < 0)
		Set_Dead();
	__super::Tick(fTimeDelta);

	m_pActor->Update_State(fTimeDelta);
}

void CMagician_GamePlay::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);
}

HRESULT CMagician_GamePlay::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

void CMagician_GamePlay::Set_Dead()
{
	m_bCheckDead = true;
	m_pActor->Set_State(new CMagician_Dead());
}

HRESULT CMagician_GamePlay::Ready_Components()
{

	if (FAILED(Ready_Components_Origin(LEVEL_BOSS2)))
		return E_FAIL;
	return S_OK;
}

void CMagician_GamePlay::Create_Card()
{
	m_pGameInstance->Add_CloneObject(LEVEL_BOSS2, TEXT("Layer_Monster"), TEXT("Prototype_GameObject_Magician_Card"));
}


CMagician_GamePlay* CMagician_GamePlay::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CMagician_GamePlay* pInstance = new CMagician_GamePlay(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CMagician_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CMagician_GamePlay* CMagician_GamePlay::Clone(void* pArg)
{
	CMagician_GamePlay* pInstance = new CMagician_GamePlay(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CMagician_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMagician_GamePlay::Free()
{
	__super::Free();
	Safe_Delete(m_pActor);
}
