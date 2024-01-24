#include "Covus_Weapon_Dagger_Tool.h"


CCovus_Weapon_Dagger_Tool::CCovus_Weapon_Dagger_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CCovus_Weapon_Dagger(pDevice, pContext)
{
}

CCovus_Weapon_Dagger_Tool::CCovus_Weapon_Dagger_Tool(const CCovus_Weapon_Dagger_Tool& rhs)
	: CCovus_Weapon_Dagger(rhs)
{
}

HRESULT CCovus_Weapon_Dagger_Tool::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL::LEVEL_TOOL)))
		return E_FAIL;

	return S_OK;
}

HRESULT CCovus_Weapon_Dagger_Tool::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	return S_OK;
}

CCovus_Weapon_Dagger_Tool* CCovus_Weapon_Dagger_Tool::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CCovus_Weapon_Dagger_Tool* pInstance = new CCovus_Weapon_Dagger_Tool(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CCovus_Weapon_Dagger_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CCovus_Weapon_Dagger_Tool::Clone(void* pArg)
{
	CCovus_Weapon_Dagger_Tool* pInstance = new CCovus_Weapon_Dagger_Tool(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CCovus_Weapon_Dagger_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CCovus_Weapon_Dagger_Tool::Free()
{
	__super::Free();
}
