#include "..\Public\Raider_Tool.h"
#include "GameInstance.h"

CRaider_Tool::CRaider_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CRaider(pDevice, pContext)
{
}

CRaider_Tool::CRaider_Tool(const CRaider_Tool& rhs)
	: CRaider(rhs)
{
}

HRESULT CRaider_Tool::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CRaider_Tool::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	m_pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(m_pGameInstance);

	return S_OK;
}

void CRaider_Tool::Priority_Tick(_float fTimeDelta)
{
	__super::Priority_Tick(fTimeDelta);
}

void CRaider_Tool::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
}

void CRaider_Tool::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);
}

HRESULT CRaider_Tool::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

_bool CRaider_Tool::Pick(_float3* out)
{
	return m_pBody->Pick(out);
}

HRESULT CRaider_Tool::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL::LEVEL_TOOL)))
		return E_FAIL;

	return S_OK;
}



CRaider_Tool* CRaider_Tool::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CRaider_Tool* pInstance = new CRaider_Tool(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CRaider_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CRaider_Tool* CRaider_Tool::Clone(void* pArg)
{
	CRaider_Tool* pInstance = new CRaider_Tool(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CRaider_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CRaider_Tool::Free()
{
	__super::Free();
	Safe_Release(m_pGameInstance);
}
