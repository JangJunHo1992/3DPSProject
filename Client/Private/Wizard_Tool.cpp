#include "..\Public\Wizard_Tool.h"
#include "GameInstance.h"

//#include "Massive_Greate_Sword_Hit_Front.h"

CWizard_Tool::CWizard_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CWizard(pDevice, pContext)
{
}

CWizard_Tool::CWizard_Tool(const CWizard_Tool& rhs)
	: CWizard(rhs)
{
}

HRESULT CWizard_Tool::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CWizard_Tool::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	m_pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(m_pGameInstance);

	return S_OK;
}

void CWizard_Tool::Priority_Tick(_float fTimeDelta)
{
	__super::Priority_Tick(fTimeDelta);
}

void CWizard_Tool::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
}

void CWizard_Tool::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);
}

HRESULT CWizard_Tool::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

void CWizard_Tool::Set_Hitted()
{
	CWizard::Wizard_State eHitted = CWizard::Wizard_State::Wizard_Hit_Body_Front;
	Set_Animation(eHitted, CModel::ANIM_STATE::ANIM_STATE_NORMAL, true);
}

_bool CWizard_Tool::Pick(_float3* out)
{
	return m_pBody->Pick(out);
}

HRESULT CWizard_Tool::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL::LEVEL_TOOL)))
		return E_FAIL;

	return S_OK;
}



CWizard_Tool* CWizard_Tool::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CWizard_Tool* pInstance = new CWizard_Tool(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CWizard_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CWizard_Tool* CWizard_Tool::Clone(void* pArg)
{
	CWizard_Tool* pInstance = new CWizard_Tool(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CWizard_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CWizard_Tool::Free()
{
	__super::Free();
	Safe_Release(m_pGameInstance);
}
