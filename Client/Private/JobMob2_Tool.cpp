#include "JobMob2_Tool.h"
#include "GameInstance.h"

CJobMob2_Tool::CJobMob2_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CJobMob2(pDevice, pContext)
{
}

CJobMob2_Tool::CJobMob2_Tool(const CJobMob2_Tool& rhs)
	: CJobMob2(rhs)
{
}

HRESULT CJobMob2_Tool::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CJobMob2_Tool::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	m_pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(m_pGameInstance);

	return S_OK;
}

void CJobMob2_Tool::Priority_Tick(_float fTimeDelta)
{
	__super::Priority_Tick(fTimeDelta);
}

void CJobMob2_Tool::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
}

void CJobMob2_Tool::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);
}

HRESULT CJobMob2_Tool::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

_bool CJobMob2_Tool::Pick(_float3* out)
{
	return m_pBody->Pick(out);
}

HRESULT CJobMob2_Tool::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL::LEVEL_TOOL)))
		return E_FAIL;

	return S_OK;
}



CJobMob2_Tool* CJobMob2_Tool::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CJobMob2_Tool* pInstance = new CJobMob2_Tool(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CJobMob2_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CJobMob2_Tool* CJobMob2_Tool::Clone(void* pArg)
{
	CJobMob2_Tool* pInstance = new CJobMob2_Tool(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CJobMob2_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CJobMob2_Tool::Free()
{
	__super::Free();
	Safe_Release(m_pGameInstance);
}
