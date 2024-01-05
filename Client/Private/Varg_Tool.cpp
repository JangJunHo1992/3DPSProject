#include "Varg_Tool.h"
#include "GameInstance.h"

CVarg_Tool::CVarg_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CVarg(pDevice, pContext)
{
}

CVarg_Tool::CVarg_Tool(const CVarg_Tool& rhs)
	: CVarg(rhs)
{
}

HRESULT CVarg_Tool::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CVarg_Tool::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	m_pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(m_pGameInstance);

	return S_OK;
}

void CVarg_Tool::Priority_Tick(_float fTimeDelta)
{
	__super::Priority_Tick(fTimeDelta);
}

void CVarg_Tool::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
}

void CVarg_Tool::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);
}

HRESULT CVarg_Tool::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

_bool CVarg_Tool::Pick(_float3* out)
{
	return m_pBody->Pick(out);
}

HRESULT CVarg_Tool::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL::LEVEL_TOOL)))
		return E_FAIL;

	return S_OK;
}



CVarg_Tool* CVarg_Tool::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CVarg_Tool* pInstance = new CVarg_Tool(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CVarg_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CVarg_Tool* CVarg_Tool::Clone(void* pArg)
{
	CVarg_Tool* pInstance = new CVarg_Tool(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CVarg_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CVarg_Tool::Free()
{
	__super::Free();
	Safe_Release(m_pGameInstance);
}
