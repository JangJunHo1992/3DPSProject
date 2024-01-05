#include "Covus_Weapon_Tool.h"


CCovus_Weapon_Tool::CCovus_Weapon_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CCovus_Weapon(pDevice, pContext)
{
}

CCovus_Weapon_Tool::CCovus_Weapon_Tool(const CCovus_Weapon_Tool& rhs)
	: CCovus_Weapon(rhs)
{
}

HRESULT CCovus_Weapon_Tool::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL::LEVEL_TOOL)))
		return E_FAIL;

	return S_OK;
}

HRESULT CCovus_Weapon_Tool::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	return S_OK;
}

CCovus_Weapon_Tool* CCovus_Weapon_Tool::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CCovus_Weapon_Tool* pInstance = new CCovus_Weapon_Tool(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CCovus_Weapon_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CCovus_Weapon_Tool::Clone(void* pArg)
{
	CCovus_Weapon_Tool* pInstance = new CCovus_Weapon_Tool(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CCovus_Weapon_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CCovus_Weapon_Tool::Free()
{
	__super::Free();
}
