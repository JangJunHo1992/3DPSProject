#include "Magician_Tool.h"
#include "GameInstance.h"

CMagician_Tool::CMagician_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CMagician(pDevice, pContext)
{
}

CMagician_Tool::CMagician_Tool(const CMagician_Tool& rhs)
	: CMagician(rhs)
{
}

HRESULT CMagician_Tool::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CMagician_Tool::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	m_pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(m_pGameInstance);

	return S_OK;
}

void CMagician_Tool::Priority_Tick(_float fTimeDelta)
{
	__super::Priority_Tick(fTimeDelta);
}

void CMagician_Tool::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
}

void CMagician_Tool::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);
}

HRESULT CMagician_Tool::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

_bool CMagician_Tool::Pick(_float3* out)
{
	return m_pBody->Pick(out);
}

HRESULT CMagician_Tool::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL::LEVEL_TOOL)))
		return E_FAIL;

	return S_OK;
}



CMagician_Tool* CMagician_Tool::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CMagician_Tool* pInstance = new CMagician_Tool(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CMagician_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CMagician_Tool* CMagician_Tool::Clone(void* pArg)
{
	CMagician_Tool* pInstance = new CMagician_Tool(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CMagician_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMagician_Tool::Free()
{
	__super::Free();
	Safe_Release(m_pGameInstance);
}
