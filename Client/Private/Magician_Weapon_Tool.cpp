#include "Magician_Weapon_Tool.h"


CMagician_Weapon_Tool::CMagician_Weapon_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CMagician_Weapon(pDevice, pContext)
{
}

CMagician_Weapon_Tool::CMagician_Weapon_Tool(const CMagician_Weapon_Tool& rhs)
	: CMagician_Weapon(rhs)
{
}

HRESULT CMagician_Weapon_Tool::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL::LEVEL_TOOL)))
		return E_FAIL;

	return S_OK;
}

HRESULT CMagician_Weapon_Tool::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	return S_OK;
}

CMagician_Weapon_Tool* CMagician_Weapon_Tool::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CMagician_Weapon_Tool* pInstance = new CMagician_Weapon_Tool(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CMagician_Weapon_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CMagician_Weapon_Tool::Clone(void* pArg)
{
	CMagician_Weapon_Tool* pInstance = new CMagician_Weapon_Tool(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CMagician_Weapon_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMagician_Weapon_Tool::Free()
{
	__super::Free();
}
