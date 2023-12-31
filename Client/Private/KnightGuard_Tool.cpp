#include "..\Public\KnightGuard_Tool.h"
#include "GameInstance.h"

//#include "Spear_Shield_Hit_Body_Front.h"

CKnightGuard_Tool::CKnightGuard_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CKnightGuard(pDevice, pContext)
{
}

CKnightGuard_Tool::CKnightGuard_Tool(const CKnightGuard_Tool& rhs)
	: CKnightGuard(rhs)
{
}

HRESULT CKnightGuard_Tool::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CKnightGuard_Tool::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	m_pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(m_pGameInstance);

	return S_OK;
}

void CKnightGuard_Tool::Priority_Tick(_float fTimeDelta)
{
	__super::Priority_Tick(fTimeDelta);
}

void CKnightGuard_Tool::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
}

void CKnightGuard_Tool::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);
}

HRESULT CKnightGuard_Tool::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

void CKnightGuard_Tool::Set_Hitted()
{
	CKnightGuard::KnightGuard_State eHitted = CKnightGuard::KnightGuard_State::Spear_Shield_Hit_Body_Front;
	Set_Animation(eHitted, CModel::ANIM_STATE::ANIM_STATE_NORMAL, true);
}

_bool CKnightGuard_Tool::Pick(_float3* out)
{
	return m_pBody->Pick(out);
}

HRESULT CKnightGuard_Tool::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL::LEVEL_TOOL)))
		return E_FAIL;

	return S_OK;
}



CKnightGuard_Tool* CKnightGuard_Tool::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CKnightGuard_Tool* pInstance = new CKnightGuard_Tool(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CKnightGuard_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CKnightGuard_Tool* CKnightGuard_Tool::Clone(void* pArg)
{
	CKnightGuard_Tool* pInstance = new CKnightGuard_Tool(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CKnightGuard_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CKnightGuard_Tool::Free()
{
	__super::Free();
	Safe_Release(m_pGameInstance);
}
