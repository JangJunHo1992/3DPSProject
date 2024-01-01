#include "..\Public\DarkKnight_GamePlay.h"

#include "GameInstance.h"
#include "Massive_Greate_Sword_Idle01.h"
#include "Massive_Greate_Sword_Hit_Front.h"

CDarkKnight_GamePlay::CDarkKnight_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CDarkKnight(pDevice, pContext)
{
}

CDarkKnight_GamePlay::CDarkKnight_GamePlay(const CDarkKnight_GamePlay& rhs)
	: CDarkKnight(rhs)
{
}


HRESULT CDarkKnight_GamePlay::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CDarkKnight_GamePlay::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(-15.f, 0.f, 20.f, 1.f));

	//m_pTransformCom->Rotation(XMVectorSet(0.f, 1.f, 0.f, 0.f), 135.f);

	m_pActor = new CActor<CDarkKnight_GamePlay>(this);
	m_pActor->Set_State(new CMassive_Greate_Sword_Idle01());

	return S_OK;
}

void CDarkKnight_GamePlay::Priority_Tick(_float fTimeDelta)
{
	__super::Priority_Tick(fTimeDelta);
}

void CDarkKnight_GamePlay::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
	m_pActor->Update_State(fTimeDelta);
}

void CDarkKnight_GamePlay::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);
}

HRESULT CDarkKnight_GamePlay::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

void CDarkKnight_GamePlay::Set_Hitted()
{
	CDarkKnight::DarkKnight_State eHitted = CDarkKnight::DarkKnight_State::Massive_Greate_Sword_Hit_Front;
	m_pActor->Set_State(new CMassive_Greate_Sword_Hit_Front());
}

HRESULT CDarkKnight_GamePlay::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL_GAMEPLAY)))
		return E_FAIL;

	return S_OK;
}


CDarkKnight_GamePlay* CDarkKnight_GamePlay::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CDarkKnight_GamePlay* pInstance = new CDarkKnight_GamePlay(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CDarkKnight_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CDarkKnight_GamePlay* CDarkKnight_GamePlay::Clone(void* pArg)
{
	CDarkKnight_GamePlay* pInstance = new CDarkKnight_GamePlay(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CDarkKnight_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CDarkKnight_GamePlay::Free()
{
	__super::Free();
	Safe_Delete(m_pActor);
}
