#include "Varg_Weapon_Tool.h"


CVarg_Weapon_Tool::CVarg_Weapon_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CVarg_Weapon(pDevice, pContext)
{
}

CVarg_Weapon_Tool::CVarg_Weapon_Tool(const CVarg_Weapon_Tool& rhs)
	: CVarg_Weapon(rhs)
{
}

HRESULT CVarg_Weapon_Tool::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL::LEVEL_TOOL)))
		return E_FAIL;

	return S_OK;
}

HRESULT CVarg_Weapon_Tool::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	return S_OK;
}

CVarg_Weapon_Tool* CVarg_Weapon_Tool::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CVarg_Weapon_Tool* pInstance = new CVarg_Weapon_Tool(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CVarg_Weapon_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CVarg_Weapon_Tool::Clone(void* pArg)
{
	CVarg_Weapon_Tool* pInstance = new CVarg_Weapon_Tool(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CVarg_Weapon_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CVarg_Weapon_Tool::Free()
{
	__super::Free();
}
