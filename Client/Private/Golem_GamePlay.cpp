#include "..\Public\Golem_GamePlay.h"

#include "GameInstance.h"
#include "Giant_Golem_Idle.h"
#include "Giant_Golem_Hit_Light_Front.h"

CGolem_GamePlay::CGolem_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CGolem(pDevice, pContext)
{
}

CGolem_GamePlay::CGolem_GamePlay(const CGolem_GamePlay& rhs)
	: CGolem(rhs)
{
}


HRESULT CGolem_GamePlay::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CGolem_GamePlay::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(-20.f, 0.f, 20.f, 1.f));

	m_pActor = new CActor<CGolem_GamePlay>(this);
	m_pActor->Set_State(new CGiant_Golem_Idle());

	return S_OK;
}

void CGolem_GamePlay::Priority_Tick(_float fTimeDelta)
{
	__super::Priority_Tick(fTimeDelta);
}

void CGolem_GamePlay::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
	m_pActor->Update_State(fTimeDelta);
}

void CGolem_GamePlay::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);
}

HRESULT CGolem_GamePlay::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

void CGolem_GamePlay::Set_Hitted()
{
	CGolem::Golem_State eHitted = CGolem::Golem_State::Giant_Golem_Hit_Light_Front;
	m_pActor->Set_State(new CGiant_Golem_Hit_Light_Front());
}

HRESULT CGolem_GamePlay::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL_GAMEPLAY)))
		return E_FAIL;

	return S_OK;
}


CGolem_GamePlay* CGolem_GamePlay::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CGolem_GamePlay* pInstance = new CGolem_GamePlay(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CGolem_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGolem_GamePlay* CGolem_GamePlay::Clone(void* pArg)
{
	CGolem_GamePlay* pInstance = new CGolem_GamePlay(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CGolem_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CGolem_GamePlay::Free()
{
	__super::Free();
	Safe_Delete(m_pActor);
}
