#include "..\Public\Wizard_GamePlay.h"

#include "GameInstance.h"
#include "Wizard_Idle00.h"
#include "Wizard_Hit_Body_Front.h"

CWizard_GamePlay::CWizard_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CWizard(pDevice, pContext)
{
}

CWizard_GamePlay::CWizard_GamePlay(const CWizard_GamePlay& rhs)
	: CWizard(rhs)
{
}


HRESULT CWizard_GamePlay::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CWizard_GamePlay::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(-30.f, 0.f, 20.f, 1.f));

	m_pActor = new CActor<CWizard_GamePlay>(this);
	m_pActor->Set_State(new CWizard_Idle00());

	return S_OK;
}

void CWizard_GamePlay::Priority_Tick(_float fTimeDelta)
{
	__super::Priority_Tick(fTimeDelta);
}

void CWizard_GamePlay::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
	m_pActor->Update_State(fTimeDelta);
}

void CWizard_GamePlay::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);
}

HRESULT CWizard_GamePlay::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

void CWizard_GamePlay::Set_Hitted()
{
	CWizard::Wizard_State eHitted = CWizard::Wizard_State::Wizard_Hit_Body_Front;
	m_pActor->Set_State(new CWizard_Hit_Body_Front());
}

HRESULT CWizard_GamePlay::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL_GAMEPLAY)))
		return E_FAIL;

	return S_OK;
}


CWizard_GamePlay* CWizard_GamePlay::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CWizard_GamePlay* pInstance = new CWizard_GamePlay(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CWizard_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CWizard_GamePlay* CWizard_GamePlay::Clone(void* pArg)
{
	CWizard_GamePlay* pInstance = new CWizard_GamePlay(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CWizard_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CWizard_GamePlay::Free()
{
	__super::Free();
	Safe_Delete(m_pActor);
}
