#include "Covus_Tool.h"
#include "GameInstance.h"

CCovus_Tool::CCovus_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CCovus(pDevice, pContext)
{
}

CCovus_Tool::CCovus_Tool(const CCovus_Tool& rhs)
	: CCovus(rhs)
{
}

HRESULT CCovus_Tool::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	

	return S_OK;
}

HRESULT CCovus_Tool::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	m_pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(m_pGameInstance);

	return S_OK;
}

void CCovus_Tool::Priority_Tick(_float fTimeDelta)
{
	__super::Priority_Tick(fTimeDelta);
}

void CCovus_Tool::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
}

void CCovus_Tool::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);
}

HRESULT CCovus_Tool::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

_bool CCovus_Tool::Pick(_float3* out)
{
	return m_pBody->Pick(out);
}

HRESULT CCovus_Tool::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL::LEVEL_TOOL)))
		return E_FAIL;

	return S_OK;
}



CCovus_Tool* CCovus_Tool::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CCovus_Tool* pInstance = new CCovus_Tool(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CCovus_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CCovus_Tool* CCovus_Tool::Clone(void* pArg)
{
	CCovus_Tool* pInstance = new CCovus_Tool(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CCovus_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CCovus_Tool::Free()
{
	__super::Free();
	Safe_Release(m_pGameInstance);
}
