#include "JobMob1_Tool.h"
#include "GameInstance.h"

CJobMob1_Tool::CJobMob1_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CJobMob1(pDevice, pContext)
{
}

CJobMob1_Tool::CJobMob1_Tool(const CJobMob1_Tool& rhs)
	: CJobMob1(rhs)
{
}

HRESULT CJobMob1_Tool::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CJobMob1_Tool::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	m_pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(m_pGameInstance);

	return S_OK;
}

void CJobMob1_Tool::Priority_Tick(_float fTimeDelta)
{
	__super::Priority_Tick(fTimeDelta);
}

void CJobMob1_Tool::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
}

void CJobMob1_Tool::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);
}

HRESULT CJobMob1_Tool::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

_bool CJobMob1_Tool::Pick(_float3* out)
{
	return m_pBody->Pick(out);
}

HRESULT CJobMob1_Tool::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL::LEVEL_TOOL)))
		return E_FAIL;

	return S_OK;
}



CJobMob1_Tool* CJobMob1_Tool::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CJobMob1_Tool* pInstance = new CJobMob1_Tool(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CJobMob1_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CJobMob1_Tool* CJobMob1_Tool::Clone(void* pArg)
{
	CJobMob1_Tool* pInstance = new CJobMob1_Tool(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CJobMob1_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CJobMob1_Tool::Free()
{
	__super::Free();
	Safe_Release(m_pGameInstance);
}
